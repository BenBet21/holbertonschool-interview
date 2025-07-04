#include "binary_trees.h"

/**
 * binary_tree_size - Calculates the size of a binary tree
 * @tree: Pointer to the root node of the tree
 * Return: Size (number of nodes), or 0 if NULL
 */
size_t binary_tree_size(const binary_tree_t *tree)
{
	return (tree ? 1 + binary_tree_size(tree->left)
	+ binary_tree_size(tree->right) : 0);
}

/**
 * get_node_at_index - Finds a node at a given position (binary index)
 * @root: Pointer to the root
 * @index: Position (starts at 1 for the root)
 * Return: Pointer to the node, or NULL if absent
 */
heap_t *get_node_at_index(heap_t *root, size_t index)
{
	size_t mask = 1;
	heap_t *node = root;

	while (mask <= index)
		mask <<= 1;
	mask >>= 2;

	while (mask && node)
	{
		if (index & mask)
			node = node->right;
		else
			node = node->left;
		mask >>= 1;
	}
	return (node);
}

/**
 * heapify_down - Restores the Max-Heap property from a node downwards
 * @node: Pointer to the node to heapify from
 */
void heapify_down(heap_t *node)
{
	heap_t *largest, *left, *right;
	int temp;

	if (!node)
		return;

	while (1)
	{
		largest = node;
		left = node->left;
		right = node->right;

		if (left && left->n > largest->n)
			largest = left;
		if (right && right->n > largest->n)
			largest = right;

		if (largest == node)
			break;

		temp = node->n;
		node->n = largest->n;
		largest->n = temp;

		node = largest;
	}
}

/**
 * heap_extract - Extracts the root node of a Max Binary Heap
 * @root: Double pointer to the root of the heap
 * Return: Value of the extracted root node, or 0 on failure
 */
int heap_extract(heap_t **root)
{
	heap_t *last;
	int extracted_value;
	size_t size;

	if (!root || !*root)
		return (0);

	extracted_value = (*root)->n;
	size = binary_tree_size(*root);

	if (size == 1)
	{
		free(*root);
		*root = NULL;
		return (extracted_value);
	}

	last = get_node_at_index(*root, size);

	(*root)->n = last->n;

	if (last->parent->left == last)
		last->parent->left = NULL;
	else if (last->parent->right == last)
		last->parent->right = NULL;

	free(last);

	heapify_down(*root);

	return (extracted_value);
}

