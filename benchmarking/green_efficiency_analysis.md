# Green Efficiency Analysis

## Measurement Methodology

 j'ai mesuré les temps d'exécution de plusieurs programmes écrits en langage C afin de comparer leurs performances et de mieux comprendre leur efficaci

Pour effectuer ces mesures, j'ai utilisé la fonctionclock et CLOCKS_PER_SEC, qui permettent de convertir le temps mesuré en secondes

J'ai exécuté plusieurs fois les programmes afin de vérifier la stabilité des résultats. Pour le progr baselineoop  j'ai effectué trois mesures : 0,227314 seconde, 0,226599 seconde et 0,226520 seconde.

J'ai également comparé deux algorithmes différents, puis mesuré séparément les différentes étapes du prinstrumentation_lab

## Observed Performance Differences

Les résultats montrent des différences importantes entre les algorithm.

L'algorithme naive a obtenu un temps moyen de 2,752636 secondes, tandis que l'algorithme single-pass a obtenu un temps moyen de 0,000108 seconde.

Cette différence s'explique par leur fonctionnement. L'algorithm single-pas parcourt les données une seule fois, contrairemen l'algorithme naive, qui effectue davantage de passages et répète certaines opératio

Dans le programme instrumentation_lab, le temps total mesuré était de 0,000771 seconde. La construction des données a nécessité 0,000290 seconde, leur traitement 0,000335 seconde et le calcul du checksum 0,000141 sec

Le traitement des données était donc l'étape la plus longue de cette exécution.

## Relation Between Runtime and Energy Consumption

Le temps d'exécution d'un programme peut avoir une influence sur sa consommation énergétique.

l'algorithme single-pass était beaucoup plus rapide que l'algorithmenaive. Cela suggère qu'une meilleure organisation des opérations pourrait permettre de réduire l'énergie néces  certains calculs.

Cependant, un programme plus rapide ne consomme pas automatiquement moins d'électricité. La consommation dépend également de la puissance utilisée par le processeur pendant son fonctionnement.

il faudrait mesurer directement la consommation électrique des deux algorithmes dans des conditions comparables

Les résultats obtenus permettent donc de conclur une amélioration des performances, mais pas de quantifier une économie d'éner.

## Limitations of the Experiment

La principale limite est que j'ai uniquement mesuré les temps d'exécution, sans mesurer directement la consommation électriq

Je ne peux donc pas affirmer quel algorithme consomme le moins d'énergie

Une autre limite concerne le nombre de mesures réalisées. Trois exécutions permettent d'observer certaines variations, mais ne suffisent pas pour garantir des résultats identiques dans toutes les conditions.

Les performances peuvent également être influencées par les programmes exécutés en arrière-plan, la charge du processeur ou les caractéristiques de l'ordinateur.

les résultats concernent uniquement les programmes et les données utilis. Ils ne représentent pa les performances de tous les programme

## Practical Engineering Takeaway

Cette expériene m'a permis de comprendre l'importance du choix des algorithmes dans le développement informatique.

J'ai constaté qu'un algorithme qui évite les opérations répétitives peut être beaucoup plus performant qu'une solution moins optimisée.

J'ai appri a  mesurer précisément les différentes étapes d'un programme afin d'identifier celles qui nécessitent le plus de t

je pourrai utiliser ces méthodes pour comparer plusieurs solutions, amélioreles programmes et éviter les calculs inutiles.

l'optimisation des performances peut contribuer �pratique plus �cologique même si des mesures énergétiques supplémentaires restent nécessaires pour démontrer un bénéfice environnemental réel.

