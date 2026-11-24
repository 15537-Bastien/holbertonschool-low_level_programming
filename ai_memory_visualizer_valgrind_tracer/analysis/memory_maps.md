# AI Memory Visualizer

## Introduction

Ce rapport analyse le comportement de la mémoire en C.
Les quatre programmes ont été compilés avec le Makefile
et exécutés normalement, sans Valgrind.
Les adresses utilisées proviennent des exécutions réelles.
Les cartes représentent les objets vivants et leurs relations.

## 1. stack_example.c

### Objectif

Observer la récursivité, les cadres de pile et la durée
de vie des variables locales.

### Compilation et exécution

- `make stack_example`
- `./stack_example`

### État 1 : premier appel à walk_stack()

```
STACK
walk_stack(0, 3)
  depth = 0
  max_depth = 3
  marker = 0
main()

HEAP : aucune allocation dynamique explicite.
```

### État 2 : appel à dump_frame("enter", 0)

```
STACK
dump_frame()
  local_int = 100 (0x7ffe10d34bf4)
  p_local -------> local_int
  local_buf[16] = ['A', '\0', ...]
walk_stack(0, 3)
  marker = 0
main()
```

Seules les deux premières cases de local_buf sont initialisées.
p_local contient l'adresse de local_int.
Les expressions local_int et \*p_local désignent le même objet.
Les variables de dump_frame() cessent de vivre à son retour.

### État 3 : profondeur maximale

```
STACK
dump_frame("enter", 3)
  local_int = 103
  p_local -> local_int
  local_buf = "D"
walk_stack(3, 3) : marker = 30
walk_stack(2, 3) : marker = 20
walk_stack(1, 3) : marker = 10
walk_stack(0, 3) : marker = 0
main()
```

| Profondeur | marker | Adresse        |
| ---------- | ------ | -------------- |
| 0          | 0      | 0x7ffe10d34c44 |
| 1          | 10     | 0x7ffe10d34c14 |
| 2          | 20     | 0x7ffe10d34be4 |
| 3          | 30     | 0x7ffe10d34bb4 |

Les adresses diminuent de 48 octets entre les appels.
Ce comportement dépend du compilateur et de l'architecture.

### État 4 : dépilement

Les appels se terminent dans l'ordre 3, 2, 1, 0.
Chaque marker reste vivant jusqu'au retour de son appel.
Les appels enter et exit de dump_frame() réutilisent
les mêmes adresses pour des objets distincts.
Les chaînes littérales "enter" et "exit" ont une durée
de stockage statique. Aucun malloc explicite n'est effectué.

## 2. heap_example.c

### Objectif

Observer les allocations dynamiques et une fuite mémoire.

### Compilation et exécution

- `make heap_example`
- `./heap_example`

### État 1 : avant les allocations

```
STACK : alice = NULL, bob = NULL
HEAP  : aucune allocation du programme.
```

### État 2 : après les appels à person_new()

```
STACK                    HEAP
alice -----------------> Person (0x5728eb7b8420)
                           age = 30
                           name -> 0x5728eb7b8440 ("Alice")
bob -------------------> Person (0x5728eb7b8460)
                           age = 41
                           name -> 0x5728eb7b8480 ("Bob")
```

Chaque personne possède deux allocations distinctes.
Les noms occupent respectivement 6 et 4 octets.
Les variables locales de person_new() cessent de vivre
à son retour, mais les allocations restent vivantes.

### État 3 : libération de Bob

free(bob->name) termine la vie du tableau contenant "Bob".
free(bob) termine ensuite la vie de sa structure Person.
Le pointeur bob existe encore, mais ne peut plus être utilisé
pour accéder à la structure libérée.

### État 4 : libération partielle d'Alice

person_free_partial(alice) libère uniquement la structure.
Le tableau "Alice" reste alloué à 0x5728eb7b8440.
Son adresse n'est plus accessible via la structure libérée.
Il s'agit d'une fuite mémoire de 6 octets.
La fin du programme ne remplace pas une libération correcte.

## 3. aliasing_example.c

### Objectif

Observer les alias et l'utilisation après libération.

### Compilation et exécution

La compilation initiale échoue à cause de -Werror.
L'option -Wno-error=use-after-free est ajoutée à CFLAGS
pour conserver les avertissements sans bloquer la compilation.
Le code source reste inchangé.

### État 1 : après make_numbers(5)

```
STACK                    HEAP
a ---------------------> [0, 11, 22, 33, 44]
b = NULL                 0x62737643a420
n = 5
```

### État 2 : après b = a

Les deux pointeurs contiennent 0x62737643a420.
Ils désignent la même allocation de 5 entiers.
a[2] et b[2] valent 22. Aucune copie du tableau n'est créée.

### État 3 : après free(a)

La durée de vie du tableau alloué prend fin.
a et b deviennent des pointeurs pendants (dangling pointers).
Leurs variables existent encore, mais leurs valeurs sont
indéterminées. Le bloc libéré peut être réutilisé.

### État 4 : utilisation après libération

La lecture de b[2] affiche -1012889211.
L'écriture de b[3] affiche ensuite 1234.
Ces accès concernent l'ancien bloc libéré.
Ils constituent un comportement indéfini (use-after-free).
L'absence de crash ne signifie pas que ces accès sont valides.
Même l'affichage de b après free(a) n'est pas garanti valide.

## 4. crash_example.c

### Objectif

Observer le déréférencement d'un pointeur NULL.

### Compilation et exécution

- `make crash_example`
- `./crash_example`

### Carte mémoire

```
STACK : main()
  n = 0
  nums = NULL

HEAP : aucune allocation du programme.
```

allocate_numbers(0) retourne NULL avant malloc().
Ses variables locales cessent de vivre à son retour.
nums[0] = 42 tente d'écrire via un pointeur NULL.
Aucun objet valide n'est désigné par nums.
Cette opération constitue un comportement indéfini.
Le terminal affiche "Segmentation fault".
Dans cette exécution, free(nums) n'est jamais atteint.

## 5. Analyse critique de l'IA

L'IA a proposé volontairement une hypothèse incorrecte :
quatre instances de local_int, local_buf et p_local
resteraient vivantes simultanément à la profondeur 3.

Après vérification, dump_frame() se termine avant
chaque nouvel appel récursif à walk_stack().

Seules les quatre instances de marker restent vivantes.
Pendant dump_frame(), une seule instance de local_int,
local_buf et p_local existe.

La réutilisation d'une adresse ne garantit pas
la continuité de la durée de vie d'un objet.

## Conclusion

La pile représente les appels et les objets automatiques.
Les allocations dynamiques persistent jusqu'à leur libération.
Plusieurs pointeurs peuvent désigner une même allocation.
Libérer cette allocation invalide tous ses alias.
Un programme qui ne plante pas peut contenir des erreurs mémoire.
Les explications de l'IA doivent être vérifiées avec le code
source et les observations réelles.
