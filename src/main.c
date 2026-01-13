#include <stdio.h>
#include "../include/fixed_size_string.h"

int main(){
	struct FixedString s1 = create_string("hello");
	struct FixedString s2 = create_string("world");
	struct FixedString concat = concat_string(s1, s2);

	printf("%s %d", concat.data, concat.length);
	
}
