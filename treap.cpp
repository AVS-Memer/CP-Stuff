#include <bits/stdc++.h>
using namespace std;

struct TreapNode {
    int key, priority, size;
    TreapNode *left, *right;

    TreapNode(int k) : key(k), priority(rand()), size(1), left(nullptr), right(nullptr) {}
};

int getSize(TreapNode* t) {
    return t ? t->size : 0;
}

void updateSize(TreapNode* t) {
    if (t) t->size = 1 + getSize(t->left) + getSize(t->right);
}

// Splits treap into two: left has keys < key, right has keys ≥ key
void split(TreapNode* t, int key, TreapNode*& left, TreapNode*& right) {
    if (!t) {
        left = right = nullptr;
    } else if (key <= t->key) {
        split(t->left, key, left, t->left);
        right = t;
    } else {
        split(t->right, key, t->right, right);
        left = t;
    }
    updateSize(t);
}

// Merges two treaps
TreapNode* merge(TreapNode* left, TreapNode* right) {
    if (!left || !right) return left ? left : right;
    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        updateSize(left);
        return left;
    } else {
        right->left = merge(left, right->left);
        updateSize(right);
        return right;
    }
}

class Treap {
    TreapNode* root = nullptr;
    bool search(TreapNode* t, int key) {
        if (!t) return false;
        if (key == t->key) return true;
        return key < t->key ? search(t->left, key) : search(t->right, key);
    }
    TreapNode* insert(TreapNode* t, TreapNode* node) {
        if (!t) return node;
        if (node->priority > t->priority) {
            split(t, node->key, node->left, node->right);
            updateSize(node);
            return node;
        } else if (node->key < t->key) {
            t->left = insert(t->left, node);
        } else if (node->key > t->key) {
            t->right = insert(t->right, node);
        } // Duplicate keys are ignored
        updateSize(t);
        return t;
    }
    TreapNode* erase(TreapNode* t, int key) {
        if (!t) return nullptr;
        if (key == t->key) {
            TreapNode* merged = merge(t->left, t->right);
            delete t;
            return merged;
        } else if (key < t->key) {
            t->left = erase(t->left, key);
        } else {
            t->right = erase(t->right, key);
        }
        updateSize(t);
        return t;
    }
    int kth(TreapNode* t, int k) {
        if (!t || k <= 0 || k > getSize(t)) return -1;  // invalid
        int leftSize = getSize(t->left);
        if (k == leftSize + 1) return t->key;
        else if (k <= leftSize) return kth(t->left, k);
        else return kth(t->right, k - leftSize - 1);
    }
    // Count keys in [L, R]
    int rangeQuery(TreapNode* t, int L, int R) {
        TreapNode *L1, *mid, *R1;
        split(t, L, L1, mid);         // < L and ≥ L
        split(mid, R + 1, mid, R1);   // ≤ R and > R
        int count = getSize(mid);
        t = merge(L1, merge(mid, R1));  // Restore original treap
        return count;
    }
    public:
        void insert(int key) {
            if (!search(root, key)) {
                root = insert(root, new TreapNode(key));
            }
        }
        void erase(int key) {
            root = erase(root, key);
        }
        bool search(int key) {
            return search(root, key);
        }
        int kth(int k) {
            return kth(root, k);
        }
        int rangeQuery(int L, int R) {
            return rangeQuery(root, L, R);
        }
};
