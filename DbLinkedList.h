#pragma once
#include<iostream>
using namespace std;


template <class K, class E>
struct DbListNode {

	E data;

	K key;

	DbListNode* lLink;

	DbListNode* rLink;

	DbListNode() {

		lLink = NULL;

		rLink = NULL;

	}

	DbListNode(K init_key, E init_data) {

		key = init_key;

		data = init_data;

		lLink = NULL;

		rLink = NULL;
	}

};

template <class K, class E>
class DbLinkedList
{
private:

	DbListNode<K, E>* first;

	int length = 0; //��¼��ǰ�ڵ�����

public:

	DbListNode<K, E>* Search(K& tar);//Ѱ��ָ��keyֵ�ڵ�

	//�±�Ϊ0��ʼ
	bool Insert(int i, K& key_value, E& data);

	bool Remove(K tar);

	bool Clear();

	bool push_front(K key_value, E data);

	void Traverse()    //�������
	{
		DbListNode<K, E>* p = first->rLink;
		while (p != first)
		{
			cout << p->data;
			p = p->rLink;
		}
		cout << endl;

	}

	DbListNode<K, E>* getFirst()
	{
		return first;
	}

	int getLength()
	{
		return length;
	}



	DbLinkedList()
	{
		this->first = new DbListNode<K, E>();
		first->lLink = first;
		first->rLink = first;
	}

	DbLinkedList(DbListNode<K, E>* node)
	{

		this->first = node;
	}






};