#!/usr/bin/python3

def validUTF8(data):
    n_bytes = 0

    for num in data:
        # Garder seulement les 8 bits de poids faible
        byte = num & 0xFF

        if n_bytes == 0:
            # Compter le nombre de bits à 1 au début du byte
            masque = 0b10000000
            while masque & byte:
                n_bytes += 1
                masque >>= 1

            if n_bytes == 0:
                continue  # 1-byte char

            if n_bytes == 1 or n_bytes > 4:
                return False  # UTF-8 ne commence jamais par 10 ou plus de 4

            n_bytes -= 1  # car le premier byte est déjà lu
        else:
            # Doit être un byte de continuation => 10xxxxxx
            if not (byte & 0b10000000 and not (byte & 0b01000000)):
                return False
            n_bytes -= 1

    return n_bytes == 0
