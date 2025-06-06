#!/usr/bin/python3

def validUTF8(data):
    n_bytes = 0

    for num in data:
        byte = num & 0xFF

        if n_bytes == 0:
            masque = 0b10000000
            while masque & byte:
                n_bytes += 1
                masque >>= 1

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
