#include <stdio.h>
#include "../include/loom.h"

int main(){

	LoomString ls1 = ls_init();
	ls_create(&ls1, "hello");

	LoomString ls2 = ls_init();
	ls_create(&ls2, "void");

	LoomString res = ls_init();
	ls_concat_cstr(&ls1, "numaan!", &res);

	printf("after concatenation: %s %lu\n", res.ptr, res.length);


}

