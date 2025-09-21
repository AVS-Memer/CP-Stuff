#include <bits/stdc++.h>
using namespace std;

class FenwickTree { // 0-indexed
    vector<int> BIT;
    public:
        FenwickTree(const vector<int>& a) {
            BIT = vector<int>(a.size());
            for (int i = 0; i < a.size(); i++) update(i, a[i]);
        }
        void update(int index, int delta) {
            for (int i = index+1; i <= BIT.size(); i+=(i&-i)) BIT[i-1] += delta;
        }
        static FenwickTree fromPrefix(const vector<int>& pref) { // 1-indexed prefix array
            BIT = vector<int>(pref.size()-1);
            for (int i = 1; i < pref.size(); i++) a.BIT[i-1] = pref[i]-pref[i-(i&-i)];
            return a;
        }
        int query(int index) const {
            int res = 0;
            for (int i = index+1; i > 0; i-=(i&-i)) res += BIT[i-1];
            return res;
        }
        int rangeQuery(int l, int r) {
            if (l == 0) return query(r);
            return query(r)-query(l-1);
        }
        void set(int i, int new_value) {
            update(i, new_value-rangeQuery(i,i));
        }
};
