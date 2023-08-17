// SPDX-License-Identifier: MIT
/**
 * @file matrix.h
 * @brief Matrix data structure using vector implementation
 * @version 0.1
 * @date 2023-05-02
 *
 * This header file defines the matrix structure and functions for
 * creating, manipulating, and destroying matrices.
 *
 * @copyright Copyright (c) 2023 lightningspirit
 */

#include <stddef.h>
#include "vector.h"

#ifndef MATRIX_H
#define MATRIX_H

/**
 * @brief Matrix data structure
 *
 * cols: number of columns
 * rows: number of rows
 * vector: underlying vector to store matrix elements
 */
typedef struct matrix_t matrix_t;

/**
 * @brief Creates a new matrix instance
 *
 * @return matrix_t* Pointer to the created matrix
 */
matrix_t *matrix_t_create(const size_t rows, const size_t cols);

/**
 * @brief Resizes a matrix to the specified number of columns and rows.
 *
 * This function resizes the given matrix to have the specified number of columns and rows.
 * If the new size is larger than the current size, the new elements are initialized to 0
 * or NULL (depending on the data type). If the new size is smaller, the excess elements
 * are discarded.
 *
 * @param matrix Pointer to the matrix to be resized.
 * @param rows The new number of columns.
 * @param cols The new number of rows..
 */
void matrix_t_resize(matrix_t *matrix, const size_t rows, const size_t cols);

/**
 * @brief Destroys a matrix and frees its memory
 *
 * @param matrix Pointer to the matrix to destroy
 */
void matrix_t_destroy(matrix_t *matrix);

/**
 * @brief Retrieves the number of columns
 *
 * @param matrix Pointer to the matrix to destroy
 */
size_t matrix_t_cols(matrix_t *matrix);

/**
 * @brief Retrieves the number of rows
 *
 * @param matrix Pointer to the matrix to destroy
 */
size_t matrix_t_rows(matrix_t *matrix);

/**
 * @brief Sets the value at the specified column and row
 *
 * @param matrix Pointer to the matrix
 * @param row Column index
 * @param col Row index
 * @param item Pointer to the item to set
 */
void matrix_t_set(matrix_t *matrix, const size_t row, const size_t col, void *item);

/**
 * @brief Gets the value at the specified column and row
 *
 * @param matrix Pointer to the matrix
 * @param row Column index
 * @param col Row index
 * @return void* Pointer to the item at the specified location
 */
void *matrix_t_get(matrix_t *matrix, const size_t row, const size_t col);

/**
 * @brief Copies the matrix
 *
 * @param matrix Pointer to the matrix
 * @return matrix_t New matrix
 */
matrix_t *matrix_t_copy(matrix_t *matrix);

/**
 * @brief Deletes the value at the specified column and row
 *
 * @param matrix Pointer to the matrix
 * @param row Column index
 * @param col Row index
 */
void matrix_t_remove(matrix_t *matrix, const size_t row, const size_t col);

/**
 * @brief Deletes the specified row
 *
 * @param matrix Pointer to the matrix
 * @param row Row index
 */
void matrix_t_remove_row(matrix_t *matrix, const size_t row);

/**
 * @brief Retrieves the internal index for given cell
 *
 * @param matrix Pointer to the matrix
 * @param row Column index
 * @param col Row index
 * @return size_t The index corresponding to the given cell.
 */
size_t matrix_t_idx(matrix_t *matrix, const size_t row, const size_t col);

/**
 * @brief Retrieves the column index corresponding to a given index in the matrix's underlying vector representation.
 *
 * This function calculates and returns the column index in the matrix for a given index in its underlying vector representation.
 *
 * @param matrix Pointer to the matrix.
 * @param index Index in the matrix's underlying vector representation.
 * @return size_t The column index corresponding to the given index.
 */
size_t matrix_t_col(matrix_t *matrix, size_t index);

/**
 * @brief Retrieves the row index corresponding to a given index in the matrix's underlying vector representation.
 *
 * This function calculates and returns the row index in the matrix for a given index in its underlying vector representation.
 *
 * @param matrix Pointer to the matrix.
 * @param index Index in the matrix's underlying vector representation.
 * @return size_t The row index corresponding to the given index.
 */
size_t matrix_t_row(matrix_t *matrix, size_t index);

#endif // MATRIX_H