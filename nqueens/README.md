Parfait Benoît — tu veux un **README** pour un exercice de programmation du problème des **N Queens**, avec toutes les contraintes de l’énoncé.  
Je te prépare un README propre, structuré, prêt à être déposé dans un repo GitHub.

---

# ♛ N Queens — README

## 📌 Description
Le projet consiste à écrire un programme Python capable de résoudre le célèbre problème des **N reines** : placer **N reines** sur un échiquier **N×N** de manière à ce qu’aucune ne puisse en attaquer une autre.

Le programme doit afficher **toutes les solutions possibles**, sans exigence d’ordre particulier.

---

## 🚀 Usage

```bash
./nqueens N
```

### Conditions d’exécution
- Si le nombre d’arguments est incorrect :  
  ```
  Usage: nqueens N
  ```
  puis sortie avec le code **1**.

- Si **N n’est pas un entier** :  
  ```
  N must be a number
  ```
  puis sortie avec le code **1**.

- Si **N < 4** :  
  ```
  N must be at least 4
  ```
  puis sortie avec le code **1**.

---

## 📤 Sortie attendue

Le programme doit afficher **une solution par ligne**, sous forme d’une liste de positions :

Exemple pour N = 4 :

```
[[0, 1], [1, 3], [2, 0], [3, 2]]
[[0, 2], [1, 0], [2, 3], [3, 1]]
```

Chaque solution représente les coordonnées `[ligne, colonne]` de chaque reine.

---

## 🧠 Contraintes techniques
- Le programme doit être écrit en **Python 3**.
- Vous ne pouvez importer que le module **sys**.
- Le programme doit utiliser une **approche récursive ou backtracking**.
- Aucune bibliothèque externe n’est autorisée.

---

## 🛠️ Exemple d’exécution

```bash
$ ./nqueens 4
[[0, 1], [1, 3], [2, 0], [3, 2]]
[[0, 2], [1, 0], [2, 3], [3, 1]]
```
