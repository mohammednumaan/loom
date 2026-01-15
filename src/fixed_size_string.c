#include <stdio.h>
#include <string.h>
#include "../include/fixed_size_string.h"

LoomString ls_init(){
	LoomString new_ls;
	new_ls.data[0] = '\0';
	new_ls.length = 0;
	return new_ls;
}

enum LoomCodes ls_create(LoomString *ls, const char *str){
	
	if (ls == NULL || str == NULL){
		return LOOM_NULL_PTR;
	}

	return ls_copy_str(ls, str);
}

enum LoomCodes ls_copy(LoomString *dest, const LoomString *src){

	if (dest == NULL || src == NULL){
		return LOOM_NULL_PTR;
	}

	if (src->length >= MAX_SIZE){
		return LOOM_OVERFLOW;
	}

	size_t idx = 0;
	while (src->data[idx] != '\0' && idx < MAX_SIZE - 1){
		dest->data[idx] = src->data[idx];
		idx++;
	}

	dest->data[idx] = '\0';
	dest->length = idx;

	return LOOM_OK;
}

enum LoomCodes ls_copy_str(LoomString *dest, const char *str){

	if (dest == NULL || str == NULL){
		return LOOM_NULL_PTR;
	}

	size_t strLength = strlen(str);
	if (strLength >= MAX_SIZE){
		return LOOM_OVERFLOW;
	}

	size_t idx = 0;
	while (str[idx] != '\0' && idx < MAX_SIZE - 1){
		dest->data[idx] = str[idx];
		idx++;
	}

	dest->data[idx] = '\0';
	dest->length = idx;

	return LOOM_OK;
}

enum LoomCodes ls_concat(const LoomString *ls1, const LoomString *ls2, LoomString *out){

	
	if (ls1 == NULL || ls2 == NULL || out == NULL){
		return LOOM_NULL_PTR;
	}

	if (ls1->length + ls2->length >= MAX_SIZE){
		return LOOM_OVERFLOW;
	}

	ls_copy(out, ls1);

	size_t idx1 = out->length;
	size_t idx2 = 0;

	while (ls2->data[idx2] != '\0' && idx1 < MAX_SIZE - 1){
		out->data[idx1] = ls2->data[idx2];
		idx1++;
		idx2++;
	}

	out->data[idx1] = '\0';
	out->length = idx1;

	return LOOM_OK;
}

enum LoomCodes ls_concat_str(const LoomString *ls, const char *str, LoomString *out){

	if (ls == NULL || str == NULL || out == NULL){
		return LOOM_NULL_PTR;
	}

	size_t strLength = strlen(str);
	if (ls->length + strLength >= MAX_SIZE){
		return LOOM_OVERFLOW;
	}

	ls_copy(out, ls);

	size_t idx1 = out->length;
	size_t idx2 = 0;

	while (str[idx2] != '\0' && idx1 < MAX_SIZE - 1){
		out->data[idx1] = str[idx2];
		idx1++;
		idx2++;
	}

	out->data[idx1] = '\0';
	out->length = idx1;

	return LOOM_OK;
}

enum LoomCodes ls_append_char(LoomString *ls, char ch){
	
	if (ls == NULL){
		return LOOM_NULL_PTR;
	}

	if (ls->length >= MAX_SIZE - 1){
		return LOOM_OVERFLOW;
	}

	size_t lastIdx = ls->length;
	ls->data[lastIdx++] = ch;

	ls->data[lastIdx] = '\0';
	ls->length = lastIdx;
	
	return LOOM_OK;

}

enum LoomCodes ls_append_str(LoomString *ls, const char *str){
	
	if (ls == NULL || str == NULL){
		return LOOM_NULL_PTR;
	}

	size_t strLength = strlen(str);
	if (ls->length + strLength >= MAX_SIZE){
		return LOOM_OVERFLOW;
	}

	size_t strIdx = 0;
	size_t lsLastIdx = ls->length;

	while (str[strIdx] != '\0'){
		ls->data[lsLastIdx] = str[strIdx];
		strIdx++;
		lsLastIdx++;
	}

	ls->data[lsLastIdx] = '\0';
	ls->length =lsLastIdx;

	return LOOM_OK;

}