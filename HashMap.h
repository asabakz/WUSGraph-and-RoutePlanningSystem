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
    
    V getValue(K& key);             //��ȡkey��Ӧ��value���������򷵻�V()

    set<K> keySet();                       //����Map�а������ļ���

    bool containsKey(K& key);        //��� Map ����ָ���� key ��ӳ�䣬��  ���� true

    void Insert(pair<K, V> k_v);           //����pair<K,V> k_v

    V Remove(K& key);               //�� Map ��ɾ��ָ���� key ��ӳ�䣨������ڣ���

    V Remove(K& key, V& val); //���ҽ���keyӳ��valʱɾ��

    void Clear();

    int getSize();                         //���� Map �еļ�-ֵ��ӳ�������

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
