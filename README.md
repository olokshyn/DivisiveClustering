# DivisiveClustering
[Divisive clustering](https://en.wikipedia.org/wiki/Hierarchical_clustering#Divisive_clustering) algorithm with several distance norms and linkage criteria.

Divisive clustering algorithm is a [hierarchial clustering](https://en.wikipedia.org/wiki/Hierarchical_clustering) algorithm that builds the hierarchial tree using "top down" approach.
The algorithm starts with the root node that contains all observations, and seperates them on every level of the tree according to the linkage criterion.
The [linkage criterion](https://en.wikipedia.org/wiki/Hierarchical_clustering#Linkage_criteria) determines the distance between sets of observations as a function of the pairwise distances between observations.

The following distance norms are implemented:
1. Minkowski
1. Manhattan
1. Euclidean
1. Squared Euclidean

A caching mechanism is provided for the norms to improve perfomance.

The following linakge criteria are implemented:
1. Middle Link
1. Distant Neighbor
1. Median Distance


The distance norms and linkage criteria could be easily replaced without changing the divisive algorithm.

The resulting hierarchial tree is rendered on the screen with the help of Qt library.



----------
# Дивизивный алгоритм кластеризации

Алгоритм является подвидом иерархического алгоритма кластеризации и строит дерево кластеров "сверху вниз".
Алгоритм начинает с одного узла, в котором содержатся все наблюдения, и на каждом уровне дерева разделяет узлы созгласно критерию связывания.

Реализованы следующие нормы расстояний:
1. Минковского
1. Манхеттенское
1. Евклидово
1. Евклидово в квадрате

Реализованы следующие критерии связывания:
1. Средней связи
1. Удаленного соседа
1. Медианной связи (расстояние между центрами кластеров)

Реализовано отображение полученного дерева кластеров с помощью библиотеки Qt.

