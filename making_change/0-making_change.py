#!/usr/bin/python3
"""
This module contains the makeChange function.
"""


def makeChange(pieces, total):
    """
    Determines the fewest number of coins needed to meet a given amount total.
    Returns -1 if total cannot be met by any combination of the coins.
    """
    if total <= 0:
        return 0

    dp = [float('inf')] * (total + 1)
    dp[0] = 0

    for i in range(1, total + 1):
        for piece in pieces:
            if i - piece >= 0:
                dp[i] = min(dp[i], dp[i - piece] + 1)

    return dp[total] if dp[total] != float('inf') else -1
