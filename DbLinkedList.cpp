#pragma once
#include"DbLinkedList.h"


template <class K, class E>
DbListNode<K, E>* DbLinkedList<K, E>::Search(K& tar)
{
	DbListNode<K, E>* index = this->first->rLink;
	while (index != first) {
		if (index->key == tar) return index;
		index = index->rLink;
	}
	return NULL;
}


template <class K, class E>
bool DbLinkedList<K, E>::Insert(int pos, K& key_value, E& data)
{
	if (pos >= length) return 0; //表头不记入长度，表头rLink下标从0开始
	DbListNode<K, E>* index = this->first;
	DbListNode<K, E>* pre = this->first;
	DbListNode<K, E>* newnode = new DbListNode<K, E>(key_value, data);
	//找到位置
	for (int i = 0; i <= pos + 1; ++i) {
		pre = index;
		index = index->rLink;
	}
	//调整指针
	newnode->rLink = index;
	newnode->lLink = pre;
	index->lLink = newnode;
	pre->rLink = newnode;
	++length;

	return 1;
}

template<class K, class E>
bool DbLinkedList<K, E>::Remove(K tar)
{
	DbListNode<K, E>* index = this->first->rLink;
	DbListNode<K, E>* pre = this->first;

	while (index != first && index->key != tar) {
		pre = index;
		index = index->rLink;
	}
	if (index == first) return 0;

	DbListNode<K, E>* temp = index;

	pre->rLink = index->rLink;

	index->rLink->lLink = pre;

	--length;

	return 1;
}

template<class K, class E>
bool DbLinkedList<K, E>::Clear()
{
	DbListNode<K, E>* index = first->rLink;
	first->rLink = first;
	first->lLink = first;
	length = 0;

	while (index != first) {
		DbListNode<K, E>* temp = index;
		index = index->rLink;
		delete temp;

	}
	return 1;
}

template<class K, class E>
bool DbLinkedList<K, E>::push_front(K key_value, E data)
{
	return (this->Insert(-1, key_value, data));
}
