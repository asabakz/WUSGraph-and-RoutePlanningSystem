#pragma once
#include"ExpandableLinkedHashTable.h"


template<class K, class E>
ExpandableLinkedHashTable<K, E>::ExpandableLinkedHashTable()
{
    TableSize = 16;
    HashTable.resizeList(16);
    for (int i = 0; i < 16; i++) {//��ʼ������Ԫ��Ϊ��ָ��
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
    for (int i = 0; i < initialSize; i++) {//��ʼ������Ԫ��Ϊ��ָ��
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
    for (int i = 0; i < initialSize; i++) {//��ʼ������Ԫ��Ϊ��ָ��
        HashTable[i] = NULL;
    }
    m_maxLoadFactor = maxLoadFactor;
    BucketSize = 0;
}





template<class K, class E>
DbListNode<K, E>* ExpandableLinkedHashTable<K, E>::findPos(K& key, int& bucket)
{
    if (!Search(key))     //�����ڸý��
    {
        bucket = -1;
        return NULL;
    }
    bucket = getBucket(key);
    DbListNode<K, E>* p = HashTable[bucket]->Search(key);          //��˫��������Ѱ�Ҷ�Ӧ���
    return p;
}





template<class K, class E>
bool ExpandableLinkedHashTable<K, E>::Search(K& key)
{
    if (TableSize == 0) return  false;     //���
    int bucket = getBucket(key);
    if (HashTable[bucket])                 //Ͱ�ǿյ����
    {
        if (HashTable[bucket]->Search(key))//Ͱ�е�˫��������ڸ�Ԫ��
            return true;
        return false;
    }
    return false;
}





template<class K, class E>
bool ExpandableLinkedHashTable<K, E>::Insert(K& k, E& e)
{
    int bucket;
    if (findPos(k, bucket))       //Ԫ���Ѵ��ڣ���ɾ�������
    {
        HashTable[bucket]->Remove(k);
        HashTable[bucket]->push_front(k, e);
        return true;
    }

    //Ԫ�ز�����
    bucket = getBucket(k);
    if (HashTable[bucket])                   //��ӦͰ��Ϊ��
    {
        HashTable[bucket]->push_front(k, e);
        return true;
    }
    else                                    //��ӦͰ��
    {
        HashTable[bucket] = new DbLinkedList<K, E>();
        HashTable[bucket]->push_front(k, e);
        BucketSize++;           //Ͱ��+1

        double factor = (double)BucketSize / (double)TableSize;


        if (factor > m_maxLoadFactor)                    //���س������ƣ�����
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
    if (HashTable[bucket] == NULL) return 0;   //ͰΪ��
    if (HashTable[bucket]->Remove(k))   //������ڸùؼ���Ľ��
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
    if (HashTable[bucket] == NULL) return 0;   //ͰΪ��
    if (HashTable[bucket]->Remove(k))   //������ڸùؼ���Ľ��
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
        if (HashTable[i])  //Ͱ��Ϊ��
        {
            DbListNode<K, E>* p = HashTable[i]->getFirst()->rLink;
            while (p != HashTable[i]->getFirst())
            {
                int bucket = getBucket(p->key);
                if (newHashTable[bucket])      //��Ϊ��                   
                {
                    newHashTable[bucket]->push_front(p->key, p->data);
                }
                else   //Ϊ��
                {
                    // cout << "�����Ͱ" << endl;
                    newHashTable[bucket] = new DbLinkedList<K, E>();
                    newHashTable[bucket]->push_front(p->key, p->data);
                }
                p = p->rLink;
            }
        }
    }

    HashTable.resizeList(TableSize);
    for (int j = 0; j < TableSize; j++)   //���¸��Ƹ�hashtable
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

    cout << "����" << TableSize << endl;
    cout << "������" << getDivisor(TableSize) << endl;
    cout << "Ͱ������" << BucketSize << endl;
    if (HashTable[1])
    {
        cout << HashTable[1]->getFirst()->rLink->key << endl;
    }

    cout << "��Ӻ�" << endl;

    for (int i = 0; i < 100; i++)
        Insert(i, i);
    if (HashTable[2])
    {
        cout << HashTable[2]->getFirst()->rLink->key << endl;
    }
    cout << "����" << TableSize << endl;
    cout << "������" << getDivisor(TableSize) << endl;
    cout << "Ͱ������" << BucketSize << endl;

}







