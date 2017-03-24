//
// Created by chillten on 24.03.17.
//

#ifndef SAOULAB2_HASHTAB_H
#define SAOULAB2_HASHTAB_H

#define HASHTAB_MUL 31

const u_int32_t HASHTAB_SIZE;

struct listnode {
    char *key;
    int value;
    struct listnode *next;
};

typedef struct listnode listnode;

u_int32_t hashtab_hash(char *key);

void hashtab_init(listnode **hashtab);

void hashtab_add(listnode **hashtab, char *key, int value);

listnode *hashtab_lookup(listnode **hashtab, char *key);

void hashtab_delete(listnode **hashtab, char *key);

#endif //SAOULAB2_HASHTAB_H
