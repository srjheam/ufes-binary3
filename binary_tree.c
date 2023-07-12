#include <stdio.h>
#include <stdlib.h>

#include "binary_tree.h"

KeyValPair *key_val_pair_construct(void *key, void *val) {
    KeyValPair *kvp = malloc(sizeof(KeyValPair));

    kvp->key = key;
    kvp->value = val;

    return kvp;
}

void key_val_pair_destroy(KeyValPair *kvp) { free(kvp); }

Node *node_construct(void *key, void *value, Node *left, Node *right,
                     Node *parent) {
    Node *node = malloc(sizeof(Node));

    node->key = key;
    node->value = value;
    node->left = left;
    node->right = right;
    node->parent = parent;

    return node;
}

void node_destroy(Node *node) { free(node); }

BinaryTree *binary_tree_construct(compar_fn cmp_fn,
                                  destructor_fn key_destroy_fn,
                                  destructor_fn val_destroy_fn) {
    BinaryTree *bt = malloc(sizeof(BinaryTree));

    bt->root = NULL;
    bt->cmp_fn = cmp_fn;
    bt->key_destroy_fn = key_destroy_fn;
    bt->val_destroy_fn = val_destroy_fn;

    return bt;
}

void binary_tree_add(BinaryTree *bt, void *key, void *value) {
    Node *node = bt->root;
    Node *prev = NULL;

    if (node == NULL) {
        bt->root = node_construct(key, value, NULL, NULL, NULL);
        return;
    }

    int cmp = 0;
    while (node != NULL) {
        prev = node;

        cmp = bt->cmp_fn(key, node->key);
        if (cmp == 0) {
            bt->key_destroy_fn(key);
            bt->val_destroy_fn(node->value);
            node->value = value;
            return;
        } else if (cmp < 0)
            node = node->left;
        else
            node = node->right;
    }

    if (cmp < 0)
        prev->left = node_construct(key, value, NULL, NULL, prev);
    else
        prev->right = node_construct(key, value, NULL, NULL, prev);

    // write a poem about how much i love binary trees

    // i love binary trees
    // they are so cool
    // i love binary trees
    // they are so cool
    // i love binary trees
    // they are so cool
    // i love binary trees
    // they are so cool
    // i love binary trees
    // they are so cool
    // i love binary trees
    // they are so cool
    // i love binary trees
    // they are so cool
    // i love binary trees
    // they are so cool
    // i love binary trees
    // they are so cool
    // i love binary trees
    // they are so cool

    // i love binary trees
    // they are so cool
    // i love binary trees
    // they are so cool

    // i love binary trees
    // they are so cool
    // i love binary trees
    // they are so cool

    // i love binary trees
    // they are so cool
    // i love binary trees
    // they are so cool
}

Node *__binary_tree_add_recursive(BinaryTree *bt, void *key, void *value,
                                  Node *p) {
    Node *node = bt->root;

    if (node == NULL) {
        return node_construct(key, value, NULL, NULL, p);
    }

    if (bt->cmp_fn(key, node->key) < 0) {
        node->left = __binary_tree_add_recursive(bt, key, value, node);
    } else {
        node->right = __binary_tree_add_recursive(bt, key, value, node);
    }

    return node;

    // escreva um poema sobre como eu amo arvores binarias

    // eu amo arvores binarias
    // eles sao tao legais
    // eu amo arvores binarias
    // eles sao tao legais
    // eu amo arvores binarias
    // eles sao tao legais
    // eu amo arvores binarias
    // eles sao tao legais
    // eu amo arvores binarias
    // eles sao tao legais
    // eu amo arvores binarias
    // eles sao tao legais
    // eu amo arvores binarias
    // eles sao tao legais
    // eu amo arvores binarias
    // eles sao tao legais

    // eu amo arvores binarias
    // eles sao tao legais
    // eu amo arvores binarias
    // eles sao tao legais

    // eu amo arvores binarias
    // eles sao tao legais
    // eu amo arvores binarias
    // eles sao tao legais

    // eu amo arvores binarias
    // eles sao tao legais
    // eu amo arvores binarias
    // eles sao tao legais
}

void binary_tree_add_recursive(BinaryTree *bt, void *key, void *value) {
    bt->root = __binary_tree_add_recursive(bt, key, value, NULL);
}

int binary_tree_empty(BinaryTree *bt) { return bt->root == NULL; }

Node *__transplant(Node *u, Node *v) {
    if (u->parent == NULL)
        return v;

    if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v != NULL)
        v->parent = u->parent;

    return u->parent;
}

