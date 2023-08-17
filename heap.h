// SPDX-License-Identifier: MIT
/**
 * @file heap.h
 * @brief malloc, ralloc calls
 * @version 0.1
 * @date 2023-01-07
 *
 * @copyright Copyright (c) 2023 lightningspirit
 */

#include <stddef.h>

#ifndef HEAP_H
#define HEAP_H

/**
 * @brief allocates or reallocates memory safely
 *
 * Inspiration:
 * https://stackoverflow.com/questions/26831981/should-i-check-if-malloc-was-successful
 *
 * @param size
 * @return void*
 */
void *malloc_realloc(size_t size, void *data);

#endif