#pragma once
#include<iostream>
using namespace std;


template<class E>
class ExpandableArrayList
{
private:
	E* m_arr;
	int m_size;   //数组大小
	int m_length;    //数组元素数量

public:
	ExpandableArrayList();         //默认大小为100
	ExpandableArrayList(int sz);
	~ExpandableArrayList() {}
	E& operator[](int i);      //重载运算符[]
	void resizeList();         //重新设置大小
	void resizeList(int sz);    //重新设置大小并删除原有内容
	void Clear();
	void push_back(E data);     //后插元素
	void show();
	int getSize()
	{
		return m_size;
	}
};