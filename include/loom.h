#ifndef LOOM_H
#define LOOM_H

#include <stddef.h>

typedef struct {
	char *ptr;
	size_t length;
} LoomString;

typedef enum {
	LOOM_OK = 0,
	LOOM_NULL_PTR,
	LOOM_ALLOC_FAIL,
	LOOM_REALLOC_FAIL,
} LoomResult;

#define ls_len(ls) ((ls)->length)

#define CHECK_PTR(ls) if ((ls) == NULL || (ls)->ptr == NULL) return LOOM_NULL_PTR
#define CHECK_CSTR(str) if ((str) == NULL) return LOOM_NULL_PTR

LoomString ls_init();
LoomResult ls_new(LoomString *ls, const char *str);

LoomResult ls_copy(LoomString *dest, const LoomString *src);
LoomResult ls_copy_cstr(LoomString *dest, const char *src);

LoomResult ls_concat(const LoomString *ls1, const LoomString *ls2,  LoomString *res);
LoomResult ls_concat_cstr(const LoomString *ls1, const char *str,  LoomString *res);

LoomResult ls_append(LoomString *ls1, const LoomString *ls2);
LoomResult ls_append_cstr(LoomString *ls, const char *str);
LoomResult ls_append_char(LoomString *ls, char ch);

LoomResult ls_realloc(LoomString *ls,  size_t newLen);
LoomResult ls_free(LoomString *ls);

#endif
