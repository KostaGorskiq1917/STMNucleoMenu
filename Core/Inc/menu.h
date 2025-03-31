/*
 * menu.h
 *
 *  Created on: Mar 24, 2025
 *      Author: drebniqv
 */
#ifndef MENU_H
#define MENU_H

#define MAX_NODES 100      // Max nodes in the tree
#define MAX_CHILDREN 10    // Max children per nod

#include <stdio.h>
#include <stdlib.h>   // For `size_t` (used implicitly by `malloc`/`realloc`)
#include <string.h>
#include "menu.h"
#include "LCDControl.h"
#include "stm32l1xx_it.h"

// Define the tree node structure
typedef struct {
    char label[20];         // Node label
    int numChildren;        // Number of children (0 = leaf)
    int parentIndex;        // Parent index (-1 if root)
    void* funcOrChildren;   // Either child indices or function
} TreeNode;

typedef void (*LeafFunc)(void);

// Function prototypes
void InitMenu(void);
int* getChildren(int nodeIndex);
int addNode(const char* label, int parentIndex, int children[], int numChildren);
void addLeaf(const char* label, int parentIndex, LeafFunc func);
void printChildren();
void PrintMenu();
void OpenMenu();
void CloseMenu();
void executeLeafFunction(int nodeIndex);
void exampleFunction();
uint8_t isLeaf(int selectedIndex);

#endif // MENU_H
