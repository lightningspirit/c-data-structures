// SPDX-License-Identifier: MIT
/**
 * @file node.h
 * @brief Instance logic declarations
 * @date 2024-08-17
 * @version 0.1
 *
 * @copyright Copyright (c) 2023 lightningspirit
 *
 */

#include <stdlib.h>

#ifndef NODE_H
#define NODE_H

/**
 * @brief Node structure
 */
typedef struct node_t node_t;

/**
 * @brief Returns a new `node_t` with given value, beginning a new list
 *
 * Allocates and initializes a new `node_t`. Create a new list by passing `NULL` in the `next` parameter.
 *
 * @param current Internal value for node.
 * @param next Pointer to the next node.
 *
 * @note `O(1)`
 * @return `node_t` Pointer to the newly created node.
 */
node_t *node_t_create(void *current, node_t *next);

/**
 * @brief Destroys the node and all linked `node_t`.
 * 
 * Iterates over all `next` nodes and calls `free`.
 * If `NULL` is given, does nothing.
 *
 * @note `O(n)`
 * @param node Pointer to the node to be destroyed.
 */
void node_t_destroy(node_t *head);

/**
 * @brief Returns number of linked `node_t`s
 * 
 * If `NULL` is passed, returns 0.
 *
 * @note `O(n)`
 * @return `size_t` List size
 */
size_t node_t_size(node_t *head);

/**
 * @brief Returns the value of the given `node_t`
 * 
 * @note `O(1)`
 * @return `void *`
 */
void *node_t_peek(node_t *node);

/**
 * @brief Returns next `node_t` or NULL.
 */
node_t *node_t_next(node_t *node);

/**
 * @brief Creates a new `node_t` and places `node` as the next linked `node_t`.
 *
 * If `NULL` is given, mutates `node` with a new `node_t`, virtually beginning a new list.
 *
 * @note `O(1)`
 */
void node_t_unshift(void *value, node_t **head);

/**
 * @brief Removes and returns the first `node_t` value, placing `node` with `next` node reference.
 *
 * Assigns next `node_t` to `node`. If it's last `node_t`,
 * returns `NULL` and assigns `NULL` to `node`.
 *
 * @note `O(1)`
 */
void *node_t_shift(node_t **head);

/**
 * @brief Creates a new `node_t` placing as `next` node.
 *
 * If node already has `next`, moves it as the `next` of the new `node_t`.
 *
 * @note `O(n)`
 * @return `node_t` the new tail
 */
node_t *node_t_push(void *value, node_t **tail);

#endif // NODE_H
