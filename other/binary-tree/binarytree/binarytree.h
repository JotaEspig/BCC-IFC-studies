#ifndef BINARYTREE_H
#define BINARYTREE_H

/**
 * @brief Node type
 * 
 */
typedef struct bt_node {
    int data;
    struct bt_node *left;
    struct bt_node *right;
} bt_node_t;

/**
 * @brief Creates a new instance of a node
 * 
 * @param data data inside the node
 * @return node
 */
bt_node_t *bt_new_node(int data);

/**
 * @brief Inserts new data into the binary tree. If root is NULL,
 * it will return the node
 * 
 * @param root pointer to the root of the binary tree
 * @param data integer value that will be added into binary tree
 * @return the root of the binary tree
 */
bt_node_t *bt_insert(bt_node_t *root, int data);

/**
 * @brief Search for a node using binary search algorithm
 * 
 * @param root pointer to the root of the binary tree
 * @param data data contained inside the node you want to get
 * @return node
 */
bt_node_t *bt_search(bt_node_t *root, int data);

void bt_print(bt_node_t *node);

#endif // BINARYTREE_H