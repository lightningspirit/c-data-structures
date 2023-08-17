// SPDX-License-Identifier: MIT
/**
 * @file vector.h
 * @brief A dynamically allocated vector specification
 * @version 0.1
 * @date 2023-05-02
 *
 * @copyright Copyright (c) 2023 lightningspirit
 *
 */

#ifndef VECTOR_H
#define VECTOR_H

/**
 * @brief generic vector container
 *
 */
typedef struct vector_t vector_t;

/**
 * @brief iterator for `vector_t`
 *
 */
typedef struct vector_t_iterator vector_t_iterator;

/**
 * @brief creates a new `vector_t`
 *
 * @param[in] size initial vector capacity
 * @return `vector_t*` pointer for created vector
 */
vector_t *vector_t_create(const size_t size);

/**
 * @brief initializes a `vector_t` pointer with 0-capacity
 *
 * @param[in] vector
 */
void vector_t_init(vector_t **vector);

/**
 * @brief destroys a `vector_t` and its members
 *
 * @param[in] vector
 */
void vector_t_destroy(vector_t *vector);

/**
 * @brief retrieves the size (capacity) of `vector_t`
 *
 * @param[in] vector
 */
size_t vector_t_size(const vector_t *vector);

/**
 * @brief grows or shrinks a `vector_t`
 *
 * @warning trims the vector, removing any member after `size`, garbage-collects.
 *
 * @param[in] vector
 * @param[in] size
 */
void vector_t_resize(vector_t *vector, const size_t size);

/**
 * @brief moves all non-null members to the beginning of vector
 *
 * Compacts a sparsed vector keeping intact the order of members.
 * All `NULL` values will be compacted to the end of the vector.
 *
 * @note `vector_t_resize` can be safely called after `vector_t_compact` using return size
 *
 * @param[in] vector
 * @return number of non-value members
 */
size_t vector_t_compact(vector_t *vector);

/**
 * @brief inserts an element at given `index` in the `vector_t`
 *
 * Does not replace any value, only places `item` in the position `index`, moving right all subsequent non-null items, unless position holds a `NULL` pointer.
 *
 * @note uses `vector_t_resize` if needed.
 *
 * @param[in] vector
 * @param[in] index
 * @param[in] item
 */
void vector_t_insert(vector_t *vector, const size_t index, void *item);

/**
 * @brief updates or inserts an element at given `index` within the `vector_t`
 *
 * @warning replaces value at `index`
 * @note uses `vector_t_resize` if needed.
 *
 * @param[in] vector
 * @param[in] index
 * @param[in] item
 */
void vector_t_set(vector_t *vector, const size_t index, void *item);

/**
 * @brief get member from `vector_t` or NULL
 *
 * @param[in] vector
 * @param[in] index
 * @return void*
 */
void *vector_t_get(const vector_t *vector, const size_t index);

/**
 * @brief removes elements from `vector_t`
 *
 * @note does not resize vector, only moves members to left overriding range
 *
 * @param[in] vector
 * @param[in] index start index, inclusive
 * @param[in] count how many to remove
 */
void vector_t_remove(vector_t *vector, size_t index, const size_t count);

/**
 * @brief inserts member right after the last non-null position of `vector_t`
 *
 * @note uses `vector_t_resize` if needed.
 * @warning for big all
 *
 * @param[in] vector
 * @param[in] element
 */
void vector_t_push(vector_t *vector, void *element);

/**
 * @brief move a member to a new index
 *
 * @warning it overrides any value in `destination`
 * @note calls `vector_t_resize` if needed
 *
 * @param[in] vector
 * @param[in] origin
 * @param[in] destination
 */
void vector_t_move(vector_t *vector, const size_t origin, const size_t destination);

/**
 * @brief swap two members in place
 *
 * @param[in] vector
 * @param[in] idx1
 * @param[in] idx2
 */
void vector_t_swap(vector_t *vector, const size_t idx1, const size_t idx2);

/**
 * @brief copy the provided `vector_t`
 *
 * @warning members keep the same pointer as original vector
 *
 * @param[in] vector
 */
vector_t *vector_t_copy(const vector_t *vector);

/**
 * @brief reverse the provided `vector_t`
 *
 * @note can pair with `vector_t_compact` to move any `NULL` to the end.
 *
 * @param[in] vector
 */
void vector_t_reverse(vector_t *vector);

/**
 * @brief sets all `vector_t` members to `NULL`
 *
 * @param[in] vector
 */
void vector_t_clean(vector_t *vector);

/**
 * @brief iterator for vector_t
 *
 * This iterator reduces the amount of code to create for loops.
 *
 * @param[in] vector
 * @return vector_t_iterator*
 */
vector_t_iterator *vector_t_iterator_create(vector_t *vector);

/**
 * @brief get the item at current position of vector_t or NULL
 *
 * @param[in] iter
 * @return void*
 */
void *vector_t_iterator_next(vector_t_iterator *iter);

/**
 * @brief get current vector cursor (index)
 *
 * @param[in] iter
 * @return cursor
 */
size_t vector_t_iterator_cursor(vector_t_iterator *iter);

/**
 * @brief resets the iterator pointer to the beggining of the vector_t
 *
 * @param[in] iter
 */
void vector_t_iterator_reset(vector_t_iterator *iter);

/**
 * @brief destroys the iterator and frees its memory
 *
 * @param[in] iter the iterator to be destroyed
 */
void vector_t_iterator_destroy(vector_t_iterator *iter);

#endif
