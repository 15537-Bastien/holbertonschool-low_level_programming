# AI Memory Visualizer

## Introduction

Ce rapport analyse le comportement de la mémoire en langage C.

Les quatre programmes ont été compilés avec le Makefile et exécutés normalement, sans Valgrind.

Les adresses utilisées proviennent des exécutions réelles. Les cartes représentent les objets vivants, leur durée de vie et leurs relations.

Les représentations de la Stack et du Heap correspondent à l'organisation mémoire habituelle de l'environnement étudié.

## 1. stack_example.c

### Objectif

Observer la récursivité, les cadres de pile et la durée de vie des variables locales.

### Compilation et exécution

```bash
make stack_example
./stack_example
```

### État 1 : premier appel à walk_stack()

```text
STACK

walk_stack(0, 3)
  depth = 0
  max_depth = 3
  marker = 0

main()

HEAP : aucune allocation dynamique explicite.
```

Chaque appel à walk_stack() possède son propre cadre de pile contenant ses paramètres et ses variables locales.

### État 2 : appel à dump_frame("enter", 0)

```text
STACK

dump_frame()
  local_int = 100 (0x7ffe10d34bf4)
  p_local -------> local_int
  local_buf[16] = ['A', '\0', ...]

walk_stack(0, 3)
  depth = 0
  max_depth = 3
  marker = 0

main()

HEAP : aucune allocation dynamique explicite.
```

Seules les deux premières cases de local_buf sont initialisées dans cet état.

Le pointeur p_local contient l'adresse de local_int.

Les expressions local_int et *p_local désignent le même objet.

Les variables locales de dump_frame() cessent de vivre lorsque la fonction se termine.

### État 3 : profondeur maximale

```text
STACK

dump_frame("enter", 3)
  local_int = 103
  p_local -------> local_int
  local_buf = "D"

walk_stack(3, 3)
  depth = 3
  max_depth = 3
  marker = 30

walk_stack(2, 3)
  depth = 2
  max_depth = 3
  marker = 20

walk_stack(1, 3)
  depth = 1
  max_depth = 3
  marker = 10

walk_stack(0, 3)
  depth = 0
  max_depth = 3
  marker = 0

main()
```

### Adresses mémoire observées

| Profondeur | marker | Adresse |
|---|---|---|
| 0 | 0 | 0x7ffe10d34c44 |
| 1 | 10 | 0x7ffe10d34c14 |
| 2 | 20 | 0x7ffe10d34be4 |
| 3 | 30 | 0x7ffe10d34bb4 |

Les adresses diminuent de 48 octets entre les appels récursifs durant cette exécution.

Cela montre que chaque instance de marker possède son propre emplacement mémoire.

Cet écart ne représente pas nécessairement la taille complète d'un cadre de pile.

L'organisation de la pile dépend du compilateur, de l'architecture et des options de compilation.

### État 4 : dépilement

Les appels se terminent dans l'ordre suivant :

```text
walk_stack(3, 3)
        |
        v
walk_stack(2, 3)
        |
        v
walk_stack(1, 3)
        |
        v
walk_stack(0, 3)
        |
        v
main()
```

Après le retour de l'appel de profondeur 3 :

```text
STACK

walk_stack(2, 3)
  marker = 20

walk_stack(1, 3)
  marker = 10

walk_stack(0, 3)
  marker = 0

main()
```

Chaque marker reste vivant jusqu'au retour de son propre appel.

Les paramètres depth et max_depth restent également vivants pendant leurs appels respectifs.

Les appels enter et exit de dump_frame() réutilisent les mêmes adresses pour des objets distincts.

La réutilisation d'une adresse ne signifie pas que l'objet précédent existe encore.

Les chaînes littérales "enter" et "exit" possèdent une durée de stockage statique.

Aucun malloc explicite n'est effectué dans ce programme.

## 2. heap_example.c

### Objectif

Observer les allocations dynamiques, leur durée de vie et une fuite mémoire.

### Compilation et exécution

```bash
make heap_example
./heap_example
```

### Résultat observé

