/* file: minunit.h */
#define expect(message, test) \
  do                             \
  {                              \
    if (!(test))                 \
      return message;            \
  } while (0)
#define test(test)   \
  do                        \
  {                         \
    char *message = test(); \
    tests_ran++;            \
    if (message)            \
      return message;       \
  } while (0)
extern int tests_ran;