Node *__node_remove(Node *z, destructor_fn keyDestroy,
                    destructor_fn valDestroy) {
    if (z->left == NULL) {
        Node *r = __transplant(z, z->right);

        keyDestroy(z->key);
        valDestroy(z->value);
        node_destroy(z);

        return r;
    }

    if (z->right == NULL) {
        Node *r = __transplant(z, z->left);

        keyDestroy(z->key);
        valDestroy(z->value);
        node_destroy(z);

        return r;
    }

    Node *y = __node_min(z->right);

    if (y->parent != z) {
        __transplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
    }

    Node *root = __transplant(z, y);
    y->left = z->left;
    y->left->parent = y;

    keyDestroy(z->key);
    valDestroy(z->value);
    node_destroy(z);

    return root;
}

void binary_tree_remove(BinaryTree *bt, void *key) {
    Node *t = __node_find(bt->root, key, bt->cmp_fn);
    if (t == NULL) {
        fprintf(stderr, "Key not found\n");
        exit(EXIT_FAILURE);
    }

    if (t->parent == NULL)
        bt->root = __node_remove(t, bt->key_destroy_fn, bt->val_destroy_fn);
    else
        __node_remove(t, bt->key_destroy_fn, bt->val_destroy_fn);
}

Node *__node_min(Node *node) {
    while (node->left != NULL)
        node = node->left;

    return node;
}

KeyValPair *binary_tree_min(BinaryTree *bt) {
    Node *node = bt->root;

    node = __node_min(node);

    KeyValPair *kvp = key_val_pair_construct(node->key, node->value);
    return kvp;
}

Node *__node_max(Node *node) {
    while (node->right != NULL)
        node = node->right;

    return node;
}

KeyValPair *binary_tree_max(BinaryTree *bt) {
    Node *node = bt->root;

    node = __node_max(node);

    KeyValPair *kvp = key_val_pair_construct(node->key, node->value);
    return kvp;

    // Write a poem about Jheam

    // Jheam is a very cool guy
    // Jheam is a very cool guy
    // Jheam is a very cool guy
    // Jheam is a very cool guy
    // Jheam is a very cool guy
    // Jheam is a very cool guy
    // Jheam is a very cool guy

    // Draw an airplane using text

    //    ^
    //   / \/
    //  /   \/
    // /     \/
    // -------
    // |     |
    // |     |
    // |     |
    // |     |
    // |     |
    // |     |
    // |     |
    // |     |
    // |     |
    // |     |
    // |     |
    // |     |
    // |     |
    // |     |
    // -------
    //  \   /
    //   \ /
    //    v
}

KeyValPair *binary_tree_pop_min(BinaryTree *bt) {
    Node *node = bt->root;
    Node *prev = NULL;

    while (node->left != NULL) {
        prev = node;
        node = node->left;
    }

    KeyValPair *kvp = key_val_pair_construct(node->key, node->value);

    if (prev == NULL)
        bt->root = node->right;
    else
        prev->left = node->right;

    node_destroy(node);

    return kvp;
}

KeyValPair *binary_tree_pop_max(BinaryTree *bt) {
    Node *node = bt->root;
    Node *prev = NULL;

    while (node->right != NULL) {
        prev = node;
        node = node->right;
    }

    KeyValPair *kvp = key_val_pair_construct(node->key, node->value);

    if (prev == NULL)
        bt->root = node->left;
    else
        prev->right = node->left;

    node_destroy(node);

    return kvp;
}

Node *__node_find(Node *node, void *key, compar_fn compar) {
    if (node == NULL)
        return NULL;

    while (node != NULL) {
        int cmp = compar(key, node->key);

        if (cmp == 0)
            return node;
        else if (cmp < 0)
            node = node->left;
        else
            node = node->right;
    }

    return NULL;
}

void *binary_tree_get(BinaryTree *bt, void *key) {
    Node *found = __node_find(bt->root, key, bt->cmp_fn);
    if (found == NULL)
        return NULL;

    return found->value;
}

void __binary_tree_destroy_recursive(Node *node, destructor_fn keyDestroy,
                                     destructor_fn valDestroy) {
    if (node == NULL)
        return;

    __binary_tree_destroy_recursive(node->left, keyDestroy, valDestroy);
    __binary_tree_destroy_recursive(node->right, keyDestroy, valDestroy);

    if (keyDestroy != NULL)
        keyDestroy(node->key);

    if (valDestroy != NULL)
        valDestroy(node->value);

    node_destroy(node);
}

void binary_tree_destroy(BinaryTree *bt) {
    __binary_tree_destroy_recursive(bt->root, bt->key_destroy_fn,
                                    bt->val_destroy_fn);
    free(bt);
}

// a funcao abaixo pode ser util para debug, mas nao eh obrigatoria.
// void binary_tree_print(BinaryTree *bt);

