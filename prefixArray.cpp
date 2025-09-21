#include <bits/stdc++.h>
using namespace std;

class PrefixArray {
    vector<int> p;
public:
    PrefixArray(vector<int>& n) {
        p = {0};
        for (int i : n) p.push_back(i+p.back());
    }
    size_t size() {
        return p.size()-1;
    }
    int rangeSum(int l, int r) {
        return p[r+1]-p[l];
    }
};

class TwoDPrefixArray {
    vector<vector<int>> p;
public:
    TwoDPrefixArray(vector<vector<int>>& n) {
        if (n.size() == 0) p = {{0}};
        else {
            p = vector<vector<int>>(n.size()+1,vector<int>(n[0].size()+1,0));
            for (size_t i = 0; i < n.size(); i++) {
                for (size_t j = 0; j < n[0].size(); j++) p[i+1][j+1] = n[i][j]+p[i+1][j]+p[i][j+1]-p[i][j];
            }
        }
    }
    pair<size_t,size_t> size() {
        return {p.size()-1,p[0].size()-1};
    }
    int rangeSum(int x1, int y1, int x2, int y2) {
        return p[x2+1][y2+1]-p[x1][y2+1]-p[x2+1][y1]+p[x1][y1];
    }
};

class ThreeDPrefixArray {
    vector<vector<vector<int>>> p;
public:
    ThreeDPrefixArray(vector<vector<vector<int>>>& n) {
        if (n.size() == 0 || n[0].size() == 0) p = {{{0}}};
        else {
            p = vector<vector<vector<int>>>(n.size()+1,vector<vector<int>>(n[0].size()+1,vector<int>(n[0][0].size()+1)));
            for (size_t i = 0; i < n.size(); i++) {
                for (size_t j = 0; j < n[0].size(); j++) {
                    for (size_t k = 0; k < n[0][0].size(); k++) p[i+1][j+1][k+1] = n[i][j][k]+p[i][j+1][k+1]+p[i+1][j][k+1]+p[i+1][j+1][k]-p[i][j+1][k]-p[i+1][j][k]-p[i][j][k+1]+p[i][j][k];
                }
            }
        }
    }
    tuple<size_t,size_t,size_t> size() {
        return {p.size()-1,p[0].size()-1,p[0][0].size()-1};
    }
    int rangeSum(int x1, int y1, int z1, int x2, int y2, int z2) {
        return p[x2+1][y2+1][z2+1]-p[x1][y2+1][z2+1]-p[x2+1][y1][z2+1]-p[x2+1][y2+1][z1]+p[x1][y1][z2+1]+p[x1][y2+1][z1]+p[x2+1][y1][z1]-p[x1][y1][z1];
    }
};
