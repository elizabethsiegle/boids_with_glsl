#ifndef LIST_H
#define LIST_H
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct node {
  void *num;
  struct node *next;
} Node;

void push(Node** head, void *new1, size_t dataSize);
void deleteList(Node** head);
void printList(Node *node, void (*fpoint)(void*));
void printI(void *n);
void printD(void *f);
void printB(void *m);
int vall(Node *node, int index, int totIndex);
double valD(Node *node, int index, int totIndex);
bool valB(Node *node, int index, int totIndex);
void addF(struct node **head, int index, int totIndex, float addVal);
float valF(struct node *node, int index, int totIndex);
double valD(struct node *node, int index, int totIndex);
int valI(struct node *node, int index, int totIndex);
void multiF(struct node **head, int index, int totIndex, float multiVal);
void printFloat(void *k);
void deleteNode(struct node **head, int index, int totIndex);
void push(Node** head, void *new1, size_t dataSize);
Node* makeNode();
Node* makeList();

#endif
