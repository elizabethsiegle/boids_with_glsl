#ifndef LIST_H
#define LIST_H
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct point {
  float x;
  float y;
  float z;
} Point;

typedef struct node {
  Point position;
  Point velocity;
  int index;
  struct node *next;
  struct node *prev;
} Node;

void push(Node* newNode);
//void deleteList(Node** head, Point *p);
void printList();
void printI(void *n);
void printD(void *f);
void printB(void *m);
int vall(Node *node, int index, int totIndex);
double valD(Node *node, int index, int totIndex);
bool valB(Node *node, int index, int totIndex);
void addF(int index, float addVal);
GLfloat valF(Node *n, int index);
double valD(struct node *node, int index, int totIndex);
int valI(struct node *node, int index, int totIndex);
//void multiF(struct node **head, int index, float multiVal);
void printFloat(void *k);
void deleteNode(Node *nodeToDelete); //head global
// Node* makeNode();
Node *makeNode(Point p1, Point p2, int ind);
Node* makeList();
Point *makePoint(float x, float y, float z);
//void deleteNode(Node *head, Node *nodeToDelete);

#endif
