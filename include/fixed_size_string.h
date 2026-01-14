#define MAX_FIXED_STRING_SIZE 20

struct FixedString {
	char data[MAX_FIXED_STRING_SIZE];
	int length;
};

// prototype defnition for creating strings
struct FixedString str_from_cstr(const char *str);
struct FixedString str_from_fs(struct FixedString fs);

// prototype defnition for copying strings
void str_copy_from_cstr(struct FixedString *dest, const char *src);
void str_copy_from_fs(struct FixedString *dest, const struct FixedString *src);

// prototype defnition for concatenating strings
struct FixedString str_cat_from_fs(struct FixedString *s1, struct FixedString *s2);
struct FixedString str_cat_from_cstr(const char *str1, const char *str2);

// other prototypes (more will be defined soon)
int string_length(struct FixedString str);
