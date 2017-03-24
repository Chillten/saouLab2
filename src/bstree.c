//
// Created by chillten on 24.03.17.
//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "bstree.h"

bstree *bstree_create(char *key, int value) {
    if (key != NULL) {
        bstree *node = (bstree *) malloc(sizeof(bstree));
        if (node != NULL) {
            node->key = key;
            node->value = value;
            node->l = node->r = NULL;
            return node;
        }
    }
    return NULL;
}

void bstree_add(bstree *tree, char *key, int value) {
    if (tree == NULL) {
        return;
    }

    bstree *currNode = tree, *branchOfCurrNode = tree;

    while (branchOfCurrNode != NULL) {
        currNode = branchOfCurrNode;
        int d = strcmp(key, currNode->key);
        if (d < 0) {
            branchOfCurrNode = currNode->l;
        } else if (d > 0) {
            branchOfCurrNode = currNode->r;
        } else {
            return;
        }
    }

    bstree *newNode = bstree_create(key, value);
    int d = strcmp(key, currNode->key);
    if (d < 0) {
        currNode->l = newNode;
    } else if (d > 0) {
        currNode->r = newNode;
    }
}

bstree *bstree_lookup(bstree *tree, char *key) {
    while (tree != NULL) {
        int d = strcmp(key, tree->key);
        if (d < 0) {
            return bstree_lookup(tree->l, key);
        } else if (d > 0) {
            tree = bstree_lookup(tree->r, key);
        } else if (d == 0) {
            return tree;
        }
    }
    return NULL;
}

bstree *bstree_min(bstree *tree) {
    if (tree != NULL) {
        while (tree->l != NULL)
            tree = tree->l;
    }
    return tree;
}

bstree *bstree_max(bstree *tree) {
    if (tree != NULL) {
        while (tree->r != NULL)
            tree = tree->r;
    }
    return tree;
}

void bstree_free(bstree *tree) {
    if (tree != NULL) {
        if (tree->l != NULL) {
            bstree_free(tree->l);
        }
        if (tree->r != NULL) {
            bstree_free(tree->r);
        }
        free(tree);
    }
}

int isBST(bstree *node, bstree *minKey, bstree *maxKey) {
    if (node == NULL) return 1;
    if (strcmp(node->key, minKey->key) < 0 || strcmp(node->key, maxKey->key) > 0) return 0;
    return isBST(node->l, minKey, node) && isBST(node->r, node, maxKey);
}