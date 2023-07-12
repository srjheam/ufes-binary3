
#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#include "deque.h"

#include "types.h"

typedef struct {
    void *key;
    void *value;
} KeyValPair;

typedef struct Node {
    void *key;
    void *value;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct {
    Node *root;
    compar_fn cmp_fn;
    destructor_fn key_destroy_fn;
    destructor_fn val_destroy_fn;
} BinaryTree;

KeyValPair *key_val_pair_construct(void *key, void *val);
void key_val_pair_destroy(KeyValPair *kvp);

Node *node_construct(void *key, void *value, Node *left, Node *right, Node *parent);
void node_destroy(Node *node);

BinaryTree *binary_tree_construct(compar_fn compar_fn, destructor_fn key_destroy_fn,
                                  destructor_fn val_destroy_fn);
void binary_tree_add(BinaryTree *bt, void *key, void *value);
Node *__binary_tree_add_recursive(BinaryTree *bt, void *key, void *value, Node *p);
void binary_tree_add_recursive(BinaryTree *bt, void *key, void *value);
int binary_tree_empty(BinaryTree *bt);
Node *__transplant(Node *u, Node *v);
Node *__node_remove(Node *z, destructor_fn keyDestroy, destructor_fn valDestroy);
void binary_tree_remove(BinaryTree *bt, void *key);
Node *__node_min(Node *node);
KeyValPair *binary_tree_min(BinaryTree *bt);
Node *__node_max(Node *node);
KeyValPair *binary_tree_max(BinaryTree *bt);
KeyValPair *binary_tree_pop_min(BinaryTree *bt);
KeyValPair *binary_tree_pop_max(BinaryTree *bt);
Node *__node_find(Node *node, void *key, compar_fn compar);
void *binary_tree_get(BinaryTree *bt, void *key);
void __binary_tree_destroy_recursive(Node *node, destructor_fn keyDestroy, destructor_fn valDestroy);
void binary_tree_destroy(BinaryTree *bt);

// a funcao abaixo pode ser util para debug, mas nao eh obrigatoria.
// void binary_tree_print(BinaryTree *bt);

Deque *binary_tree_inorder_traversal(BinaryTree *bt);
Deque *binary_tree_preorder_traversal(BinaryTree *bt);
Deque *binary_tree_postorder_traversal(BinaryTree *bt);
Deque *binary_tree_levelorder_traversal(BinaryTree *bt);

Deque *binary_tree_inorder_traversal_recursive(BinaryTree *bt);

Deque *binary_tree_preorder_traversal_recursive(BinaryTree *bt);

void __binary_tree_postorder_traversal_recursive(Node *root, Deque *q);
Deque *binary_tree_postorder_traversal_recursive(BinaryTree *bt);

#endif