#include <stdio.h>
#include "../include/fixed_size_string.h"

int main(){
	// struct FixedString s1 = str_from_cstr("hello");
	// struct FixedString s2 = str_from_cstr("world");
	// struct FixedString concat = str_cat_from_fs(s1, s2);
	struct FixedString s1 = str_from_cstr(NULL);
	str_copy_from_cstr(&s1, "luqmaan");

	struct FixedString s2 = str_from_cstr(NULL);
	str_copy_from_cstr(&s2, " is goo");

	struct FixedString concat1 = str_cat_from_fs(&s1, &s2);
	struct FixedString concat2 = str_cat_from_cstr("hello", " world");

	printf("%s %d", concat2.data, concat2.length);
	
}
