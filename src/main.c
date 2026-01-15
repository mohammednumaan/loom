#include <stdio.h>
#include "../include/fixed_size_string.h"

int main(){
	LoomString str1 = ls_create("hello");
	LoomString str2 = ls_create("world");

	printf("%s %lu\n", str1.data, str1.length);
	printf("%s %lu\n", str2.data, str2.length);
}

