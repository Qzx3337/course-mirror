#include <stdio.h> 

void func(int a[10][10])
{
	int b_in_func[10][10];
	printf("in func: sizeof(a): %d\n", sizeof(a));
	printf("sizeof(b_in_func): %d\n", sizeof(b_in_func));
}

int main()
{
	int a[10][10];
	printf("sizeof(int): %d\n", sizeof(int));
	printf("sizeof(a): %d\n", sizeof(a));
	func(a);

	int*** p = &a;
	printf("sizeof(*(&a))): %d\n", sizeof(*(&a)));
	printf("sizeof(p): %d\n", sizeof(*(p)));

	return 0;
}
