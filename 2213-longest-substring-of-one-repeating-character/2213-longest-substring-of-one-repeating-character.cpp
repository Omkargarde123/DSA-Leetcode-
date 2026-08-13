struct Node {
    int max_len = 0;
    int prefix_len = 0;
    int suffix_len = 0;
    char left_char = ' ';
    char right_char = ' ';
};

class SegmentTree {
private:
    int n;
    vector<Node> tree;

    Node merge(const Node& left, const Node& right, int left_sz, int right_sz) {
        Node res;
        res.left_char = left.left_char;
        res.right_char = right.right_char;

        res.max_len = max(left.max_len, right.max_len);

        if (left.right_char == right.left_char) {
            res.max_len = max(res.max_len, left.suffix_len + right.prefix_len);
        }

        res.prefix_len = left.prefix_len;
        if (left.prefix_len == left_sz && left.right_char == right.left_char) {
            res.prefix_len += right.prefix_len;
        }

        res.suffix_len = right.suffix_len;
        if (right.suffix_len == right_sz && left.right_char == right.left_char) {
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
        build(s, 2 * node, start, mid);
        build(s, 2 * node + 1, mid + 1, end);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1], mid - start + 1, end - mid);
    }

    void update(int node, int start, int end, int idx, char val) {
        if (start == end) {
            tree[node] = {1, 1, 1, val, val};
            return;
        }
        int mid = start + (end - start) / 2;
        if (start <= idx && idx <= mid) {
            update(2 * node, start, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        tree[node] = merge(tree[2 * node], tree[2 * node + 1], mid - start + 1, end - mid);
    }

public:
    SegmentTree(const string& s) {
        n = s.length();
        tree.resize(4 * n);
        build(s, 1, 0, n - 1);
    }

    void update(int idx, char val) {
        update(1, 0, n - 1, idx, val);
    }

    int getMaxLen() {
        return tree[1].max_len;
    }
};

class Solution {
public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        SegmentTree st(s);
        int k = queryIndices.size();
        vector<int> ans(k);

        for (int i = 0; i < k; ++i) {
            st.update(queryIndices[i], queryCharacters[i]);
            ans[i] = st.getMaxLen();
        }

        return ans;
    }
};