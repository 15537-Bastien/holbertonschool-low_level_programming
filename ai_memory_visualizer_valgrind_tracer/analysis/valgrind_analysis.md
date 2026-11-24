# Analyse de la mémoire avec Valgrind

## Introduction

Ce rapport analyse les résultats obtenus avec Valgrind Memcheck sur les quatre programmes étudiés.

L'objectif est d'identifier les erreurs mémoire, de comprendre leurs causes et de vérifier leur cohérence avec les cartes mémoire réalisées précédemment.

Les adresses observées sous Valgrind peuvent différer de celles obtenues lors des exécutions normales.

Les résultats présentés correspondent aux exécutions réalisées dans l'environnement étudié.

## 1. Analyse de stack_example

### Résultats de Valgrind

- Erreurs mémoire : 0
- Fuites mémoire : 0 octet
- Nombre total d'allocations : 1
- Nombre total de libérations : 1
- Quantité totale de mémoire allouée : 1 024 octets

### Analyse de la mémoire

Chaque appel récursif de la fonction crée son propre cadre de pile (stack frame), contenant ses paramètres et ses variables locales.

Chaque variable locale reste valide pendant sa durée de vie.

Lorsqu'une fonction se termine, la durée de vie de ses variables locales prend fin et l'espace correspondant sur la pile peut être réutilisé.

Valgrind n'a détecté aucun accès mémoire invalide, aucune utilisation de mémoire non initialisée et aucune fuite mémoire durant cette exécution.

Tous les blocs de mémoire alloués sur le tas (heap) ont été libérés avant la fin du programme.

L'allocation de 1 024 octets ne contredit pas l'absence de malloc explicite dans le code source. La bibliothèque standard peut effectuer ses propres allocations internes, notamment pour les opérations d'affichage.

### Vérification avec la cartographie mémoire

Les résultats sont cohérents avec la durée de vie des variables locales représentée dans memory_maps.md.

Chaque appel possède ses propres variables, et aucun accès invalide à un objet dont la durée de vie est terminée n'a été détecté.

### Conclusion

Aucune mauvaise utilisation de la mémoire n'a été détectée durant cette exécution.

Cela ne constitue toutefois pas une preuve générale de l'absence de toute erreur mémoire dans toutes les conditions d'exécution possibles.

## 2. Analyse de heap_example

### Résultats de Valgrind

- Erreurs signalées : 1
- Fuites mémoire : 6 octets dans 1 bloc
- Nombre total d'allocations : 5
- Nombre total de libérations : 4
- Quantité totale de mémoire allouée : 1 066 octets
- Classification de la fuite : definitely lost (mémoire définitivement perdue)

### Analyse de la mémoire

La fonction person_new() effectue deux allocations distinctes :

- Une allocation pour la structure Person à la ligne 14.
- Une allocation pour le prénom à la ligne 21.

Le bloc mémoire perdu contient la chaîne de caractères "Alice", ainsi que son caractère de fin de chaîne '\0', soit un total de 6 octets.

À la ligne 69, la fonction person_free_partial(alice) est appelée.

Cette fonction libère la structure Person à la ligne 41, sans libérer la mémoire allouée pour son prénom.

Par conséquent, le programme perd l'accès au bloc mémoire contenant le prénom.

### Analyse de la durée de vie

La durée de vie de la structure Person prend fin lors de sa libération.

Cependant, la durée de vie de l'allocation contenant le prénom ne prend pas fin, car aucun free correspondant n'est effectué.

Ces deux allocations possèdent des durées de vie indépendantes.

### Vérification avec la cartographie mémoire

La cartographie mémoire montre que la structure Alice est libérée alors que le tableau contenant son prénom reste alloué.

Valgrind confirme cette observation en identifiant un bloc définitivement perdu de 6 octets.

### Vérification des explications de l'intelligence artificielle

Une explication volontairement incorrecte de l'IA suggérait que la fuite mémoire était causée par l'absence de libération de la structure Person.

Après vérification du code source, cette explication s'est révélée incorrecte.

La structure est correctement libérée à la ligne 41.

Cependant, la mémoire allouée pour le prénom à la ligne 21 n'est jamais libérée.

Cela démontre l'importance de vérifier les explications de l'intelligence artificielle en les comparant au code source et aux cartographies mémoire.

### Conclusion

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

Chaque entier occupe 4 octets dans l'environnement étudié, ce qui représente une allocation de 20 octets.

Les pointeurs a et b désignent le même bloc mémoire à la suite de l'affectation b = a.

Cette affectation ne crée pas de nouvelle allocation.

### Analyse de la durée de vie

À la ligne 38, free(a) libère le tableau.

Les pointeurs a et b deviennent alors des pointeurs pendants (dangling pointers).

