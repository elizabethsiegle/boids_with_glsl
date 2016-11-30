#include<stdlib.h>
#include <stdbool.h>
#include "list.h"

extern Node* head; //!headx

Point *makePoint(float x, float y, float z) {
  Point* newp = (Point*)malloc(sizeof(Point));
  newp->x = x;
  newp->y = y;
  newp->z = z;
}

Node *makeNode(Point p1, Point p2, int ind) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  newNode->position = p1;
  newNode->velocity = p2;
  newNode->index = ind;
  newNode->next = NULL;
}

void push(Node* newNode) {
    newNode->next = head;
    head = newNode;
}

//****Delete list*****//
// void deleteList(Node** head) {
//    printf("\nlist deleted!\n");
//    struct node* here = *head;
//    struct node* next;
//
//    while(here != NULL) {
//        next = here->next;
//        //free node
//        free(here);
//        here = next;
//        }
//    *head = NULL;
// }

//data ugh
void deleteNode(Node *nodeToDelete) {
  if(head == nodeToDelete) {
    if(head->next == NULL) {
      return;
    }
    head->data = head->next->data;
    nodeToDelete = head->next;
    head->next = head->next->next;
    free(nodeToDelete);
    return;
  }//if
  //find prev node if !first node
  Node *prev = head;
  while(prev->next != NULL && prev->next != nodeToDelete) {
    prev = prev->next;

    //check if node really exists in LL
    if(prev->next == NULL) {
      printf("\n given node is not in LL");
      return;
    } //if

    //remove node from LL
    prev->next = prev->next->next;

    //free mem
    free(nodeToDelete);
    return;
  }
}

//*******Print******//
void printList() {
  while (head != NULL) {
    printf("%d", head->data);
    head = head->next;
  } //while
  printf("\n");
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
