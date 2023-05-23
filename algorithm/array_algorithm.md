# Array

### 前言

```c++
数组、链表的算法技巧主要是双指针：
	中间向两端扩散
	两端向中间收缩
	快慢指针
	
技巧：前缀和：适用于快速、频繁计算一个索引区间的元素之和。
	 差分：频繁对原始数组的某区间进行增减。
	 
前缀和：一维数组的前缀和303  二维数组的前缀和304
```



## 一、prefix sums

### 1.1 303_区域和检索，数组不可变

```c++
// 思路分析：
这类题最简单就是遍历数组求和，但是这肯定不是我们想要的答案。当方法被频繁调用时，频繁遍历就变得不可取了。时间复杂度是很糟糕的。所以，我们要想办法把遍历去除掉，或者说尽可能的少遍历。这就引出了前缀和技巧。
demo:
nums:    [3,5,2,-2,4,1];
preSum:[0,3,8,10,8,12,13];  // 为什么下标0不设值呢？待会说
求[1,3]的和？
正常思路即：5+2+(-2) = 5
和的思路即：从0开始到3的元素的和 - 从0开始到0的元素的和 = 下标1到下标3的元素的和
			3+5+2+(-2)=8			3					5
  
第一步：先求出前缀和数组
	下一个前缀和元素值 = 上一个前缀和元素值 + 当前数组元素值
	preSum[i]		 = preSums[i-1]	    + nums[i-1] 
									(这里i-1是因为遍历数组是从1开始的，下标0并没有用来存值)
第二步：求索引区间的式子
	由上面和的思路可得： (int left, int right) [left,right]
	从0开始到3的元素的和 - 从0开始到0的元素的和 = 下标1到下标3的元素的和
	因为我们0是没有用来存值的，所以 [left,right]+1 -> [left+1, right+1]
	preSum[right+1] - preSum[left](即left左边一个元素值) = sum[left,right]
```

```c++
// 代码实现
class NumArray
{
  public:
  	std::vector<int> preSum;
  
  	NumArray(std::vector<int>& nums)
    {
      int n = nums.size();
      preSum.resize(n + 1);
      for (int i = 1; i < n + 1; ++i)
      {
		preSum[i] = preSum[i - 1] + nums[i - 1];
      }
    }
  
  	int sumRange (int left, int right)
    {
      return preSum[right + 1] - preSum[left];
    }
}
```

### 1.2 304 二维区域和检索，矩阵不可变

```c++
// 后面应该按照最笨的方法，遍历去实现哈。而不是直接来技巧。303同理。
// 思路分析
最为关键的两点就是进行图像切割组合 + 切割后的图像都是从(0,0)开始的。
或者我们可以理解成，按照以(0,0)为起点的图像切换，这样才能构成前缀和的必要条件。

这里有点前提，就是必须至少包含4个块。比如你求[0,0,0,1]这种就是不行的。只有2个块。
最简单的理解就是用一个至少长2宽2的框框，去矩阵中套。求被套中的值。
1. 接下来问题是如何求前缀和数组？
这里是从0开始，303是从1开始。后面和从1开始对比哈。
preSum[i + 1][j + 1] = sums[i][j + 1](横长条) + sums[i + 1][j](竖) - sums[i][j](多加的那个) + matrix[i][j](右下角的一个块);
图解：
![矩阵](C:\Users\ghost\Desktop\矩阵.png)

2. 求索引区间的式子
最简单的理解就是用一个至少长2宽2的框框，去矩阵中套。求被套中的值。
这里是前缀和了哈，联想一维数组的哈，不要和上面求前缀和数组混淆了。
s套 = s大 - s行 - s列 + s重 
int sumRegion(int row1, int col1, int row2, int col2)
s套 = sums[row2+1][col2+1](类比一维数组right+1,因为矩阵也是从0，0开始的) 
      - sums[row1][col2+1](s行，切记+1哈，类比right+1，因为矩阵是从0，0开始的)
      - sums[row2+1][col1](s列，同上)
  	  + sums[row1][col1](为何不减1，因为是从0，0开始的);
```

