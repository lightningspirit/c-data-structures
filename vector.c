/**
 * @file vector.c
 * @author lightningspirit@gmail.com
 * @brief Vector implementation
 * @version 0.1
 * @date 2023-01-07
 *
 * @copyright Copyright (c) 2023 MIT License
 *
 */
#include <stdlib.h>
#include "malloc.h"
#include "vector.h"

/**
 * @brief Construct a new t vector nullify object
 * 
 * @param v 
 * @param start 0-based index
 * @param end 0-based index
 */
static inline void t_vector_nullify(t_vector *v, size_t start, size_t end)
{
  for (; start <= end; start++) {
    v->elements[start] = NULL;
  }
}

/**
 * @brief 
 * 
 * @param size 
 */
static inline size_t zero_based(size_t size)
{
  return size - 1;
}

/**
 * @brief Construct a new count based object
 * 
 * @param index 
 */
static inline size_t count_based(size_t index)
{
  return index + 1;
}

t_vector* t_vector_create(size_t size)
{
  t_vector *v;
  
  v = malloc_safe(sizeof(*v));
  
  v->size = 0;
  v->elements = NULL;

  if (size > 0) {
    t_vector_resize(v, size);
    v->size = size;
  }

  return v;
}

void t_vector_destroy(t_vector *v)
{
  t_vector_clean(v);
  free(v);
  v = NULL;
}

void t_vector_clean(t_vector *v)
{
  if (v->elements != NULL) {
    free(v->elements);
    v->elements = NULL;
  }
}

size_t t_vector_size(t_vector *v)
{
  return v->size;
}

void t_vector_resize(t_vector *v, size_t size)
{
  v->elements = malloc_realloc_safe(sizeof(void *) * size, v->elements);

  if (size > v->size) {
    t_vector_nullify(v, v->size - 1, size);
  }
}

void t_vector_compact(t_vector *v)
{
  size_t null_values = 0;

  for (size_t i = 0; i < v->size; i++) {
    if (v->elements[i] == NULL) {
      null_values++;
    } else {
      if (null_values > 0) {
        t_vector_swap(v, zero_based(null_values), i);
      }
    }
  }

  if (null_values > 0) {
    // null_values is now used to count new size
    null_values = v->size - null_values;
    t_vector_resize(v, null_values);
    v->size = null_values;
  }
}

void t_vector_push(t_vector *v, void *element)
{
  // first ensure the correct size
  t_vector_resize(v, v->size + 1);
  v->elements[v->size++] = element;
}

void t_vector_set(t_vector *v, size_t position, void *element)
{
  if (position > zero_based(v->size)) {
    t_vector_resize(v, count_based(position));
    v->size = count_based(position);
  }

  v->elements[position] = element;
}

void t_vector_swap(t_vector *v, size_t pos1, size_t pos2)
{
  if (pos1 > zero_based(v->size) || pos2 > zero_based(v->size)) {
    // resize if pos1 or pos2 overflows vector size
    size_t new_size = count_based(pos1 > pos2 ? pos1 : pos2);
    t_vector_resize(v, new_size);
    v->size = new_size;
  }

  void *tmp = t_vector_get(v, pos1);
  t_vector_set(v, pos1, t_vector_get(v, pos2));
  t_vector_set(v, pos2, tmp);
}

void* t_vector_get(t_vector *v, size_t position)
{
  if (position > zero_based(v->size)) return NULL;
  return v->elements[position];
}

void t_vector_remove(t_vector *v, size_t position)
{
  // first ensure the correct size
  if (position > zero_based(v->size)) return;

  void *elem = v->elements[position];
  free(elem);

  // move all subsequent one position before
  while (position <= zero_based(v->size)) {
    v->elements[position] = v->elements[position + 1];
    position++;
  }

  t_vector_resize(v, v->size - 1);
  v->size--;
}

void t_vector_pop(t_vector *v)
{
  t_vector_remove(v, zero_based(v->size));
}

void t_vector_shift(t_vector *v)
{
  return t_vector_remove(v, 0);
}

void* t_vector_first(t_vector *v)
{
  if (t_vector_size(v) > 0) {
    return t_vector_get(v, 0);
  }

  return NULL;
}

void* t_vector_last(t_vector *v)
{
  if (t_vector_size(v) > 0) {
    return t_vector_get(v, zero_based(v->size));
  }

  return NULL;
}

void t_vector_reverse(t_vector *v)
{
  size_t n = v->size / 2;

  for (size_t i = 0; i < n; i++) {
    t_vector_swap(v, i, v->size - i - 1);
  }
}
