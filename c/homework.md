# homework(only select import)

## 31_days

```c
typedef int DATA;
struct SNode
{
  DATA data;
  SNode* pNext;
};
struct SNode* g_pHead = NULL;

(1)编写以下函数， 向链表头部添加一个数据：(头插法)
void AddHead (DATA data)
{
  SNode* p = (SNode*)malloc(sizeof(SNode));
  if (!p)
    return;
  
  p->data = data;
  p->pNext = g_pHead;
  g_pHead = p;
}

(2)编写以下函数， 删除一个链表的节点：（删除成功返回1，否则返回0）
int Delete (DATA data)
{
  SNode* p = g_pHead, *q = NULL;
  while (p)
  {
    if (p->data == data)
    {
      if (q)
        q->pNext = p->pNext;
      else 
      {
        g_pHead = p->pNext;
        free(p);
      }
      return 1;
    }
    q = p;
    p = p->pNext;
  }
  
  return 0;
}

(3)编写以下函数，打印所有链表的节点内容：
void Print ()
{
  SNode* p = g_pHead;
  while (p)
  {
    printf("%d ", p->data);
    p = p->pNext;
  }
}

(4) 编写以下函数，对链表所有的节点进行删除并使之成为空链表：
void RemoveAll ()
{
  SNode* p = g_Head;
  while (p)
  {
    SNode* q = p;
    p = p->pNext;
    free(q);
  }
  g_pHead = NULL; // 万一后面又要使用，这里一定要有置空
}

(5)编写以下函数，对链表排序：选择排序
void Sort ()
{
  SNode* p = g_pHead;
  while (p)
  {
    SNode* m = p, *q = p->pNext;
    while (q)
    {
      if (q->data < m->data)
        m = q;
      q = q->pNext;
    }
    
    if (m != p)
    {
      DATA t = p->data;
      p->data = m->data;
      m->data = t;
    }
    
    p = p->pNext;
  }
}

(6)编写以下函数，不使用嵌套循环也不使用额外函数AddTail和AddHead，只用一个循环加载数据。
void Load ()
{
  FILE* pf = fopen(sFile, "rb");
  if (!pf)
    return;
  SNode* q = g_pHead;
  while (1)
  {
    SNode*p = (SNode*)malloc(sizeof(SNode));
    if (!p)
      break;
    if (fread(&p->data, sizeof(SInfo), 1, pf) <= 0)
    {
      free(p);
      break;
    }
    if (q)
      q->pNext = p;
    else 
      g_pHead = p;
    
    q = p;
  }
  
  if (q)
    q->pNext = NULL;
  
  fclose(pf);
}
```





