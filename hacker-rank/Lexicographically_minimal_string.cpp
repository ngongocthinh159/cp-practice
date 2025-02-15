/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://www.hackerearth.com/practice/data-structures/disjoint-data-strutures/basics-of-disjoint-data-structures/practice-problems/algorithm/lexicographically-minimal-string-6edc1406/
*/

#include<bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> size;
    DSU(int n, bool auto_make_set = true) {
        parent.resize(n + 1);
        size.resize(n + 1);
        if (auto_make_set) {
            for (int i = 0; i <= n; i++) parent[i] = i, size[i] = 1;
        }
    }
    void make_set(int x) {
        parent[x] = x;
        size[x] = 1;
    }
    int find(int x) {
        return x == parent[x] ? x : parent[x] = find(parent[x]);
    }
    bool same_set(int a, int b) {
        return find(a) == find(b);
    }
    void unite(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if (ra != rb) {
            if (size[ra] < size[rb]) swap(ra,rb);
            size[ra] += size[rb];
            parent[rb] = ra;
        }
    }
    int find_size(int x) {
        return size[find(x)];
    }
};

string Solution (string a, string c, string b) {
   // Write your code here
    int len_a = a.size();
    int len_c = c.size();

    DSU dsu(26);
    for (int i = 0; i < len_a; i++) {
        dsu.unite(a[i] - 'a', b[i] - 'a');
    }
    int next[26];
    for (int c = 0; c < 26; c++)
        for (int first = 0; first <= c; first++) if (dsu.same_set(c, first)) {
            next[c] = first; 
            break;
        }
    for (int i = 0; i < len_c; i++) {
        c[i] = next[c[i] - 'a'] + 'a';
    }
    return c;
}

int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    string A;
    getline(cin, A);
    string B;
    getline(cin, B);
    string C;
    getline(cin, C);

    string out_;
    out_ = Solution(A, C, B);
    cout << out_;
}
