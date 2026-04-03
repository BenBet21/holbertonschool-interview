# Reddit Hot Keywords Counter

Recursive Python function that queries the Reddit API to count keyword occurrences in hot article titles.

Fetches paginated results via `after` token, aggregates case-insensitive whole-word matches, and prints keywords sorted by count (desc) then alphabetically — duplicates in `word_list` are summed, punctuation-attached words are excluded, and invalid/empty subreddits print nothing.

Usage: `count_words("python", ["python", "java", "javascript"])`