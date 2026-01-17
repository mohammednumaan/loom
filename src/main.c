#include <stdio.h>
#include "../include/loom.h"

void print_result(const char *operation, LoomResult result) {
	const char *status[] = {"OK", "NULL_PTR", "ALLOC_FAIL", "REALLOC_FAIL"};
	printf("  %s: %s\n", operation, status[result]);
}

int main() {

	/*
	 * the following examples have been written by Claude. i was too lazy to write them :|
	*/
	LoomResult result;

	printf("=== Loom String Library Examples ===\n\n");

	// Example 1: Basic string creation with ls_new()
	printf("1. Creating strings with ls_new()\n");
	LoomString greeting = ls_init();
	LoomString name = ls_init();
	
	result = ls_new(&greeting, "Hello");
	print_result("ls_new(&greeting, \"Hello\")", result);
	printf("  greeting = \"%s\" (length: %zu)\n", greeting.ptr, greeting.length);
	
	result = ls_new(&name, "World");
	print_result("ls_new(&name, \"World\")", result);
	printf("  name = \"%s\" (length: %zu)\n\n", name.ptr, name.length);

	// Example 2: String copying with ls_copy()
	printf("2. Copying strings with ls_copy()\n");
	LoomString copy = ls_init();
	ls_new(&copy, "placeholder");
	
	result = ls_copy(&copy, &greeting);
	print_result("ls_copy(&copy, &greeting)", result);
	printf("  copy = \"%s\" (length: %zu)\n\n", copy.ptr, copy.length);

	// Example 3: Copying from C string with ls_copy_cstr()
	printf("3. Copying from C string with ls_copy_cstr()\n");
	LoomString from_cstr = ls_init();
	ls_new(&from_cstr, "temp");
	
	result = ls_copy_cstr(&from_cstr, "Copied from C string!");
	print_result("ls_copy_cstr(&from_cstr, \"Copied from C string!\")", result);
	printf("  from_cstr = \"%s\" (length: %zu)\n\n", from_cstr.ptr, from_cstr.length);

	// Example 4: Concatenation with ls_concat()
	printf("4. Concatenating strings with ls_concat()\n");
	LoomString concat_result = ls_init();
	ls_new(&concat_result, "");
	
	result = ls_concat(&greeting, &name, &concat_result);
	print_result("ls_concat(&greeting, &name, &concat_result)", result);
	printf("  concat_result = \"%s\" (length: %zu)\n\n", concat_result.ptr, concat_result.length);

	// Example 5: Concatenation with C string using ls_concat_cstr()
	printf("5. Concatenating with C string using ls_concat_cstr()\n");
	LoomString concat_cstr_result = ls_init();
	ls_new(&concat_cstr_result, "");
	
	result = ls_concat_cstr(&greeting, " everyone!", &concat_cstr_result);
	print_result("ls_concat_cstr(&greeting, \" everyone!\", &concat_cstr_result)", result);
	printf("  concat_cstr_result = \"%s\" (length: %zu)\n\n", concat_cstr_result.ptr, concat_cstr_result.length);

	// Example 6: Appending with ls_append()
	printf("6. Appending strings with ls_append()\n");
	LoomString sentence = ls_init();
	LoomString suffix = ls_init();
	ls_new(&sentence, "Loom is ");
	ls_new(&suffix, "awesome!");
	
	printf("  Before: \"%s\"\n", sentence.ptr);
	result = ls_append(&sentence, &suffix);
	print_result("ls_append(&sentence, &suffix)", result);
	printf("  After: \"%s\" (length: %zu)\n\n", sentence.ptr, sentence.length);

	// Example 7: Appending C string with ls_append_cstr()
	printf("7. Appending C string with ls_append_cstr()\n");
	LoomString message = ls_init();
	ls_new(&message, "Status: ");
	
	printf("  Before: \"%s\"\n", message.ptr);
	result = ls_append_cstr(&message, "Success!");
	print_result("ls_append_cstr(&message, \"Success!\")", result);
	printf("  After: \"%s\" (length: %zu)\n\n", message.ptr, message.length);

	// Example 8: Appending a single character with ls_append_char()
	printf("8. Appending a character with ls_append_char()\n");
	LoomString word = ls_init();
	ls_new(&word, "Hell");
	
	printf("  Before: \"%s\"\n", word.ptr);
	result = ls_append_char(&word, 'o');
	print_result("ls_append_char(&word, 'o')", result);
	printf("  After: \"%s\" (length: %zu)\n\n", word.ptr, word.length);

	// Example 9: Error handling - NULL pointer detection
	printf("9. Error handling - NULL pointer detection\n");
	result = ls_new(NULL, "test");
	print_result("ls_new(NULL, \"test\")", result);
	
	LoomString empty = ls_init();
	result = ls_append_cstr(&empty, "test");
	print_result("ls_append_cstr on uninitialized string", result);
	printf("\n");

	// Example 10: Cleanup with ls_free()
	printf("10. Cleanup with ls_free()\n");
	ls_free(&greeting);
	ls_free(&name);
	ls_free(&copy);
	ls_free(&from_cstr);
	ls_free(&concat_result);
	ls_free(&concat_cstr_result);
	ls_free(&sentence);
	ls_free(&suffix);
	ls_free(&message);
	ls_free(&word);
	printf("  All strings freed!\n");
	printf("  After free: ptr = %p, length = %zu\n", (void*)greeting.ptr, greeting.length);

	printf("\n=== Examples Complete ===\n");
	
	return 0;
}
