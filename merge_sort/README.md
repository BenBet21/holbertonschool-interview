# Merge Sort

Top-down merge sort implementation in C that sorts an integer array in ascending order.

The array is recursively split so the left half is always ≤ the right half in size, left is sorted before right, and merging is done with a single `malloc`/`free` call for the temporary buffer.

Time complexity — best, average and worst case: **O(n log n)** (written in `0-O`).