```c++
class NumMatrix
{
  vector< vector<int> > sums;
  
  NumMatrix(vector< vector<int> >& matrix)
  {
    int m = matrix.size();
    if (m > 0)
    {
      int n = matrix[0].size();
      sums.resize(m+1, vector<int>(n + 1));
      for (int i = 1; i < m; ++i)
      {
        for (int j = 1; j < n; ++j)
        {
          sums[i + 1][j + 1] = sums[i][j + 1] + sums[i + 1][j] - sums[i][j] + matrix[i][j];
        }
      }
    }
  }
  
  int sumRegion (int row1, int col1, int row2, int col2)
  {
    return sums[row2 + 1][col2 + 1] - sums[row1][col2 + 1] - sums[row2 + 1][col1] + sums[row1][col1];
  }
}
```

## 二、diff sums

### 2.0 introduce diff sums

```c++
nums: 8  5  9  6  1
diff: 8 -3  4 -3 -5  // diff[i] = nums[i] - nums[i-1] 后者减前者
// 根据差分数组，反求出原数组
// nums[i] = diff[i] + nums[i-1]
diff: 8 -3  4  -3  -5 
nums: 8  5  9   6   1
// 上面即是一个完整的过程，在这个过程中，我们可以体会到根据数值之间的和差关系来确定数值是可行的，
// 把对数组的区间操作(不方便操作)，转换到了和差关系中(较好操作)，最后再转换会原数组。即数学转换法。

  比如我想 nums数组[1,3]都加3：[i,j]+-k
  diff: 8 -3  4  -3  -5 
  我们只需要再差分数组中，i+=3,j+1-=3即可。
  diff: 8 0(-3+3)  4  -3  -8(-5-3)
  然后求出原数组：
  nums: 8  8 12  9  1
 原nums:8  5  9  6  1
```

```c++
// 把差分数组抽象成一个类，函数increment方法和result方法：
// 查分数组工具类
class Diffrence
{
	// 差分数组
  	private:
  		vector<int> diff;
  
  	public:
  		Diffrence(vector<int>& nums)
        {
			int n = nums.size();
          	 diff.resize(n);
          	 // 根据初始操作数组构造差分数组
          	 diff[0] = nums[0];
          	 for (int i = 1; i < n; ++i)
             {
				diff[i] = nums[i] - nums[i-1];
             }
        }
  
  		// 给区间 [i, j] 增加 val(可正负)
  		void increment (int i, int j, int val)
        {
          diff[i] += val;
          if (j + 1 < diff.length) // 严禁，而且万一就是 [倒数第二,倒数第一] 直接j+1就越界
            					 // 这种情况，就不需要j+1，只需要上面+=val即可。
          {
            diff[j + 1] -= val;
          }
        }
  
  	   // 返回结果数组
  	   vector<int>& result ()
       {
		vector<int> res = new int[diff.size()];
         int n = diff.size();
         res[0] = diff[0];
         for (int i = 1; i < n; ++i)
         {
			res[i] = res[i - 1] + diff[i]; // 从1开始，所以没有i-1了
         }
         return res;
       }
}
```

### 2.1 370_区间加法

```c++
收费题目
题目描述：
假设你有一个长度为 n 的数组，初始情况下所有的数字均为 0，你将会被给出 k 个更新的操作。
其中，每个操作会被表示为一个三元组：[startIndex, endIndex, inc]，你需要将子数组 nums[startIndex … endIndex]（包括 startIndex 和 endIndex）增加 inc。
请你返回 k 次操作后的数组。
示例:
输入: length = 5, updates = [[1,3,2],[2,4,3],[0,2,-2]] 输出: [-2,0,3,5,3]
解释:
初始状态: [0,0,0,0,0]
进行了操作 [1,3,2]: [0,2,2,2,0]
进行了操作 [2,4,3]: [0,2,5,5,3]
进行了操作 [0,2,-2]: [-2,0,3,5,3]
[-2,0,3,5,3]
```

