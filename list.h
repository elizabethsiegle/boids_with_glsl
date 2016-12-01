#ifndef LIST_H
#define LIST_H
#include "common.hpp"
typedef struct point {
  float x;
  float y;
  float z;
} Point;

typedef struct node {
  Point position;
  Point velocity;
  struct node *next;
  struct node *prev;
} Node;

void push(Node* newNode);
//void deleteList(Node** head, Point *p);
void printList();
void addF(int index, float addVal);
GLfloat valF(Node *n, int index);
//void multiF(struct node **head, int index, float multiVal);
void deleteNode(Node *nodeToDelete); //head global

// Node* makeNode();
Node *makeNode(Point p1, Point p2);
Node* makeList();
Point *makePoint(float x, float y, float z);
//void deleteNode(Node *head, Node *nodeToDelete);

#endif
