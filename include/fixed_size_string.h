#define MAX_SIZE 20

typedef struct {
	char data[MAX_SIZE];
	size_t length;
} LoomString;

LoomString ls_create(const char *str);

void ls_copy(LoomString *dest, const LoomString *src);
void ls_copy_cstr(LoomString *dest, const char *src);


LoomString ls_concat(const LoomString *ls0, const LoomString *ls2);
