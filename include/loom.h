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

LoomString ls_init();
LoomResult ls_create(LoomString *ls, const char *str);

LoomResult ls_copy(LoomString *dest, const LoomString *src);
LoomResult ls_realloc(LoomString *ls, size_t newLen);


size_t ls_length(const LoomString *ls);
