Peer Review Readiness Check

1. Compréhension du modèle mémoire

La stack contient notamment les variables locales et les informations liées aux appels de fonctions. Les variables locales automatiques deviennent invalides lorsque leur durée de vie se termine.

Le heap permet d'allouer dynamiquement de la mémoire avec malloc(). Contrairement à la stack, cette mémoire reste allouée après la fin d'une fonction tant qu'elle n'est pas libérée avec free().

Le développeur doit identifier le propriétaire de chaque allocation et déterminer qui est responsable de sa libération.

2. Pointeurs et aliasing

Deux pointeurs peuvent contenir la même adresse et accéder au même bloc mémoire.

Lorsqu'un bloc est libéré, les pointeurs qui le désignaient deviennent invalides. Accéder à cette mémoire provoque un use-after-free.

Attribuer NULL à un pointeur ne modifie pas automatiquement les autres pointeurs qui partageaient son adresse.

Libérer deux fois le même bloc constitue un double free.

3. Interprétation de Valgrind

Valgrind permet de détecter et de localiser différentes erreurs mémoire.

Dans heap_example.c, une fuite mémoire de 6 octets a été identifiée. La structure Alice est libérée, mais pas le bloc mémoire alloué pour son nom.

Il faut libérer les allocations internes avant de libérer la structure.

Dans aliasing_example.c, les accès effectués après la libération du bloc provoquent des lectures et des écritures invalides.

L'analyse du code source permet de comprendre l'origine de ces erreurs, et pas uniquement de constater leur présence dans Valgrind.

4. Analyse de la cause du crash

Dans crash_example.c, la fonction retourne NULL lorsque le nombre d'éléments demandé est égal à zéro.

Le programme tente ensuite d'écrire la valeur 42 à travers ce pointeur NULL.

Valgrind indique une écriture invalide de 4 octets à l'adresse 0x0.

Le crash observé est donc la conséquence directe d'un accès mémoire invalide.

Une vérification du pointeur avant son déréférencement permettrait d'éviter cette erreur.

5. Utilisation critique de l'intelligence artificielle

J'ai utilisé l'intelligence artificielle pour m'accompagner dans l'analyse du code, la compréhension des erreurs mémoire et l'interprétation des résultats de Valgrind.

Certaines hypothèses proposées lors des exercices étaient incorrectes, notamment :

Un échec de malloc.

Un débordement de la stack.

Un use-after-free comme origine du crash.

L'analyse du code source et des résultats de Valgrind a permis d'écarter ces hypothèses et d'identifier le déréférencement d'un pointeur NULL.

Il est essentiel de vérifier les réponses de l'intelligence artificielle, car elle peut se tromper. Ses réponses doivent être considérées comme des informations ou des hypothèses, et non comme des vérités absolues.

Conclusion

Ce projet m'a permis de mieux comprendre le fonctionnement de la mémoire en C, la durée de vie des allocations, les relations entre les pointeurs et les responsabilités du développeur.

J'ai également appris à utiliser Valgrind pour analyser les erreurs mémoire et à vérifier les hypothèses proposées par l'intelligence artificielle.

Une simulation d'évaluation de 15 questions m'a permis de vérifier mes connaissances, d'identifier mes difficultés et de corriger mes erreurs avant la soumission du projet.

