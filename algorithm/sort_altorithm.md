# sort

## 一、BubbleSort(array)

```c
void BubbleSort (int arr[], size_t len)
{
	for (int i = 0; i < len; ++i)
    {
      for (int j = 0; j < len - i - 1; ++j)
      {
		if (arr[j] > arr[j + 1])
        {
          int temp = arr[j];
          arr[j] = arr[j+1];
          arr[j+1] = temp;
        }
      }
    }
}

// test
int arr[] = { 10,9,8,7,6,5,4,3,2,1 };
int len = sizeof(arr) / sizeof(arr[0]);
BubbleSort(arr, len);
for (int i = 0; i < len; ++i)
{
  printf("%d ", arr[i]);
}
```

## 二、SelectSort(linkedList)

```c
struct SNode
{
  int data;
  struct SNode* pNext;
};

void SelectSort(struct SNode* p)
{
	while (p)
    {
      	struct SNode * m = p, * n = p->pNext;
      	while (n)
        {
          if (n->data < m->data)
            m = n;
          n = n->pNext;
        }
      	if (m != p)
        {
			int d = p->data;
          	 p->data = m->data;
          	 m->data = d;
        }
		p = p->pNext;
    }
}

// test
	struct SNode* p = (SNode*)malloc(sizeof(SNode));
	if (p)
	{
		p->data = 6;
		p->pNext = nullptr;
	}
	struct SNode* p2 = (SNode*)malloc(sizeof(SNode));
	if (p2)
	{
		p2->data = 8;
		p2->pNext = nullptr;
		p && (p->pNext = p2);
	}
	struct SNode* p3 = (SNode*)malloc(sizeof(SNode));
	if (p3)
	{
		p3->data = 7;
		p3->pNext = nullptr;
		p2 && (p2->pNext = p3);
	}
	while (p) // 遍历1 6 8 7 
	{
		printf("%d ", p->data);
		p = p->pNext;
	}
	SelectSort(p);
	while (p) // 遍历2 6 7 8 
	{
		printf("%d ", p->data);
		p = p->pNext;
	}

// 思考，如何更加通用呢？比较大小抽取成函数，类型换成typedef泛型化，等？下面迭代
```

