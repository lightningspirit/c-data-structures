/**
 * @file test.c
 * @author lightningspirit@gmail.com
 * @brief Unit tests
 * @version 0.1
 * @date 2023-01-07
 *
 * @copyright Copyright (c) 2023 MIT License
 *
 */
#include <stdio.h>
#include "test.h"
#include "malloc.h"
#include "vector.h"

typedef struct
{
  int id;
} t_test;

int tests_ran = 0;

static char *test_t_vector_create()
{
  t_vector *v = t_vector_create(1);
  expect("t_vector_create", v != NULL);
  return 0;
}

static char *test_t_vector_size()
{
  t_vector *v = t_vector_create(5);
  expect("t_vector_size", t_vector_size(v) == 5);
  return 0;
}

static char *test_t_vector_destroy()
{
  t_vector *v = t_vector_create(5);
  t_vector_destroy(v);
  expect("t_vector_destroy", sizeof(v) != sizeof(t_vector));
  return 0;
}

static char *test_t_vector_set()
{
  t_vector *v = t_vector_create(1);
  t_test *s1, *s2;
  
  s1 = malloc_safe(sizeof(*s1));
  s1->id = 42;

  t_vector_set(v, 0, s1);
  expect("t_vector_set", ((t_test *) v->elements[0])->id == s1->id);

  s2 = malloc_safe(sizeof(*s2));
  s2->id = 100000000;

  t_vector_set(v, 10, s2);
  expect("t_vector_set (out of boundaries)", ((t_test *) v->elements[10])->id == s2->id);

  return 0;
}

static char *test_t_vector_push()
{
  t_vector *v = t_vector_create(1);
  t_test *s1, *s2;
  
  s1 = malloc_safe(sizeof(*s1));
  s1->id = 42;

  s2 = malloc_safe(sizeof(*s2));
  s2->id = 100000000;

  t_vector_push(v, s2);
  expect("t_vector_push (size == 2)", t_vector_size(v) == 2);
  expect("t_vector_push (right element)", ((t_test *) v->elements[1])->id == s2->id);

  return 0;
}

static char *test_t_vector_first()
{
  t_vector *v = t_vector_create(2);
  t_test *s1, *s2;

  s1 = malloc_safe(sizeof(*s1));
  s1->id = 42;

  s2 = malloc_safe(sizeof(*s2));
  s2->id = 100000000;

  t_vector_set(v, 0, s1);
  t_vector_set(v, 1, s2);
  
  expect("t_vector_first", t_vector_first(v) == s1);

  return 0;
}

static char *test_t_vector_last()
{
  t_vector *v = t_vector_create(2);
  t_test *s1, *s2;

  s1 = malloc_safe(sizeof(*s1));
  s1->id = 42;

  s2 = malloc_safe(sizeof(*s2));
  s2->id = 100000000;

  t_vector_set(v, 0, s1);
  t_vector_set(v, 1, s2);
  
  expect("t_vector_last", t_vector_last(v) == s2);

  return 0;
}


static char *test_t_vector_swap()
{
  t_vector *v = t_vector_create(2);
  t_test *s1, *s2;
  
  s1 = malloc_safe(sizeof(*s1));
  s1->id = 42;

  s2 = malloc_safe(sizeof(*s2));
  s2->id = 100000000;

  t_vector_set(v, 0, s1);
  t_vector_set(v, 1, s2);

  t_vector_swap(v, 0, 1);
  expect("t_vector_swap", ((t_test *) v->elements[0])->id == s2->id);
  expect("t_vector_swap", ((t_test *) v->elements[1])->id == s1->id);

  return 0;
}

static char *test_t_vector_reverse()
{
  t_vector *v = t_vector_create(3);
  t_test *s1, *s2, *s3;
  
  s1 = malloc_safe(sizeof(*s1));
  s1->id = 42;

  s2 = malloc_safe(sizeof(*s2));
  s2->id = 100000000;

  s3 = malloc_safe(sizeof(*s3));
  s3->id = 1;

  t_vector_set(v, 0, s1);
  t_vector_set(v, 1, s2);
  t_vector_set(v, 2, s3);

  t_vector_reverse(v);
  expect("t_vector_reverse", v->elements[0] == s3);
  expect("t_vector_reverse", v->elements[2] == s1);

  return 0;
}

static char *test_t_vector_pop()
{
  t_vector *v = t_vector_create(2);
  t_test *s1, *s2;
  
  s1 = malloc_safe(sizeof(*s1));
  s1->id = 42;

  s2 = malloc_safe(sizeof(*s2));
  s2->id = 100000000;

  t_vector_set(v, 0, s1);
  t_vector_set(v, 1, s2);

  t_vector_pop(v);
  expect("t_vector_pop (size)", t_vector_size(v) == 1);
  expect("t_vector_pop", v->elements[0] == s1);

  return 0;
}

static char *test_t_vector_shift()
{
  t_vector *v = t_vector_create(1);
  t_test *s1, *s2;
  
  s1 = malloc_safe(sizeof(*s1));
  s1->id = 42;

  s2 = malloc_safe(sizeof(*s2));
  s2->id = 100000000;

  t_vector_set(v, 0, s1);
  t_vector_set(v, 1, s2);

  t_vector_shift(v);
  expect("t_vector_shift (size)", t_vector_size(v) == 1);
  expect("t_vector_shift", v->elements[0] == s2);

  return 0;
}

static char *test_t_vector_clean()
{
  t_vector *v = t_vector_create(1);

  t_vector_set(v, 0, malloc_safe(sizeof(t_test)));

  t_vector_clean(v);
  expect("t_vector_clean", v->elements == NULL);

  return 0;
}

static char *all_tests()
{
  test(test_t_vector_create);
  test(test_t_vector_size);
  test(test_t_vector_destroy);
  test(test_t_vector_set);
  test(test_t_vector_push);
  test(test_t_vector_first);
  test(test_t_vector_last);
  test(test_t_vector_swap);
  test(test_t_vector_reverse);
  test(test_t_vector_pop);
  test(test_t_vector_shift);
  test(test_t_vector_clean);

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