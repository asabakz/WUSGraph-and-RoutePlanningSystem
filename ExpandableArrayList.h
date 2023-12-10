#pragma once
#include<iostream>
using namespace std;


template<class E>
class ExpandableArrayList
{
private:
	E* m_arr;
	int m_size;   //�����С
	int m_length;    //����Ԫ������

public:
	ExpandableArrayList();         //Ĭ�ϴ�СΪ100
	ExpandableArrayList(int sz);
	~ExpandableArrayList() {}
	E& operator[](int i);      //���������[]
	void resizeList();         //�������ô�С
	void resizeList(int sz);    //�������ô�С��ɾ��ԭ������
	void Clear();
	void push_back(E data);     //���Ԫ��
	void show();
	int getSize()
	{
		return m_size;
	}
};