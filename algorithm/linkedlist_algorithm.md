# Linkedlist algorithm(c++)

## 无法熟悉写出三种链表数据结构，禁止开启本关卡

## 一、双指针

### 1.1 合并两个有序链表(简单)

```c++
// 思路： 比较简单 逐次比较

// 代码：
class Solution
{
public:
  ListNode* mergeTwoLists (ListNode* l1, ListNode* l2)
  {
	ListNode* preHead = new ListNode(-1);
    
    ListNode* prev = preHead; // 为了保持头节点不变 另起变量
    while (l1 != nullptr && l2 != nullptr)
    {
      if (l1->val < l2->val)
      {
        prev->next = l1;
        l1 = l1->next;
      } 
      else 
      {
        prev->next = l2;
        l2 = l2->next;
      }
      prev = prev->next; // 这句我老忘记 迭代新链表
    }
    
    prev->next = l1 = nullptr ? l2 : l1;
    
    return preHead->next;
  }
}

// O(n+m) 其中n和m分别是两个链表的长度，while循环的次数不会超过两个链表的长度之和。
// 最多是一个是1，另一个很长，这样最坏情况会循环 长度之和-1次。
```



### 1.2 单链表的分解(中等)

```c++
// 思路：拆成两个子链表

// 代码：
class Solution
{
public:
  ListNode* partition (ListNode* head, int x)
  {
	ListNode* small = new ListNode(0);
    ListNode* smallHead = small;
    ListNode* large = new ListNode(0);
    ListNode* largeHead = large;
    
    while (head != nullptr)
    {
      if (head->val < x)
      {
        small->next = head;
        small = small->next;
      }
      else 
      {
        large->next = next;
        large = large->next;
      }
      head = head->next;
    }
    large->next = nullptr;
    small->next = largeHead->next;
    return smallHead->next;
  }
}

// 时间复杂度: O(n)O(n)，其中 nn 是原链表的长度。我们对该链表进行了一次遍历。
// 空间复杂度: O(1)O(1)。
```



### 1.3 合并K个有序链表(困难)

```c++
// 思路： 有多种，选择一种即可
// 思路一：每次可选出最小的？加入链表即可。使用优先队列(小顶堆) c++有 priority_queue提供。
// 把链表节点放入一个最小堆，就可以每次获取k个节点中的最小节点
// 1. 形参是二维数组，内部数组是指针数组
// 2. 先遍历二维数组，把内部的首节点和首元节点指针加入到优先队列中
// 3. 然后逐一的对每个链表数组进行处理，最小堆出一个，然后加入一个，直到q为空
// 4. 最后返回首元节点的指针
```

```c++
// 前置知识：优先级队列(完全二叉树数组实现)
// 见同级目录：二叉堆实现

// 代码：
class Solution
{
  public:
  	struct Status
    {
      int val;
      ListNode *ptr;
      bool operator< (const Status &rhs) const 
      {
        return val > rhs.val;
      }
    };
  
  	priority_queue<Status> q;
  	
  	ListNode* mergeKLists (vector<ListNode*>& lists)
    {
      for (auto node: lists)
      {
        if (node)
        {
          q.push({node->val, node}); // 链表数组 加入首元节点和首元节点指针
        }
      }
        
      ListNode head, *tail = &head;
      while (!q.empty())
      {
        auto f = q.top(); q.pop(); // 出最小值 加入链表
        tail->next = f.ptr;
        tail = tail->next;
        if (f.ptr->next)
        {
          q.push({ f.ptr->next->val, f.ptr->next }); // 加入下一个
        }
      }
      
      return head.next;
    }
}

// 优先队列 pq 中的元素个数最多是 k，所以⼀次 poll 或者 add ⽅法的时间复杂度是 O(logk)；
// 所有的链表节点都会被加⼊和弹出 pq，所以算法整体的时间复杂度是 O(Nlogk)，
// 其中 k 是链表的条数，N 是这些链表的节点总数。
```



### 1.4 寻找单链表的倒数第K个节点(剑指offer 22 简单)

```c++
// 思路：最简单粗暴的则是直接两次遍历，但是我这使用一次遍历的方法，即双指针
// 使用另外一个计数器，来辅助我们达到需求，生活无处不在的转换法。
// 注意点：粗暴法中，假设链表有n个节点，倒数第K个节点就是正数第n - k + 1个节点。
// p1先走k步，然后p2再开始准备走，p1和p2同时走，p1走到链表末尾的空指针时前进了n-k步，p2也从head
// 开始前进了n - k步，停留在n-k+1个节点上，即恰好停链表的倒数第k个节点上。

// 代码：
class Solution
{
  public:
  	ListNode* findFronEnd (ListNode* plist, int k)
    {
      ListNode p = plist;
      for (int i = 0; i < k; ++i)
      {
        p = p.next;
      }
      ListNode p2 = plist;
      while (p != null)
      {
        p2 = p2.next;
        p = p.next;
      }
      
      return p2;
    }
}
```



### 1.5 删除链表的倒数第N个节点(中等)

