#pragma once
#include"HashMap.h"

template<class K, class V>
V HashMap<K, V>::getValue(K& key) {
    int bucket = -1;

    Map->findPos(key, bucket);
    if (bucket != -1) {
        return Map->findPos(key, bucket)->data.second;
    }

    else return V();
}

template<class K,class V>
bool HashMap<K, V>::containsKey(K& key) {
    int bucket = -1;
    Map->findPos(key, bucket);
    return bucket != -1;
}

template<class K,class V>
void HashMap<K, V>::Insert(pair<K, V> k_v) {
    K key = k_v.first;
    Map->Insert(key, k_v);
    key_array.insert(key);
}

template<class K,class V>
V HashMap<K, V>::Remove(K& key) {
    int bucket = -1;

    if (Map->findPos(key, bucket)) {
        V value = getValue(key);
        Map->Remove(key);
        key_array.erase(key);
        return value;
    }

    else return V();
}

//É¾³ýkeyµ±ÇÒ½öµ±val==key
template<class K, class V>
V HashMap<K, V>::Remove(K& key, V& val) {
    int bucket = -1;

    if (Map->findPos(key, bucket)->data == val) {
        Map->Remove(key);
       key_array.erase(key);
        return val;
    }

    else return V();
}

template<class K,class V>
void HashMap<K, V>::Clear() {
    Map->Clear();
}

template<class K,class V>
int HashMap<K, V>::getSize() {
    int count = 0;

    for (int i = 0; i < Map->getSize(); ++i) {
        count += Map->getBucketSize(i);
    }

    return count;
}

template<class K,class V>
void HashMap<K, V>::resizeTable() {
    Map->resizeTable();
}

template<class K, class V>
void HashMap<K, V>::Travel()
{
    for (int i = 0; i < Map->getSize(); ++i) {
       
    }
}

template<class K,class V>
set<K> HashMap<K, V>::keySet() {
    return key_array;
}