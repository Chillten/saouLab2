//
// Created by chillten on 24.03.17.
//

#ifndef SAOULAB2_BSTREE_H
#define SAOULAB2_BSTREE_H

typedef struct bstree {
    int value;
    char *key;
    struct bstree *l, *r;
} bstree;

bstree *bstree_create(char *key, int value);

void bstree_add(bstree *tree, char *key, int value);

bstree *bstree_lookup(bstree *tree, char *key);

bstree *bstree_min(bstree *tree);

bstree *bstree_max(bstree *tree);

void bstree_free(bstree *tree);

int isBST(bstree *node, bstree *minKey, bstree *maxKey);

#endif //SAOULAB2_BSTREE_H
