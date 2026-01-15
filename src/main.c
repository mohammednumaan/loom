#include <stdio.h>
#include "../include/fixed_size_string.h"

int main(){
	LoomString str1 = ls_create("hello");
	LoomString str2 = ls_create("world");

	printf("%s %lu\n", str1.data, str1.length);
	printf("%s %lu\n", str2.data, str2.length);

	char randomStr[] = "random string";
	ls_copy_cstr(&str1, randomStr);

	printf("copied strings: %s %lu\n", str1.data, str1.length);

	LoomString concat = ls_concat(&str1, &str2);
	printf("concatenated strings %s %lu", concat.data, concat.length);
}

