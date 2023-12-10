#pragma once
#include"DbLinkedList.h"
#include"ExpandableArrayList.h"
#include"ExpandableLinkedHashTable.h"
#include"HashMap.h"
#include<iostream>
using namespace std;

template<class V, class W>
struct Vertex;

template<class V, class W>
struct Edge;

template<class V, class W>
struct Neighbors;

template<class V, class W>
class WUSGraph;


template<class V, class W>
struct Vertex {

    int pos_x;   //x����

    int pos_y;   //y����

    int data;    //�����������

    int degree;//����Ķ�

    DbLinkedList<int, Edge<int, W>> EdgeList;//����ı�����

    Vertex<V, W>() {

        data = -999;

        degree = 0;

    }

    Vertex<V, W>(int init_data, int init_degree = 0, int init_x = -999, int init_y = -999) {

        data = init_data;

        degree = init_degree;

        pos_x = init_x;

        pos_y = init_y;

    }

    Vertex<int, W>& operator =(Vertex<int, W>& v)//���ظ�ֵ�����
    {
        this->data = v.data;

        this->degree = v.degree;

        return *this;

    }

    bool operator == (const Vertex<int, W> v)
    {

        if (this->data == v.data)
            return true;
        else
            return false;

    }
};

template<class V, class W>
struct Edge {

    DbListNode<V, Vertex<V, W>>* vertex_point; 

    DbListNode<V, Edge<V, W>>* friend_point;

    W weight;

    Edge<V, W>(){

        vertex_point = NULL;

        friend_point = NULL;

    }
    

    Edge<V, W>(DbListNode<V, Vertex<V, W>>* init_vertex_point, DbListNode<V, Edge<V, W>>* init_friend_point, W& init_weight) {
       
        vertex_point = init_vertex_point;

        friend_point = init_friend_point;
    
        weight = init_weight;
    }
};



//����getNeighbors����
template<class V, class W>
struct Neighbors {

    DbLinkedList<int, Vertex<int, W>> object;  //��Ӧ�������� 
    
    DbLinkedList<int, W> weight;              //��ӦȨֵ����
    
    Neighbors()
    {

    }

};

template<class V, class W>
class WUSGraph {
private:

    HashMap<V, int> vertex_hash;           //�ڲ������ڵ����������

    HashMap<V, pair<int, int>> edge_hash;  //�ڲ�����������������<int,int>����

    DbLinkedList<int, Vertex<int, W>> vertex_list; //����˫����

    int vertex_count = 0;                   //��������

    int edge_count = 0;                     //������

    V* vertex_array;                        //����V* getVerices()���ض�������

    int index = 1;                              //��indexλ�ò��룬��ʼֵΪ1�������²���ڵ�

public:

    WUSGraph(int v = 0) {
        vertex_array = new V[v + 1];

    }

    int vertexCount();

    int edgeCount();

    V* getVertices();

    void addVertex(V tar_key);

    void removeVertex(V tar_key);

    bool isVertex(V tar_key);

    int Degree(V tar_key);

    Neighbors<W, V> getNeighbors(V tar_key);

    void addEdge(V v1_key, V v2_key, W input_weight);

    void removeEdge(V v1_key, V v2_key);

    bool isEdge(V v1_key, V v2_key);

    W getWeight(V v1_key, V v2_key);

    void Travel_Single_Bucket(V vertex_key);

        

};

