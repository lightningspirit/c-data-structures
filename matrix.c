// SPDX-License-Identifier: MIT
/**
 * @file matrix.c
 * @brief Implementation of matrix operations using vector
 * @version 0.1
 * @date 2023-05-02
 *
 * This file contains the implementation of the matrix functions
 * defined in matrix.h.
 *
 * @copyright Copyright (c) 2023 lightningspirit
 */

#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include "heap.h"

struct matrix_t
{
  size_t cols;
  size_t rows;
  vector_t *vector;
};

matrix_t *matrix_t_create(const size_t rows, const size_t cols)
{
  matrix_t *matrix = (matrix_t *)malloc_realloc(sizeof(matrix_t), NULL);
  matrix->cols = cols;
  matrix->rows = rows;
  matrix->vector = vector_t_create(rows * cols);

  return matrix;
}

void matrix_t_resize(matrix_t *matrix, const size_t rows, const size_t cols)
{
  matrix->cols = cols;
  matrix->rows = rows;

  vector_t_resize(matrix->vector, cols * rows);
}

void matrix_t_destroy(matrix_t *matrix)
{
  vector_t_destroy(matrix->vector);
  free(matrix);
}

size_t matrix_t_cols(matrix_t *matrix)
{
  return matrix->cols;
}

size_t matrix_t_rows(matrix_t *matrix)
{
  return matrix->rows;
}

void matrix_t_set(matrix_t *matrix, const size_t row, const size_t col, void *item)
{
  if (col < matrix->cols && row < matrix->rows)
  {
    size_t index = matrix_t_idx(matrix, row, col);
    vector_t_set(matrix->vector, index, item);
  }
}

void *matrix_t_get(matrix_t *matrix, const size_t row, const size_t col)
{
  if (col < matrix->cols && row < matrix->rows)
  {
    size_t index = matrix_t_idx(matrix, row, col);
    return vector_t_get(matrix->vector, index);
  }

  return NULL;
}

matrix_t *matrix_t_copy(matrix_t *matrix)
{
  matrix_t *copied = matrix_t_create(matrix->rows, matrix->cols);
  copied->vector = vector_t_copy(matrix->vector);
  return copied;
}

void matrix_t_remove(matrix_t *matrix, const size_t row, const size_t col)
{
  if (row >= matrix->rows || col >= matrix->cols)
    return;

  size_t index = matrix_t_idx(matrix, row, col);
  vector_t_remove(matrix->vector, index, 1);
}

void matrix_t_remove_row(matrix_t *matrix, const size_t row)
{
  if (row >= matrix->rows)
    return;

  size_t start = matrix_t_idx(matrix, row, 0);
  size_t end = matrix_t_idx(matrix, row, matrix->cols - 1);
  vector_t_remove(matrix->vector, start, end);
}

size_t matrix_t_idx(matrix_t *matrix, const size_t row, const size_t col)
{
  return row * matrix->cols + col;
}

size_t matrix_t_col(matrix_t *matrix, size_t index)
{
  return index % matrix->cols;
}

size_t matrix_t_row(matrix_t *matrix, size_t index)
{
  return index / matrix->cols;
}