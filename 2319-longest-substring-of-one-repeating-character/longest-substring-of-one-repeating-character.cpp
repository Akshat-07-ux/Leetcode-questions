#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Node {
    int max_len;
    int prefix_len;
    int suffix_len;
    char left_char;
    char right_char;
};

class Solution {
private:
    vector<Node> tree;

    Node merge(const Node& left, const Node& right, int left_len, int right_len) {
        Node res;
        res.left_char = left.left_char;
        res.right_char = right.right_char;

        // Base max length is the maximum of the two children
        res.max_len = max(left.max_len, right.max_len);

        // Check if characters at the border match
        if (left.right_char == right.left_char) {
            res.max_len = max(res.max_len, left.suffix_len + right.prefix_len);
        }

        // Calculate Prefix Length
        res.prefix_len = left.prefix_len;
        if (left.prefix_len == left_len && left.right_char == right.left_char) {
            res.prefix_len += right.prefix_len;
        }

        // Calculate Suffix Length
        res.suffix_len = right.suffix_len;
        if (right.suffix_len == right_len && left.right_char == right.left_char) {
            res.suffix_len += left.suffix_len;
        }

        return res;
    }

    void build(const string& s, int node, int start, int end) {
        if (start == end) {
            tree[node] = {1, 1, 1, s[start], s[start]};
            return;
        }

        int mid = start + (end - start) / 2;
        int left_child = 2 * node;
        int right_child = 2 * node + 1;

        build(s, left_child, start, mid);
        build(s, right_child, mid + 1, end);

        tree[node] = merge(tree[left_child], tree[right_child], mid - start + 1, end - mid);
    }

    void update(int node, int start, int end, int idx, char ch) {
        if (start == end) {
            tree[node] = {1, 1, 1, ch, ch};
            return;
        }

        int mid = start + (end - start) / 2;
        int left_child = 2 * node;
        int right_child = 2 * node + 1;

        if (idx <= mid) {
            update(left_child, start, mid, idx, ch);
        } else {
            update(right_child, mid + 1, end, idx, ch);
        }

        tree[node] = merge(tree[left_child], tree[right_child], mid - start + 1, end - mid);
    }

public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        int n = s.length();
        int k = queryIndices.size();
        
        tree.resize(4 * n);
        build(s, 1, 0, n - 1);

        vector<int> result(k);
        for (int i = 0; i < k; ++i) {
            update(1, 0, n - 1, queryIndices[i], queryCharacters[i]);
            result[i] = tree[1].max_len;
        }

        return result;
    }
};