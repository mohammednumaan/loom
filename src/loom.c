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

LoomResult ls_copy_cstr(LoomString *dest, const char *src){
	if(src == NULL || dest == NULL){
		return LOOM_NULL_PTR;
	}

	size_t srcLen = strlen(src);
	size_t destLen = ls_length(dest);

	if (srcLen >= destLen){
		ls_realloc(dest, srcLen + 1);
	}
	
	memcpy(dest->ptr, src, srcLen + 1);
	dest->length = srcLen;
	return LOOM_OK;
}

LoomResult ls_concat(const LoomString *ls1, const LoomString *ls2, LoomString *res){

	if(ls1 == NULL || ls2 == NULL || res == NULL){
		return LOOM_NULL_PTR;
	}

	size_t len1 = ls_length(ls1);
	size_t len2 = ls_length(ls2);
	size_t resLen = ls_length(res);

	if (len1 + len2 >= resLen){
		LoomResult result = ls_realloc(res, len1 + len2 + 1);
		if (result != LOOM_OK){
			return result;
		};
	}

	// this copies the content from ls1 to res (len1 bytes)
	memcpy(res->ptr, ls1->ptr, len1);
	// because res is a pointer, we can use pointer arithmetic
	// so the first arg for memcpy should be (res + len1)
	// res gives the first character's address, doing + len1 gives
	// us res[len + 1] address, and we can copy ls2 content from res + len1 to len2 
	memcpy((res->ptr + len1) , ls2->ptr, len2 + 1);
	res->length = len1 + len2;
	return LOOM_OK;
}

LoomResult ls_concat_cstr(const LoomString *ls, const char *str, LoomString *res){
	if(ls == NULL || str == NULL || res == NULL){
		return LOOM_NULL_PTR;
	}

	size_t len1 = ls_length(ls);
	size_t len2 = strlen(str);
	size_t resLen = ls_length(res);

	if (len1 + len2 >= resLen){
		LoomResult result = ls_realloc(res, len1 + len2 + 1);
		if (result != LOOM_OK){
			return result;
		};
	}

	memcpy(res->ptr, ls->ptr, len1);
	memcpy((res->ptr + len1) , str, len2 + 1);
	res->length = len1 + len2;
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
