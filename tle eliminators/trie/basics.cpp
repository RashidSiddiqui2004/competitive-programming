#include <iostream>
#include <vector>

using namespace std;

struct Node
{
    bool isend;
    int words;
    vector<Node *> children;

    Node()
    {
        isend = false;
        words = 0;
        children = vector<Node *>(26, nullptr);
    }
};

class Trie
{
    Node *root;

    void insert(Node *node, string &s, int pos = 0)
    {
        int n = s.size();
        int index = s[pos] - 'a';
        if (pos == n - 1)
        {
            if (node->children[index] == nullptr)
            {
                node->children[index] = new Node();
            }
            node->children[index]->isend = true;
        }
        else
        {
            if (node->children[index] != nullptr)
            {
                insert(node->children[index], s, pos + 1);
            }
            else
            {
                node->children[index] = new Node();
                insert(node->children[index], s, pos + 1);
            }
        }
        node->children[index]->words++;
    }

    bool search(Node *node, string &s, int pos = 0)
    {
        int n = s.size();
        int index = s[pos] - 'a';
        if (pos == n - 1)
        {
            if (node->children[index] == nullptr || node->children[index]->isend == false)
            {
                return false;
            }
            return true;
        }
        else
        {
            if (node->children[index] == nullptr)
            {
                return false;
            }
            return search(node->children[index], s, pos + 1);
        }
    }

    int numberOfWordswithPrefix(Node *node, string &prefix, int pos = 0)
    {
        int n = prefix.size();
        int index = prefix[pos] - 'a';
        if (pos == n - 1)
        {
            if (node->children[index] != nullptr)
            {
                return node->children[index]->words;
            }
            return 0;
        }
        else
        {
            if (node->children[index] != nullptr)
            {
                return numberOfWordswithPrefix(node->children[index], prefix, pos + 1);
            }
            return 0;
        }
    }

public:
    Trie()
    {
        root = new Node();
    }

    void insert(string &s)
    {
        insert(root, s);
    }

    bool search(string &s)
    {
        return search(root, s);
    }

    int numberOfWordswithPrefix(string &prefix)
    {
        return numberOfWordswithPrefix(root, prefix);
    }
};

int main()
{
    Trie *trie = new Trie();

    string s = "hello";
    trie->insert(s);
    cout << trie->search(s) << endl;

    int n;
    cout << "Number of words in dictionary: \n";
    cin >> n;

    string word;

    for (size_t i = 0; i < n; i++)
    {
        cin >> word;
        trie->insert(word);
    }

    int m;
    cout << "Number of queries: \n";
    cin >> m;

    string query;

    for (size_t i = 0; i < m; i++)
    {
        cin >> query;
        cout << "Query: " << query << ": " << trie->search(query) << endl;
    }

    // prefix queries
    cout << "Number of queries: \n";
    cin >> m;

    for (size_t i = 0; i < m; i++)
    {
        cin >> query;
        cout << "Query: " << query << ": " << trie->numberOfWordswithPrefix(query) << endl;
    }

    delete trie;
    return 0;
}