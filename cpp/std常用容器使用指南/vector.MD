# operator=
    因为一个力扣的题目 当时直接把一个容器赋值给了另外一个容器 看不懂代码
    std::vector<int> foo(3, 0);
    std::vector<int> bar(5, 0);
    bar = foo; 一个容器给另外一个容器
    foo = std::vector<int>(); 给一个容器重新赋值一个新的容器

# Modifiers
    1 2 3 4 5
    v.begin() 指向1 
    v.begin()+3 指向4
    (v.begin(), v.begin()+3) 包含了 1 2 3 

    ## assign 
	 用于声明 初始化
	 assign(个数，元素内容)
	 assign(迭代器开始，迭代器结束) 不含迭代器结束的元素[)
	 assign(基指针，基指针+偏移量); (数组测试 数组名)

    ## insert
    insert(插入的迭代器位置 插入内容)
    insert(插入的迭代器位置 另外容器的开始迭代器 结束迭代器(不含))
    insert(插入的迭代器位置 开始指针 结束指针(不含)) (数组演示)

    ## erase
    erase(删除元素的迭代器) 删除单个
    erase(删除元素的开始迭代器，删除元素的结束迭代器) 删除多个

    ## swap
    swap(容器名)

    ## clear 
    清空 无参数

    c11: emplace_front emplace emplace_back 提高性能
    ->   push_front    insert  push_back 

# Element access:
    ## at 
    可用于访问 或者 容器赋值
    即可做左值，又可做右值
    v.at(i) = i+1;
    cout << v.at(i);

    ## front
    即可做左值，也可做右值
    v.push_back(90);
    v.push_back(80);
    v.front() -= v.back();  --做左值
    cout v.front() 10  现在容器中值是：10 80   --做右值

    ## back 
    v.push_back(10);
    while (v.back() != 0) 然后在加入9后的 容器中 拿到back最后一个元素
    {
        v.push_back( v.back()-1 ); // 第一次 v.p(10-1)
    } 10 9 8 7 6 5 4 3 2 1 0
    第一次粗看我没看懂。目的就是打印 一个数不断减少到0 的所有数

    ## data 
    这玩意就是指针
    int *p = v.data();
    *p = 10;
    ++p;
    p[2] = 30; 这是基于当前的p 的偏移量 

# Capacity:
    ## size    已存元素个数
       capacity 容器的容量
        std::vector<int> v;
        for (int i=0; i<100; ++i)
            v.push_back(i);
        cout v.size()     100
        cout v.capacity() 141

    ## resize   
       reverse 
       改变容器元素的数量大小
      resize: 既分配了空间，也创建了对象，会调用构造函数
              既修改capacity大小，也修改size大小。
      reverse: 表示容器预留空间，但不是真正的创建对象，需要通过insert()或push_back()等操作创建对象
              只修改capacity大小，不修改size大小，
    
       在只需要足够的空间而不需要生成对象时（通常是为了节约插入元素的时间），应该选择reserve方法。
    
       for (int i=1; i<10; ++i) v.push_back(i);
       v.resize(5); 1 2 3 4 5 截断了
       v.resize(8, 100); 扩充了3 用100填充这3个位置
       v.resize(12); 扩充到了12 因为是int型 用0默认填充
       结果： 1 2 3 4 5 100 100 100  0 0 0 0 

    ## empty   容器是否为空


# 迭代器就不说了。