Les accès effectués aux lignes 42, 44 et 45 interviennent après la fin de la durée de vie du tableau.

Ces trois erreurs sont donc des use-after-free.

### Vérification avec le code source et la cartographie mémoire

L'adresse initiale du tableau lors de l'exécution sous Valgrind est 0x4a91480.

- b[2] : décalage de 8 octets, adresse 0x4a91488.
- b[3] : décalage de 12 octets, adresse 0x4a9148c.

Ces décalages correspondent aux résultats de Valgrind et confirment la représentation du tableau dans la cartographie mémoire.

### Comparaison avec l'exécution normale

| Observation                      | Exécution normale | Exécution sous Valgrind |
| -------------------------------- | ----------------- | ----------------------- |
| Adresse initiale du tableau      | 0x62737643a420    | 0x4a91480               |
| Lecture de b[2] après libération | -1012889211       | 22                      |
| Lecture de b[3] après écriture   | 1234              | 1234                    |

Les adresses et les valeurs peuvent différer, car il s'agit d'exécutions distinctes dans des conditions différentes.

Les valeurs obtenues après la libération ne sont pas garanties par le langage C.

Le fait que Valgrind permette d'observer la valeur 22 ne signifie pas que la lecture est valide.

### Conclusion

Le programme ne présente aucune fuite mémoire, mais contient trois accès invalides à un bloc déjà libéré.

Bien que le programme affiche les valeurs 22 et 1234 sous Valgrind, ces accès constituent un comportement indéfini.

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

L'instruction responsable est :

```c
nums[0] = 42;
```

Cette erreur correspond au déréférencement d'un pointeur NULL.

### Objet mémoire concerné

Le pointeur nums est censé désigner un tableau d'entiers dans le heap.

Cependant, la variable n est initialisée à 0.

La fonction allocate_numbers retourne donc NULL avant d'exécuter malloc.

Aucun tableau n'est alloué.

### Analyse de la durée de vie

Le tableau n'a jamais été créé.

Le programme tente donc d'accéder à un objet mémoire inexistant.

Lors de cette exécution, l'écriture à l'adresse 0x0 provoque une erreur de segmentation et entraîne l'arrêt brutal du programme.

Les instructions suivantes, notamment free(nums), ne sont pas exécutées.

### Analyse de la mémoire restante

Valgrind indique 1 024 octets classés comme still reachable.

La trace d'allocation montre que cette mémoire provient du buffer d'affichage de la bibliothèque standard.

L'arrêt brutal du programme empêche son nettoyage habituel.

Cette mémoire reste néanmoins accessible et n'est pas considérée comme définitivement perdue.

Il est donc important de distinguer les catégories definitely lost et still reachable.

### Vérification avec le code source et la cartographie mémoire

Les résultats de Valgrind confirment la cartographie mémoire :

- La variable n contient 0.
- Le pointeur nums contient NULL.
- Aucun tableau n'est alloué dans le heap.
- L'écriture de 4 octets à l'adresse 0x0 est invalide.

### Vérification critique d'une explication de l'IA

Exemple volontairement incorrect d'une explication de l'IA :

« Le programme provoque un segmentation fault parce que malloc n'a pas réussi à allouer les 1 024 octets nécessaires au tableau nums. »

Cette explication est incorrecte.

La fonction allocate_numbers retourne NULL avant l'appel à malloc.

Les 1 024 octets correspondent au buffer d'affichage, comme le confirme la trace d'allocation de Valgrind.

### Conclusion

Le programme contient une erreur de déréférencement d'un pointeur NULL.

Aucune fuite mémoire définitive n'a été détectée.

L'analyse approfondie de la cause du crash et des corrections possibles est présentée dans crash_report.md.

## 5. Synthèse des résultats

| Programme        | Erreurs | Definitely lost | Still reachable |
| ---------------- | ------- | --------------- | --------------- |
| stack_example    | 0       | 0 octet         | 0 octet         |
| heap_example     | 1       | 6 octets        | 0 octet         |
| aliasing_example | 3       | 0 octet         | 0 octet         |
| crash_example    | 1       | 0 octet         | 1 024 octets    |

## Conclusion générale

Valgrind permet de détecter différentes formes de mauvaise utilisation de la mémoire, même lorsqu'un programme semble fonctionner normalement.

Les résultats obtenus confirment les relations entre les objets et les pointeurs représentées dans les cartes mémoire.

Une absence de fuite mémoire ne signifie pas nécessairement une absence d'accès invalides.

Il est également important de distinguer une allocation définitivement perdue d'une allocation encore accessible à la fin du programme.

L'utilisation de Valgrind doit être accompagnée d'une analyse du code source et de la durée de vie des objets.

Les explications proposées par l'intelligence artificielle doivent être vérifiées à partir de ces éléments avant d'être considérées comme correctes.
