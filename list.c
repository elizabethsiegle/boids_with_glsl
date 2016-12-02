#include<stdlib.h>
#include <stdbool.h>
#include "list.h"

Node *head; //!headx
//what is num in this version of the linked list see functions getF, deleteNode, addF, and setF

Point *makePoint(float x, float y, float z) {
  Point* newp = (Point*)malloc(sizeof(Point));
  newp->x = x;
  newp->y = y;
  newp->z = z;
}

Node *makeNode(Point p1, Point p2) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  newNode->position = p1;
  newNode->velocity = p2;
  newNode->next = NULL;
}

void push(Node* newNode) {
    newNode->next = head;
    head = newNode;
}

//data ugh
void deleteNode(Node *nodeToDelete) {
  if(head == nodeToDelete) {
    if(head->next == NULL) {
      printf("Trying to delete null node!");
      return;
    }
    head->position = head->next->position;
    nodeToDelete = head->next;
    head->next = head->next->next;
    free(nodeToDelete);
    printf("Deleted first boid!");
    return;
  }

  //Not first node
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

//*******Print******//
void printList() {
  while (head != NULL) {
    printf("%d", head);
    head = head->next;
  } //while
  printf("\n");
}

float valF(Node *n, int index) {
  float temp = 0;
  for(int i = 0; i < index; i++) {
   if(n != NULL) {
     temp =  n->position.x;
        n = n->next;
    } else {
      printf("list empty! \n");
    }
   }
   return temp;
}

void addF(int index, float addVal) {
  //add value to a give index
  struct node* newVal = head;
  for (int i=0; newVal!=NULL && i<index; i++) {
     newVal = newVal->next;
  }
  newVal->position.x += addVal;
  newVal->position.y += addVal;
  newVal->position.z += addVal;
  newVal->velocity.x += addVal;
  newVal->velocity.y += addVal;
  newVal->velocity.z += addVal;
}

//*a => value of a/defreferemced a
//a => where *a is located aka the pointer
//&a => pass by reference mem location
//-> the next node that is point too
