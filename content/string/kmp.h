/**
 * Author: Anonymous
 */
vector<int> prefix_function(string s) {
  int n = (int)s.length();
  vector<int> pi(n);
  for (int i = 1; i < n; i++) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j])
      j = pi[j - 1];
    if (s[i] == s[j])
      j++;
    pi[i] = j;
  }
  return pi;
}

vector<int> KMP(string text, string pattern) {
  string s = pattern + "#" + text;
  vector<int> pi = prefix_function(s);
  vector<int> matches;
  int p = pattern.length();

  for (int i = 0; i < s.length(); i++) {
    if (pi[i] == p) {
      int match_pos = i - 2 * p;
      matches.push_back(match_pos); // 0-based index in text
    }
  }
  return matches;
}