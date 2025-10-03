#!/usr/bin/python3
"""
Log parsing script that computes metrics from stdin
"""
import sys
import re


def print_stats(total_size, status_codes):
    """
    Print the current statistics
    
    Args:
        total_size: Total file size accumulated
        status_codes: Dictionary of status codes and their counts
    """
    print("File size: {}".format(total_size))
    
    # Print status codes in ascending order
    valid_codes = [200, 301, 400, 401, 403, 404, 405, 500]
    for code in valid_codes:
        if code in status_codes and status_codes[code] > 0:
            print("{}: {}".format(code, status_codes[code]))


def parse_line(line):
    """
    Parse a log line and extract status code and file size
    
    Args:
        line: The log line to parse
        
    Returns:
        tuple: (status_code, file_size) or (None, None) if invalid
    """
    # Pattern plus permissif pour matcher différentes variations du format
    pattern = r'^\S+\s+-\s+\[.*?\]\s+"GET\s+/projects/260\s+HTTP/1\.1"\s+(\d+)\s+(\d+)\s*$'
    
    match = re.match(pattern, line.strip())
    if not match:
        return None, None
    
    try:
        status_code = int(match.group(1))
        file_size = int(match.group(2))
        return status_code, file_size
    except ValueError:
        return None, None


def main():
    """
    Main function that processes stdin line by line
    """
    total_size = 0
    status_codes = {}
    line_count = 0
    valid_line_count = 0
    
    try:
        for line in sys.stdin:
            line_count += 1
            status_code, file_size = parse_line(line)
            
            # Si la ligne est valide, mettre à jour les stats
            if status_code is not None and file_size is not None:
                valid_line_count += 1
                total_size += file_size
                
                # Compter seulement les codes de statut valides
                valid_codes = [200, 301, 400, 401, 403, 404, 405, 500]
                if status_code in valid_codes:
                    status_codes[status_code] = status_codes.get(status_code, 0) + 1
            
            # Afficher les stats toutes les 10 lignes (valides ou non)
            if line_count % 10 == 0:
                print_stats(total_size, status_codes)
        
        # Afficher les stats finales dans tous les cas
        if line_count % 10 != 0 or line_count == 0:
            print_stats(total_size, status_codes)
                
    except KeyboardInterrupt:
        # Afficher les stats finales lors d'une interruption
        print_stats(total_size, status_codes)
        raise


if __name__ == "__main__":
    main()
