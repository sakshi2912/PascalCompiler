/* The authors of this work have released all rights to it and placed it
in the public domain under the Creative Commons CC0 1.0 waiver
(http://creativecommons.org/publicdomain/zero/1.0/).

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Retrieved from: http://en.literateprograms.org/Hash_table_(C)?oldid=19638
*/

#include "hashtbl.h"

#include <string.h>
#include <stdio.h>

extern FILE *yyin;

extern FILE *yyout;

static char *mystrdup(const char *s)
{
	char *b;
	if (!(b = malloc(strlen(s) + 1)))
		return NULL;
	strcpy(b, s);
	return b;
}

static hash_size def_hashfunc(const char *key)
{
	hash_size hash = 0;

	while (*key)
		hash += (unsigned char)*key++;

	return hash;
}

HASHTBL *hashtbl_create(hash_size size, hash_size (*hashfunc)(const char *))
{
	HASHTBL *hashtbl;

	if (!(hashtbl = malloc(sizeof(HASHTBL))))
		return NULL;

	if (!(hashtbl->nodes = calloc(size, sizeof(struct hashnode_s *))))
	{
		free(hashtbl);
		return NULL;
	}

	hashtbl->size = size;

	if (hashfunc)
		hashtbl->hashfunc = hashfunc;
	else
		hashtbl->hashfunc = def_hashfunc;

	return hashtbl;
}

void hashtbl_destroy(HASHTBL *hashtbl)
{
	hash_size n;
	struct hashnode_s *node, *oldnode;

	for (n = 0; n < hashtbl->size; ++n)
	{
		node = hashtbl->nodes[n];
		while (node)
		{
			free(node->key);
			oldnode = node;
			node = node->next;
			free(oldnode);
		}
	}
	free(hashtbl->nodes);
	free(hashtbl);
}

int hashtbl_insert(HASHTBL *hashtbl, const char *key, void *data, int scope, char *value)
{
	struct hashnode_s *node;
	hash_size hash = hashtbl->hashfunc(key) % hashtbl->size;

	//printf("HASHTBL_INSERT(): KEY = %s, HASH = %ld,  \tDATA = %s, SCOPE = %d\n", key, hash, (char *)data, scope);

	node = hashtbl->nodes[hash];
	while (node)
	{
		if (!strcmp(node->key, key) && (node->scope == scope))
		{
			node->data = data;
			return 0;
		}
		node = node->next;
	}

	if (!(node = malloc(sizeof(struct hashnode_s))))
		return -1;
	if (!(node->key = mystrdup(key)))
	{
		free(node);
		return -1;
	}
	node->data = data;
	node->value = mystrdup(value);
	node->scope = scope;
	node->next = hashtbl->nodes[hash];
	hashtbl->nodes[hash] = node;

	return 0;
}

int hashtbl_remove(HASHTBL *hashtbl, const char *key, int scope)
{
	struct hashnode_s *node, *prevnode = NULL;
	hash_size hash = hashtbl->hashfunc(key) % hashtbl->size;

	node = hashtbl->nodes[hash];
	while (node)
	{
		if ((!strcmp(node->key, key)) && (node->scope == scope))
		{
			free(node->key);
			if (prevnode)
				prevnode->next = node->next;
			else
				hashtbl->nodes[hash] = node->next;
			free(node);
			return 0;
		}
		prevnode = node;
		node = node->next;
	}

	return -1;
}

void *hashtbl_get(HASHTBL *hashtbl, int scope)
{
	int rem;
	hash_size n;
	struct hashnode_s *node, *oldnode;

	for (n = 0; n < hashtbl->size; ++n)
	{
		node = hashtbl->nodes[n];
		while (node)
		{
			if (node->scope == scope)
			{
				//printf("HASHTBL_GET():\tSCOPE = %d, KEY = %s,  \tDATA = %s\n", node->scope, node->key, (char *)node->data);
				oldnode = node;
				node = node->next;
				rem = hashtbl_remove(hashtbl, oldnode->key, scope);
			}
			else
				node = node->next;
		}
	}

	//if (rem == -1)
	//	printf("\t\t\t\t\tHASHTBL_GET():\tThere are no elements in the hash table with this scope!\n\t\tSCOPE = %d\n", scope);

	return NULL;
}

void *print_table(HASHTBL *hashtbl)
{
	int rem;
	hash_size n;
	struct hashnode_s *node, *oldnode;
	printf("Symbol table\n\n");
	printf("KEY\t\tDATATYPE\tVALUE\tSCOPE\n-------------------------------------------\n\n");
	for (n = 0; n < hashtbl->size; ++n)
	{
		node = hashtbl->nodes[n];
		while (node)
		{

			printf("%s\t\t%s\t\t%s\t%d\n", node->key, (char *)node->data, (char *)node->value, node->scope);
			oldnode = node;
			node = node->next;
		}
	}
}

//if (rem == -1)
//	printf("\t\t\t\t\tHASHTBL_GET():\tThere are no elements in the hash table with this scope!\n\t\tSCOPE = %d\n", scope);
void *hashtbl_update(HASHTBL *hashtbl, const char *key, char *value)
{
	int rem;
	hash_size n;
	struct hashnode_s *node, *oldnode;

	for (n = 0; n < hashtbl->size; ++n)
	{
		node = hashtbl->nodes[n];
		while (node)
		{
			if (strcmp(node->key, key) == 0)
			{
				//oldnode = node;
				node->value = mystrdup(value);
				//printf("HASHTBL_GET():\tSCOPE = %d, KEY = %s,  \tDATA = %s\n", node->scope, node->key, (char *)node->data);
				return NULL;
				//node = node->next;
			}
			else
				node = node->next;
		}
	}
	if (rem == -1)
		printf("\t\t\t\t\tHASHTBL_GET():\tThere are no elements in the hash table with this key");

	return NULL;
}

/*
void main()
{
	HASHTBL *symbol;
	symbol = hashtbl_create(16, NULL);
	hashtbl_insert(symbol, "x", "integer", 0, "20");
	print_table(symbol);
	hashtbl_update(symbol, "x", "30");
	print_table(symbol);
}*/