#include <stdio.h>
#include <stdlib.h>

#include "structures/structures.h"

int test_queue() {
    printf("\n");
    printf("----------------------------------- \n");
    printf("Testing Queue Implementation. \n");

    printf("\n");
    printf("Initalizing Queue ... \n");
    
    queue * q = malloc(sizeof(queue));
    q->head = NULL;
    q->tail = NULL;
    
    if ( q == NULL) {
        printf("Could not allocate queue \n");
        return 1;
    }    
    
    printf("\n");
    
    int value;
    
    value = 0;
    printf("Enqueue %i ... \n", value);
    enqueue(q, value); print_queue(q);
    
    value = 1;
    printf("Enqueue %i ... \n", value);
    enqueue(q, value); print_queue(q);
    
    value = 2;
    printf("Enqueue %i ... \n", value);
    enqueue(q, value); print_queue(q);

    value = dequeue(q);
    printf("Dequeued %i ... \n", value); print_queue(q);

    value = 3;
    printf("Enqueue %i ... \n", value);
    enqueue(q, value); print_queue(q);
    
    value = 4;
    printf("Enqueue %i ... \n", value);
    enqueue(q, value); print_queue(q);
    
    value = 5;
    printf("Enqueue %i ... \n", value);
    enqueue(q, value); print_queue(q);

    value = dequeue(q);
    printf("Dequeued %i ... \n", value); print_queue(q);

    value = dequeue(q);
    printf("Dequeued %i ... \n", value); print_queue(q);

    value = dequeue(q);
    printf("Dequeued %i ... \n", value); print_queue(q);

    value = dequeue(q);
    printf("Dequeued %i ... \n", value); print_queue(q);

    value = dequeue(q);
    printf("Dequeued %i ... \n", value); print_queue(q);

    value = dequeue(q);
    printf("Dequeued %i ... \n", value); print_queue(q);
    
    
    printf("\n");

    return 0;    
    
}

int test_stack() {

    printf("\n");
    printf("----------------------------------- \n");
    printf("Testing Stack Implementation. \n");

    printf("\n");
    printf("Initalizing Stack with the Value 0 ... \n");

    stack * s = stack_create(0);
    print_stack(s);

    if (s == NULL) {
        printf("Could not allocate stack \n");
        return 1;
    }
    
    printf("\n");
    
    int values[] = { 1, 2, 3, 4, 5 };

    for (int i=0; i<5; i++) {
        printf("Pushing Value %i ... \n", values[i]);
        s = stack_push(s, values[i]);    
        print_stack(s);
    }

    printf("\n");

    for (int i=0; i<6; i++) {
        int pop_val;
        pop_val = stack_pop(s);
        s = s->next;
        printf("Poping %i ... \n", pop_val);
        print_stack(s);
    }
    
    printf("\n");

    return 0;
}

int test_llist() {
    

    printf("\n");
    printf("----------------------------------- \n");
    printf("Testing Linked List Implementation. \n");
    
    printf("\n");
    printf("Initalizing List with the Value 0 ... \n");
    llist* list = llist_create(0);
    
    if (list == NULL) {
        printf("Could not allocate list \n");
        return 2;
    }
    
    printf("\n");
    
    int val;
    
    val = 1;
    printf("Inserting Value %d ... \n", val);
    llist_insert(list, val);
    val = 2;
    printf("Inserting Value %d ... \n", val);
    llist_insert(list, val);
    val = 3;
    printf("Inserting Value %d ... \n", val);
    llist_insert(list, val);
    
    val = 4;
    printf("Inserting Value %d ... \n", val);
    llist_insert(list, val);

    print_llist(list);
    printf("\n");

    llnode* target = list->head;
    
    val = target->val;
    llist_remove_target(list, target);
    printf("Removed head value: %d ... \n", val);

    print_llist(list);
    printf("\n");

    target = list->tail;
    val = target->val;
    llist_remove_target(list, target);
    printf("Removed tail value: %d ... \n", val);

    print_llist(list);
    printf("\n");

    val = 5;
    printf("Inserting Value %d ... \n", val);
    llist_insert(list, val);

    print_llist(list);
    printf("\n");

    val = 5;
    llist_remove_value(list, val);
    printf("Removed Value %d ... \n", val);

    print_llist(list);

    printf("\n");

    int search_val = 2;
    printf("Searching List for the Value  %i ... \n", search_val);
    if ( llist_search(list, search_val) != NULL ) printf("%i, is in list\n\n", search_val);
    
    printf("Destroying the list ... \n");
    llist_destroy(list);
    
    printf("\n");
    
    return 0;
    
}

int test_hashtable() {
    
    printf("\n");
    printf("----------------------------------- \n");
    printf("Testing Hashtable Implementation. \n");


    printf("ht_create() \n");
    
    hashtable* ht = ht_create();

    printf("ht_insert(ht, 1) \n");
    ht_insert(ht, 1);
    printf("ht_insert(ht, 2) \n");
    ht_insert(ht, 2);
    printf("ht_insert(ht, 3) \n");
    ht_insert(ht, 3);
    printf("ht_insert(ht, 4) \n");
    ht_insert(ht, 4);
    printf("ht_insert(ht, 78) \n");
    ht_insert(ht, 78);
    printf("ht_insert(ht, 92) \n");
    ht_insert(ht, 92);
    printf("ht_insert(ht, 2390) \n");
    ht_insert(ht, 2390);
    printf("ht_insert(ht, 34423) \n");
    ht_insert(ht, 34423);
    printf("ht_insert(ht, 36) \n");
    ht_insert(ht, 36);
    printf("ht_insert(ht, 12) \n");
    ht_insert(ht, 12);
    
    print_hashtable(ht);

    printf("ht_search(ht, 36) \n");
    llnode* result = ht_search(ht, 36);
    if (result != NULL)
        printf("found %d \n\n", result->val);
    else
        printf("did not find %d \n\n", 36);
        
    printf("ht_remove(ht, 36) \n");
    ht_remove(ht, 36);

    printf("ht_remove(ht, 3) \n");
    ht_remove(ht, 3);

    print_hashtable(ht);

    printf("ht_destroy(ht) \n");
    
    ht_destroy(ht);
    
    printf("return \n");
    
    return 0;
}

int main(void) {
    
    test_hashtable();
    test_llist();
    test_stack();
    test_queue();
    
    return 0;
}