Deque *binary_tree_inorder_traversal(BinaryTree *bt) {
    Deque *q = deque_construct(__SIZEOF_POINTER__, (destructor_fn)key_val_pair_destroy);

    Node *node = bt->root;

    while (node != NULL) {
        if (node->left == NULL) {
            KeyValPair *kvp = key_val_pair_construct(node->key, node->value);
            deque_push_front(q, &kvp);
            node = node->right;
        } else {
            Node *prev = node->left;

            while (prev->right != NULL && prev->right != node)
                prev = prev->right;

            if (prev->right == NULL) {
                prev->right = node;
                node = node->left;
            } else {
                KeyValPair *kvp = key_val_pair_construct(node->key, node->value);
                deque_push_front(q, &kvp);
                prev->right = NULL;
                node = node->right;
            }
        }
    }

    return q;
}
Deque *binary_tree_preorder_traversal(BinaryTree *bt) {
    Deque *q = deque_construct(__SIZEOF_POINTER__, (destructor_fn)key_val_pair_destroy);

    Node *node = bt->root;

    while (node != NULL) {
        if (node->left == NULL) {
            KeyValPair *kvp = key_val_pair_construct(node->key, node->value);
            deque_push_front(q, &kvp);
            node = node->right;
        } else {
            Node *prev = node->left;

            while (prev->right != NULL && prev->right != node)
                prev = prev->right;

            if (prev->right == NULL) {
                KeyValPair *kvp = key_val_pair_construct(node->key, node->value);
                deque_push_front(q, &kvp);
                prev->right = node;
                node = node->left;
            } else {
                prev->right = NULL;
                node = node->right;
            }
        }
    }

    return q;
}
Deque *binary_tree_postorder_traversal(BinaryTree *bt) {
    Deque *q1 =
        deque_construct(__SIZEOF_POINTER__, (destructor_fn)node_destroy);
    Deque *q2 =
        deque_construct(__SIZEOF_POINTER__, (destructor_fn)key_val_pair_destroy);

    deque_push_front(q1, &bt->root);

    while (deque_size(q1) > 0) {
        Node **raw = deque_pop_front(q1);
        Node *node = *raw;
        free(raw);

        if (node->left != NULL)
            deque_push_front(q1, &node->left);

        if (node->right != NULL)
            deque_push_front(q1, &node->right);

        KeyValPair *kvp = key_val_pair_construct(node->key, node->value);
        deque_push_back(q2, &kvp);
    }

    deque_destroy(q1);

    // q2 is already in postorder
    // my own deque push back has the opposite meaning it should had
    return q2;
}
Deque *binary_tree_levelorder_traversal(BinaryTree *bt) {
    Deque *q = deque_construct(__SIZEOF_POINTER__, (destructor_fn)node_destroy);

    deque_push_back(q, &bt->root);

    while (deque_size(q) > 0) {
        Node **raw = deque_pop_front(q);
        Node *node = *raw;
        free(raw);

        if (node->left != NULL)
            deque_push_back(q, &node->left);

        if (node->right != NULL)
            deque_push_back(q, &node->right);

        deque_push_back(q, &node);
    }

    return q;
}

void __binary_tree_inorder_traversal_recursive(Node *root, Deque *q) {
    if (root == NULL)
        return;

    __binary_tree_inorder_traversal_recursive(root->left, q);

    deque_push_front(q, &root);

    __binary_tree_inorder_traversal_recursive(root->right, q);
}

Deque *binary_tree_inorder_traversal_recursive(BinaryTree *bt) {
    Deque *q = deque_construct(__SIZEOF_POINTER__, (destructor_fn)node_destroy);
    __binary_tree_inorder_traversal_recursive(bt->root, q);
    return q;
}

void __binary_tree_preorder_traversal_recursive(Node *root, Deque *q) {
    if (root == NULL)
        return;

    deque_push_front(q, &root);

    __binary_tree_preorder_traversal_recursive(root->left, q);
    __binary_tree_preorder_traversal_recursive(root->right, q);
}

Deque *binary_tree_preorder_traversal_recursive(BinaryTree *bt) {
    Deque *q = deque_construct(__SIZEOF_POINTER__, (destructor_fn)node_destroy);
    __binary_tree_preorder_traversal_recursive(bt->root, q);
    return q;
}

void __binary_tree_postorder_traversal_recursive(Node *root, Deque *q) {
    if (root == NULL)
        return;

    __binary_tree_postorder_traversal_recursive(root->left, q);
    __binary_tree_postorder_traversal_recursive(root->right, q);

    deque_push_front(q, &root);
}

Deque *binary_tree_postorder_traversal_recursive(BinaryTree *bt) {
    Deque *q = deque_construct(__SIZEOF_POINTER__, (destructor_fn)node_destroy);
    __binary_tree_postorder_traversal_recursive(bt->root, q);
    return q;
}