```c++
// 思路：同上。技巧同上。
// 进阶算法：使用一趟扫描实现

class Solution
{
  public:
  	ListNode* removeNthFromEnd (ListNode* plist, int n)
    {
      ListNode* dummy = new listNode(0, plist);
      // 删除倒数第 n 个，要先找到倒数第 n + 1 个节点
      ListNode x = findFronEnd(dummy, n + 1);
      ListNode * ans = x->next;
      x.next = x.next.next;
      delete ans;
      return dummy;
    }
}

// 时间复杂度：O(L),其实L是链表的长度
// 空间复杂度：O(1)
```



### 1.6 寻找单链表的中点(中等)

```c++
// 思路: 问题的关键在于我们无法直接得到单链表的长度n，常规方法也是先遍历链表计算n,再遍历一次得到
// 第 n / 2个节点，也就是中间节点。
// 如果想一次性遍历就得到中间节点，就要点技巧了，使用快慢指针。
// 两个指针slow和fast分别指向链表头节点head,每当慢指针slow前进一步，快指针fast就前进两步，这样，当
// fast走到链表末尾时，slow就指向了链表中点。
// 利用了关系：中点 / 整个长度 = 1 / 2 这就是关系式

// 代码：
class Solution
{
  public:
  	ListNode* middleNode (ListNode* plist)
    {
      ListNode* slow = plist, fast = plist;
      while (fast != null && fast->next != null)
      {
		slot = slow->next;
         fast = fast->next->next;
      }
      return slow;
    }
}

// 时间复杂度：O(N)，其中N是给定链表的节点数目
// 空间复杂度：O(1)，只需要常数空间存放 slow 和 fast 两个指针。
```

### 1.7 判断链表是否包含环141(简单)

```c++
// 思路：龟兔赛跑。技巧：快慢指针。
class Solution
{
  public:
  	boolean hasCycle (ListNode* plist)
    {
      ListNode *slow = plist, *fast = head;
      while (fast != null && fast->next != null)
      {
        slow = slow->next;
        fast = fast->next->next;
        // 快慢指针相遇，说明含有环
        if (slot == fast)
        {
          return true;
        }
      }
      return false; 
    }
}

```

### 1.8 判断链表是否包含环，计算这个环的起点(中等142)

```c++
// 思路： 可以看到，当快慢指针相遇时，让其中任⼀个指针指向头节点，然后让它俩以相同速度前进，再次相遇时所在的节点位置就是环开始的位置。
// 所以，只要我们把快慢指针中的任⼀个重新指向 head，然后两个指针同速前进，k - m 步后⼀定会相遇，相遇之处就是环的起点了。
// 相遇时： slow 走了k步    fast走了2k步
// 假设有环：假设环起点到相遇点是m 头节点到环起点是x    
// slow = k = x + m 即：x = k -m 
// fast = 2k = x + L环 + m;  2k = (k - m) + L环 + m;  k = L环 这时候我们发现：
// 从相遇点绕圆到环起点：L环 - m = k - m 和slow得出一样的长度 
// 于是就利用了这点，任意哪点均可求出。

// code 
class Solution
{
  public:
  	ListNode *detectCycle (ListNode *head) 
    {
      ListNode *slow = head, *fast = head;
      while (fast != nullptr)
      {
        slow = slow->next;
        if (fast->next == nullptr)
        {
          return nullptr;
        }
        fast = fast->next->next;
        if (fast == slow)
        {
          ListNode *ptr = head;
           while (ptr != slow)
           {
              ptr = ptr->next;
              slow = slow->next;
           }
           return ptr;
        }
      }
      return nullptr;
    }
}
```



### 1.9 判断单链表是否相交并找出起点(160)

```c++
// 思路：这个题直接的想法可能是⽤ HashSet 记录⼀个链表的所有节点，然后和另⼀条链表对⽐，但这就需要额外的空间。 如果不⽤额外的空间，只使⽤两个指针，你如何做呢？  哈希表写法也可以实现哈
// 说实话，这个最开始把我难住了，我不知道如何去思考这个玩意。
// 逆向数学思维，抽象建模这个题模型。
// A：非共节点个数：x     共同节点个数：a
// B: 非共节点个数：y 	   
// 问题出发点是，两个有相同的节点个数是a. 如何能顺序得到相交起点元素？
// A: (x+a) + y 
// B: (y+a) + x 
// A == B 下一个节点就是相同点 

// 代码：
class Solution
{
  public:
  	ListNode *getIntersectionNode (ListNode *headA, ListNode *headB)
    {
      if (headA == nullptr || headB == nullptr)
      {
		return nullptr;
      }
      ListNode *pA = headA, *pB = headB;
      while (pA != pB)
      {
        pA = pA == nullptr ? headB : pA->next;
        pB = pB == nullptr ? headA : pB->next;
      }
      return pA;
    }
}

// 时间复杂度：O(m+n)O(m+n)，其中 mm 和 nn 是分别是链表 \textit{headA}headA 和 \textit{headB}headB 的长度。两个指针同时遍历两个链表，每个指针遍历两个链表各一次。
// 空间复杂度：O(1)O(1)。
```



### 1.10 

```c++


```

