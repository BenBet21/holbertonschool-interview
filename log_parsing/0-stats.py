#!/usr/bin/python3
"""Parse logs and return error count and file size"""

import sys

STATUS_CODES = [200, 301, 400, 401, 403, 404, 405, 500]


def parse_line(line):
    """Extract status (optional) and size (required if numeric)"""
    parts = line.strip().split()
    if not parts:
        return None, None

    try:
        size = int(parts[-1])
    except (ValueError, IndexError):
        size = None

    status = None
    if len(parts) >= 2:
        try:
            status = int(parts[-2])
        except ValueError:
            status = None

    return status, size


def print_stats(total, count):
    """Prints stats"""
    print(f"File size: {total}")
    for code in sorted(STATUS_CODES):
        if code in count:
            print(f"{code}: {count[code]}")


def stats():
    """Extracts stats"""
    total = 0
    count = {}
    line_number = 0

    try:
        for line in sys.stdin:
            line_number += 1
            status, size = parse_line(line)

            if size is not None:
                total += size

            if status is not None and status in STATUS_CODES:
                count[status] = count.get(status, 0) + 1

            if line_number % 10 == 0:
                print_stats(total, count)

    except KeyboardInterrupt:
        pass

    finally:
        print_stats(total, count)


if __name__ == '__main__':
    stats()
