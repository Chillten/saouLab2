#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include "bstree.h"
#include "hashtab.h"
#include "get_time.c"

const int MAX_WORDS = 350000;
const int STEP = 10000;
const int COUNT_OF_SEARCH = 100;

extern int USE_JENK;

int f(bstree *tree) {
    if (tree == NULL)
        return 1;
    int t = 0;
    if (tree->r != NULL)
        t += f(tree->r);
    if (tree->l != NULL)
        t += f(tree->l);
    return t + 1;
}

int getrand(int min, int max) {
    return (double) rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

int main() {
    srand(time(NULL));

    double timeTable[MAX_WORDS / STEP + 1];
    double t;
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int i = 0;
    char *words[MAX_WORDS];

    fp = fopen("Words/EnglishWordsShuted.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    while ((getline(&line, &len, fp)) != -1 && i < MAX_WORDS) {
        line[strlen(line) - 1] = '\0';
        words[i] = malloc(strlen(line) + 1);
        strcpy(words[i++], line);
    }

//    bstree *tree = bstree_create(words[0], 0), *node;
//
//    for(i = 1; i < MAX_WORDS; i++){
//        int ti = (i-1) / STEP;
//        bstree_add(tree, words[i], i);
////        hashtab_add(hashtab, words[i], i);
//        if(i % STEP == 0){
//            timeTable[ti] = 0;
//            for(int j = 0; j < COUNT_OF_SEARCH; j++){
//                int r = getrand(1, i);
//                t = get_time();
//                node = bstree_lookup(tree, words[r]);
////                node = bstree_min(tree);
////                node = hashtab_lookup(hashtab, words[r]);
//                timeTable[ti] += get_time() - t;
//               if(strcmp(node->key, words[r]) != 0){
//                   printf("aAAAAAAAAAAAAAA!!!\n");
//                }
//            }
//            timeTable[ti] /= COUNT_OF_SEARCH;
//            printf("%d %.9lf\n", i, timeTable[ti]);
//        }
//    }

    listnode *hashtab[HASHTAB_SIZE], *node;
    hashtab_init(hashtab);
    double timeTableExtendet[2][MAX_WORDS / STEP + 1];

    listnode *hashtabJenk[HASHTAB_SIZE], *nodeJenk;
    hashtab_init(hashtabJenk);

    for (i = 0; i < MAX_WORDS; i++) {
        int ti = (i - 1) / STEP;
//        bstree_add(tree, words[i], i);
        USE_JENK = 0;
        hashtab_add(hashtab, words[i], i);
        USE_JENK = 1;
        hashtab_add(hashtabJenk, words[i], i);
        if (i % STEP == 0 && i != 0) {
            timeTableExtendet[0][ti] = timeTableExtendet[1][ti] = 0;
            for (int j = 0; j < COUNT_OF_SEARCH; j++) {
                int r = getrand(0, i);

                USE_JENK = 0;
                t = get_time();
                node = hashtab_lookup(hashtab, words[r]);
                timeTableExtendet[0][ti] += get_time() - t;
                if (strcmp(node->key, words[r]) != 0) {
                    printf("aAAAAAAAAAAAAAA!!!\n");
                }

                USE_JENK = 1;
                t = get_time();
                nodeJenk = hashtab_lookup(hashtabJenk, words[r]);
                timeTableExtendet[1][ti] += get_time() - t;
                if (strcmp(nodeJenk->key, words[r]) != 0) {
                    printf("aAAAAAAAAAAAAAA!!!\n");
                }
            }
            timeTableExtendet[0][ti] /= COUNT_OF_SEARCH;
            timeTableExtendet[1][ti] /= COUNT_OF_SEARCH;

            int colCountDef = 0, colCountJen = 0;
            for(int k = 0; k < HASHTAB_SIZE; k++){
                if(hashtab[k] == NULL) colCountDef++;
                if(hashtabJenk[k] == NULL) colCountJen++;
            }

            printf("%d %.9lf %d %.9lf %d \n", i, timeTableExtendet[0][ti],colCountDef,timeTableExtendet[1][ti], colCountJen);
        }
    }


    //printf("Size of tree = %d\n", f(tree));
//    bstree_free(tree);
    hashtab_free(hashtab);
    hashtab_free(hashtabJenk);
    exit(EXIT_SUCCESS);
}