```c++
// 代码
vector<int>& getModifiedArray (int length, vector< vector<int> >& updates)
{
	int m = updates.size();
  	if (m > 0)
    {
		int n = updates[0].size();
      	vector< vector<int> > nums;
      	nums.resize(m, vector<int>(n)); // 是否+1？暂不
      	// 构造差分数组
      	Diffrence df(nums);
      
      	for (auto update : updates)
        {
			int i = update[0];
          	 int j = update[1];
          	 int val = update[2];
          	 df.increment(i, j, val);
        }
      
       return df.result();
    }
}
```

### 2.2 1109_航班

```c++
// 思路分析
// 思路，题意就是一个差分数组
// 题目说，n是从1开始计数的，而数组索引从0开始的，所以对于输入的三元组(i,j,k)，
// 数组区间应该对应 [i-1, j-1]

// 代码
vector<int>& corpFlightBookings (int length, vector< vector<int> >& bookings)
{
	int m = bookings.size();
  	if (m > 0)
    {
		int n = bookings[0].size();
      	vector< vector<int> > nums;
      	nums.resize(m, vector<int>(n)); // 是否+1？暂不
      	// 构造差分数组
      	Diffrence df(nums);
      
      	for (auto booking : bookings)
        {
			int i = booking[0] - 1; // 题目n是从1开始计数的 所以-1
          	 int j = booking[1] - 1; // 题目n是从1开始计数的 所以-1
          	 int val = booking[2];   // 值 不需要-1
          	 df.increment(i, j, val);
        }
      
       return df.result();
    }
}
```

### 2.3 1094_拼车

```c++
// 思路：
// 题目没有给差分数组的长度(车站的个数)是多少？但给了数据取值范围。
// 0 <= trips[i][1] < trips[i][2] <= 1000 
// 车站从0开始编号，最多到1000，也就是最多有1001个车站，我们就把差分数组长度可以设置成1001，这样涵盖所有车站的编号。

// 代码：
booloean carPooling (int capacity, vector< vector<int> >& trips)
{
	int m = trips.size();
  	if (m > 0)
    {
		int n = trips[0].size();
      	vector< vector<int> > nums;
      	nums.resize(1001); 
      	// 构造差分数组
      	Diffrence df(nums);
      
      	for (auto trip : trips)
        {
			int i = trip[1];     // 第 trip[1] 站乘客上车
          	 int j = trip[2] - 1; // 第 trip[2] 站乘客已经下车
          						// 即 乘客在车上区间是 [trip[1], trip[2] - 1]
          	 int val = trip[0];   // 乘客数量
          	 df.increment(i, j, val);
        }
      
       int[] res = df.result();
      
      // 客车自始自种不能超载
      for (int i = 0; i < res.length; ++i)
      {
		if (capacity < res[i])
          return false;
      }
      return true;
    }
}
```

## 三、双指针(快慢)

```c++
// 双指针技巧主要分两类：左右指针和快慢指针
// 左右指针：就是两个指针相向而行或者相背而行
// 快慢指针：就是两个指针同向而行，一快一慢

// 在数组中并没有真正意义上的指针，但我们可以把索引当做数组中的指针，这样也可以在数组中施展双指针
// 技巧。
// 数组问题中⽐较常⻅的快慢指针技巧，是让你原地修改数组。
```

### 3.1 删除有序数组的重复项(简单26)

```c++
// 思路：排序数组，立马think到双指针，这就是典型的快慢指针阿，不一样就赋值给慢指针，如果是C++，多出的
// 节点内存就需要释放内存了。
// 题目要求原地修改。如果你遍历就是O(n^2) 不可能
// fast slow  

// coding:
class Solution
{
  public:
  	int removeDuplicates (vector<int>& nums)
    {
		int n = nums.size();
      	 if (n == 0)
           return 0;
      	 int fast = 1, slow = 1;
      	 while (fast < n)
         {
           if (nums[fast] != nums[fast - 1])
           {
			nums[slow] = nums[fast];
             ++slow;
           }
           ++fast;
         }
      	return slow;
    }
}

// 时间复杂度：O(n)O(n)，其中 nn 是数组的长度。快指针和慢指针最多各移动 nn 次。
// 空间复杂度：O(1)O(1)。只需要使用常数的额外空间。
```

