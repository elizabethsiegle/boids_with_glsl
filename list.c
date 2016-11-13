#include<stdlib.h>
#include <stdbool.h>
#include "list.h"

// struct node {
//     void  *num;
//     struct node *next;
//     struct node *prev;
// };

void push(struct node** head, void *newLol, size_t dataSz) {
    //Memory for node
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    //new node
    newNode -> num  = malloc(dataSz);
    newNode -> next = (*head);
    for(int i = 0; i < dataSz; i++) {
        *(char *)(newNode->num + i) = *(char *)(newLol + i);
    }
    (*head) = newNode;
}

//****Delete list*****//
void deleteList(struct node** head) {
   printf("\nlist deleted!\n");
   struct node* here = *head;
   struct node* next;

   while(here != NULL) {
       next = here->next;
       //free node
       free(here);
       here = next;
       }
   *head = NULL;
}

void deleteNode(struct node **head, int index, int totIndex) {
   index = totIndex - index;
   struct node* temp = *head;
   //if it is the head
   for (int i=0; temp!=NULL && i<index-1; i++) {
         temp = temp->next;
   }
   struct node *next = temp->next->next;
   free(temp->next);
   temp->next = next;
}

//*******Print******//
void printList(struct node *node, void (*fpoint)(void *)) {
  //prints backwards
  // for(node; node != NULL; node = node->next) {
  while(node != NULL) {
       (*fpoint)(node->num);
       node = node->next;
      }
}

//integer
void printI(void *n) {
   printf(" %d", *(int *)n);
}

//double
void printD(void *f) {
   printf(" %f", *(double *)f);
}

//bool
void printB(void *m) {
   printf(" %d", *(bool *)m);
}

//bool
void printFloat(void *k) {
   printf(" %f", *(float *)k);
}


//*********Return******//
int valI(struct node *node, int index, int totIndex) {
    int temp = 0;
    index = totIndex - index + 1;
    for(int i = 0; i < index; i++) {
      if(node != NULL) {
        temp =  *((int *)(node->num));
        node = node->next;
       } else {
        printf("list empty! \n");
      }
    }
    return temp;
}

double valD(struct node *node, int index, int totIndex) {
  //double valD(struct node *node) {
  double temp = 0;
  index = totIndex - index + 1;
  for(int i = 0; i < index; i++) {
    if(node != NULL) {
      temp =  *((double *)(node->num));
        node = node->next;
    } else {
      printf("list empty! \n");
    }
  }
    return temp;
}

bool valB(struct node *node, int index, int totIndex) {
  bool temp = 0;
  index = totIndex - index + 1;
  for(int i = 0; i < index; i++) {
   if(node != NULL) {
     temp =  *((bool *)(node->num));
        node = node->next;
    } else {
      printf("list empty! \n");
    }
   }
    return temp;
}

float valF(struct node *node, int index, int totIndex) {
  float temp = 0;
  index = totIndex - index + 1;
  for(int i = 0; i < index; i++) {
   if(node != NULL) {
     temp =  *((float *)(node->num));
        node = node->next;
    } else {
      printf("list empty! \n");
    }
   }
    return temp;
}

//*a => value of a/defreferemced a
//a => where *a is located aka the pointer
//&a => pass by reference mem location
//-> the next node that is point too

//*a => value of a/defreferenced a
//a => where *a is located aka the pointer
//&a => pass by reference mem location

/* void append(Node *n, Node *t) { */
/*   Node* tempCopy = t->prev; */
/*   tempCopy->next = n; */
/*   n->prev = tempCopy; */
/*   n->next = t; */
/*   t->prev = n; */
/* } //append */

/* void freeList(Node* h) { */
/*     while(h->next != NULL) { */
/* 	    Node* curr = h->next; */
/* 	    h->next = h->next->next; */
/* 	    freeNode(curr); */
/*     } //while */
/*     freeNode(h); */
/* } //freeList */
