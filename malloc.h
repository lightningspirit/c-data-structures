#include <stddef.h>

#ifndef MALLOC_SAFE_H
#define MALLOC_SAFE_H
/**
 * @brief allocates or reallocates memory safely
 * 
 * Inspiration:
 * https://stackoverflow.com/questions/26831981/should-i-check-if-malloc-was-successful
 * 
 * @param size 
 * @return void* 
 */
void *malloc_realloc_safe(size_t size, void *data);
/**
 * @brief allocates memory safely
 * 
 * @param size 
 * @return void* 
 */
void *malloc_safe(size_t size);
/**
 * @brief reallocates memory safely
 * 
 * @param size 
 * @return void* 
 */
void *realloc_safe(void *data, size_t size);
#endif
