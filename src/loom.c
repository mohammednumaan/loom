#include <stdlib.h>
#include <string.h>
#include "../include/loom.h"

LoomString ls_init(){
	LoomString ls;
	ls.ptr = NULL;
	ls.length = 0;
	return ls;
}

LoomResult ls_new(LoomString *ls, const char *str){
	if (ls == NULL) return LOOM_NULL_PTR;
	CHECK_CSTR(str);
	
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
	CHECK_PTR(dest);
	CHECK_PTR(src);

	size_t srcLen = ls_len(src);
	size_t destLen = ls_len(dest);

	if (srcLen >= destLen){
		LoomResult result = ls_realloc(dest, srcLen + 1);
		if (result != LOOM_OK){
			return result;
		}
	}

	memcpy(dest->ptr, src->ptr, srcLen + 1);
	dest->length = srcLen;
	return LOOM_OK;
}

LoomResult ls_copy_cstr(LoomString *dest, const char *src){
	CHECK_PTR(dest);
	CHECK_CSTR(src);

	size_t srcLen = strlen(src);
	size_t destLen = ls_len(dest);

	if (srcLen >= destLen){
		LoomResult result = ls_realloc(dest, srcLen + 1);
		if (result != LOOM_OK){
			return result;
		}
	}
	
	memcpy(dest->ptr, src, srcLen + 1);
	dest->length = srcLen;
	return LOOM_OK;
}

LoomResult ls_concat(const LoomString *ls1, const LoomString *ls2, LoomString *res){
	CHECK_PTR(ls1);
	CHECK_PTR(ls2);
	CHECK_PTR(res);

	size_t len1 = ls_len(ls1);
	size_t len2 = ls_len(ls2);
	size_t resLen = ls_len(res);

	if (len1 + len2 >= resLen){
		LoomResult result = ls_realloc(res, len1 + len2 + 1);
		if (result != LOOM_OK){
			return result;
		}
	}

	memcpy(res->ptr, ls1->ptr, len1);
	memcpy((res->ptr + len1), ls2->ptr, len2 + 1);
	res->length = len1 + len2;
	return LOOM_OK;
}

LoomResult ls_concat_cstr(const LoomString *ls, const char *str, LoomString *res){
	CHECK_PTR(ls);
	CHECK_PTR(res);
	CHECK_CSTR(str);

	size_t len1 = ls_len(ls);
	size_t len2 = strlen(str);
	size_t resLen = ls_len(res);

	if (len1 + len2 >= resLen){
		LoomResult result = ls_realloc(res, len1 + len2 + 1);
		if (result != LOOM_OK){
			return result;
		}
	}

	memcpy(res->ptr, ls->ptr, len1);
	memcpy((res->ptr + len1), str, len2 + 1);
	res->length = len1 + len2;
	return LOOM_OK;
}

LoomResult ls_append(LoomString *ls1, const LoomString *ls2){
	CHECK_PTR(ls1);
	CHECK_PTR(ls2);

	size_t len1 = ls_len(ls1);
	size_t len2 = ls_len(ls2);
	if (len2 > 0){
		LoomResult result = ls_realloc(ls1, len1 + len2 + 1);
		if (result != LOOM_OK){
			return result;
		}
	}

	memcpy(ls1->ptr + len1, ls2->ptr, len2 + 1);
	ls1->length = len1 + len2;
	return LOOM_OK;
}

LoomResult ls_append_cstr(LoomString *ls, const char *str){
	CHECK_PTR(ls);
	CHECK_CSTR(str);

	size_t len1 = ls_len(ls);
	size_t len2 = strlen(str);
	if (len2 > 0){
		LoomResult result = ls_realloc(ls, len1 + len2 + 1);
		if (result != LOOM_OK){
			return result;
		}
	}

	memcpy(ls->ptr + len1, str, len2 + 1);
	ls->length = len1 + len2;
	return LOOM_OK;
}

LoomResult ls_append_char(LoomString *ls, char ch){
	CHECK_PTR(ls);

	size_t len = ls_len(ls);
	LoomResult result = ls_realloc(ls, len + 2);
	if (result != LOOM_OK){
		return result;
	}

	ls->ptr[len] = ch;
	ls->ptr[len + 1] = '\0';
	ls->length = len + 1;
	return LOOM_OK;
}

LoomResult ls_realloc(LoomString *ls, size_t newLen){
	if (ls == NULL) return LOOM_NULL_PTR;

	char *newPtr = (char *) realloc(ls->ptr, newLen);
	if (newPtr == NULL){
		return LOOM_REALLOC_FAIL;
	}
	ls->ptr = newPtr;
	return LOOM_OK;
}

LoomResult ls_free(LoomString *ls){
	if (ls == NULL) return LOOM_NULL_PTR;

	free(ls->ptr);
	ls->ptr = NULL;
	ls->length = 0;
	return LOOM_OK;
}
