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

//双向链表测试
/*
void dbtext() {
	DbLinkedList<int, int> db1;
	cout << "加入: ";
	for (int i = 0; i < 5; ++i) db1.push_front(i, i);
	db1.Traverse();
	int i = 3;
	db1.Remove(i);
	cout << "删除key == 3后: "; db1.Traverse();
	 i = 2;
	 db1.Remove(i);
	 cout << "删除key == 2后: "; db1.Traverse();
	db1.Clear();
	cout << "clear后: ";
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

	cout << "当前节点数量为:  " << W1.vertexCount() << endl;  	cout << endl;

	cout << "当前边数量为:  " << W1.edgeCount() << endl;  	cout << endl;

	cout << "遍历节点5415的边节点: " << endl;  	cout << endl;

   W1.Travel_Single_Bucket(5415); cout << endl;

	cout << "遍历节点5417的边节点: " << endl;   cout << endl;

	W1.Travel_Single_Bucket(5417);  	cout << endl;

	W1.removeEdge(5415, 5417);

	cout << "删除边5415,5417后再遍历5415节点: " << endl; 	cout << endl;

	W1.Travel_Single_Bucket(5415);  cout << endl;

	cout << "删除边5415,5417后再遍历5417节点: " << endl; cout << endl;

	W1.Travel_Single_Bucket(5417); cout << endl;

	int tar_weight = W1.getWeight(940, 942);

	cout << "940-942的权值为" << tar_weight << "  正确值为948" << endl;
}



int main() {
	test_WUSGraph();
}




