#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node
{
    bool isend = false;
    unordered_map<char, Node *> children;
};

class Trie
{
    Node *root;

public:
    Trie()
    {
        root = new Node();
    }

    ~Trie()
    {
        delete root;
    }

    void insert(const string &s)
    {
        Node *temp = root;
        for (auto ch : s)
        {
            if (!temp->children.count(ch))
            {
                temp->children[ch] = new Node();
            }
            temp = temp->children[ch];
        }
        temp->isend = true;
    }

    // checks if prefix exists
    bool isSubstring(const string &s)
    {
        Node *temp = root;
        for (auto ch : s)
        {
            if (!temp->children.count(ch))
            {
                return false;
            }
            temp = temp->children[ch];
        }
        return true;
    }

    void dfs(Node *node, vector<string> &result, string &curr)
    {
        if (result.size() == 3)
        {
            return;
        }
        if (node->isend)
        {
            result.push_back(curr);
        }
        for (int i = 0; i < 26; i++)
        {
            if (node->children.count('A' + i))
            {
                curr.push_back('A' + i);
                dfs(node->children['A' + i], result, curr);
                curr.pop_back();
            }
            if (node->children.count('a' + i))
            {
                curr.push_back('a' + i);
                dfs(node->children['a' + i], result, curr);
                curr.pop_back();
            }
        }
    }

    vector<string> getSuggestions(const string &prefix)
    {
        if (isSubstring(prefix) == false)
        {
            return {"No result found!"};
        }
        Node *temp = root;
        for (auto ch : prefix)
        {
            temp = temp->children[ch];
        }
        vector<string> result;
        string curr = prefix;
        dfs(temp, result, curr);
        return result;
    }
};

// return at most 3 suggestions (alphabetically sorted) after min 2 characters
vector<vector<string>> searchSuggestions(vector<string> &repo, string customerQuery)
{
    Trie trie;
    for (auto &word : repo)
    {
        trie.insert(word);
    }

    vector<vector<string>> result;
    string prefix;
    for (int i = 0; i < customerQuery.size(); i++)
    {
        prefix.push_back(customerQuery[i]);
        if (prefix.size() >= 2)
        {
            vector<string> suggestions = trie.getSuggestions(prefix);
            result.push_back(suggestions);
        }
    }
    return result;
}

int main()
{
    vector<string> repo = {"a", "ab", "abC", "abvfi", "abcdef", "abcr", "abcrf"};
    string query = "abcdej";

    auto suggestions = searchSuggestions(repo, query);

    for (int i = 0; i < suggestions.size(); i++)
    {
        cout << "After typing \"" << query.substr(0, i + 2) << "\": ";
        for (auto &s : suggestions[i])
            cout << s << " ";
        cout << "\n";
    }

    return 0;
}