### 3.2 删除排序链表中的重复元素(83)

```c++
// 思路：同上。

// coding:
class Solution
{
  public:
  	ListNode* deleteDuplicates (ListNode* head)
    {
		if (!head)
          return head;
      
      	 ListNode* cur = head;
      	 while (cur->next)
         {
			if (cur->val == cur->next->val)
              	cur->next = cur->next->next;
             else 
                 cur = cur->next;
         }
      	return head;
    }
}

```

### 3.3 移除元素(27)

```c++
// 除了让你在有序数组、链表中去重，题目还可能让你对数组中的某些元素进行原地删除！

// 思路：同上不变
// 给一个数组和一个val，数组中的val值全部删除。并返回新长度

// coding 
class Soution
{
  public:
  	int removeElement (vector<int>& nums, int val)
    {
		int n = nums.size();
      	 int left = 0;
      	 for (int right = 0; right < n; ++right)
         {
			if (nums[right] != val)
            {
				nums[left] = nums[right];
              	 ++left;
            }
         }
      	return left;
    }
}

// 时间复杂度：O(n)O(n)，其中 nn 为序列的长度。我们只需要遍历该序列至多两次。
// 空间复杂度：O(1)O(1)。我们只需要常数的空间保存若干变量。

// 双指针优化 因为题目说元素的顺序可以改变 看力扣官方思路，这里不写了 看别人的优化点
// coding
class Solution
{
  public:
  	int removeElement(vector<int>& nums, int val)
    {
      int left = 0, right = nums.size();
      while (left < right)
      {
		if (nums[left] == val)
        {
          nums[left] = nums[right - 1];
          --right;
        }
        else 
          ++left;
      }
      return left;
    }
}

// 这样的方法两个指针在最坏的情况下合起来只遍历了数组一次。与方法一不同的是，方法二避免了需要保留的元素的重复赋值操作。
// 时间复杂度：O(n)O(n)，其中 nn 为序列的长度。我们只需要遍历该序列至多一次。
// 空间复杂度：O(1)O(1)。我们只需要常数的空间保存若干变量。
```

### 3.4 移动零(283)

```c++
// 题目：把数组中的零，挪动到最后，其实就是把0干掉，然后最后的多出的元素位置，填充成0即可。

// coding 
class Solution
{
  public:
  	void moveZeroes (vector<int>& nums)
    {
		int n = nums.size(), left = 0, right = 0;
      	 while (right < n)
         {
           if (nums[right])
           {
             swap[nums[left], nums[right]]; // 这里使用的是交换，另外思路是最后处理成0
             ++left;
           }
           ++right;
         }
    }
}

// coding2 
void moveZeroes (vector<int>& nums)
{
  int n = nums.size();
  int p = removeElement(nums, 0); // 上题的去除元素
  for (; p < n; ++p)
    nums[p] = 0;
}

```

## 四、双指针(左右)

```c++
// 左右指针的常用算法
```

### 4.1 二分查找

```c++
class Solution
{
  public:
  	int binarySearch (vector<int>& nums, int target)
    {
      int left = 0, right = nums.length - 1;
      while (left <= right)
      {
		int mid = [right + left] / 2;
         if (nums[mid] == target)
           return mid;
         else if (nums[mid] < target)
           left = mid + 1;
         else if (nums[mid] > target)
           right = mid - 1;
      }
      return -1;
    }
}
```

### 4.2 两数之和2(167)

