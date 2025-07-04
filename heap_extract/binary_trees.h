#ifndef BINARY_TREES_H
#define BINARY_TREES_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * struct binary_tree_s - Nœud d’un arbre binaire
 *
 * @n: Valeur stockée
 * @parent: Pointeur vers le parent
 * @left: Pointeur vers l’enfant gauche
 * @right: Pointeur vers l’enfant droit
 */
struct binary_tree_s
{
    int n;
    struct binary_tree_s *parent;
    struct binary_tree_s *left;
    struct binary_tree_s *right;
};

typedef struct binary_tree_s binary_tree_t;
typedef struct binary_tree_s heap_t;

int heap_extract(heap_t **root);
size_t binary_tree_size(const binary_tree_t *tree);
heap_t *get_node_at_index(heap_t *root, size_t index);
void heapify_down(heap_t *node);


#endif /* BINARY_TREES_H */
