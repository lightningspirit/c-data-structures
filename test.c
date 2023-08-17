/**
 * @file test.c
 * @brief Unit tests
 * @version 0.1
 * @date 2023-01-07
 *
 * @copyright Copyright (c) 2023 MIT License
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "test.h"
#include "heap.h"
#include "vector.h"
#include "matrix.h"
#include "node.h"

typedef struct
{
  int id;
} t_test;

int tests_ran = 0;

typedef void (*vector_t_operate)(vector_t *, size_t);

static int with_elapsed(vector_t *v, size_t s, vector_t_operate f)
{
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);

  f(v, s);

  clock_gettime(CLOCK_MONOTONIC, &end);
  return (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000;
}

static char *test_vector_t_create()
{
  vector_t *v = vector_t_create(0);
  expect("vector_t_create (0)", v != NULL);
  expect("vector_t_size (0)", vector_t_size(v) == 0);

  vector_t_destroy(v);

  return 0;
}

static char *test_vector_t_resize()
{
  vector_t *v = vector_t_create(0);
  expect("vector_t_size (0)", vector_t_size(v) == 0);

  vector_t_resize(v, 100);
  expect("vector_t_resize (100)", vector_t_size(v) == 100);

  int it = 42;
  vector_t_set(v, 99, &it);
  expect("vector_t_get (99, it)", *((int *)vector_t_get(v, 99)) == it);

  vector_t_resize(v, 10);
  expect("vector_t_resize (10)", vector_t_size(v) == 10);
  expect("vector_t_get (99, it)", ((int *)vector_t_get(v, 99)) == NULL);

  vector_t_destroy(v);

  return 0;
}

static char *test_vector_t_set_get()
{
  vector_t *v = vector_t_create(3);

  t_test s1 = {42};
  t_test *s2;

  expect("vector_t_size (3)", vector_t_size(v) == 3);

  vector_t_set(v, 0, &s1);
  expect("vector_t_set/get (0, s1)", ((t_test *)vector_t_get(v, 0))->id == s1.id);

  s2 = malloc(sizeof(*s2));
  s2->id = 100000000;

  vector_t_set(v, 10, s2);
  expect("vector_t_set/get (10, s2)", ((t_test *)vector_t_get(v, 10))->id == s2->id);
  expect("vector_t_size (11)", vector_t_size(v) == 11);

  vector_t_destroy(v);
  free(s2);

  return 0;
}

static char *test_vector_t_compact()
{
  vector_t *v = vector_t_create(10);
  t_test s1 = {42};

  vector_t_set(v, 0, NULL);
  vector_t_set(v, 1, NULL);
  vector_t_set(v, 2, &s1);
  vector_t_set(v, 3, &s1);
  vector_t_set(v, 4, NULL);
  vector_t_set(v, 5, &s1);

  size_t size = vector_t_compact(v);

  expect("vector_t_compact size", size == 3);
  expect("vector_t_size (10)", vector_t_size(v) == 10);

  expect("vector_t_get (0) == s1", ((t_test *)vector_t_get(v, 0))->id == s1.id);
  expect("vector_t_get (1) == s1", ((t_test *)vector_t_get(v, 1))->id == s1.id);
  expect("vector_t_get (2) == s1", ((t_test *)vector_t_get(v, 2))->id == s1.id);
  expect("vector_t_get (3) == NULL", ((t_test *)vector_t_get(v, 3)) == NULL);
  expect("vector_t_get (4) == NULL", ((t_test *)vector_t_get(v, 4)) == NULL);
  expect("vector_t_get (5) == NULL", ((t_test *)vector_t_get(v, 5)) == NULL);
  expect("vector_t_get (6) == NULL", ((t_test *)vector_t_get(v, 6)) == NULL);
  expect("vector_t_get (7) == NULL", ((t_test *)vector_t_get(v, 7)) == NULL);
  expect("vector_t_get (8) == NULL", ((t_test *)vector_t_get(v, 8)) == NULL);
  expect("vector_t_get (9) == NULL", ((t_test *)vector_t_get(v, 9)) == NULL);
  expect("vector_t_get (10) == NULL", ((t_test *)vector_t_get(v, 10)) == NULL);
  expect("vector_t_get (100) == NULL", ((t_test *)vector_t_get(v, 100)) == NULL);

  vector_t_resize(v, size);
  expect("vector_t_size (3)", vector_t_size(v) == 3);
  expect("vector_t_get (0) == s1", ((t_test *)vector_t_get(v, 0))->id == s1.id);
  expect("vector_t_get (1) == s1", ((t_test *)vector_t_get(v, 1))->id == s1.id);
  expect("vector_t_get (2) == s1", ((t_test *)vector_t_get(v, 2))->id == s1.id);
  expect("vector_t_get (3) == NULL", ((t_test *)vector_t_get(v, 3)) == NULL);

  vector_t_destroy(v);

  return 0;
}

static char *test_vector_t_mutations()
{
  vector_t *v = vector_t_create(3);
  expect("vector_t_size (3)", vector_t_size(v) == 3);

  t_test s1 = {42};
  t_test s2 = {37};
  t_test s3 = {101};

  vector_t_insert(v, 1, &s1);
  expect("vector_t_insert (1)", vector_t_size(v) == 3);

  expect("vector_t_get (0) == NULL", ((t_test *)vector_t_get(v, 0)) == NULL);
  expect("vector_t_get (1) == s1", ((t_test *)vector_t_get(v, 1))->id == s1.id);
  expect("vector_t_get (2) == NULL", ((t_test *)vector_t_get(v, 2)) == NULL);

  vector_t_insert(v, 1, &s2);
  expect("vector_t_insert (1)", vector_t_size(v) == 3);

  expect("vector_t_get (0) == NULL", ((t_test *)vector_t_get(v, 0)) == NULL);
  expect("vector_t_get (1) == s2", ((t_test *)vector_t_get(v, 1))->id == s2.id);
  expect("vector_t_get (2) == s1", ((t_test *)vector_t_get(v, 2))->id == s1.id);

  vector_t_insert(v, 1, &s3);
  expect("vector_t_insert (1)", vector_t_size(v) == 4);

  expect("vector_t_get (0) == NULL", ((t_test *)vector_t_get(v, 0)) == NULL);
  expect("vector_t_get (1) == s3", ((t_test *)vector_t_get(v, 1))->id == s3.id);
  expect("vector_t_get (2) == s2", ((t_test *)vector_t_get(v, 2))->id == s2.id);
  expect("vector_t_get (3) == s1", ((t_test *)vector_t_get(v, 3))->id == s1.id);

  vector_t_insert(v, 9, &s1);
  expect("vector_t_insert (9)", vector_t_size(v) == 10);

  expect("vector_t_get (0) == NULL", ((t_test *)vector_t_get(v, 0)) == NULL);
  expect("vector_t_get (1) == s3", ((t_test *)vector_t_get(v, 1))->id == s3.id);
  expect("vector_t_get (2) == s2", ((t_test *)vector_t_get(v, 2))->id == s2.id);
  expect("vector_t_get (3) == s1", ((t_test *)vector_t_get(v, 3))->id == s1.id);
  expect("vector_t_get (4) == NULL", ((t_test *)vector_t_get(v, 4)) == NULL);
  expect("vector_t_get (5) == NULL", ((t_test *)vector_t_get(v, 5)) == NULL);
  expect("vector_t_get (6) == NULL", ((t_test *)vector_t_get(v, 6)) == NULL);
  expect("vector_t_get (7) == NULL", ((t_test *)vector_t_get(v, 7)) == NULL);
  expect("vector_t_get (8) == NULL", ((t_test *)vector_t_get(v, 8)) == NULL);
  expect("vector_t_get (9) == s1", ((t_test *)vector_t_get(v, 9))->id == s1.id);

  vector_t_remove(v, 7, 1);
  expect("vector_t_remove (7)", vector_t_size(v) == 10);

  expect("vector_t_get (0) == NULL", ((t_test *)vector_t_get(v, 0)) == NULL);
  expect("vector_t_get (1) == s3", ((t_test *)vector_t_get(v, 1))->id == s3.id);
  expect("vector_t_get (2) == s2", ((t_test *)vector_t_get(v, 2))->id == s2.id);
  expect("vector_t_get (3) == s1", ((t_test *)vector_t_get(v, 3))->id == s1.id);
  expect("vector_t_get (4) == NULL", ((t_test *)vector_t_get(v, 4)) == NULL);
  expect("vector_t_get (5) == NULL", ((t_test *)vector_t_get(v, 5)) == NULL);
  expect("vector_t_get (6) == NULL", ((t_test *)vector_t_get(v, 6)) == NULL);
  expect("vector_t_get (7) == NULL", ((t_test *)vector_t_get(v, 7)) == NULL);
  expect("vector_t_get (8) == s1", ((t_test *)vector_t_get(v, 8))->id == s1.id);
  expect("vector_t_get (9) == NULL", ((t_test *)vector_t_get(v, 9)) == NULL);

  vector_t_remove(v, 7, 10);
  expect("vector_t_remove (7)", vector_t_size(v) == 10);

  expect("vector_t_get (0) == NULL", ((t_test *)vector_t_get(v, 0)) == NULL);
  expect("vector_t_get (1) == s3", ((t_test *)vector_t_get(v, 1))->id == s3.id);
  expect("vector_t_get (2) == s2", ((t_test *)vector_t_get(v, 2))->id == s2.id);
  expect("vector_t_get (3) == s1", ((t_test *)vector_t_get(v, 3))->id == s1.id);
  expect("vector_t_get (4) == NULL", ((t_test *)vector_t_get(v, 4)) == NULL);
  expect("vector_t_get (5) == NULL", ((t_test *)vector_t_get(v, 5)) == NULL);
  expect("vector_t_get (6) == NULL", ((t_test *)vector_t_get(v, 6)) == NULL);
  expect("vector_t_get (7) == NULL", ((t_test *)vector_t_get(v, 7)) == NULL);
  expect("vector_t_get (8) == NULL", ((t_test *)vector_t_get(v, 8)) == NULL);
  expect("vector_t_get (9) == NULL", ((t_test *)vector_t_get(v, 9)) == NULL);

  vector_t_remove(v, 100, 1);
  expect("vector_t_remove (100)", vector_t_size(v) == 10);

  vector_t_push(v, &s1);
  expect("vector_t_push (s1)", vector_t_size(v) == 10);

  expect("vector_t_get (0) == NULL", ((t_test *)vector_t_get(v, 0)) == NULL);
  expect("vector_t_get (1) == s3", ((t_test *)vector_t_get(v, 1))->id == s3.id);
  expect("vector_t_get (2) == s2", ((t_test *)vector_t_get(v, 2))->id == s2.id);
  expect("vector_t_get (3) == s1", ((t_test *)vector_t_get(v, 3))->id == s1.id);
  expect("vector_t_get (4) == s1", ((t_test *)vector_t_get(v, 4))->id == s1.id);
  expect("vector_t_get (5) == NULL", ((t_test *)vector_t_get(v, 5)) == NULL);
  expect("vector_t_get (6) == NULL", ((t_test *)vector_t_get(v, 6)) == NULL);
  expect("vector_t_get (7) == NULL", ((t_test *)vector_t_get(v, 7)) == NULL);
  expect("vector_t_get (8) == NULL", ((t_test *)vector_t_get(v, 8)) == NULL);
  expect("vector_t_get (9) == NULL", ((t_test *)vector_t_get(v, 9)) == NULL);

  vector_t_insert(v, 9, &s1);
  expect("vector_t_insert (9)", vector_t_size(v) == 10);
  expect("vector_t_get (9) == s1", ((t_test *)vector_t_get(v, 9))->id == s1.id);

  vector_t_push(v, &s2);
  expect("vector_t_push (s2)", vector_t_size(v) == 11);

  expect("vector_t_get (0) == NULL", ((t_test *)vector_t_get(v, 0)) == NULL);
  expect("vector_t_get (1) == s3", ((t_test *)vector_t_get(v, 1))->id == s3.id);
  expect("vector_t_get (2) == s2", ((t_test *)vector_t_get(v, 2))->id == s2.id);
  expect("vector_t_get (3) == s1", ((t_test *)vector_t_get(v, 3))->id == s1.id);
  expect("vector_t_get (4) == s1", ((t_test *)vector_t_get(v, 4))->id == s1.id);
  expect("vector_t_get (5) == NULL", ((t_test *)vector_t_get(v, 5)) == NULL);
  expect("vector_t_get (6) == NULL", ((t_test *)vector_t_get(v, 6)) == NULL);
  expect("vector_t_get (7) == NULL", ((t_test *)vector_t_get(v, 7)) == NULL);
  expect("vector_t_get (8) == NULL", ((t_test *)vector_t_get(v, 8)) == NULL);
  expect("vector_t_get (9) == s1", ((t_test *)vector_t_get(v, 9))->id == s1.id);
  expect("vector_t_get (10) == s2", ((t_test *)vector_t_get(v, 10))->id == s2.id);

  vector_t_move(v, 1, 5);
  expect("vector_t_push (1, 5)", vector_t_size(v) == 11);

  expect("vector_t_get (0) == NULL", ((t_test *)vector_t_get(v, 0)) == NULL);
  expect("vector_t_get (1) == NULL", ((t_test *)vector_t_get(v, 1)) == NULL);
  expect("vector_t_get (2) == s2", ((t_test *)vector_t_get(v, 2))->id == s2.id);
  expect("vector_t_get (3) == s1", ((t_test *)vector_t_get(v, 3))->id == s1.id);
  expect("vector_t_get (4) == s1", ((t_test *)vector_t_get(v, 4))->id == s1.id);
  expect("vector_t_get (5) == s3", ((t_test *)vector_t_get(v, 5))->id == s3.id);
  expect("vector_t_get (6) == NULL", ((t_test *)vector_t_get(v, 6)) == NULL);
  expect("vector_t_get (7) == NULL", ((t_test *)vector_t_get(v, 7)) == NULL);
  expect("vector_t_get (8) == NULL", ((t_test *)vector_t_get(v, 8)) == NULL);
  expect("vector_t_get (9) == s1", ((t_test *)vector_t_get(v, 9))->id == s1.id);
  expect("vector_t_get (10) == s2", ((t_test *)vector_t_get(v, 10))->id == s2.id);

  vector_t_move(v, 3, 15);
  expect("vector_t_push (3, 15)", vector_t_size(v) == 16);

  expect("vector_t_get (0) == NULL", ((t_test *)vector_t_get(v, 0)) == NULL);
  expect("vector_t_get (1) == NULL", ((t_test *)vector_t_get(v, 1)) == NULL);
  expect("vector_t_get (2) == s2", ((t_test *)vector_t_get(v, 2))->id == s2.id);
  expect("vector_t_get (3) == NULL", ((t_test *)vector_t_get(v, 3)) == NULL);
  expect("vector_t_get (4) == s1", ((t_test *)vector_t_get(v, 4))->id == s1.id);
  expect("vector_t_get (5) == s3", ((t_test *)vector_t_get(v, 5))->id == s3.id);
  expect("vector_t_get (6) == NULL", ((t_test *)vector_t_get(v, 6)) == NULL);
  expect("vector_t_get (7) == NULL", ((t_test *)vector_t_get(v, 7)) == NULL);
  expect("vector_t_get (8) == NULL", ((t_test *)vector_t_get(v, 8)) == NULL);
  expect("vector_t_get (9) == s1", ((t_test *)vector_t_get(v, 9))->id == s1.id);
  expect("vector_t_get (10) == s2", ((t_test *)vector_t_get(v, 10))->id == s2.id);
  expect("vector_t_get (10) == s2", ((t_test *)vector_t_get(v, 10))->id == s2.id);
  expect("vector_t_get (14) == NULL", ((t_test *)vector_t_get(v, 14)) == NULL);
  expect("vector_t_get (15) == s1", ((t_test *)vector_t_get(v, 15))->id == s1.id);

  vector_t_swap(v, 2, 0);
  expect("vector_t_swap (2, 0)", vector_t_size(v) == 16);

  expect("vector_t_get (0) == s2", ((t_test *)vector_t_get(v, 0))->id == s2.id);
  expect("vector_t_get (1) == NULL", ((t_test *)vector_t_get(v, 1)) == NULL);
  expect("vector_t_get (2) == NULL", ((t_test *)vector_t_get(v, 2)) == NULL);
  expect("vector_t_get (3) == NULL", ((t_test *)vector_t_get(v, 3)) == NULL);
  expect("vector_t_get (4) == s1", ((t_test *)vector_t_get(v, 4))->id == s1.id);
  expect("vector_t_get (5) == s3", ((t_test *)vector_t_get(v, 5))->id == s3.id);

  vector_t_swap(v, 5, 20);
  expect("vector_t_swap (5, 20)", vector_t_size(v) == 21);
  expect("vector_t_get (5) == NULL", ((t_test *)vector_t_get(v, 5)) == NULL);
  expect("vector_t_get (20) == s3", ((t_test *)vector_t_get(v, 20))->id == s3.id);

  vector_t_destroy(v);

  return 0;
}

static char *test_vector_t_copy()
{
  vector_t *v = vector_t_create(6);
  t_test s1 = {42};

  vector_t_set(v, 0, NULL);
  vector_t_set(v, 1, NULL);
  vector_t_set(v, 2, &s1);
  vector_t_set(v, 3, &s1);
  vector_t_set(v, 4, NULL);
  vector_t_set(v, 5, &s1);

  vector_t *vv = vector_t_copy(v);

  expect("vector_t_copy size", vector_t_size(vv) == 6);

  expect("vector_t_get (0) == NULL", ((t_test *)vector_t_get(vv, 0)) == NULL);
  expect("vector_t_get (1) == NULL", ((t_test *)vector_t_get(vv, 1)) == NULL);
  expect("vector_t_get (2) == s1", ((t_test *)vector_t_get(vv, 2))->id == s1.id);
  expect("vector_t_get (3) == s1", ((t_test *)vector_t_get(vv, 3))->id == s1.id);
  expect("vector_t_get (4) == NULL", ((t_test *)vector_t_get(vv, 4)) == NULL);
  expect("vector_t_get (5) == s1", ((t_test *)vector_t_get(vv, 5))->id == s1.id);

  vector_t_destroy(vv);
  vector_t_destroy(v);

  return 0;
}

static char *test_vector_t_reverse()
{
  vector_t *v = vector_t_create(6);
  t_test s1 = {42};

  vector_t_set(v, 0, NULL);
  vector_t_set(v, 1, NULL);
  vector_t_set(v, 2, &s1);
  vector_t_set(v, 3, &s1);
  vector_t_set(v, 4, NULL);
  vector_t_set(v, 5, &s1);

  vector_t_reverse(v);
  expect("vector_t_reverse size", vector_t_size(v) == 6);

  expect("vector_t_get (5) == NULL", ((t_test *)vector_t_get(v, 5)) == NULL);
  expect("vector_t_get (4) == NULL", ((t_test *)vector_t_get(v, 4)) == NULL);
  expect("vector_t_get (3) == s1", ((t_test *)vector_t_get(v, 3))->id == s1.id);
  expect("vector_t_get (2) == s1", ((t_test *)vector_t_get(v, 2))->id == s1.id);
  expect("vector_t_get (1) == NULL", ((t_test *)vector_t_get(v, 1)) == NULL);
  expect("vector_t_get (0) == s1", ((t_test *)vector_t_get(v, 0))->id == s1.id);

  vector_t_destroy(v);

  return 0;
}

static char *test_vector_t_clean()
{
  vector_t *v = vector_t_create(6);
  t_test s1 = {42};

  vector_t_set(v, 0, NULL);
  vector_t_set(v, 1, NULL);
  vector_t_set(v, 2, &s1);
  vector_t_set(v, 3, &s1);
  vector_t_set(v, 4, NULL);
  vector_t_set(v, 5, &s1);

  vector_t_clean(v);
  expect("vector_t_clean size", vector_t_size(v) == 6);

  expect("vector_t_get (0) == NULL", ((t_test *)vector_t_get(v, 0)) == NULL);
  expect("vector_t_get (1) == NULL", ((t_test *)vector_t_get(v, 1)) == NULL);
  expect("vector_t_get (2) == NULL", ((t_test *)vector_t_get(v, 2)) == NULL);
  expect("vector_t_get (3) == NULL", ((t_test *)vector_t_get(v, 3)) == NULL);
  expect("vector_t_get (4) == NULL", ((t_test *)vector_t_get(v, 4)) == NULL);
  expect("vector_t_get (5) == NULL", ((t_test *)vector_t_get(v, 5)) == NULL);

  vector_t_destroy(v);

  return 0;
}

static void vector_t_insert_batch(vector_t *v, size_t size)
{
  t_test s1 = {100000000};

  for (int i = 0; i < size; i++)
  {
    vector_t_insert(v, i, &s1);
  }
}

static void vector_t_push_batch(vector_t *v, size_t size)
{
  t_test s1 = {100000000};

  for (int i = 0; i < size; i++)
  {
    vector_t_push(v, &s1);
  }
}

static void vector_t_remove_batch(vector_t *v, size_t size)
{
  vector_t_remove(v, 0, size);
}

static char *test_vector_t_performance()
{
  vector_t *v = vector_t_create(1000000);
  int elapsed;

  elapsed = with_elapsed(v, 1000000, vector_t_insert_batch);
  expect("vector_t_insert_batch < 10ms", elapsed < 10);
  expect("vector_t_insert_batch size", vector_t_size(v) == 1000000);

  elapsed = with_elapsed(v, 100000, vector_t_push_batch);
  expect("vector_t_push_batch < 50ms", elapsed < 50);
  expect("vector_t_push_batch size", vector_t_size(v) == 1100000);

  elapsed = with_elapsed(v, 100000, vector_t_remove_batch);
  expect("vector_t_remove_batch < 50ms", elapsed < 50);
  expect("vector_t_remove_batch size", vector_t_size(v) == 1100000);
  expect("vector_t_remove_batch compact", vector_t_compact(v) == 1000000);

  vector_t_destroy(v);

  return 0;
}

static char *test_vector_t_iterator()
{
  vector_t *v = vector_t_create(1000000);
  vector_t_insert_batch(v, 1000000);

  vector_t_iterator *i = vector_t_iterator_create(v);
  void *t = NULL;

  while ((t = vector_t_iterator_next(i)) != NULL)
  {
    expect("vector_t_iterator_next < 1000000", vector_t_iterator_cursor(i) < 1000000);
  }

  vector_t_iterator_reset(i);
  expect("vector_t_iterator_reset", vector_t_iterator_cursor(i) == 0);

  vector_t_destroy(v);
  vector_t_iterator_destroy(i);

  return 0;
}

static char *test_matrix_t()
{
  matrix_t *m = matrix_t_create(2, 3);

  expect("matrix_t_cols", matrix_t_cols(m) == 3);
  expect("matrix_t_rows", matrix_t_rows(m) == 2);

  int s[20] = {1, 2, 3, 4, 5, 6};

  for (size_t i = 0; i < matrix_t_rows(m); i++)
    for (size_t j = 0; j < matrix_t_cols(m); j++)
      matrix_t_set(m, i, j, &s[i * matrix_t_cols(m) + j]);

  for (size_t i = 0; i < matrix_t_rows(m); i++)
    for (size_t j = 0; j < matrix_t_cols(m); j++)
      expect("matrix_t_set", (*(int *)matrix_t_get(m, i, j)) == s[matrix_t_idx(m, i, j)]);

  matrix_t_remove(m, 0, 0);
  expect("matrix_t_remove", matrix_t_get(m, 1, 2) == NULL);

  matrix_t_resize(m, 3, 4);

  expect("matrix_t_cols", matrix_t_cols(m) == 4);
  expect("matrix_t_rows", matrix_t_rows(m) == 3);

  matrix_t_remove_row(m, 1);

  for (size_t i = 0; i < matrix_t_cols(m); i++)
    expect("matrix_t_remove_row", matrix_t_get(m, matrix_t_rows(m) - 1, i) == NULL);

  expect("matrix_t_col", matrix_t_col(m, 2) == 2);
  expect("matrix_t_row", matrix_t_row(m, 2) == 0);

  expect("matrix_t_col", matrix_t_col(m, 9) == 1);
  expect("matrix_t_row", matrix_t_row(m, 9) == 2);

  matrix_t_destroy(m);

  return 0;
}

static char *test_node_t()
{
  int s[4] = {1, 37, 42, 101};

  node_t *head = node_t_create(&s[2], NULL);
  node_t *tail = NULL;
  node_t *iter = NULL;

  expect("node_t_peek", (*(int *)node_t_peek(head)) == s[2]);
  expect("node_t_peek", (*(int *)node_t_peek(head)) == s[2]);

  node_t_unshift(&s[1], &head);
  expect("node_t_unshift", (*(int *)node_t_peek(head)) == s[1]);

  expect("node_t_shift", (*(int *)node_t_shift(&head)) == s[1]);
  expect("node_t_shift", (*(int *)node_t_peek(head)) == s[2]);

  node_t_unshift(&s[1], &head);
  expect("node_t_unshift", (*(int *)node_t_peek(head)) == s[1]);

  node_t_unshift(&s[0], &head);
  expect("node_t_unshift", (*(int *)node_t_peek(head)) == s[0]);

  tail = node_t_push(&s[3], &head);
  expect("node_t_push", (*(int *)node_t_peek(head)) == s[0]);
  expect("node_t_push", (*(int *)node_t_peek(tail)) == s[3]);

  iter = head;
  for (size_t i = 0; i < sizeof(s) / sizeof(s[0]); i++)
  {
    expect("iter", (*(int *)node_t_peek(iter)) == s[i]);
    iter = node_t_next(iter); 
  }

  expect("node_t_size", node_t_size(head) == 4);
  expect("node_t_size", node_t_size(head) == 4);

  node_t_destroy(head);
  return 0;
}

static char *all_tests()
{
  test(test_vector_t_create);
  test(test_vector_t_resize);
  test(test_vector_t_set_get);
  test(test_vector_t_compact);
  test(test_vector_t_mutations);
  test(test_vector_t_copy);
  test(test_vector_t_reverse);
  test(test_vector_t_clean);
  test(test_vector_t_iterator);
  test(test_vector_t_performance);
  test(test_matrix_t);
  test(test_node_t);

  return 0;
}

int main()
{
  char *result = all_tests();

  if (result != 0)
    printf("%s\nFAILED!\n", result);
  else
    printf("All tests passed.\n");

  printf("Tests ran: %d\n", tests_ran);

  return result != 0;
}