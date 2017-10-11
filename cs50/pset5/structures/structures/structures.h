#include <stdbool.h>

enum {HT_MAX_CAPACITY=24};

// hashtable structures
typedef struct hashtable {
    struct llist* container[HT_MAX_CAPACITY];
} hashtable;

// linked list structures
typedef struct llist {
	struct llnode* head;
	struct llnode* tail;
} llist;

typedef struct llnode {
	int val;
	struct llnode* next;
	struct llnode* prev;
} llnode;

// queue structures
typedef struct queueNode {
	int val;
	struct queueNode *prev;
	struct queueNode *next;
} queueNode;

typedef struct queue {
	queueNode *head;
	queueNode *tail;
} queue;

// stack algorithms
typedef struct stack {
    int val;
    struct stack* next;
} stack;

// hashtable algorithms
hashtable* ht_create();
int ht_hash(int value);
void ht_insert(hashtable* ht, int value);
struct llnode* ht_search(hashtable* ht, int value);
void ht_remove(hashtable* ht, int value);
void ht_destroy(hashtable *ht);

// llinked list algorithms
struct llist* llist_create(int val);
void llist_insert(llist* list, int val);
struct llnode* llist_search(llist* list, int val);
void llist_remove_target(llist* list, llnode* target);
void llist_remove_value(llist* list, int value);
void llist_destroy(llist* list);

// queue algorithms
struct queue* queue_create();
int enqueue(queue* q, int val);
int dequeue(queue *q);

// stack algorithms
struct stack* stack_create(int val);
struct stack* stack_push(stack *s, int val);
int stack_pop(stack *s);

// debugging
void print_hashtable(hashtable* ht);
void print_llist(llist* list);
void print_stack(stack* s);
void print_queue(queue* q);
