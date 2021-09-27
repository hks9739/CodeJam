# CodeJam
Exercise for coding test



# 예제 소스

## Quick Sort
```c
#include <stdlib.h>

static int compare(const void *a1, const void *a2)
{
	const int *v1 = a1;
	const int *v2 = a2;

	return *v1 - *v2;
}

int main(void)
{
	int a[10] = { 4, 5, 6 };
	
	qsort(a, 10, sizeof(int), compare);
  
	return 0;
}
```
