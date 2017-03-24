//
// Created by chillten on 24.03.17.
//

#include <wchar.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include "hashtab.h"

int USE_JENK = 0;

const u_int32_t HASHTAB_SIZE = 41;

u_int32_t jenkins_one_at_a_time_hash(char *key, size_t len) {
    u_int32_t hash, i;
    for (hash = i = 0; i < len; ++i) {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

u_int32_t hashtab_hash(char *key) {
    if (USE_JENK) {
        return jenkins_one_at_a_time_hash(key, strlen(key)) % HASHTAB_SIZE;
    } else {
        u_int32_t h = 0;
        char *p;
        for (p = key; *p != '\0'; p++) {
            h = h * HASHTAB_MUL + (u_int32_t) *p;
        }
        return h % HASHTAB_SIZE;
    }
}

void hashtab_init(listnode **hashtab) {
    int i;
    for (i = 0; i < HASHTAB_SIZE; i++) {
        hashtab[i] = NULL;
    }
}

void hashtab_add(listnode **hashtab, char *key, int value) {
    listnode *node;
    int index = hashtab_hash(key);
    int isExist = 0;

    for (listnode *pointer = hashtab[index]; pointer != NULL && isExist == 0; pointer = pointer->next) {
        if (strcmp(pointer->key, key) == 0) {
            isExist = 1;
            pointer->value = value;
        }
    }

    if (!isExist) {
        node = malloc(sizeof(*node));
        if (node != NULL) {
            node->key = key;
            node->value = value;
            node->next = hashtab[index];
            hashtab[index] = node;
        }
    }
}

struct listnode *hashtab_lookup(listnode **hashtab, char *key) {
    int index = hashtab_hash(key);
    for (listnode *node = hashtab[index]; node != NULL; node = node->next) {
        if (strcmp(node->key, key) == 0) {
            return node;
        }
    }
    return NULL;
}

void hashtab_delete(listnode **hashtab, char *key) {
    int index;
    listnode *p, *prev = NULL;
    index = hashtab_hash(key);
    for (p = hashtab[index]; p != NULL; p = p->next) {
        if (strcmp(p->key, key) == 0) {
            if (prev == NULL) {
                hashtab[index] = p->next;
            } else {
                prev->next = p->next;
            }
            free(p);
            return;
        }
        prev = p;
    }
}