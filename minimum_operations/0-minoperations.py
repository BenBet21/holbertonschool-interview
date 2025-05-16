#!/usr/bin/python3
"""
Minimum Operations
Given a number n, the goal is to find the minimum number of operations
to reach n characters in a text file starting with 1 character.
"""


def minOperations(n):
    """
    Calculate the minimum number of operations to reach n characters
    in a text file starting with 1 character.
    """
    if n <= 1:
        return 0

    operations = 0
    factor = 2

    while n > 1:
        if n % factor == 0:
            n = n // factor
            operations += factor
        else:
            factor += 1

    return operations
