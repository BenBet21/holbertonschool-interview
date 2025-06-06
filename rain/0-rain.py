#!/usr/bin/python3
"""
0-rain
Calculates how much water will be retained after rainfall
"""


def rain(walls):
    """
    Calculates the total amount of rainwater retained.

    Args:
        walls (list of int): Heights of the walls.

    Returns:
        int: Total units of retained water.
    """
    if not walls or len(walls) < 3:
        return 0

    n = len(walls)
    water = 0

    # Arrays to store max height to the left/right of each index
    left_max = [0] * n
    right_max = [0] * n

    # Fill left_max
    left_max[0] = walls[0]
    for i in range(1, n):
        left_max[i] = max(left_max[i - 1], walls[i])

    # Fill right_max
    right_max[-1] = walls[-1]
    for i in range(n - 2, -1, -1):
        right_max[i] = max(right_max[i + 1], walls[i])

    # Calculate trapped water
    for i in range(1, n - 1):
        trapped = min(left_max[i], right_max[i]) - walls[i]
        if trapped > 0:
            water += trapped

    return water
