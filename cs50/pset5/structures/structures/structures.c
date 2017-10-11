#include <stdlib.h>
#include <stdio.h>

#include "structures.h"

hashtable* ht_create() {
    
    // malloc hashtable
    hashtable* ht = malloc(sizeof(hashtable));
    
    // initalize container entries to NULL
    for (int i=0; i < HT_MAX_CAPACITY; i++)
        ht->container[i] = NULL;
 
    return ht;
    
}

int ht_hash(int value) {
    
    // simplified temp implementation
    return value % HT_MAX_CAPACITY;
    
}

void ht_insert(hashtable* ht, int value) {
    
    int hash = ht_hash(value);
    
    // check if llist exists at this hash, if not create it
    if (ht->container[hash] == NULL) 
        ht->container[hash] = llist_create(value);
    
    // else insert value into the existing llist
    else llist_insert(ht->container[hash], value);
    
}

llnode* ht_search(hashtable* ht, int value) {
    
    int hash = ht_hash(value);
    
    if (ht->container[hash] == NULL) 
        return NULL;
    else
        return llist_search(ht->container[hash], value);
    
}

void ht_remove(hashtable* ht, int value) {
    
    int hash = ht_hash(value);
    
    llist* list = ht->container[hash];
    
    if (list == NULL) 
        return;
    else
        llist_remove_value(list, value);
        
    // If list is empty, destroy it and set container entry to NULL
    if (list->head == NULL) {
        llist_destroy(list);
        ht->container[hash] = NULL;
    }
}

void ht_destroy(hashtable *ht) {
    
    for (int i = 0; i<HT_MAX_CAPACITY; i++) {
        if (ht->container[i] != NULL)
            llist_destroy(ht->container[i]);
    }
    
    free(ht);
    
}

llist* llist_create(int val) {
    
    // malloc space for list head
    llist* list = malloc(sizeof(llnode));
    
    // malloc space for new node
    llnode* node = malloc(sizeof(llnode));

    // check to make sure we didn't run out of memory
    if ( list == NULL || node == NULL ) return NULL; 

    // initalize list head and tail
    list->head = node;
    list->tail = node;

    // initialize the nodes val field
    node->val = val;
    
    // initialize the nodes next field
    node->next = NULL;
    node->prev = NULL;
    
    // return a pointer to the newly created node
    return list;
}


llnode* llist_search(llist* list, int val) {
    
    // create a traversal pointer pointing to the lists head
    llnode* trav = list->head;
    
    // while traveral is not null, check node for value then point to next node
    do {
        
        if(trav->val == val) return trav;
        trav = trav->next;
        
    } while(trav != NULL);
    
    return NULL;
}

void llist_insert(llist* list, int val) {
    
    // malloc space for new node
    llnode* node = malloc(sizeof(llnode));
    
    // check that we didnt run out of memory
    if(node == NULL) return;
    
    node->val = val;
    node->next = NULL;
    node->prev = NULL;
    
    // insert the node at the beginning of the list
    node->next = list->head;

    // fix the prev pointer of the old head of the linked list
    list->head->prev = node;
    
    // update head
    list->head = node;
    
    
}

void llist_remove_target(llist* list, llnode* target) {
    /*
    update surrounding pointers to skip over target
    update list head and tail accordinly
    */
    
    if ( target == NULL || list == NULL ) return;
    
    if (target->next != NULL && target->prev != NULL) {
        target->prev->next = target->next;
        target->next->prev = target->prev;

    } else if (target->next != NULL && target->prev == NULL) {
        // assert, target is list head
        target->next->prev = NULL;
        list->head = target->next;
        
    } else if (target->next == NULL && target->prev != NULL) {
        // assert, target is list tail
        target->prev->next = NULL;
        list->tail = target->prev;
        
    } else {
        // assert, this is the only node in the list
        list->head = NULL;
        list->tail = NULL;
    
    }
    
    // free target
    free(target);
    
}

void llist_remove_value(llist* list, int value) {

    llnode* target = llist_search(list, value);
    
    if (target != NULL && target->val == value)
    
        llist_remove_target(list, target);

    else
        
        printf("llist_search did not return an appropriate target \n");

}


void llist_destroy(llist* list) {

    llnode* head = list->head;

    // if you've reached a null pointer, free header and stop
    if (head == NULL) {
        free(list);
        return;
    }
    
    // update pointer to new head
    list->head = head->next;
    
    // delete the rest of the list
    llist_destroy(list);
    
    // free the current node
    free(head);
}

