Bien sûr ! Voici un **README simple et clair** pour ton projet Menger Sponge en C :

---

# Éponge de Menger en C

Ce projet permet de générer une **éponge de Menger 2D** dans la console, en utilisant uniquement des caractères `#` pour les parties pleines et des espaces pour les trous.

## Description

L’éponge de Menger est une **figure fractale** obtenue en subdivisant un carré en 9 parties égales et en enlevant le carré central, puis en répétant cette opération pour chaque sous-carré restant.

Ce programme utilise :

* La fonction `is_hole` pour déterminer si une position doit être un trou.
* La fonction `menger` pour dessiner la grille correspondante à un niveau donné.

## Fichiers

* `menger.c` : Contient les fonctions principales pour générer et afficher l’éponge.
* `menger.h` : Header correspondant (déclarations des fonctions).

## Utilisation

1. Inclure le fichier `menger.h` dans votre programme principal.
2. Appeler la fonction `menger(level)` avec un niveau `level` ≥ 0.

Exemple :

```c
#include "menger.h"

int main(void)
{
    menger(2); // Dessine une éponge de Menger de niveau 2
    return 0;
}
```

## Exemple de sortie

Pour `level = 2`, la console affiche quelque chose comme :

```
#########
# ## ## #
#########
###   ###
# #   # #
###   ###
#########
# ## ## #
#########
```

## Compilation

```bash
gcc -Wall -Wextra -Werror -o menger menger.c main.c -lm
```

> Le flag `-lm` est nécessaire car le programme utilise `pow` de la bibliothèque mathématique.


