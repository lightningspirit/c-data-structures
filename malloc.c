/**
 * @file malloc.c
 * @author lightningspirit@gmail.com
 * @brief Malloc Safe implementation
 * @version 0.1
 * @date 2023-01-07
 *
 * @copyright Copyright (c) 2023 MIT License
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void *malloc_realloc_safe(size_t size, void *data)
{
  void *allocation = data == NULL ? malloc(size) : realloc(data, size);

  if (allocation == NULL) {
    fprintf(stderr, "error: calling `%s`, not able to allocate memory", data == NULL ? "malloc" : "realloc");
    exit(1);
  }

  return allocation;
}

void *malloc_safe(size_t size)
{
  return malloc_realloc_safe(size, NULL);
}

void *realloc_safe(size_t size, void *data)
{
  return malloc_realloc_safe(size, data);
}