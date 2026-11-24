Analyse de la mémoire avec Valgrind

1. stack_example
   Résultats de Valgrind

- Erreurs mémoire : 0
- Fuites mémoire : 0 octet
- Nombre total d'allocations : 1
- Nombre total de libérations : 1
- Quantité totale de mémoire allouée : 1 024 octets
  Analyse de la mémoire
  Chaque appel récursif de la fonction crée son propre cadre de pile (stack frame) contenant ses variables locales.

Chaque variable locale reste valide pendant sa durée de vie. Lorsqu'une fonction se termine, la durée de vie de ses variables locales prend fin et l'espace correspondant sur la pile peut être réutilisé.

Valgrind n'a détecté aucun accès mémoire invalide, aucune utilisation de mémoire non initialisée et aucune fuite mémoire durant cette exécution.

Tous les blocs de mémoire alloués sur le tas (heap) ont été libérés avant la fin du programme.
Conclusion
Aucune mauvaise utilisation de la mémoire n'a été détectée durant cette exécution.

2. heap_example
   Résultats de Valgrind

- Erreurs mémoire : 1
- Fuites mémoire : 6 octets dans 1 bloc
- Nombre total d'allocations : 5
- Nombre total de libérations : 4
- Quantité totale de mémoire allouée : 1 066 octets
- Classification de la fuite : definitely lost (mémoire définitivement perdue)
  Analyse de la mémoire
  La fonction person_new() effectue deux allocations de mémoire distinctes : une pour la structure Person à la ligne 14 et une autre pour le prénom à la ligne 21.

Le bloc mémoire perdu contient la chaîne de caractères « Alice », ainsi que son caractère de fin de chaîne \0, soit un total de 6 octets.

À la ligne 69, la fonction person_free_partial(alice) est appelée. Cette fonction libère la structure Person à la ligne 41, sans libérer la mémoire allouée pour son prénom.

Par conséquent, le programme perd l'accès au bloc mémoire contenant le prénom.
Vérification des explications de l'intelligence artificielle
Une explication volontairement incorrecte de l'IA suggérait que la fuite mémoire était causée par l'absence de libération de la structure Person.

Après vérification du code source, cette explication s'est révélée incorrecte.

La structure est correctement libérée à la ligne 41. Cependant, la mémoire allouée pour le prénom à la ligne 21 n'est jamais libérée.

Cela démontre l'importance de vérifier les explications de l'intelligence artificielle en les comparant au code source et aux cartographies mémoire.
Conclusion
L'erreur détectée est une fuite mémoire due à une perte de propriété (leak due to lost ownership).

Le programme perd l'accès à un bloc de 6 octets alloué dynamiquement après avoir libéré la structure qui contenait son adresse.

## 3. Analyse de aliasing_example

### Résultats de Valgrind

- Nombre d'allocations : 2
- Nombre de libérations : 2
- Mémoire totale allouée : 1 044 octets
- Mémoire restante : 0 octet
- Fuites mémoire : aucune
- Nombre d'erreurs : 3

### Classification des erreurs

| Ligne | Erreur        | Taille   | Cause                               |
| ----- | ------------- | -------- | ----------------------------------- |
| 42    | Invalid read  | 4 octets | Lecture de b[2] après libération    |
| 44    | Invalid write | 4 octets | Écriture dans b[3] après libération |
| 45    | Invalid read  | 4 octets | Lecture de b[3] après libération    |

### Objet mémoire concerné

Le bloc mémoire concerné est un tableau de cinq entiers, alloué dynamiquement dans le heap par la fonction make_numbers à la ligne 12.

Chaque entier occupe 4 octets, ce qui représente une allocation de 20 octets.

Les pointeurs a et b désignent le même bloc mémoire à la suite de l'affectation b = a.

### Analyse de la durée de vie

À la ligne 38, free(a) libère le tableau. Les pointeurs a et b deviennent alors des pointeurs pendants (dangling pointers).

Les accès effectués aux lignes 42, 44 et 45 interviennent après la fin de la durée de vie du tableau.

Ces trois erreurs sont donc des use-after-free.

### Vérification avec le code source et la cartographie mémoire

L'adresse initiale du tableau est 0x4a91480.

- b[2] : décalage de 8 octets, adresse 0x4a91488.
- b[3] : décalage de 12 octets, adresse 0x4a9148c.

Ces décalages correspondent aux résultats de Valgrind et confirment la représentation du tableau dans la cartographie mémoire.

### Conclusion

Le programme ne présente aucune fuite mémoire, mais contient trois accès invalides à un bloc déjà libéré.

Bien que le programme affiche les valeurs 22 et 1234, ces accès constituent un comportement indéfini.

L'absence de fuite mémoire ne garantit donc pas la sécurité mémoire d'un programme.

## 4. Analyse de crash_example

### Résultats de Valgrind

- Nombre d'allocations : 1
- Nombre de libérations : 0
- Mémoire totale allouée : 1 024 octets
- Mémoire restante : 1 024 octets
- Mémoire définitivement perdue : 0 octet
- Nombre d'erreurs : 1
- Signal reçu : SIGSEGV (signal 11)

### Classification de l'erreur

Valgrind détecte une erreur de type Invalid write of size 4 à la ligne 32 du fichier crash_example.c.

L'instruction responsable est `nums[0] = 42;`.

Cette erreur correspond au déréférencement d'un pointeur NULL.

### Objet mémoire concerné

Le pointeur nums est censé désigner un tableau d'entiers dans le heap.

Cependant, la variable n est initialisée à 0. La fonction allocate_numbers retourne donc NULL avant d'exécuter malloc.

Aucun tableau n'est alloué.

### Analyse de la durée de vie

Le tableau n'a jamais été créé. Le programme tente donc d'accéder à un objet mémoire inexistant.

L'écriture à l'adresse 0x0 provoque un segmentation fault et entraîne l'arrêt brutal du programme.

Les instructions suivantes, notamment free(nums), ne sont pas exécutées.

### Analyse de la mémoire restante

Valgrind indique 1 024 octets classés comme Still reachable.

La trace d'allocation montre que cette mémoire provient du buffer d'affichage de la bibliothèque standard.

L'arrêt brutal du programme empêche son nettoyage habituel. Cette mémoire reste néanmoins accessible et n'est pas considérée comme définitivement perdue.

### Vérification avec le code source et la cartographie mémoire

Les résultats de Valgrind confirment la cartographie mémoire :

- La variable n contient 0.
- Le pointeur nums contient NULL.
- Aucun tableau n'est alloué dans le heap.
- L'écriture de 4 octets à l'adresse 0x0 est invalide.

### Vérification critique d'une explication de l'IA

Exemple volontairement incorrect d'une explication de l'IA :

« Le programme provoque un segmentation fault parce que malloc n'a pas réussi à allouer les 1 024 octets nécessaires au tableau nums. »

Cette explication est incorrecte. La fonction allocate_numbers retourne NULL avant l'appel à malloc.

Les 1 024 octets correspondent au buffer d'affichage, comme le confirme la trace d'allocation de Valgrind.

### Conclusion

Le programme contient une erreur de déréférencement d'un pointeur NULL.

Cette erreur aurait pu être évitée en vérifiant la valeur de nums avant son utilisation.

Aucune fuite mémoire définitive n'a été détectée.
