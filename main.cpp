#pragma once
#include<iostream>
#include"HashMap.h"
#include"HashMap.cpp"
#include"ExpandableLinkedHashTable.h"
#include"ExpandableLinkedHashTable.cpp"
#include"DbLinkedList.h"
#include"DbLinkedList.cpp"
#include"ExpandableArrayList.h"
#include"ExpandableArrayList.cpp"
#include"WUSGraph.h"
#include"WUSGraph.cpp"

using namespace std;

//˫���������
/*
void dbtext() {
	DbLinkedList<int, int> db1;
	cout << "����: ";
	for (int i = 0; i < 5; ++i) db1.push_front(i, i);
	db1.Traverse();
	int i = 3;
	db1.Remove(i);
	cout << "ɾ��key == 3��: "; db1.Traverse();
	 i = 2;
	 db1.Remove(i);
	 cout << "ɾ��key == 2��: "; db1.Traverse();
	db1.Clear();
	cout << "clear��: ";
	db1.Traverse();
}
*/

void test05() {

	HashMap<int, int> h1;
	for (int i = 0; i < 1000; ++i) {
		h1.Insert(pair<int,int>(i,i));
	}
	h1.Travel();

}

void test_WUSGraph() {
	WUSGraph<int, int> W1(10000);

	for (int i = 1; i <= 10000; ++i) {
		W1.addVertex(i);
	}
	for (int i = 1; i <= 9998; ++i) {
		W1.addEdge(i, i + 2, i + 8);
	}

	cout << "��ǰ�ڵ�����Ϊ:  " << W1.vertexCount() << endl;  	cout << endl;

	cout << "��ǰ������Ϊ:  " << W1.edgeCount() << endl;  	cout << endl;

	cout << "�����ڵ�5415�ı߽ڵ�: " << endl;  	cout << endl;

   W1.Travel_Single_Bucket(5415); cout << endl;

	cout << "�����ڵ�5417�ı߽ڵ�: " << endl;   cout << endl;

	W1.Travel_Single_Bucket(5417);  	cout << endl;

	W1.removeEdge(5415, 5417);

	cout << "ɾ����5415,5417���ٱ���5415�ڵ�: " << endl; 	cout << endl;

	W1.Travel_Single_Bucket(5415);  cout << endl;

	cout << "ɾ����5415,5417���ٱ���5417�ڵ�: " << endl; cout << endl;

	W1.Travel_Single_Bucket(5417); cout << endl;

	int tar_weight = W1.getWeight(940, 942);

	cout << "940-942��ȨֵΪ" << tar_weight << "  ��ȷֵΪ948" << endl;
}



int main() {
	test_WUSGraph();
}