```c++
// 只要数组有序，就要think到双指针技巧
// 解法类似二分查找，通过调节left和right就可以调整sum的大小
// 本题 下标从1开始，题目要求的
// 数组已有序

// 首先固定第一个数，然后寻找第二个数
// 利用数组的有序性质，可以通过二分查找的方法寻找第二个数。
// 为了避免重复寻找，在寻找第二个数时，只在第一个数的右侧寻找。
// coding: 二分查找
class Solution
{
  public:
  	vector<int> twoSum (vector<int>& nums, int target)
    {
      for (int i = 0; i < nums.size(); ++i)
      {
        int low = i + 1, high = nums.size() - 1;
        while (low <= high)
        {
			int mid = (high - low) / 2 + low; ??
          	 if (nums[mid] == target - nums[i])
               return [i + 1, mid + 1];
             else if (nums[mid] > target - nums[i])
               high = mid - 1;
          	 else 
               low = mid + 1;
        }
      }
      return [-1, -1];
    }
}
// 时间复杂度：O(n \log n)O(nlogn)，其中 nn 是数组的长度。需要遍历数组一次确定第一个数，时间复杂度是 O(n)O(n)，寻找第二个数使用二分查找，时间复杂度是 O(\log n)O(logn)，因此总时间复杂度是 O(n \log n)O(nlogn)。
// 空间复杂度：O(1)O(1)。

// coding2: 双指针
class Solution
{
  public:
  	vector<int> twoSum (vector<int>& nums, int target)
    {
      int low = 0, high = nums.size() - 1;
      while (low < high)
      {
        int sum = nums[low] + nums[high];
        if (sum == target)
          return [low + 1, high + 1];
         else if (sum < target)
           ++low;
         else 
           --high;
      }
      return [-1, -1];
    }
}

// 时间复杂度：O(n)O(n)，其中 nn 是数组的长度。两个指针移动的总次数最多为 nn 次
// 空间复杂度：O(1)O(1)。
```

### 4.3 反转数组 反转字符串(344)

```c++
// 

// coding:
class Solution:
{
  public:
  	void reverseString (vector<char>& s)
    {
      int n = s.size();
      for (int left = 0, right = n - 1; left < right; ++left, --right)
      {
        swap(s[left], s[right]);
      }
    }
}
// 时间复杂度：O(N)O(N)，其中 NN 为字符数组的长度。一共执行了 N/2N/2 次的交换。
// 空间复杂度：O(1)O(1)。只使用了常数空间来存放若干变量。
```

### 4.4 回文串判断

```c++
// 回文串：正着 反着 都是一样的字符串 
// 其实看到这种应该能想到 双指针

// coding:
boolean isPalinrome (String s)
{
  int left = 0, right = s.length() - 1;
  while (left < right)
  {
	if (s.charAt(left) != s.charAt(right))
      return false;
    ++left;
    --right;
  }
  return true;
}
```

### 4.5 最长回文子串(5)

```c++
// 思考：找回文串的难点在于，回文串的长度可能是奇数也可以是偶数，解决该问题的核心是 从中心向两端扩散的双指针技巧。
// 如果回文串的长度为奇数，则它有一个中心字符
// 如果回文串的长度为偶数，则可以认为它有两个中心字符串

// 辅助工具函数：
// 在 s 中寻找以 s[l] 和 s[r] 为中心的最长回文串
String palindrome (String s, int l, int r)
{
  while (l >= 0 && r < s.length()
                && s.charAt(l) == s.charAt(r))
  {
    --l; ++r;
  }
  // 返回以 s[l] 和 s[r] 为中新的最长回文传串 
  returm s.substring(l + 1, r);
}
// 这样，如果输⼊相同的 l 和 r，就相当于寻找⻓度为奇数的回⽂串，如果输⼊相邻的 l 和 r，则相当于寻找
// ⻓度为偶数的回⽂串。

// coding:
String longestPalindrome (String s)
{
  String res = "";
  for (int i = 0; i < s.length(); ++i)
  {
    String s1 = palindrome(s, i, i);
    String s2 = palindrome(s, i, i + 1);
    // res = longest(res, s1, s2); 分别和s1 s2比较
    res = res.length() > s1.length() ? res : s1;
    res = res.length() > s2.length() ? res : s2;
  }
  return res;
}

// 你应该能发现最⻓回⽂⼦串使⽤的左右指针和之前题⽬的左右指针有⼀些不同：之前的左右指针都是从两端
// 向中间相向⽽⾏，⽽回⽂⼦串问题则是让左右指针从中⼼向两端扩展。
```















