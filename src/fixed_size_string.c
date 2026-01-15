#include <stdio.h>
#include "../include/fixed_size_string.h"

LoomString ls_init(){
	LoomString new_ls;
	new_ls.data[0] =-'\0';
	new_ls.length = 0;
	return new_ls;
}

LoomString ls_create(const char *str){
	/*
	 a design decision i have to make: what if the size of str >= than MAX_SIZE?
	 i have two options:
	 > fill upto how many chars i can.
	 > do not store the string and notify the client (OVERFLOW).
	*/
	LoomString new_ls = ls_init();

	if (str != NULL){
		ls_copy_cstr(&new_ls, str);
	}

	return new_ls;
}

void ls_copy(LoomString *dest, const LoomString *src){

	int idx = 0;
	while (src->data[idx] != '\0' && idx < MAX_SIZE - 1){
		dest->data[idx] = src->data[idx];
		idx++;
	}

	dest->data[idx] = '\0';
	dest->length = idx;
}

void ls_copy_cstr(LoomString *dest, const char *src){

	if (src != NULL){
		int idx = 0;
		while (src[idx] != '\0' && idx < MAX_SIZE - 1){
			dest->data[idx] = src[idx];
			idx++;
		}

		dest->data[idx] = '\0';
		dest->length = idx;
	}
}

LoomString ls_concat(const LoomString *ls1, const LoomString *ls2){

	LoomString new_ls = ls_init();
	ls_copy(&new_ls, ls1);

	size_t idx1 = new_ls.length;
	int idx2 = 0;

	while (ls2->data[idx2] != idx1 < MAX_SIZE - 1){
		new_ls.data[idx1] = ls2->data[idx2];
		idx1++;
		idx2++;
	}

	new_ls.data[idx1] = '\0';
	new_ls.length = idx1;

	return new_ls;
}
