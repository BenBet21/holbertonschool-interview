#include "binary_trees.h"

/**
 * binary_tree_size - Calcule la taille d’un arbre binaire
 * @tree: Pointeur vers la racine de l’arbre
 * Return: Taille (nombre de nœuds), ou 0 si NULL
 */
size_t binary_tree_size(const binary_tree_t *tree)
{
    if (!tree)
        return 0;
    return 1 + binary_tree_size(tree->left) + binary_tree_size(tree->right);
}

/**
 * heap_extract - Extrait la racine d’un Max Binary Heap
 * @root: Double pointeur vers la racine du tas
 * Return: Valeur de l’ancienne racine, ou 0 en cas d’échec
 */
int heap_extract(heap_t **root)
{
    heap_t *last;
    int extracted_value;
    size_t size;

    if (!root || !*root)
        return 0;

    extracted_value = (*root)->n;
    size = binary_tree_size(*root);

    if (size == 1)
    {
        free(*root);
        *root = NULL;
        return extracted_value;
    }

    last = get_node_at_index(*root, size);

    // Remplacer la racine par la valeur du dernier nœud
    (*root)->n = last->n;

    // Détacher le dernier nœud de son parent
    if (last->parent->left == last)
        last->parent->left = NULL;
    else if (last->parent->right == last)
        last->parent->right = NULL;

    free(last);

    // TODO: heapify-down pour restaurer le Max-Heap à partir de la racine
    heapify_down(*root);

    return extracted_value;
}

/**
 * get_node_at_index - Trouve un nœud à une position donnée (index binaire)
 * @root: Pointeur vers la racine
 * @index: Position (commence à 1 pour la racine)
 * Return: Pointeur vers le nœud, ou NULL si absent
 */
heap_t *get_node_at_index(heap_t *root, size_t index)
{
    size_t mask = 1;
    heap_t *node = root;

    /* Trouver le bit le plus significatif (sauter le 1er bit) */
    while (mask <= index)
        mask <<= 1;
    mask >>= 2; /* Revenir au bit juste après le plus significatif */

    while (mask && node)
    {
        if (index & mask)
            node = node->right;
        else
            node = node->left;
        mask >>= 1;
    }

    return node;
}

void heapify_down(heap_t *node)
{
    heap_t *largest = node;
    heap_t *left, *right;
    int temp;

    while (1)
    {
        left = largest->left;
        right = largest->right;

        if (left && left->n > largest->n)
            largest = left;
        if (right && right->n > largest->n)
            largest = right;

        if (largest == node)
            break;

        // Échange les valeurs
        temp = node->n;
        node->n = largest->n;
        largest->n = temp;

        node = largest;
    }
}
