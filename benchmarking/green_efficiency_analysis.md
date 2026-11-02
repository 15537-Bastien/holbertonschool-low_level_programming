# Green Efficiency Analysis

## Measurement Methodology

Pour cet exercice, j'ai travaillé sur plusieurs programmes en langage C pour voir les différences de temps d'exécution et comprendre ce qui pouvait jouer sur leurs performances.

j'ai utilis� �clock() avec CLOCKS_PER_SE afin d'obtenir les résultats en secondes. J'ai aussi lancé les programmes plusieurs fois pour voir si les résultats étaient à peu près les

pour baseline_loop, j'ai obtenu 0,227314 seconde au premier essai, 0,226599 seconde au deuxième et 0,226520 seconde au troisième. Les résultats étaient donc assezche

J'ai comparé deux algorithmes,naive et single-pass. Pour finir, j'ai utilis� instrumentation_lab pour mesurer le temps passé dans chaque partie du programme.

## Observed Performance Differences

Ce qui m'a le plus marqué pendant les tests, c'est la différence de vitesse entre les deux algorithmes.

L'algorithme naive a mis en moyenne 2,752636 secondes pour terminer, alors que single-pass a mis seulement 0,000108 seconde.

La différence est vraiment important j'ai compris que single-pass parcourt les données une seule fois, alors quenaive répète davantage d'opérations. Cela explique pourquoi il prend beaucoup plus dp

Avec instrumentation_lab, j'ai pu voir que toutes les parties du programme ne prennent pas le même temps. Sur un total de 0,000771 seconde, la création des données a pris 0,000290 seconde, le traitement 0,000335 seconde et le calcul du checksum 0,000141 onde.

C'est donc le traitement des données qui a demandé le plus de temps.

## Relation Between Runtime and Energy Consumption

Je ne faisais pas forcément le lien entre le temps d'exécution d'un programme et sa consommation d'énergie.

En comparant les résultats, je me suis rendu compte qu'un programme qui évite des calculs inutiles peut terminer beaucoup plus rapidement.

Dans mon cas, single-pass était nettement plus rapide que naive. On peut donc penser qu'il pourrait aussi utiliser moins d'énergie puisqu'il travaille moins longtemps.

Mais je ne peux pas le confirmer avec ces tests. Je n'ai mesuré que le temps d'exécution, pas la quantité d'électricité réellement consommée.

Pour savoir lequel consomme le moins, il faudrait faire d'autres mesures avec un outil adapté.

## Limitations of the Experiment

Il y a  plusieurs limites dans les tests que j'ai réalisés.

La première est que je n'ai pas mesuré directement la consommation électrique. Je peux comparer les vitesses des programmes, mais pas dire exactement combien d'énergie ils utilisent.

Je n'ai fait que trois essais pour les premières comparaisons. Même si les résultats sont assez proches, ils pourraient changer avec davantage de tests.

Il faut aussi prendre en compte l'ordinateur utilisé. Si d'autres programmes fonctionnent en même temps ou si le processeur est plus sollicité, les résultats peuvent être diffé (j'ai quelques programmes qui tournent en même temp).

## Practical Engineering Takeaway

Cet exercice m'a permis de mieux comprendre pourquoi il est important de réfléchià la manière dont on écrit un programme.

Deux algorithmes qui donnent le même résultat peuvent sembler équivalents. Mes mesures montrent qu'ils peuvent avoir des temps d'exécution très différents.

Pour mes prochains projets, je pense que ce sera utile de tester plusieurs méthodes plutôt que de garder directement la première solution qui fonctionne.

Je retiens qu'un code bien pensé peut être plus rapide et éviter du travail inutile au processeur. Cela peut aussi être intéressant pour réduire la consommation d'énergie, même s'il faut des mesures supplémentaires pour lr



