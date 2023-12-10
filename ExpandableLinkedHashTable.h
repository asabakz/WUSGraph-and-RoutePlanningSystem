#pragma once
#include<iostream>
#include"ExpandableArrayList.cpp"
#include"DbLinkedList.cpp"

template<class K, class E>
class ExpandableLinkedHashTable {

public:

    ExpandableLinkedHashTable();
    ExpandableLinkedHashTable(int initialSize);
    ExpandableLinkedHashTable(int initialSize, double maxLoadFactor);
    ~ExpandableLinkedHashTable()
    {

    }

    DbListNode<K, E>* findPos(K& key, int& bucket);

    bool Search(K& k);

    bool Insert(K& k, E& e);

    int Remove(K& k, E& e);

    int Remove(K& k);

    void resizeTable();

    void Clear();

    bool isPrime(int n)  //判断素数
    {
        if (n <= 1)
            return false;
        else
        {
            for (int i = 2; i < n; i++) {
                if (n % i == 0) {
                    return false;
                }
            }
            return true;
        }
    }
    int getDivisor(int tablesize)                    //获取除数
    {
        if (isPrime(tablesize)) return tablesize;
        while (!isPrime(tablesize))
        {
            tablesize--;
        }
        return tablesize;
    }
    int getCapcity()
    {
        return TableSize;
    }
    int getSize()
    {
        return BucketSize;
    }
    int getBucket(K& key)      //获取桶位置
    {
        int t = getDivisor(TableSize);
        return key % t;
    }
    int getBucketSize(int i)
    {
        return HashTable[i]->getLength();
    }
    //void TraverseHT();

    void test_hashtb();

    void Travel_singel_bucket(int i) {
        HashTable[i]->Traverse();
    }
    
private:


    ExpandableArrayList<DbLinkedList<K, E>*> HashTable;
    int TableSize;      //表长
    int BucketSize;     //桶长
    double m_maxLoadFactor;   //最大装载因子


};