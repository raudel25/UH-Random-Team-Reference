#include <bits/stdc++.h>
 
using namespace std;

// begin

struct avl {
    int key;
    int height;
    int size;
    avl *left;
    avl *right;

    avl(int k) {
        key = k;
        height = 1;
        size = 1;
        left = NULL;
        right = NULL;
    }

    int getBalance() {
        int leftHeight = 0;
        int rightHeight = 0;

        if (left != NULL)
            leftHeight = left->height;

        if (right != NULL)
            rightHeight = right->height;

        return leftHeight - rightHeight;
    }

    void updateSize() {
        int leftSize = 0;
        int rightSize = 0;

        if (left != NULL)
            leftSize = left->size;

        if (right != NULL)
            rightSize = right->size;

        size = leftSize + rightSize + 1;
    }

    void updateHeight() {
        int leftHeight = 0;
        int rightHeight = 0;

        if (left != NULL)
            leftHeight = left->height;

        if (right != NULL)
            rightHeight = right->height;

        height = max(leftHeight, rightHeight) + 1;
    }

    avl *rotateLeft() {
        avl *newRoot = right;
        right = newRoot->left;
        newRoot->left = this;
        updateHeight();
        newRoot->updateHeight();
        return newRoot;
    }

    avl *rotateRight() {
        avl *newRoot = left;
        left = newRoot->right;
        newRoot->right = this;
        updateHeight();
        newRoot->updateHeight();
        return newRoot;
    }

    avl *balance() {
        updateHeight();
        updateSize();
        int balance = getBalance();

        if (balance == 2) {
            if (left->getBalance() < 0)
                left = left->rotateLeft();
            return rotateRight();
        }

        if (balance == -2) {
            if (right->getBalance() > 0)
                right = right->rotateRight();
            return rotateLeft();
        }

        return this;
    }

    avl *insert(int k) {
        if (k < key) {
            if (left == NULL)
                left = new avl(k);
            else
                left = left->insert(k);
        }
        else {
            if (right == NULL)
                right = new avl(k);
            else
                right = right->insert(k);
        }

        return balance();
    }

    avl *findMin() {
        if (left == NULL)
            return this;
        else
            return left->findMin();
    }

    avl *removeMin() {
        if (left == NULL)
            return right;
        left = left->removeMin();
        return balance();
    }

    avl *remove(int k) {
        if (k < key)
            left = left->remove(k);
        else if (k > key)
            right = right->remove(k);
        else {
            avl *leftChild = left;
            avl *rightChild = right;

            delete this;

            if (rightChild == NULL)
                return leftChild;

            avl *min = rightChild->findMin();
            min->right = rightChild->removeMin();
            min->left = leftChild;
            return min->balance();
        }

        return balance();
    }

    int getRank(int k) {
        if (k < key) {
            if (left == NULL)
                return 0;
            else
                return left->getRank(k);
        }
        else if (k > key) {
            if (right == NULL)
                return 1 + left->size;
            else
                return 1 + left->size + right->getRank(k);
        }
        else
            return left->size;
    }

    int getKth(int k) {
        if (k < left->size)
            return left->getKth(k);
        else if (k > left->size)
            return right->getKth(k - left->size - 1);
        else
            return key;
    }

    static avl *join(avl *left, avl *right) {
        if (left->height < right->height) {
            right->left = join(left, right->left);
            return right->balance();
        }
        else if (left->height > right->height) {
            left->right = join(left->right, right);
            return left->balance();
        }
        else {
            avl *min = right->findMin();
            min->right = right->removeMin();
            min->left = left;
            return min->balance();
        }
    }

    pair<avl *, avl *> split(int k) {
        if (k < key) {
            pair<avl *, avl *> p = left->split(k);
            left = p.second;
            return {p.first, join(this, left)};
        }
        else {
            pair<avl *, avl *> p = right->split(k);
            right = p.first;
            return {join(this, right), p.second};
        }
    }
};

// end