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


```



### 2.3 1094_拼车











































