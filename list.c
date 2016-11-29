#include<stdlib.h>
#include <stdbool.h>
#include "list.h"

void push(Node** head, void *new1, size_t dataSize) {
    //Memory for node
    Node* newNode = (struct node*)malloc(sizeof(struct node));
    //new node
    newNode->num  = malloc(dataSize);
    newNode->next = (*head);
    for(int i = 0; i < dataSize; i++) {
        *(char *)(newNode->num + i) = *(char *)(new1);
    }
    (*head) = newNode;
}

//****Delete list*****//
void deleteList(Node** head) {
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

void addF(struct node **head, int index, int totIndex, float addVal) {
  //add value to a give index
  struct node* newVal = *head;
  index = totIndex - index;
  for (int i=0; newVal!=NULL && i<index; i++) {
     newVal = newVal->next;
  }
  *((float *)(newVal->num)) += addVal;
}

//*********multiply******//
void multiF(struct node **head, int index, int totIndex, float multiVal) {
  //add value to a give index
  struct node* newVal = *head;
  index = totIndex - index;
  for (int i=0; newVal!=NULL && i<index; i++) {
     newVal = newVal->next;
  }
  *((float *)(newVal->num)) *= multiVal;

}

//*********divide******//
void diviF(struct node **head, int index, int totIndex, float diviVal) {
  //add value to a give index
  struct node* newVal = *head;
  index = totIndex - index;
  for (int i=0; newVal!=NULL && i<index; i++) {
     newVal = newVal->next;
  }
  *((float *)(newVal->num)) /= diviVal;

}

//*********sub******//
void subF(struct node **head, int index, int totIndex, float subVal) {
  //add value to a give index
  struct node* newVal = *head;
  index = totIndex - index;
  for (int i=0; newVal!=NULL && i<index; i++) {
     newVal = newVal->next;
  }

  *((float *)(newVal->num)) -= subVal;

}

//*********set******//
void setF(struct node **head, int index, int totIndex, float setVal) {
  //add value to a give index
  struct node* newVal = *head;
  index = totIndex - index;
  // for (int i=0; newVal!=NULL && i<index; i++) {
  //    newVal = newVal->next;
  // }

  *((float *)(newVal->num)) = setVal;

}


//*a => value of a/defreferemced a
//a => where *a is located aka the pointer
//&a => pass by reference mem location
//-> the next node that is point too
