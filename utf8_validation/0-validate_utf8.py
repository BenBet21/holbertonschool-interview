#!/usr/bin/python3
"""
Module 0-validate_utf8
Provides a method to validate UTF-8 encoding from a list of integers.
"""


def validUTF8(data):
    """
    Determines if a given list of integers represents a valid UTF-8 encoding.

    Args:
        data (list of int): A list where each integer represents a byte
        (only the 8 least significant bits are considered).

    Returns:
        bool: True if data is a valid UTF-8 encoding, False otherwise.
    """
    n_bytes = 0

    for num in data:
        byte = num & 0xFF

        if n_bytes == 0:
            mask = 0b10000000
            while mask & byte:
                n_bytes += 1
                mask >>= 1

            if n_bytes == 0:
                continue

            if n_bytes == 1 or n_bytes > 4:
                return False

            n_bytes -= 1
        else:
            if not (byte & 0b10000000 and not (byte & 0b01000000)):
                return False
            n_bytes -= 1

    return n_bytes == 0
