# CodeJam
Exercise for coding test



# 예제 소스

## 매크로
```c
#define min(a, b) (((a) < (b)) ? (a) : (b))

```

## 정렬
```c
#include <stdlib.h>

static int compare(const void *a1, const void *a2)
{
	const int *v1 = a1;
	const int *v2 = a2;

	// 오름 차순 정렬인 경우
	return *v1 - *v2;
}

int main(void)
{
	int a[10] = { 4, 5, 6 };
	
	qsort(a, 10, sizeof(int), compare);
  
	return 0;
}

/**
 * 오름차순으로 정렬된 arr에서 first와 last index 사이에 value 값보다 큰 첫번째 index 
 */
static int lower_bound(int *arr, int first, int last, int value)
{
	int mid;

	while (first < last) {
		mid = (first + last) / 2;
		if (arr[mid] < value)
			first = mid + 1;
		else
			last = mid;
	}

	return last;
}


```
