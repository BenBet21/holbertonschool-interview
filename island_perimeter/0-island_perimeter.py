#!/usr/bin/python3
"""
Module qui calcule le périmètre d'une île dans une grille.
"""


def island_perimeter(grid):
    """
    Retourne le périmètre de l'île représentée dans la grille.

    Args:
        grid (list of list of int): 0 pour l'eau, 1 pour la terre.

    Returns:
        int: Le périmètre de l'île.
    """
    perimeter = 0
    height = len(grid)
    width = len(grid[0]) if height > 0 else 0

    for row in range(height):
        for col in range(width):
            if grid[row][col] == 1:
                # On ajoute 4 côtés pour chaque case de terre
                perimeter += 4

                # Si la case du dessus est aussi de la terre,
                # alors elles partagent un côté (on en enlève 2)
                if row > 0 and grid[row - 1][col] == 1:
                    perimeter -= 2

                # Si la case de gauche est aussi de la terre,
                # elles partagent également un côté
                if col > 0 and grid[row][col - 1] == 1:
                    perimeter -= 2

    return perimeter
