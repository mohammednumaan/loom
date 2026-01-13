#define MAX_FIXED_STRING_SIZE 20

struct FixedString {
	char data[MAX_FIXED_STRING_SIZE];
	int length;
};

struct FixedString create_string(char *input);
struct FixedString concat_string(struct FixedString s1, struct FixedString s2);
int string_length(struct FixedString str);