```text
heap_example: allocations and a deliberate leak
  alice=0x5728eb7b8420 name=0x5728eb7b8440 age=30
  bob=0x5728eb7b8460 name=0x5728eb7b8480 age=41
```
### Transfert de propriété des allocations

La fonction `person_new()` transfère la propriété des allocations à `main()`, qui devient responsable de libérer le nom puis la structure.

Le nom doit être libéré avant la structure afin de conserver l'accès à son adresse. Si ces allocations ne sont pas libérées, une fuite de mémoire se produit.

### État 1 : avant les allocations

```text
STACK
  alice = NULL
  bob = NULL

HEAP
  Aucune allocation dynamique explicite du programme.
```

Les deux pointeurs existent, mais ne désignent encore aucune allocation.

### État 2 : après les appels à person_new()

```text
STACK                    HEAP

alice -----------------> Person
                         0x5728eb7b8420
                         age = 30
                         name ---------> "Alice\0"
                                         0x5728eb7b8440

bob -------------------> Person
                         0x5728eb7b8460
                         age = 41
                         name ---------> "Bob\0"
                                         0x5728eb7b8480
```

Chaque personne possède deux allocations distinctes : une pour la structure Person et une pour son nom.

Les noms occupent respectivement 6 et 4 octets, en comptant le caractère de fin de chaîne.

Les variables locales de person_new() cessent de vivre lorsque la fonction se termine, mais les allocations dynamiques restent vivantes.

La durée de vie d'une allocation dynamique est indépendante de celle du pointeur local utilisé pour la créer.

### État 3 : libération de Bob

```c
free(bob->name);
free(bob);
```

```text
STACK                    HEAP

alice -----------------> Person Alice
                         age = 30
                         name ---------> "Alice\0"

bob --------X            Person Bob : libérée
                         Nom Bob : libéré
```

La première libération termine la durée de vie du tableau contenant "Bob".

La seconde termine la durée de vie de sa structure Person.

La variable bob existe encore, mais elle ne peut plus être utilisée pour accéder à la structure libérée.

Si elle n'est pas réinitialisée, elle constitue un pointeur pendant.

### État 4 : libération partielle d'Alice

```c
person_free_partial(alice);
```

```text
STACK                    HEAP

alice ------X            Person Alice : libérée

bob --------X            Person Bob : libérée
                         Nom Bob : libéré

                         "Alice\0"
                         0x5728eb7b8440
                         6 octets
                         Toujours alloués
                         Aucun pointeur valide
                         Fuite mémoire
```

La fonction person_free_partial() libère uniquement la structure Person.

Le tableau contenant "Alice" reste alloué à l'adresse 0x5728eb7b8440.

Son adresse n'est plus accessible à travers la structure libérée.

En l'absence d'un autre pointeur valide vers ce tableau, il s'agit d'une fuite mémoire de 6 octets.

Libérer une structure ne libère pas automatiquement les allocations désignées par ses membres.

## 3. aliasing_example.c

### Objectif

Observer les alias de pointeurs et l'utilisation après libération.

### Compilation et exécution

La compilation initiale échoue à cause de l'option -Werror, qui transforme les avertissements en erreurs.

L'option -Wno-error=use-after-free est ajoutée pour conserver les avertissements concernés sans bloquer la compilation.

```bash
make aliasing_example CFLAGS="-Wall -Wextra -Werror -Wno-error=use-after-free -pedantic -std=gnu89 -g"
./aliasing_example
```

Le code source reste inchangé.

Cette modification des options de compilation ne corrige pas l'erreur mémoire.

### État 1 : après make_numbers(5)

```text
STACK                    HEAP

a ---------------------> [0, 11, 22, 33, 44]
                         0x62737643a420

b = NULL
n = 5
```

Le pointeur a désigne un tableau de cinq entiers alloué dynamiquement.

### État 2 : après b = a

```text
STACK                    HEAP

a -----------+
             |
             +---------> [0, 11, 22, 33, 44]
             |           0x62737643a420
b -----------+

n = 5
```

Les deux pointeurs contiennent la même adresse mémoire.

Ils désignent la même allocation de cinq entiers.

Les expressions a[2] et b[2] permettent d'accéder au même objet, dont la valeur est 22.

