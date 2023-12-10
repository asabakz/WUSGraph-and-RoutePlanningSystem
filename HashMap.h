#pragma once
#include<iostream>
#include<set>
#include"ExpandableLinkedHashTable.h"
using namespace std;

template<class K, class V>
class HashMap {
private:

    ExpandableLinkedHashTable<K, pair<K, V>>* Map;

    set<K> key_array;

public:

    HashMap() {
        Map = new ExpandableLinkedHashTable<K, pair<K, V>>(16,0.7);

    }

    HashMap(int initialSize, double MaxLoadFactor) {
        Map = new ExpandableLinkedHashTable<K, pair<K, V>>(initialSize, MaxLoadFactor);
        
    }
    
    V getValue(K& key);             //获取key对应的value，不包含则返回V()

    set<K> keySet();                       //返回Map中包含键的集合

    bool containsKey(K& key);        //如果 Map 包含指定键 key 的映射，则  返回 true

    void Insert(pair<K, V> k_v);           //插入pair<K,V> k_v

    V Remove(K& key);               //从 Map 中删除指定键 key 的映射（如果存在）。

    V Remove(K& key, V& val); //当且仅当key映射val时删除

    void Clear();

    int getSize();                         //返回 Map 中的键-值对映射的总数

    void resizeTable();

    void Travel();

    ~HashMap() {
        this->Clear();
        delete Map;
    }

    int getBucketNum() {
        return Map->getSize();

    }

};
