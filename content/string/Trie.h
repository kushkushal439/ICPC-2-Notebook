/**
 * Author: Anonymous
 * Description: Trie
 */
class TrieNode {
public:
  unordered_map<char, TrieNode *> children;
  bool isEndOfWord;

  TrieNode() : isEndOfWord(false) {}
};
class Trie {
private:
  TrieNode *root;

public:
  Trie() { root = new TrieNode(); }
  void insert(const string &word) {
    TrieNode *node = root;
    for (char ch : word) {
      if (node->children.find(ch) == node->children.end()) {
        node->children[ch] = new TrieNode();
      }
      node = node->children[ch];
    }
    node->isEndOfWord = true;
  }
  bool search(const string &word) {
    TrieNode *node = root;
    for (char ch : word) {
      if (node->children.find(ch) == node->children.end()) {
        return false;
      }
      node = node->children[ch];
    }
    return node->isEndOfWord;
  }
  bool startsWith(const string &prefix) {
    TrieNode *node = root;
    for (char ch : prefix) {
      if (node->children.find(ch) == node->children.end()) {
        return false;
      }
      node = node->children[ch];
    }
    return true;
  }
};

// for bits
struct trieobject {
  trieobject() {
    children[0] = NULL;
    children[1] = NULL;
    numelems = 0;
  };

  struct trieobject* children[2];
  int numelems;
};

struct trie {
  trieobject base;
  trie() {
    trieobject base;
  }
  void add(int x) {
    int pow2 = (1ll << 31ll);
    trieobject* temp = &base;
    while (pow2 > 0) {
      if (temp->children[1 && (x & pow2)] == NULL) {
        temp->children[1 && (x & pow2)] = new trieobject;
      }
      temp->children[1 && (x & pow2)]->numelems++;
      temp = temp->children[1 && (x & pow2)];
      pow2 /= 2;
    }
  }
  // ADD FUNCTION BELOW
  
};