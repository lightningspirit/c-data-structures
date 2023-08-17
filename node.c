// SPDX-License-Identifier: MIT
/**
 * @file node.c
 * @brief Instance logic declarations
 * @date 2024-08-17
 * @version 0.1
 *
 * @copyright Copyright (c) 2023 lightningspirit
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "heap.h"
#include "node.h"

struct node_t
{
  void *value;
  struct node_t *next;
};

node_t *node_t_create(void *value, node_t *next)
{
  node_t *n = malloc_realloc(sizeof(*n), NULL);

  n->value = value;
  n->next = next;

  return n;
}

void node_t_destroy(node_t *head)
{
  node_t *next;

  while (head != NULL)
  {
    next = head->next;
    free(head);
    head = next;
  }
}

size_t node_t_size(node_t *head)
{
  node_t *t = head;
  size_t size = 0;

  while (t != NULL)
  {
    t = t->next;
    size++;
  }

  return size;
}

void *node_t_peek(node_t *n)
{
  return n != NULL ? n->value : NULL;
}

node_t *node_t_next(node_t *n)
{
  return n != NULL ? n->next : NULL;
}

void node_t_unshift(void *value, node_t **head)
{
  *head = node_t_create(value, *head);
}

void *node_t_shift(node_t **head)
{
  if (*head == NULL)
    return NULL;

  node_t *shift = *head;
  void *v = shift->value;
  *head = shift->next;
  free(shift);
  return v;
}

node_t *node_t_push(void *value, node_t **head)
{
  node_t *tail = node_t_create(value, NULL);

  if (*head == NULL)
  {
    *head = tail;
  }
  else
  {
    node_t *cursor = *head;

    while (cursor->next != NULL)
      cursor = cursor->next;
    cursor->next = tail;
  }

  return tail;
}
