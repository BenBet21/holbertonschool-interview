#!/usr/bin/python3
def canUnlockAll(boxes):
    n = len(boxes)
    opened = set([0])  # On commence avec la boîte 0 ouverte
    keys = [0]         # Liste des boîtes à visiter (on commence par la 0)

    while keys:
        current = keys.pop()  # On prend une boîte à ouvrir
        for key in boxes[current]:
            if key < len(boxes) and key not in opened:
                opened.add(key) # On ajoute la boîte à visiter si elle n'est pas déjà ouverte
                keys.append(key) #On la met dans keys pour l’ouvrir plus tard
                
    # On vérifie si toutes les boîtes sont ouvertes
    return len(opened) == len(boxes)