#include <stdio.h>
#include "../include/fixed_size_string.h"

struct FixedString create_string(char *input){
	struct FixedString new_str;

	// i initialize the string to use these values because *input could
	// be null, if we didn't give defaults, it would contain garbage values 
	new_str.length = 0;
	new_str.data[0] = '\0';
	
	// the reason i put MAX_FIXED_SIZE - 1 is because the last character
	// must be a null character which is '\0'
	if (input != NULL){
		int i = 0;
		while (input[i] != '\0' && i < MAX_FIXED_STRING_SIZE - 1){
			new_str.data[i] = input[i];
			i++;
		}

		new_str.data[i] = '\0';
		new_str.length = i;
	}

	return new_str;
}

struct FixedString concat_string(struct FixedString s1, struct FixedString s2){
	struct FixedString new_str;
	new_str.length = 0;
	new_str.data[0] = '\0';
	
	if (s1.data[0] == '\0' && s2.data[0] == '\0'){
		return new_str;
	}	

	int idx = 0;
	int i = 0;

	// there might be a better way to do this? 
	while (s1.data[i] != '\0' && idx < MAX_FIXED_STRING_SIZE - 1){
		new_str.data[idx++] = s1.data[i++];
	}

	new_str.data[idx] = '\0';
	new_str.length = idx;
	
	i = 0;
	while (s2.data[i] != '\0' && idx < MAX_FIXED_STRING_SIZE - 1){
		new_str.data[idx++] = s2.data[i++];
	}

	new_str.length = idx;
	new_str.data[10] = '\0';
	return new_str;
	
}

int string_length(struct FixedString str){
	return str.length;
}
