#ifndef HASHTBL_H_INCLUDE_GUARD
#define HASHTBL_H_INCLUDE_GUARD

#include <stdlib.h>

typedef size_t hash_size;

struct hashnode_s
{
	char *key;
	void *data;
	int scope;
	char *value;
	int line_no;
	struct hashnode_s *next;
};

typedef struct hashtbl
{
	hash_size size;
	struct hashnode_s **nodes;
	hash_size (*hashfunc)(const char *);
} HASHTBL;

HASHTBL *hashtbl_create(hash_size size, hash_size (*hashfunc)(const char *));
void hashtbl_destroy(HASHTBL *hashtbl);
int hashtbl_insert(HASHTBL *hashtbl, const char *key, void *data, int scope, char *value, int line_no);
int hashtbl_remove(HASHTBL *hashtbl, const char *key, int scope);
void *hashtbl_get(HASHTBL *hashtbl, int scope);
void *hashtbl_update(HASHTBL *hashtbl, const char *key, char *value);
void *print_table(HASHTBL *hashtbl);

#endif
