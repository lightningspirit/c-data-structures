// SPDX-License-Identifier: MIT
/**
 * @file vector.c
 * @brief Dynamically vector implementation
 * @version 0.1
 * @date 2023-05-02
 *
 * @copyright Copyright (c) 2023 lightningspirit
 *
 */

#include <stdlib.h>
#include <string.h>
#include "heap.h"
#include "vector.h"

struct vector_t
{
  size_t size;
  void **items;
};

struct vector_t_iterator
{
  size_t cursor;
  vector_t *vector;
};

void vector_t_init(vector_t **v)
{
  *v = malloc_realloc(sizeof(**v), NULL);

  if (*v == NULL)
    return;

  (*v)->size = 0;
  (*v)->items = NULL;
}

vector_t *vector_t_create(size_t size)
{
  vector_t *v = NULL;
  vector_t_init(&v);

  if (size > 0)
  {
    vector_t_resize(v, size);
    v->size = size;
  }

  return v;
}

void vector_t_destroy(vector_t *v)
{
  if (v == NULL)
    return;

  if (v->items != NULL)
    free(v->items);

  free(v);
}

void vector_t_resize(vector_t *v, const size_t size)
{
  if (v == NULL)
    vector_t_init(&v);

  v->items = malloc_realloc(sizeof(void *) * size, v->items);

  for (size_t i = v->size; i < size; i++)
    v->items[i] = NULL;

  v->size = size;
}

size_t vector_t_compact(vector_t *v)
{
  if (v == NULL || v->items == NULL)
    return 0;

  size_t cursor = 0;

  for (size_t i = 0; i < v->size; i++)
  {
    if (v->items[i] != NULL)
    {
      v->items[cursor] = v->items[i];
      cursor++;
    }
  }

  for (size_t i = cursor; i < v->size; i++)
    v->items[i] = NULL;

  return cursor;
}

void vector_t_insert(vector_t *v, const size_t index, void *item)
{
  if (v == NULL || v->items == NULL)
    vector_t_resize(v, index);

  if (index >= v->size)
  {
    vector_t_resize(v, index + 1);
  }
  else
  {
    if (v->items[index] != NULL)
    {
      if (v->items[v->size - 1] != NULL)
        vector_t_resize(v, v->size + 1);

      memmove(&v->items[index + 1], &v->items[index], (v->size - index) * sizeof(void *));
    }
  }

  v->items[index] = item;
}

void vector_t_set(vector_t *v, const size_t index, void *item)
{
  if (v == NULL || v->items == NULL || index >= v->size)
    vector_t_resize(v, index + 1);

  v->items[index] = item;
}

void vector_t_remove(vector_t *v, size_t index, const size_t count)
{
  if (v->items == NULL || index >= v->size)
    return;

  // size:= 10, index:= 7, count := 1
  // 7; 7 < 10 -> v[7] = v[8]
  // 8; 8 < 10 -> v[8] = v[9]
  // 9; 9 < 10 -> v[9] = NULL

  // size:= 10, index:= 5, count := 2
  // 5; 5 < 10 -> v[5] = v[7]
  // 6; 6 < 10 -> v[6] = v[8]
  // 7; 7 < 10 -> v[7] = v[9]
  // 8; 8 < 10 -> v[8] = NULL
  // 9; 9 < 10 -> v[9] = NULL
  for (; index < v->size; index++)
    v->items[index] = index + count < v->size
                          ? v->items[index + count]
                          : NULL;
}

void vector_t_push(vector_t *v, void *item)
{
  size_t i = v->size - 1;

  for (; i >= 0; i--)
    if (v->items[i] != NULL)
      break;

  i++;

  if (i == v->size)
    vector_t_resize(v, i + 1);

  v->items[i] = item;
}

void *vector_t_get(const vector_t *vector, const size_t index)
{
  if (vector->items == NULL || index >= vector->size)
    return NULL;

  return vector->items[index];
}

size_t vector_t_size(const vector_t *vector)
{
  return vector->size;
}

void vector_t_move(vector_t *v, const size_t origin, const size_t destination)
{
  if (v == NULL || v->items == NULL || origin >= v->size)
    return;

  if (destination >= v->size)
    vector_t_resize(v, destination + 1);

  v->items[destination] = v->items[origin];
  v->items[origin] = NULL;
}

void vector_t_swap(vector_t *v, size_t idx1, size_t idx2)
{
  if (v == NULL || v->items == NULL)
    return;

  if (idx1 >= v->size || idx2 >= v->size)
    vector_t_resize(v, (idx1 > idx2 ? idx1 : idx2) + 1);

  if (idx1 == idx2)
    return;

  void *t = v->items[idx1];
  v->items[idx1] = v->items[idx2];
  v->items[idx2] = t;
}

vector_t *vector_t_copy(const vector_t *o)
{
  vector_t *v = vector_t_create(o->size);
  memcpy(v->items, o->items, v->size * sizeof(void *));
  return v;
}

void vector_t_reverse(vector_t *v)
{
  void *t = NULL;

  for (size_t i = 0; i < (size_t)v->size / 2; i++)
  {
    t = v->items[i];
    v->items[i] = v->items[v->size - 1 - i];
    v->items[v->size - 1 - i] = t;
  }
}

void vector_t_clean(vector_t *v)
{
  if (v == NULL || v->items == NULL)
    return;

  for (size_t i = 0; i < v->size; i++)
  {
    v->items[i] = NULL;
  }
}

vector_t_iterator *vector_t_iterator_create(vector_t *vector)
{
  vector_t_iterator *iter = malloc_realloc(sizeof(vector_t_iterator), NULL);
  iter->cursor = 0;
  iter->vector = vector;
  return iter;
}

void vector_t_iterator_destroy(vector_t_iterator *iter)
{
  free(iter);
}

size_t vector_t_iterator_cursor(vector_t_iterator *iter)
{
  return iter->cursor == 0 ? 0 : iter->cursor - 1;
}

void *vector_t_iterator_next(vector_t_iterator *iter)
{
  if (iter->cursor >= iter->vector->size)
    return NULL;

  return vector_t_get(iter->vector, iter->cursor++);
}

void vector_t_iterator_reset(vector_t_iterator *iter)
{
  iter->cursor = 0;
}
