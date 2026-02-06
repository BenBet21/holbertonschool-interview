#!/usr/bin/python3
"""Solve the N queens problem.

This script prints all possible solutions to the N queens problem
for a given board size N, provided as a command-line argument.
"""

import sys


def parse_arguments():
    """Parse and validate command-line arguments.

    Returns:
        int: The board size N.

    Raises:
        SystemExit: With code 1 if arguments are invalid.
    """
    if len(sys.argv) != 2:
        print("Usage: nqueens N")
        sys.exit(1)

    n_str = sys.argv[1]

    if not n_str.isdigit():
        print("N must be a number")
        sys.exit(1)

    n = int(n_str)

    if n < 4:
        print("N must be at least 4")
        sys.exit(1)

    return n


def is_safe(queens, row, col):
    """Check if a queen can be placed at (row, col).

    Args:
        queens (list[int]): Columns of already placed queens by row index.
        row (int): Row index where we want to place the queen.
        col (int): Column index where we want to place the queen.

    Returns:
        bool: True if position is safe, False otherwise.
    """
    for r in range(row):
        c = queens[r]
        if c == col:
            return False
        if abs(c - col) == abs(r - row):
            return False
    return True


def solve_nqueens(n, row, queens, solutions):
    """Recursively build all solutions for the N queens problem.

    Args:
        n (int): Board size.
        row (int): Current row to place a queen.
        queens (list[int]): Current partial solution.
        solutions (list[list[int]]): Collected complete solutions.
    """
    if row == n:
        solutions.append(queens.copy())
        return

    for col in range(n):
        if is_safe(queens, row, col):
            queens[row] = col
            solve_nqueens(n, row + 1, queens, solutions)


def print_solutions(solutions):
    """Print all solutions in the required format.

    Args:
        solutions (list[list[int]]): List of solutions as column indices.
    """
    for queens in solutions:
        coords = []
        for row, col in enumerate(queens):
            coords.append([row, col])
        print(coords)


def main():
    """Entry point of the script."""
    n = parse_arguments()
    queens = [-1] * n
    solutions = []
    solve_nqueens(n, 0, queens, solutions)
    print_solutions(solutions)


if __name__ == "__main__":
    main()
