#pragma once
#include"ExpandableArrayList.h"


template<class E>
ExpandableArrayList<E>::ExpandableArrayList()
{
	m_arr = new E[100];
	m_size = 100;
	m_length = 0;
}


template<class E>
ExpandableArrayList<E>::ExpandableArrayList(int sz)
{
	m_arr = new E[sz];
	m_size = sz;
	m_length = 0;
}







template<class E>
E& ExpandableArrayList<E>::operator[](int i)
{
	return m_arr[i];
}


template<class E>
void ExpandableArrayList<E>::resizeList()
{

	E* newarr = new E[2 * m_size];
	for (int i = 0; i < m_length; i++)        //复制原数组
	{
		newarr[i] = m_arr[i];
	}
	m_arr = newarr;
	m_size = 2 * m_size;

}


template<class E>
void ExpandableArrayList<E>::resizeList(int sz)
{

	E* newarr = new E[sz];
	m_arr = newarr;
	m_size = sz;
}



template<class E>
void ExpandableArrayList<E>::push_back(E data)
{
	if (m_length == m_size) resizeList();
	m_arr[m_length] = data;
	m_length++;
}



template<class E>
void ExpandableArrayList<E>::Clear()
{
	delete[] m_arr;
	m_arr = NULL;
}

template<class E>
void ExpandableArrayList<E>::show()
{
	for (int i = 0; i < m_length; i++)
	{
		cout << m_arr[i];
	}
	cout << endl;
}



