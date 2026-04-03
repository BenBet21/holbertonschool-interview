#!/usr/bin/python3
"""Count keywords in hot Reddit post titles recursively."""

import requests


def count_words(subreddit, word_list, after=None, word_count=None, duplicates=None):
    """
    Fonction récursive qui compte les occurrences de mots-clés dans les titres
    des posts "hot" d'un subreddit Reddit.

    Args:
        subreddit  : nom du subreddit à analyser (ex: "python")
        word_list  : liste de mots-clés à rechercher (ex: ["java", "Java", "python"])
        after      : token de pagination Reddit (None = première page)
        word_count : dictionnaire {mot: comptage} accumulé au fil des pages
        duplicates : dictionnaire {mot: nb_occurrences_dans_word_list}
                     → gère le cas où word_list contient plusieurs fois le même mot
    """

    # -------------------------------------------------------------------------
    # INITIALISATION (premier appel uniquement)
    # -------------------------------------------------------------------------
    # On entre ici uniquement lors du premier appel (word_count vaut None).
    # C'est le seul moment où on construit les deux dictionnaires de travail.
    if word_count is None:
        word_count = {}
        duplicates = {}

        for word in word_list:
            normalized = word.lower()  # Normalisation en minuscules

            # duplicates compte combien de fois chaque mot apparaît dans word_list.
            # Ex: word_list = ["java", "Java", "python"]
            # → duplicates = {"java": 2, "python": 1}
            # Ce multiplicateur sera utilisé plus tard lors du comptage.
            duplicates[normalized] = duplicates.get(normalized, 0) + 1

            # On n'initialise word_count qu'une seule fois par mot unique.
            # Les doublons dans word_list sont gérés via duplicates, pas en
            # créant plusieurs entrées dans word_count.
            if normalized not in word_count:
                word_count[normalized] = 0

    # -------------------------------------------------------------------------
    # CONSTRUCTION DE LA REQUÊTE HTTP
    # -------------------------------------------------------------------------
    url = "https://www.reddit.com/r/{}/hot.json".format(subreddit)

    # User-Agent obligatoire : Reddit rejette les requêtes sans identifiant client
    headers = {"User-Agent": "linux:count_words:v1.0 (by /u/holberton)"}

    # Limite maximale de l'API Reddit : 100 posts par page
    params = {"limit": 100}

    # On utilise "is not None" (et non juste "if after") pour être explicite :
    # after pourrait théoriquement être une chaîne vide, qu'on voudrait ignorer
    if after is not None:
        params["after"] = after

    # -------------------------------------------------------------------------
    # APPEL À L'API REDDIT
    # -------------------------------------------------------------------------
    try:
        response = requests.get(
            url,
            headers=headers,
            params=params,
            allow_redirects=False,  # Bloque les redirections (subreddit invalide → 302)
            timeout=10,             # Abandon si pas de réponse en 10 secondes
                                    # (absent dans la version précédente → risque de gel)
        )
    except requests.RequestException:
        # requests.RequestException couvre toutes les erreurs réseau :
        # timeout, connexion refusée, DNS introuvable, etc.
        # Plus précis que "except Exception" qui attraperait n'importe quelle erreur.
        return

    if response.status_code != 200:
        return

    # -------------------------------------------------------------------------
    # DÉCODAGE JSON ET EXTRACTION DES DONNÉES
    # -------------------------------------------------------------------------
    # Ici la version précédente utilisait deux .get() séparés avec un try/except.
    # Cette version chaîne directement les appels, ce qui est plus concis.
    # Si le JSON est invalide, une exception remontera naturellement.
    data = response.json().get("data", {})
    posts = data.get("children", [])
    # Structure JSON de Reddit :
    # {
    #   "data": {
    #     "after": "t3_xxxx",      ← token page suivante (ou null)
    #     "children": [
    #       { "data": { "title": "titre du post", ... } },
    #       ...
    #     ]
    #   }
    # }

    # -------------------------------------------------------------------------
    # ANALYSE DES TITRES ET COMPTAGE
    # -------------------------------------------------------------------------
    for post in posts:
        # Récupération + normalisation + découpage du titre en une seule ligne
        # Ex: "Java is GREAT!" → ["java", "is", "great!"]
        title = post.get("data", {}).get("title", "").lower().split()

        for token in title:
            # -----------------------------------------------------------------
            # NETTOYAGE : suppression des caractères non-alphabétiques
            # en début et en fin de mot
            # -----------------------------------------------------------------
            # On utilise deux curseurs (start, end) pour "rogner" le token.
            # Ex: "java!"  → start=0, end=4 → "java"
            #     ".java." → start=1, end=5 → "java"
            #     "java_8" → reste "java_8" → refusé par isalpha()
            start = 0
            end = len(token)

            while start < end and not token[start].isalpha():
                start += 1
            while end > start and not token[end - 1].isalpha():
                end -= 1

            cleaned = token[start:end]

            # -----------------------------------------------------------------
            # COMPTAGE AVEC MULTIPLICATEUR (différence clé avec la v1)
            # -----------------------------------------------------------------
            # Condition : le mot nettoyé est purement alphabétique ET
            # fait partie de notre liste de mots-clés.
            if cleaned.isalpha() and cleaned in word_count:
                # DIFFÉRENCE MAJEURE par rapport à la version précédente :
                # Au lieu d'ajouter 1, on ajoute duplicates[cleaned].
                # Si "java" apparaissait 2 fois dans word_list, chaque occurrence
                # dans un titre est comptée 2 fois directement ici.
                # Ex: word_list = ["java", "java"] et titre contient "java java"
                # → word_count["java"] += 2 * 2 = 4 au total
                word_count[cleaned] += duplicates[cleaned]

    # -------------------------------------------------------------------------
    # RÉCURSION : passage à la page suivante
    # -------------------------------------------------------------------------
    next_after = data.get("after")

    # "is not None" est important : si after vaut None, il n'y a plus de page suivante.
    # Une chaîne vide "" serait aussi considérée comme "plus de page" avec un simple "if".
    if next_after is not None:
        # On transmet word_count ET duplicates pour conserver l'état complet
        return count_words(subreddit, word_list, next_after, word_count, duplicates)

    # -------------------------------------------------------------------------
    # AFFICHAGE DES RÉSULTATS
    # -------------------------------------------------------------------------
    # On trie en une seule passe avec sorted() (plus pythonique qu'un .sort() séparé).
    # Critère 1 : count décroissant  → -item[1]
    # Critère 2 : alphabétique croissant → item[0]
    sorted_items = sorted(
        word_count.items(),
        key=lambda item: (-item[1], item[0]),
    )

    # Le filtre c > 0 est appliqué à l'affichage (et non avant le tri),
    # ce qui est légèrement différent de la v1 qui filtrait avant de trier.
    # Le résultat est identique car les mots à 0 seraient triés en dernier de toute façon.
    for word, count in sorted_items:
        if count > 0:
            print("{}: {}".format(word, count))
