
#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

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
    cmp_fn cmp_fn;
    destructor_fn key_destroy_fn;
    destructor_fn val_destroy_fn;
} BinaryTree;

KeyValPair *key_val_pair_construct(void *key, void *val);
void key_val_pair_destroy(KeyValPair *kvp);

Node *node_construct(void *key, void *value, Node *left, Node *right, Node *parent);
void node_destroy(Node *node);

BinaryTree *binary_tree_construct(cmp_fn cmp_fn, destructor_fn key_destroy_fn,
                                  destructor_fn val_destroy_fn);
void binary_tree_add(BinaryTree *bt, void *key, void *value);
void binary_tree_add_recursive(BinaryTree *bt, void *key, void *value);
int binary_tree_empty(BinaryTree *bt);
void binary_tree_remove(BinaryTree *bt, void *key);
KeyValPair binary_tree_min(BinaryTree *bt);
KeyValPair binary_tree_max(BinaryTree *bt);
KeyValPair binary_tree_pop_min(BinaryTree *bt);
KeyValPair binary_tree_pop_max(BinaryTree *bt);
void *binary_tree_get(BinaryTree *bt, void *key);
void binary_tree_destroy(BinaryTree *bt);

// a funcao abaixo pode ser util para debug, mas nao eh obrigatoria.
// void binary_tree_print(BinaryTree *bt);

Deque *binary_tree_inorder_traversal(BinaryTree *bt);
Deque *binary_tree_preorder_traversal(BinaryTree *bt);
Deque *binary_tree_postorder_traversal(BinaryTree *bt);
Deque *binary_tree_levelorder_traversal(BinaryTree *bt);

Deque *binary_tree_inorder_traversal_recursive(BinaryTree *bt);
Deque *binary_tree_preorder_traversal_recursive(BinaryTree *bt);
Deque *binary_tree_postorder_traversal_recursive(BinaryTree *bt);

#endif