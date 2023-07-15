#include <bits/stdc++.h>

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b
#define int long long
#define vi vector<int>

using namespace std;

#define alphabet 26

// begin
class Trie
{
private:
    int cant_string;
    int cant_string_me;
    int cant_node;
    char value;
    Trie *children[alphabet];

public:
    Trie(char a)
    {
        cant_string = 0;
        cant_node = 1;
        cant_string_me = 0;
        value = a;

        for (int i = 0; i < alphabet; i++)
            children[i] = nullptr;
    }

    pair<Trie *, int> search(string s)
    {
        Trie *node = this;
        int i = 0;

        while (node->children[s[i] - 'a'] != nullptr && i < s.size())
        {
            node = node->children[s[i] - 'a'];

            i++;
        }

        return {node, i};
    }

    void insert(string s)
    {
        int q = s.size() - search(s).second;

        Trie *node = this;

        for (int i = 0; i < s.size(); i++)
        {
            node->cant_node += q;

            if (node->children[s[i] - 'a'] == nullptr)
            {
                node->children[s[i] - 'a'] = new Trie(s[i]);
                q--;
            }

            node = node->children[s[i] - 'a'];
            node->cant_string_me++;
        }

        node->cant_string++;
    }

    void eliminate(string s)
    {
        if (!contains(s))
            return;

        Trie *node = this;
        int q = 0;

        for (int i = 0; i < s.size(); i++)
        {
            if (node->children[s[i] - 'a'] == nullptr)
            {
                node->children[s[i] - 'a'] = new Trie(s[i]);
            }

            if (node->children[s[i] - 'a']->cant_string_me == 1)
            {
                node->children[s[i] - 'a'] = nullptr;

                q = s.size() - i;
                break;
            }

            node = node->children[s[i] - 'a'];
            node->cant_string_me--;

            if (i == s.size() - 1)
                node->cant_string--;
        }

        node = this;

        for (int i = 0; i < s.size() - q + 1; i++)
        {
            node->cant_node -= q;
            node = node->children[s[i] - 'a'];
        }
    }

    bool contains(string s)
    {
        auto q = search(s);
        return q.second == s.size() && q.first->cant_string >= 1;
    }

    int cant_words_me() { return cant_string_me; }

    int cant_words() { return cant_string; }

    Trie *get(char a) { return children[a - 'a']; }

    int size() { return cant_node; }
};
// end

void solve()
{
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();

    return 0;
}