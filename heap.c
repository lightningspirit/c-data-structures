// SPDX-License-Identifier: MIT
/**
 * @file heap.c
 * @brief malloc and ralloc safe calls
 * @version 0.1
 * @date 2023-01-07
 *
 * @copyright Copyright (c) 2023 lightningspirit
 */

#include <stdlib.h>

void *malloc_realloc(size_t size, void *data)
{
  return data == NULL ? malloc(size) : realloc(data, size);
}
