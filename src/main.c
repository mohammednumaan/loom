#include <stdio.h>
#include "../include/loom.h"

int main(){

	LoomString ls1 = ls_init();
	ls_create(&ls1, "old string");

	LoomString ls2 = ls_init();
	ls_create(&ls2, "new string with a different length");


	printf("before copy: %s %lu\n", ls1.ptr, ls1.length);
	printf("src string to copy: %s %lu\n", ls2.ptr, ls2.length);
	ls_copy(&ls1, &ls2);
	printf("after copy: %s %lu", ls1.ptr, ls1.length);


}

