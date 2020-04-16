#include <stdio.h>
#include <stdlib.h>
 
typedef struct {
    /* header */
    size_t nelems;
    int other;
    int things;
    /* actual array */
    int a[1];
} Test;
 
int main(void) {
	// your code goes here
	Test* test = malloc(sizeof(Test) + sizeof(int) * 10);
	test->nelems = 1;
	test->other = 2;
	test->things = 3;
	test->a[0] = 0;
	test->a[1] = 2;
	test->a[9] = 9;
	printf("%d %d %d %d %d %d", 
		test->nelems, test->other, test->things, test->a[0], test->a[1], test->a[9]);
	return 0;
}
 
