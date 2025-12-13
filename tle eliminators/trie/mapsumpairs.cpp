// https://leetcode.com/problems/map-sum-pairs

#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct Node {
    bool isend;
    int words;
    int val;
    vector<Node*> children;

    Node() {
        isend = false;
        words = 0;
        val = 0;
        children = vector<Node*>(26, nullptr);
    }
};

class Trie {
    Node* root;

    void insert(Node* node, string& s, int val, int pos = 0) {
        int n = s.size();
        int index = s[pos] - 'a';
        if (pos == n - 1) {
            if (node->children[index] == nullptr) {
                node->children[index] = new Node();
            }
            node->children[index]->isend = true;
        } else {
            if (node->children[index] != nullptr) {
                insert(node->children[index], s, val, pos + 1);
            } else {
                node->children[index] = new Node();
                insert(node->children[index], s, val, pos + 1);
            }
        }
        node->children[index]->words++;
        node->children[index]->val += val;
    }

    bool search(Node* node, string& s, int pos = 0) {
        int n = s.size();
        int index = s[pos] - 'a';
        if (pos == n - 1) {
            if (node->children[index] == nullptr ||
                node->children[index]->isend == false) {
                return false;
            }
            return true;
        } else {
            if (node->children[index] == nullptr) {
                return false;
            }
            return search(node->children[index], s, pos + 1);
        }
    }

    int numberOfWordswithPrefix(Node* node, string& prefix, int pos = 0) {
        int n = prefix.size();
        int index = prefix[pos] - 'a';
        if (pos == n - 1) {
            if (node->children[index] != nullptr) {
                return node->children[index]->words;
            }
            return 0;
        } else {
            if (node->children[index] != nullptr) {
                return numberOfWordswithPrefix(node->children[index], prefix,
                                               pos + 1);
            }
            return 0;
        }
    }

    int valueWithPrefix(Node* node, string& prefix, int pos = 0) {
        int n = prefix.size();
        int index = prefix[pos] - 'a';
        int ans = 0;
        if (pos == n - 1) {
            if (node->children[index] != nullptr) {
                return node->children[index]->val;
            }
            return 0;
        } else {
            if (node->children[index] != nullptr) {
                return valueWithPrefix(node->children[index], prefix, pos + 1);
            }
            return 0;
        }
    }

public:
    Trie() { root = new Node(); }

    void insert(string& s, int val) { insert(root, s, val); }

    bool search(string& s) { return search(root, s); }

    int numberOfWordswithPrefix(string& prefix) {
        return numberOfWordswithPrefix(root, prefix);
    }

    int valueWithPrefix(string& prefix) {
        return valueWithPrefix(root, prefix);
    }
};

class MapSum {
    Trie* trie;
    map<string, int> mp;

public:
    MapSum() { trie = new Trie(); }

    void insert(string key, int val) {
        if (mp.count(key)) {
            int newval = -mp[key] + val;
            trie->insert(key, newval);
        } else {
            trie->insert(key, val);
        }
        mp[key]=val;
    }

    int sum(string prefix) { return trie->valueWithPrefix(prefix); }
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum* obj = new MapSum();
 * obj->insert(key,val);
 * int param_2 = obj->sum(prefix);
 */