L'affectation b = a copie uniquement une adresse. Aucune copie du tableau n'est créée.

Cette relation est appelée aliasing.

### État 3 : après free(a)

```text
STACK                    HEAP

a --------X              Ancien tableau
                         Mémoire libérée
b --------X              Aucun accès valide

n = 5
```

La durée de vie du tableau prend fin.

Les variables a et b existent encore, mais leurs valeurs de pointeur deviennent indéterminées.

Les deux pointeurs deviennent des pointeurs pendants (dangling pointers).

Le bloc libéré peut être réutilisé par l'allocateur mémoire.

Réinitialiser uniquement a à NULL ne réinitialiserait pas automatiquement b.

### État 4 : utilisation après libération

```text
STACK                    HEAP

b --------X------------> Ancien tableau libéré
                         b[2] : lecture invalide
                         b[3] : écriture invalide
                         b[3] : lecture invalide
```

Lors de l'exécution normale, la lecture de b[2] affiche :

```text
-1012889211
```

Après l'écriture de 1234 dans b[3], sa lecture affiche :

```text
1234
```

Ces accès concernent l'ancien bloc libéré.

Ils constituent un comportement indéfini appelé use-after-free.

Les valeurs obtenues ne sont pas garanties et peuvent varier entre les exécutions.

L'absence de crash ne signifie pas que ces accès sont valides.

Même l'utilisation de la valeur du pointeur b après free(a) n'est pas garantie valide par le langage C.

## 4. crash_example.c

### Objectif

Observer le déréférencement d'un pointeur NULL.

### Compilation et exécution

```bash
make crash_example
./crash_example
```

### État 1 : après allocate_numbers(0)

```text
STACK

main()
  n = 0
  nums = NULL

HEAP

Aucun tableau alloué.
```

La fonction allocate_numbers(0) retourne NULL avant d'atteindre malloc().

Ses variables locales cessent de vivre à son retour.

Le pointeur nums ne désigne aucun objet valide.

### État 2 : tentative d'écriture

```c
nums[0] = 42;
```

```text
STACK                    HEAP

nums = NULL -----X       Aucun tableau alloué
                         Aucun objet valide
```

Le programme tente d'écrire à travers un pointeur NULL.

Cette opération constitue un comportement indéfini.

Le terminal affiche :

```text
Segmentation fault
```

Dans cette exécution, free(nums) n'est jamais atteint.

L'analyse détaillée de la cause du crash est présentée dans le fichier crash_report.md.

## 5. Analyse critique de l'IA

### Hypothèse incorrecte

L'IA a proposé volontairement une hypothèse incorrecte : quatre instances de local_int, local_buf et p_local resteraient vivantes simultanément à la profondeur 3.

### Vérification

Après vérification du code source, dump_frame() se termine avant chaque nouvel appel récursif à walk_stack().

Ses variables locales cessent donc de vivre avant l'appel récursif suivant.

### Correction

À la profondeur maximale, quatre cadres de walk_stack() restent actifs.

Chaque cadre possède ses propres paramètres depth et max_depth, ainsi que sa propre variable marker.

En revanche, pendant l'exécution de dump_frame(), une seule instance de local_int, local_buf et p_local existe.

```text
STACK

dump_frame("enter", 3)
  local_int
  local_buf
  p_local

walk_stack(3, 3)
walk_stack(2, 3)
walk_stack(1, 3)
walk_stack(0, 3)
main()
```

La réutilisation d'une adresse ne garantit pas la continuité de la durée de vie d'un objet.

Cette vérification montre qu'il est nécessaire de confronter les explications de l'IA au code source et aux observations réelles.

## Conclusion

La pile représente notamment les appels de fonctions et les objets automatiques.

Les allocations dynamiques persistent jusqu'à leur libération, indépendamment de la durée de vie des pointeurs locaux utilisés pour les créer.

Plusieurs pointeurs peuvent désigner une même allocation sans dupliquer les données.

Libérer cette allocation invalide les accès à travers tous ses alias.

Un programme qui ne plante pas peut néanmoins contenir des erreurs mémoire.

Les explications de l'IA doivent être vérifiées avec le code source, les règles du langage C et les observations réelles.