void print_llist(llist* list) {

    
    if (list->head == NULL || list->tail == NULL) {
        printf("this appears to be an empty list \n");
        return;
    }
    
    llnode* trav = list->head;
    
    int count = 0;

    
    while(trav != NULL) {
        
        printf("[");
        if (trav->prev == NULL) printf("\\|");
        else printf("*|");
        printf("%d|", trav->val);
        if (trav->next == NULL) printf("\\");
        else printf("*");        
        printf("] ");

        trav = trav->next;
        count++;
        if (count>99) {
            printf (" Something went wrong... ");
            break;
        }
    }    
    
    printf(" list size: %d", count);

}


// initalize queue
queue* queue_create() {
	
	queue * q = malloc(sizeof(queue));
    q->head = NULL;
    q->tail = NULL;
    
    return q;
}

// add value to queue
int enqueue(queue* q, int val) {
	
	// malloc new node
	queueNode* node = malloc(sizeof(queueNode));

    if ( node == NULL) return 1;

	// capture value to return
    node->val = val;

	// set node next pointer to NULL
	node->next = NULL;
	
	// set node prev pointer to the tail if it exists
	if (q->tail != NULL) {
	
		// update prev pointer to tail
		node->prev = q->tail;
		// update tail next to node
		q->tail->next = node;

	}
	
	// move the tail pointer to the newly created node
	q->tail = node;
	
	// if queue was empty, head is not pointing to anything
	// move the head pointer to the newly created node
	if (q->head == NULL ) q->head = node;
	
	// success
	return 0;
}

//remove and return oldest value from queue
int dequeue(queue *q) {

	// check if queue has any values
	if (q->head == NULL) return -1;
	
	// store value of head
	int val = q->head->val;

	// traverse to second element (if it exists)
	queueNode *trav = NULL;
	if (q->head->next != NULL)
		trav = q->head->next;
		
	// free head from the queue
	free (q->head);
	
	// move head pointer to the former second element
	q->head = trav;
	
	// move prev pointer to NULL
	if(q->head != NULL)
	    q->head->prev = NULL;
	
	return val;
}


stack* stack_create(int val) {
    
    // malloc for a new stack node
    stack* node = malloc(sizeof(stack));
    
    if (node == NULL) return NULL;
    
    // initalize node
    node->val = val;
    node->next = NULL;
    
    // return node pointer
    return node;
    
}

stack* stack_push(stack *s, int val) {

    if (s == NULL) return NULL;
    
    // malloc new node
    stack* top = stack_create(val);
    
    if (top == NULL) return NULL;
    
    // update new node next to s
    top->next = s;
    
    // return pointer to new node
    return top;
    
}

int stack_pop(stack *s) {
    
    if (s == NULL) return -1;
    
    // capture head val
    int val = s->val;
    
    // free head
    free(s);
    
    // return val
    return val;
    
}

void print_stack(stack* s) {
    
    if (s == NULL) return;
    
    stack* top = s;
    
    int i = 0;
    
    printf("Stack: ");
    
    while(top != NULL) {
        
        if (top->next != NULL )
            printf("[%i:*%i]", top->val, top->next->val );
        else 
            printf("[%i:\\]", top->val);
            
        top = top->next;
        i++;
    }    
    
    printf("\n");
    
}

void print_queue(queue* q) {
    
    if (q == NULL) return;
    
    if (q->tail == NULL || q->head == NULL ) {
        printf("[\\:\\]\n");
        return;
    }
    
    int i = 0;
    
    queueNode *trav = q->head;
    
    printf("Queue: ");
    
    while(trav != NULL) {
        
        if (trav->next != NULL )
            printf("[%i:*%i]", trav->val, trav->next->val );
        else 
            printf("[%i:\\]", trav->val);
            
        trav = trav->next;
        i++;
    }    
    
    printf("\n");
    
}

void print_hashtable(hashtable* ht) {
    
    printf("Hashtable results: \n");
    
    for (int i = 0; i<HT_MAX_CAPACITY; i++) {
        if (ht->container[i] == NULL)
            printf("[ ]");
        else
            print_llist(ht->container[i]);
        printf("\n");
    }
    
    printf("\n");
}