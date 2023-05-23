# String

## 涉及字符串的题大部分都是中等和困难，请认真对待

## 一、双指针(滑动窗口)

```c++
滑动窗口算法的思路：
把索引左闭右开区间[left,right)称为一个窗口。思考为何是左闭右开？

```



### 1.1 最小覆盖字串(76 困难)

```c++
// 暴力破解 O(n^2) 请实现

// 双指针
string minWindow (string s, string t)
{
	unordered_map<char, int> need, window;
  	for (char c : t) need[c]++;
  
  	int left = 0, right = 0;
  	int valid = 0;
  	// 记录最小覆盖字串的起始索引及长度
  	int start = 0, len = INT_MAX;
  	while (right < s.size())
    {
      // c 是将移入窗口的字符
      char c = s[right];
      // 扩大窗口
      ++right;
      // 进行窗口内的一系列更新
      if (need.count(c))
      {
        window[c]++;
        if (window[c] == need[c])
          valid++;
      }
      
      // 判断左侧窗口是否要收缩
      while (valid == need.size())
      {
        // 在这里更新最小覆盖字串 ?? 这是if 不是while 搞错了
        if (right - left < len)
        {
          start = left;
          len = right - left;
        }
        
        // d 是将移除窗口的字符
        char d = s[left];
        // 缩小窗口
        ++left;
        // 进行窗口内数据的一系列更新
        if (need.count(d))
        {
          if (window[d] == need[d])
            valid--;
          
          window[d]--;
        }
      }
    }
  	// 返回最小覆盖字串
  	return len == INT_MAX ? : "" : s.substr(start, len);
}

```

### 1.2 字符串的排列(567 中等)

```c++
// 思路：这里就不是最小覆盖了，还会改变窗口，这里的窗口应该是定长的了。
// 是较为明显的滑动窗口算法，相当给你一个S和一个T，请问你S中是否存在一个字串，包含T中所有字符且不含其他字符。

// coding:
class Solution
{
  public:
  	bool checkInclusion (string s1, string s2)
    {
		int n = s1.length, m = s2.length();
      	 if (n > m)
           return false;
      	 vector<int> cnt1(26), cnt2(26);
      	 for (int i = 0; i < n; ++i)
         {
			++cnt1[s1[i] - 'a']; ?? 懂了，相减会控制在26的范围内 对应的数++即可
           	 ++cnt2[s2[i] - 'a'];
         }
      	 if (cnt1 == cnt2)
           return true;
      	 for (int i = n; i < m; ++i)
         {
			++cnt2[s2[i] - 'a'];  右移一位 长字符串 
           	 --cnt2[s2[i - n] - 'a']; 左移一位 问题在于i-n的处理 即：i-n 从0开始的 这是下标
             if (cnt1 == cnt2)
               return true;
         }
      	 return false;
    }
}

```

### 1.3 找字符串中所有字母异位词(438 中等)

```c++
// 分析：异位词 是指由相同字母重排列形成的字符串(包括相同的字符串)
// 字母异位词 - 就是排列。
// 题意：输入一个串S，一个串T，找到S中所有T的排列，返回它们的起始索引。
// 跟寻找字符串的排列⼀样，只是找到⼀个合法异位词（排列）之后将起始索引加⼊ res 即可。

// coding:
class Solution
{
	public:
  	vector<int> findAnagrams (string s, string p)
    {
		int sLen = s.size(), pLen = p.size();
      
      	if (sLen < pLen)
        {
          return vector<int>();
        }
      
      	vector<int> ans;
      	vector<int> sCount(26);
      	vector<int> pCount(26);
      	for (int i = 0; i < pLen; ++i)
        {
			++sCount[s[i] - 'a'];
          	 ++pCount[p[i] - 'a'];
        }
      
      	if (sCount == pCount)
        {
			ans.emplace_back(0);
        }
      
      	for (int i = 0; i < sLen - pLen; ++i)
        {
			--sCount[s[i] - 'a'];
          	 ++sCount[s[i + pLen] - 'a'];
          
          	 if (sCount == pCount)
             {
				ans.emplace_back(i + 1);
             }
        }
      
      	return ans;
    }
}

// 时间复杂度：O(m + (n-m) \times \Sigma)O(m+(n−m)×Σ)，其中 nn 为字符串 ss 的长度，mm 为字符串 pp 的长度，\SigmaΣ 为所有可能的字符数。我们需要 O(m)O(m) 来统计字符串 pp 中每种字母的数量；需要 O(m)O(m) 来初始化滑动窗口；需要判断 n-m+1n−m+1 个滑动窗口中每种字母的数量是否与字符串 pp 中每种字母的数量相同，每次判断需要 O(\Sigma)O(Σ) 。因为 ss 和 pp 仅包含小写字母，所以 \Sigma = 26Σ=26。

// coding2: 优化版本
```

## 1.4 最长无重复字串(3 中等)

```c++
// 思路：返回无重复最长字子串的长度。
// 这⾥和之前不⼀样，要在收缩窗⼝完成后更新 res，因为窗⼝收缩的 while 条件是存在重复元素，换句话说
// 收缩完成后⼀定保证窗⼝中没有重复嘛。

// coding:
class Solution
{
  public:
  int lengthOfLongestSubstring (string s)
  {
    unordered_set<char> occ; // 用的 unordered_set 
    int n = s.size();
    int rk = -1, ans = 0;
    for (int i = 0; i < n; ++i)
    {
		if (i != 0)
          occ.erase(s[i - 1]);
      
      	 while (rk + 1 < n && !occ.count(s[rk + 1]))
         {
           occ.insert(s[rk + 1]);
           ++rk;
         }
      	 ans = max(ans, rk - i + 1);
    }
    return ans;
  }
}

// coding2:
class Solution
{
  public:
  int lengthOfLongestSubstring (string s)
  {
	unordered_map<char, int> window;
    
    int left = 0, right = 0;
    int res = 0;
    while (right < s.size())
    {
      char c = s[right];
      right++;
      window[c]++; // 每次添加完一个字符 都要判断当前字符的次数是否大于1 
      
      while (window[c] > 1) // 当 window[c] 值⼤于 1 时，说明窗⼝中存在重复字符，不符合条件，就该移动 left 缩⼩窗⼝了嘛。
      {
        char d = s[left];
        left++;
        window[d]--;
      }
      res = max(res, right - left);
    }
    return res;
  }
}
```

