#include <stddef.h>

#define MAX_SIZE 20

typedef struct {
	char data[MAX_SIZE];
	size_t length;
} LoomString;

enum LoomCodes {
	LOOM_OK = 0,
	LOOM_OVERFLOW,
	LOOM_NULL_PTR,
};

LoomString ls_init();
enum LoomCodes ls_create(LoomString *ls, const char *str);

enum LoomCodes ls_copy(LoomString *dest, const LoomString *src);
enum LoomCodes ls_copy_str(LoomString *dest, const char *src);

enum LoomCodes ls_concat(const LoomString *ls1, const LoomString *ls2, LoomString *out);
enum LoomCodes ls_concat_str(const LoomString *ls, const char *str, LoomString *out);

enum LoomCodes ls_append_char(LoomString *ls, char ch);
enum LoomCodes ls_append_str(LoomString *ls, const char *str);
