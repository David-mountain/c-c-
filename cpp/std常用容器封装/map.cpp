/*
    hashMap
    Map封装:
        1. 增加 setAt
        2. 查找 lookup
        3. 删除 removeKey

        4. 内存释放
        5. 重载[]
        6. 元素个数
*/

template<class KEY, class VALUE>
class CMap
{
    struct SData
    {
        KEY key;
        VALUE value;
        SData* pNext;
    };
    SData** p_mData{};
    int m_nCount{};
    int m_bucket{1};

    CMap () :m_nCount(0) {}
    explicit CMap(int nSize) :m_bucket{nSize}, m_nCount{0} {}
    ~CMap()
    {
        removeAll();
        delete[] p_mData;
    }
    void SetAt(KEY key, VALUE value);
    bool Lookup(KEY key);
    bool removeKey(KEY key);
    void removeAll();
    SData& operator[] (KEY key);
    inline int getCount () const
    {
        return m_nCount;
    }
}

template<class KEY, class VALUE>
void CMap::SetAt(KEY key, VALUE value)
{
    // 第一种： 一级指针写法 
    // 存在即覆盖 不存在即添加
    int i = key % m_bucket;
    SData* p = m_bucket[i];
    SData* q = nullptr;

    while (p)
    {
        if (p->value == value)
        {
            p->value = value;
            return;
        }
        q = p;
        p = p->pNext;
    }
    p = new SData{ key, value, nullptr };

    // 我就写到这里就没有了 下面是对比之后添加的
    // 我上面只是申请了 还没有挂载 傻逼了 
    if (q == nullptr)
    {
        m_bucket[i] = p;
    }
    else 
    {
        q->pNext = p;
    }

    ++m_nCount;
}

template<class KEY, class VALUE>
bool CMap::Lookup(KEY key)
{
    int i = key % m_bucket;
    SData* p = m_bucket[i];

    if (p)
    {
        if (p->key == key)
        {
            return true;
        }
        p = p->pNext;
    }
    return false;
}

template<class KEY, class VALUE>
bool CMap::removeKey(KEY key) /还没有对比
{
    if (m_nCount <= 0)
        return;

    int i = key % m_bucket;
    SData* p = m_bucket[i];
    SData* q = nullptr;

    if (p)
    {
        if (p->key == key)
        {
            // SData* q = p;  // 放在局部 q ??
            // delete q;

            if (m_nCount == 1)
            {
                p = nullptr;
                return true;
            }
            else 
            {
                SData* m = p;
                q->pNext = p->pNext;
                delete m;
            }
        }
        q = p;
        p = p->pNext;
    }
    return false;
}

template<class KEY, class VALUE>
void CMap::removeAll()
{
    int n = m_bucket;
    while (n--)
    {
        SData* p = m_bucket[n];
        while (p)
        {
            SData* q = p;
            p = p->pNext;
            delete q;
        }
    }
    m_nCount = 0;
}

、我不会写重载 包括返回值应该是什么 我对应用没有理解到位 主要就是返回值理解 理解实现比较简单 明天自己重写
template<class KEY, class VALUE>
inline VALUE& CMap<KEY, VALUE>::operator[] (KEY key)
{
    // 存在即访问，反之即添加

}