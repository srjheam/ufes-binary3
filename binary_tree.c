#include <stdlib.h>

#include "deque.h"

#include "binary_tree.h"

KeyValPair *key_val_pair_construct(void *key, void *val) {
    KeyValPair *kvp = malloc(sizeof(KeyValPair));

    kvp->key = key;
    kvp->value = val;

    return kvp;
}

void key_val_pair_destroy(KeyValPair *kvp) { free(kvp); }

Node *node_construct(void *key, void *value, Node *left, Node *right, Node *parent) {
    Node *node = malloc(sizeof(Node));

    node->key = key;
    node->value = value;
    node->left = left;
    node->right = right;
    node->parent = parent;

    return node;
}

void node_destroy(Node *node) { free(node); }

BinaryTree *binary_tree_construct(cmp_fn cmp_fn, destructor_fn key_destroy_fn,
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

    while (node != NULL) {
        prev = node;

        if (bt->cmp_fn(key, node->key) < 0)
            node = node->left;
        else
            node = node->right;
    }

    if (bt->cmp_fn(key, prev->key) < 0)
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

Node *__binary_tree_add_recursive(BinaryTree *bt, void *key, void *value, Node *p) {
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

void binary_tree_remove(BinaryTree *bt, void *key) {}

KeyValPair binary_tree_min(BinaryTree *bt) {
    Node *node = bt->root;

    while (node->left != NULL)
        node = node->left;

    KeyValPair kvp = {node->key, node->value};
    return kvp;
}

KeyValPair binary_tree_max(BinaryTree *bt) {
    Node *node = bt->root;

    while (node->right != NULL)
        node = node->right;

    KeyValPair kvp = {node->key, node->value};
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
    //   / \
    //  /   \
    // /     \
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

KeyValPair binary_tree_pop_min(BinaryTree *bt) {
    Node *node = bt->root;
    Node *prev = NULL;

    while (node->left != NULL) {
        prev = node;
        node = node->left;
    }

    KeyValPair kvp = {node->key, node->value};

    if (prev == NULL)
        bt->root = node->right;
    else
        prev->left = node->right;

    node_destroy(node);

    return kvp;
}

KeyValPair binary_tree_pop_max(BinaryTree *bt) {
    Node *node = bt->root;
    Node *prev = NULL;

    while (node->right != NULL) {
        prev = node;
        node = node->right;
    }

    KeyValPair kvp = {node->key, node->value};

    if (prev == NULL)
        bt->root = node->left;
    else
        prev->right = node->left;

    node_destroy(node);

    return kvp;
}

void *binary_tree_get(BinaryTree *bt, void *key) {
    Node *node = bt->root;

    while (node != NULL) {
        int cmp = bt->cmp_fn(key, node->key);

        if (cmp == 0)
            return node->value;
        else if (cmp < 0)
            node = node->left;
        else
            node = node->right;
    }

    return NULL;
}

void binary_tree_destroy(BinaryTree *bt);

// a funcao abaixo pode ser util para debug, mas nao eh obrigatoria.
// void binary_tree_print(BinaryTree *bt);

Deque *binary_tree_inorder_traversal(BinaryTree *bt) {
    Deque *v = deque_construct();

    Node *node = bt->root;
    Node *prev = NULL;

    while (node != NULL) {
        if (prev == node->left) {
            deque_push_back(v, key_val_pair_construct(node->key, node->value));

            if (node->right != NULL) {
                prev = node;
                node = node->right;
            } else {
                prev = node;
                node = node->parent;
            }
        } else if (prev == node->right) {
            prev = node;
            node = node->parent;
        } else {
            if (node->left != NULL) {
                prev = node;
                node = node->left;
            } else {
                deque_push_back(v,
                                 key_val_pair_construct(node->key, node->value));

                if (node->right != NULL) {
                    prev = node;
                    node = node->right;
                } else {
                    prev = node;
                    node = node->parent;
                }
            }
        }
    }

    return v;
}
Deque *binary_tree_preorder_traversal(BinaryTree *bt) {
    Deque *v = deque_construct();

    Node *node = bt->root;
    Node *prev = NULL;

    while (node != NULL) {
        if (prev == node->left) {
            deque_push_back(v, key_val_pair_construct(node->key, node->value));

            if (node->right != NULL) {
                prev = node;
                node = node->right;
            } else {
                prev = node;
                node = node->parent;
            }
        } else if (prev == node->right) {
            prev = node;
            node = node->parent;
        } else {
            if (node->left != NULL) {
                deque_push_back(v,
                                 key_val_pair_construct(node->key, node->value));

                prev = node;
                node = node->left;
            } else {
                if (node->right != NULL) {
                    deque_push_back(v,
                                     key_val_pair_construct(node->key,
                                                            node->value));

                    prev = node;
                    node = node->right;
                } else {
                    prev = node;
                    node = node->parent;
                }
            }
        }
    }

    return v;
}
Deque *binary_tree_postorder_traversal(BinaryTree *bt) {
    Deque *v = deque_construct();

    Node *node = bt->root;
    Node *prev = NULL;

    while (node != NULL) {
        if (prev == node->left) {
            if (node->right != NULL) {
                prev = node;
                node = node->right;
            } else {
                deque_push_back(v, key_val_pair_construct(node->key, node->value));

                prev = node;
                node = node->parent;
            }
        } else if (prev == node->right) {
            deque_push_back(v, key_val_pair_construct(node->key, node->value));

            prev = node;
            node = node->parent;
        } else {
            if (node->left != NULL) {
                prev = node;
                node = node->left;
            } else {
                if (node->right != NULL) {
                    prev = node;
                    node = node->right;
                } else {
                    deque_push_back(v,
                                     key_val_pair_construct(node->key,
                                                            node->value));

                    prev = node;
                    node = node->parent;
                }
            }
        }
    }

    return v;
}
Deque *binary_tree_levelorder_traversal(BinaryTree *bt) {
    Deque *v = deque_construct();

    Deque *q = deque_construct();

    queue_push(q, bt->root);

    while (!queue_empty(q)) {
        Node *node = queue_front(q);
        queue_pop(q);

        deque_push_back(v, key_val_pair_construct(node->key, node->value));

        if (node->left != NULL)
            queue_push(q, node->left);

        if (node->right != NULL)
            queue_push(q, node->right);
    }

    queue_destroy(q);

    return v;
}

Deque *binary_tree_inorder_traversal_recursive(BinaryTree *bt) {
    Deque *v = deque_construct();

    binary_tree_inorder_traversal_recursive_helper(bt->root, v);

    return v;
}

Deque *binary_tree_preorder_traversal_recursive(BinaryTree *bt) {
    Deque *v = deque_construct();

    binary_tree_preorder_traversal_recursive_helper(bt->root, v);

    return v;
}

Deque *binary_tree_postorder_traversal_recursive(BinaryTree *bt) {
    Deque *v = deque_construct();

    binary_tree_postorder_traversal_recursive_helper(bt->root, v);

    return v;
}
