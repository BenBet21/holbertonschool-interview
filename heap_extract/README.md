# holbertonschool-interview / Heap - Extract

# Heap Extract - Max Binary Heap Extraction

## Description

Ce projet implémente une fonction `heap_extract` qui extrait la racine d’un tas binaire max (Max Binary Heap).

Le tas est représenté sous forme d’arbre binaire, où chaque nœud respecte la propriété Max-Heap : la valeur d’un nœud est toujours supérieure ou égale à celles de ses enfants.

La fonction `heap_extract` :

- Extrait la valeur de la racine (maximum du tas).
- Remplace la racine par le dernier nœud en ordre de niveau.
- Supprime ce dernier nœud.
- Réorganise le tas pour restaurer la propriété Max-Heap (heapify down).
- Retourne la valeur extraite.

---

## Fichiers

- `0-main.c` : fichier de test principal.
- `0-heap_extract.c` : implémentation de la fonction `heap_extract` et fonctions auxiliaires.
- `binary_tree_print.c` : fonction d’affichage de l’arbre (fournie pour visualiser le tas).
- `binary_trees.h` : définitions de la structure de l’arbre et prototypes des fonctions.

---

## Compilation

```bash
gcc -Wall -Wextra -Werror -pedantic 0-main.c 0-heap_extract.c binary_tree_print.c -L. -lheap -o 0-heap_extract
