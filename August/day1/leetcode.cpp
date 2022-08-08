// https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/

class DSU {
    public:
    unordered_map<int,int> par, size;
    DSU() {
        
    } 
    void create(int x) {
        if(par.find(x) != par.end()) return;
        par[x] = x;
        size[x] = 1;
    }
    int find(int x) {
        if(par[x] == x) return x;
        return par[x] = find(par[x]);
    }
    void merge(int x, int y) {
        x = find(x);
        y = find(y);
        if(x != y) {
            if(size[x] < size[y]) swap(x, y);
            par[y] = par[x];
            size[x] += size[y];
        }
    }
};
class Solution {
public:
    int removeStones(vector<vector<int>>& stones) {
        unordered_map<int, set<vector<int>>> mp_row, mp_col;
        int n = 0, m = 0;
        for(auto &it: stones) {
            mp_row[it[0]].insert(it);
            mp_col[it[1]].insert(it);
            n = max(n, it[0]);
            m = max(m, it[1]);
        }
        n++; m++;
        DSU dsu;
        for(auto &it: stones) {
            int idx = m * it[0] + it[1];
            dsu.create(idx);
            for(auto &it1: mp_row[it[0]]) {
                int id = m * it1[0] + it1[1];
                dsu.create(id);
                dsu.merge(idx, id);
            }
            for(auto &it1: mp_col[it[1]]) {
                int id = m * it1[0] + it1[1];
                dsu.create(id);
                dsu.merge(idx, id);
            }
        }
        int res = 0;
        for(auto &it: dsu.par) {
            if(it.first == it.second) {
                res += (dsu.size[it.first] - 1);
            }
        } 
        return res;
    }
};

// https://leetcode.com/problems/largest-component-size-by-common-factor/

class DSU {
public:
    vector<int> par, size;
    DSU(int n) {
        par.resize(n  + 1, -1);
        size.resize(n + 1, 0);
    }    
    void create(int u) {
        if(par[u] != -1) return;
        par[u] = u;
        size[u] = 1;
    }
    int find(int u) {
        if(u == par[u]) return u;
        return par[u] = find(par[u]);
    }
    void Union(int u, int v) {
        u = find(u);
        v = find(v);
        if(u == v) return;
        if(size[u] > size[v]) swap(u, v);
        par[u] = par[v];
        size[v] += size[u];
    }
};
class Solution {
public:
    int largestComponentSize(vector<int>& nums) {
        int n = *max_element(nums.begin(), nums.end());
        DSU dsu(n + 1);
        for(int i: nums) {
            dsu.create(i);
            for(int j = 2; j*j <= i; ++j) {
                if(i % j == 0) {
                    dsu.create(j);
                    dsu.create(i/j);
                    
                    dsu.Union(i, j);
                    dsu.Union(i, i/j);
                }
            }
        }
        map<int, int> mp;
        int res = 0;
        for(int i: nums) {
            res = max(res, ++mp[dsu.find(i)]);
        }
        return res;
    }
};