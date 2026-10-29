#include <bits/stdc++.h>
using namespace std;

class Solution {
    int n;
    vector<vector<int>> adj;
    string s;
    vector<int> tin, tout, head, p, depth, sz, heavy, pos;
    vector<long long> tree;
    int timer;

    void dfs1(int u, int d, int par) {
        depth[u] = d;
        p[u] = par;
        sz[u] = 1;
        int max_sz = 0;
        for (int v : adj[u]) {
            if (v != par) {
                dfs1(v, d + 1, u);
                sz[u] += sz[v];
                if (sz[v] > max_sz) {
                    max_sz = sz[v];
                    heavy[u] = v;
                }
            }
        }
    }

    void dfs2(int u, int h) {
        head[u] = h;
        tin[u] = ++timer;
        pos[timer] = u;
        if (heavy[u] != -1) {
            dfs2(heavy[u], h);
        }
        for (int v : adj[u]) {
            if (v != p[u] && v != heavy[u]) {
                dfs2(v, v);
            }
        }
        tout[u] = timer;
    }

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = (1LL << (s[pos[start]] - 'a'));
            return;
        }
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        tree[node] = tree[2 * node] ^ tree[2 * node + 1];
    }

    void update_tree(int node, int start, int end, int idx, long long val) {
        if (start == end) {
            tree[node] = val;
            return;
        }
        int mid = (start + end) / 2;
        if (start <= idx && idx <= mid)
            update_tree(2 * node, start, mid, idx, val);
        else
            update_tree(2 * node + 1, mid + 1, end, idx, val);
        tree[node] = tree[2 * node] ^ tree[2 * node + 1];
    }

    long long query_tree(int node, int start, int end, int l, int r) {
        if (r < start || end < l)
            return 0;
        if (l <= start && end <= r)
            return tree[node];
        int mid = (start + end) / 2;
        return query_tree(2 * node, start, mid, l, r) ^ query_tree(2 * node + 1, mid + 1, end, l, r);
    }

    long long query_path(int u, int v) {
        long long res = 0;
        for (; head[u] != head[v]; v = p[head[v]]) {
            if (depth[head[u]] > depth[head[v]])
                swap(u, v);
            res ^= query_tree(1, 1, n, tin[head[v]], tin[v]);
        }
        if (depth[u] > depth[v])
            swap(u, v);
        res ^= query_tree(1, 1, n, tin[u], tin[v]);
        return res;
    }

public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s, vector<string>& queries) {
        this->n = n;
        this->s = s;
        adj.assign(n, vector<int>());
        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        tin.resize(n + 1);
        tout.resize(n + 1);
        head.resize(n);
        p.resize(n);
        depth.resize(n);
        sz.resize(n);
        heavy.assign(n, -1);
        pos.resize(n + 1);
        tree.assign(4 * (n + 1), 0);
        timer = 0;

        dfs1(0, 0, -1);
        dfs2(0, 0);
        build(1, 1, n);

        vector<bool> ans;
        for (auto& q : queries) {
            stringstream ss(q);
            string type;
            ss >> type;
            if (type == "update") {
                int u;
                char c;
                ss >> u >> c;
                s[u] = c;
                update_tree(1, 1, n, tin[u], (1LL << (c - 'a')));
            } else {
                int u, v;
                ss >> u >> v;
                long long mask = query_path(u, v);
                if ((mask & (mask - 1)) == 0) {
                    ans.push_back(true);
                } else {
                    ans.push_back(false);
                }
            }
        }
        return ans;
    }
};