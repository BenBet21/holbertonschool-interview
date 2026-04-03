#!/usr/bin/python3
"""Count keywords in hot Reddit post titles recursively."""

import requests


def count_words(subreddit, word_list, after=None,
                word_count=None, duplicates=None):
    """Print counts of words from word_list found in subreddit hot titles."""
    if word_count is None:
        word_count = {}
        duplicates = {}
        for word in word_list:
            normalized = word.lower()
            duplicates[normalized] = duplicates.get(normalized, 0) + 1
            if normalized not in word_count:
                word_count[normalized] = 0

    url = "https://www.reddit.com/r/{}/hot.json".format(subreddit)
    headers = {"User-Agent": "linux:count_words:v1.0 (by /u/holberton)"}
    params = {"limit": 100}
    if after is not None:
        params["after"] = after

    try:
        response = requests.get(
            url,
            headers=headers,
            params=params,
            allow_redirects=False,
            timeout=10,
        )
    except requests.RequestException:
        return

    if response.status_code != 200:
        return

    data = response.json().get("data", {})
    posts = data.get("children", [])

    for post in posts:
        title = post.get("data", {}).get("title", "").lower().split()
        for token in title:
            start = 0
            end = len(token)
            while start < end and not token[start].isalpha():
                start += 1
            while end > start and not token[end - 1].isalpha():
                end -= 1
            cleaned = token[start:end]
            if cleaned.isalpha() and cleaned in word_count:
                word_count[cleaned] += duplicates[cleaned]

    next_after = data.get("after")
    if next_after is not None:
        return count_words(subreddit, word_list,
                           next_after, word_count, duplicates)

    sorted_items = sorted(
        word_count.items(),
        key=lambda item: (-item[1], item[0]),
    )
    for word, count in sorted_items:
        if count > 0:
            print("{}: {}".format(word, count))
