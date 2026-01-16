#include <stdlib.h>
#include <string.h>
#include "../include/loom.h"

size_t ls_length(const LoomString *ls) {
	return ls->length;
}

LoomString ls_init(){
	LoomString ls;
	ls.ptr = NULL;

	ls.length = 0;
	return ls;
}

LoomResult ls_create(LoomString *ls, const char *str){
	if (ls == NULL || str == NULL){
		return LOOM_NULL_PTR;
	}
	
	size_t strLen = strlen(str);
	char *ptr = (char *) malloc(strLen + 1);

	if (ptr == NULL){
		return LOOM_ALLOC_FAIL;
	}
	
	memcpy(ptr, str, strLen);
	ptr[strLen] = '\0';

	ls->ptr = ptr;
	ls->length = strLen;
	return LOOM_OK;
}

LoomResult ls_copy(LoomString *dest, const LoomString *src){
	if(src == NULL || dest == NULL){
		return LOOM_NULL_PTR;
	}

	size_t srcLen = ls_length(src);
	size_t destLen = ls_length(dest);

	if (srcLen >= destLen){
		ls_realloc(dest, srcLen + 1);
	}


	memcpy(dest->ptr, src->ptr, srcLen + 1);
	dest->length = srcLen;
	return LOOM_OK;
}

LoomResult ls_realloc(LoomString *ls,  size_t newLen){
	/*
		realloc can do 2 things:
		> expand/shrink the existing memory
		> completely allocate a new block and free up the old one
	*/

	if (ls == NULL){
		return LOOM_NULL_PTR;
	}
	char *newPtr = (char *) realloc(ls->ptr, newLen);
	if (newPtr == NULL){
		return LOOM_REALLOC_FAIL;
	}

	// if its a completely new block, the existing memory is invalid
	// so i re-point it to the new memory block
	if (ls->ptr != newPtr){
		ls->ptr = newPtr;
	}

	return LOOM_OK;

}
