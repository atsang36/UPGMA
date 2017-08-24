# UPGMA
UPGMA (Unweighted Pair Group Method with Arithmetic Mean) is a simple bottom-up hierarchical clustering method used to construct a phylogenetic tree (a tree of life) from the pairwise (evolutionary) distances between species invented by Sokal and Michener in 1958. The method works by clustering the species, at each stage joining two clusters together that have the smallest distance. The input to the algorithm is a sequence of strings with names of the species and distances between the species represented by n rows each containing n numbers, where the j-th decimal number in a row i represents the distance between the i-th species and the j-th species. You can assume that the distance between the i-th species and the j-species in the input is the same as the distances between the j-th species and the i-th species


species.txt, species10.txt, species100.txt files are samples tests that are arguements required to pass to UPGMA.
