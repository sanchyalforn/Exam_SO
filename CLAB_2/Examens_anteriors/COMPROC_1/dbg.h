/* Adapted from http://c.learncodethehardway.org/book/ex20.html */
/* enricm  2015 */

#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

char *color_green= "\033[00;32m";
char *color_red = "\033[01;31m";
char *color_end = "\033[00m";

#ifdef NDEBUG

#define debug(M, ...)

#else

#define debug(M, ...) \
  fprintf(stderr, "%s[DEBUG]%s %s:%d: " M "\n", color_green, color_end, __FILE__, __LINE__, ##__VA_ARGS__)

#endif

#define clean_errno() \
  (errno == 0 ? "None" : strerror(errno))

#define panic(M, ...) { \
  fprintf(stderr, "%s[ERROR]%s (%s:%d: errno: %s) " M "\n", color_red, color_end, __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__); \
  exit(EXIT_FAILURE); \
} while(0)

#endif
