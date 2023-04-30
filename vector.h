#include <stddef.h>

#ifndef T_VECTOR_H
#define T_VECTOR_H
#define T_VECTOR_FREE_ELEMS 1;
/**
 * @brief creates a generic vector
 * 
 * Must be instantiated with t_vector_create.
 * 
 */
typedef struct {
  size_t size;
  void **elements;
} t_vector;

/**
 * @brief create a new t_vector
 * 
 * @param size 
 * @return t_vector* 
 */
t_vector* t_vector_create(size_t size);

/**
 * @brief destroy a t_vector
 * 
 * @param vector 
 */
void t_vector_destroy(t_vector *vector);

/**
 * @brief clean t_vector
 * 
 * @param vector 
 */
void t_vector_clean(t_vector *vector);

/**
 * @brief get t_vector size
 * 
 * @param vector 
 */
size_t t_vector_size(t_vector *vector);

/**
 * @brief resize a t_vector
 * 
 * all new positions are initialized with no value
 * 
 * @param vector 
 * @param size 
 */
void t_vector_resize(t_vector *vector, size_t size);

/**
 * @brief shrink size to non-null values of t_vector
 * 
 * @param vector 
 */
void t_vector_compact(t_vector *vector);

/**
 * @brief insert element in the last position of t_vector
 * 
 * side-effect: resizes t_vector
 * 
 * @param vector 
 * @param element 
 */
void t_vector_push(t_vector *vector, void *element);

/**
 * @brief replace position of t_vector with element
 * 
 * @param vector 
 * @param position 
 * @param element 
 */
void t_vector_set(t_vector *vector, size_t position, void *element);

/**
 * @brief swap two elements
 * 
 * @param vector 
 * @param pos1 
 * @param pos2 
 */
void t_vector_swap(t_vector *vector, size_t pos1, size_t pos2);

/**
 * @brief fetch element on given position of t_vector
 * 
 * @param vector 
 * @param position 
 */
void* t_vector_get(t_vector *vector, size_t position);

/**
 * @brief remove element in position
 * 
 * side-effect: resizes t_vector
 * 
 * @param vector 
 * @param position 
 */
void t_vector_remove(t_vector *vector, size_t position);

/**
 * @brief remove last element of t_vector
 * 
 * side-effect: resizes t_vector
 * 
 * @param vector 
 */
void t_vector_pop(t_vector *vector);

/**
 * @brief remove first element of t_vector
 * 
 * side-effect: resizes t_vector
 * 
 * @param vector 
 */
void t_vector_shift(t_vector *vector);

/**
 * @brief fetch first element of t_vector
 * 
 * @param vector 
 * @return void* 
 */
void* t_vector_first(t_vector *vector);

/**
 * @brief fetch last element of t_vector
 * 
 * @param vector 
 * @return void* 
 */
void* t_vector_last(t_vector *vector);

/**
 * @brief reverse the provided t_vector
 * 
 * @param vector 
 */
void t_vector_reverse(t_vector *vector);

#endif
