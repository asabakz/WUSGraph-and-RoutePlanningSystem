#pragma once
#include"ExpandableLinkedHashTable.h"


template<class K, class E>
ExpandableLinkedHashTable<K, E>::ExpandableLinkedHashTable()
{
    TableSize = 16;
    HashTable.resizeList(16);
    for (int i = 0; i < 16; i++) {//初始化数组元素为空指针
        HashTable[i] = NULL;
    }
    m_maxLoadFactor = 0.7;
    BucketSize = 0;
}






template<class K, class E>
ExpandableLinkedHashTable<K, E>::ExpandableLinkedHashTable(int initialSize)
{
    TableSize = initialSize;
    HashTable.resizeList(initialSize);
    for (int i = 0; i < initialSize; i++) {//初始化数组元素为空指针
        HashTable[i] = NULL;
    }
    m_maxLoadFactor = 0.7;
    BucketSize = 0;
}






template<class K, class E>
ExpandableLinkedHashTable<K, E>::ExpandableLinkedHashTable(int initialSize, double maxLoadFactor)
{
    TableSize = initialSize;
    HashTable.resizeList(initialSize);
    for (int i = 0; i < initialSize; i++) {//初始化数组元素为空指针
        HashTable[i] = NULL;
    }
    m_maxLoadFactor = maxLoadFactor;
    BucketSize = 0;
}





template<class K, class E>
DbListNode<K, E>* ExpandableLinkedHashTable<K, E>::findPos(K& key, int& bucket)
{
    if (!Search(key))     //不存在该结点
    {
        bucket = -1;
        return NULL;
    }
    bucket = getBucket(key);
    DbListNode<K, E>* p = HashTable[bucket]->Search(key);          //在双向链表中寻找对应结点
    return p;
}





template<class K, class E>
bool ExpandableLinkedHashTable<K, E>::Search(K& key)
{
    if (TableSize == 0) return  false;     //表空
    int bucket = getBucket(key);
    if (HashTable[bucket])                 //桶非空的情况
    {
        if (HashTable[bucket]->Search(key))//桶中的双向链表存在该元素
            return true;
        return false;
    }
    return false;
}





template<class K, class E>
bool ExpandableLinkedHashTable<K, E>::Insert(K& k, E& e)
{
    int bucket;
    if (findPos(k, bucket))       //元素已存在，先删除再添加
    {
        HashTable[bucket]->Remove(k);
        HashTable[bucket]->push_front(k, e);
        return true;
    }

    //元素不存在
    bucket = getBucket(k);
    if (HashTable[bucket])                   //对应桶不为空
    {
        HashTable[bucket]->push_front(k, e);
        return true;
    }
    else                                    //对应桶空
    {
        HashTable[bucket] = new DbLinkedList<K, E>();
        HashTable[bucket]->push_front(k, e);
        BucketSize++;           //桶数+1

        double factor = (double)BucketSize / (double)TableSize;


        if (factor > m_maxLoadFactor)                    //负载超出限制，扩容
            resizeTable();
        return true;
    }

    return false;
}



template<class K, class E>
int  ExpandableLinkedHashTable<K, E>::Remove(K& k, E& e)
{
    if (TableSize == 0) return  0;
    int bucket = getBucket(k);
    if (HashTable[bucket] == NULL) return 0;   //桶为空
    if (HashTable[bucket]->Remove(k))   //如果存在该关键码的结点
    {
        return 1;
    }
    return 0;
}

//
template<class K, class E>
int  ExpandableLinkedHashTable<K, E>::Remove(K& k)
{
    if (TableSize == 0) return  0;
    int bucket = getBucket(k);
    if (HashTable[bucket] == NULL) return 0;   //桶为空
    if (HashTable[bucket]->Remove(k))   //如果存在该关键码的结点
    {
        return 1;
    }
    return 0;
}










template<class K, class E>
void ExpandableLinkedHashTable<K, E>::resizeTable()
{
    int preBucketSize = getDivisor(TableSize);
    TableSize = getDivisor(2 * TableSize);
    ExpandableArrayList<DbLinkedList<K, E>* > newHashTable(TableSize);

    for (int i = 0; i < TableSize; i++)
        newHashTable[i] = NULL;

    for (int i = 0; i < preBucketSize; i++)
    {
        if (HashTable[i])  //桶不为空
        {
            DbListNode<K, E>* p = HashTable[i]->getFirst()->rLink;
            while (p != HashTable[i]->getFirst())
            {
                int bucket = getBucket(p->key);
                if (newHashTable[bucket])      //不为空                   
                {
                    newHashTable[bucket]->push_front(p->key, p->data);
                }
                else   //为空
                {
                    // cout << "插入空桶" << endl;
                    newHashTable[bucket] = new DbLinkedList<K, E>();
                    newHashTable[bucket]->push_front(p->key, p->data);
                }
                p = p->rLink;
            }
        }
    }

    HashTable.resizeList(TableSize);
    for (int j = 0; j < TableSize; j++)   //重新复制给hashtable
    {

        HashTable[j] = newHashTable[j];

    }


}



template<class K, class E>
void  ExpandableLinkedHashTable<K, E>::Clear()
{
    for (int i = 0; i < TableSize; i++)
    {
        if (HashTable[i])
        {
            HashTable[i]->Clear();
            HashTable[i] = NULL;
        }

    }
    HashTable.Clear();
    TableSize = 0;
}



template<class K, class E>
void ExpandableLinkedHashTable<K, E>::test_hashtb()
{
    int a = 14;
    Insert(a, a);

    cout << "表长：" << TableSize << endl;
    cout << "除数：" << getDivisor(TableSize) << endl;
    cout << "桶数量：" << BucketSize << endl;
    if (HashTable[1])
    {
        cout << HashTable[1]->getFirst()->rLink->key << endl;
    }

    cout << "添加后：" << endl;

    for (int i = 0; i < 100; i++)
        Insert(i, i);
    if (HashTable[2])
    {
        cout << HashTable[2]->getFirst()->rLink->key << endl;
    }
    cout << "表长：" << TableSize << endl;
    cout << "除数：" << getDivisor(TableSize) << endl;
    cout << "桶数量：" << BucketSize << endl;

}







