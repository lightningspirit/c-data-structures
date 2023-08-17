# c-data-structures
Implementation of data structures for C language

### Supported
- `vector_t` a simple dynamically allocated vector implementation
- `matrix_t` implementation using vector
- `node_t` a simple linked list implementation using only node structure

### Usage
```c
#include "vector.h"
#include "matrix.h"
#include "node.h"

int main() {
  // create vector with size = 3
  vector_t *v = vector_t_create(3);

  int i = 42;
  vector_t_set(v, 0, &i);

  // it's the same pointer
  (*(int *)vector_t_get(v, 0)) == i

  int j = 101;
  // insert j in 3rd position
  vector_t_insert(v, 2, &j);
  // remove two positions, starting in index 1, positions are set to `NULL`
  // does not actually resize the vector
  vector_t_remove(v, 1, 2);

  // matrix of 2 x 3
  matrix_t *m = matrix_t_create(2, 3);

  matrix_t_cols(m) == 3;
  matrix_t_rows(m) == 2;


  int s[4] = {1, 37, 42, 101};

  // head(42) -> NULL
  node_t *head = node_t_create(&s[2], NULL);
  node_t *tail = NULL;

  // head(37) -> next(42) -> NULL
  node_t_unshift(&s[1], &head);
  
  // head(1) -> next(37) -> next(42) -> NULL
  node_t_unshift(&s[0], &head);

  // head(1) -> next(37) -> next(42) -> next(101) -> NULL
  tail = node_t_push(&s[3], &head);

  // head(1)
  node_t_peek(head);

  // tail(101)
  node_t_peek(tail);

  // i = 1
  // head(37) -> next(42) -> next(101) -> NULL
  int i = *(int *)node_t_shift(&head);

  // head(37)
  node_t_peek(head);

  // do not forget to free memory
  node_t_destroy(head);
  vector_t_destroy(v);
  matrix_t_destroy(m);

  // check out test.c for all details
}
```
