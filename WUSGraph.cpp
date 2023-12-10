#pragma once
#include"WUSGraph.h"

template<class W, class V>
int WUSGraph<W, V>::vertexCount() {
	return this->vertex_count;
}

template<class V, class W>
int WUSGraph<V, W>::edgeCount()
{
	return this->edge_count;
}

template<class V, class W>
V* WUSGraph<V, W>::getVertices()
{
	return this->vertex_array;
}

template<class V, class W>
void WUSGraph<V, W>::addVertex(V tar_key)
{
	if (isVertex(tar_key)) return;
	vertex_hash.Insert(pair<V, int>(tar_key, index));   //���붥���ϣ��
	
	Vertex<int, W> newVertex(index);
	vertex_list.push_front(index, newVertex);           //���붥������

	vertex_array[index++] = tar_key;                    //���붥���¼����

	++vertex_count;
}

template<class V, class W>
bool WUSGraph<V, W>::isVertex(V tar_key)
{
	return this->vertex_hash.containsKey(tar_key);
}

template<class V, class W>
int WUSGraph<V, W>::Degree(V tar_key)
{
	int node_No = vertex_hash.getValue(tar_key);
	if (node_No != 0) return vertex_list.Search(node_No)->data.degree; //�ҵ��򷵻�����ڵ��degree
	else return 0;
	
}

template<class V, class W>
Neighbors<W, V> WUSGraph<V, W>::getNeighbors(V tar_key)
{
	Neighbors<int, W > m_neighbor;
	if (!isVertex(tar_key)) return m_neighbor;       //�ڵ㲻����
	int vertex_No = vertex_hash.getValue(tar_key);  //���ҵ�ǰ�ڵ����ֵ
	DbListNode<int, Vertex<int, W>>* tar_Node = vertex_list.Search(vertex_No); //�ҵ���������Ŀ��ڵ�
	Vertex<int, W> tar_vertex = tar_Node->data;     //��ȡĿ��ڵ�
	DbListNode<int, Edge<int, W>>* first = tar_vertex.EdgeList.getFirst();
	DbListNode<int, Edge<int, W>>* point_index = first->rLink;
	while (point_index != first) {    //����Ŀ��ڵ�edge_list,�����ݼ�¼��m_neighbor��
		DbListNode<V, Vertex<V, W>>* vertex_temp = point_index->data.vertex_point;
		int key_temp = vertex_temp->data.data;
		Vertex<int, W> newvertex(key_temp);
		W weight_temp = point_index->data.weight;              //��ȡ��ǰ�߽ڵ�ָ��Ķ�����ź�Ȩֵ
	    
		m_neighbor.object.push_front(key_temp, newvertex);     
		m_neighbor.weight.push_front(weight_temp);            //���뵽m_neighbor��
		
		point_index = point_index->rLink;                          
	}
	return m_neighbor;
}


template<class V, class W>
void WUSGraph<V, W>::addEdge(V v1_key, V v2_key, W input_weight)
{
	if (isEdge(v1_key, v2_key)) return;
	if (isVertex(v1_key && isVertex(v2_key))) {
	
		int v1_No = vertex_hash.getValue(v1_key);
		int v2_No = vertex_hash.getValue(v2_key);
		DbListNode<int, Vertex<int, W>>* vertex_dbnode1 = vertex_list.Search(v1_No);
		DbListNode<int, Vertex<int, W>>* vertex_dbnode2 = vertex_list.Search(v2_No);
		Vertex<int, W> vertex1 = vertex_dbnode1->data;
		Vertex<int, W> vertex2 = vertex_dbnode2->data;                                             

		edge_hash.Insert(pair<V, pair<int, int>>(v1_key + v2_key, pair<int, int>(v1_No, v2_No)));
		edge_hash.Insert(pair<V, pair<int, int>>(v1_key + v2_key, pair<int, int>(v2_No, v1_No)));  //����߹�ϣ����

		Edge<int, W> edge1;
		Edge<int, W> edge2;
		edge1.vertex_point = vertex_dbnode2;
		edge2.vertex_point = vertex_dbnode1;
		edge1.weight = input_weight;
		edge2.weight = input_weight;
		vertex1.EdgeList.push_front(v2_No, edge1);
		vertex2.EdgeList.push_front(v1_No, edge2);                                             //�����ڽӱ���

		DbListNode<int, Edge<int, W>>* edge_Node1 = vertex1.EdgeList.getFirst()->rLink;
		DbListNode<int, Edge<int, W>>* edge_Node2 = vertex2.EdgeList.getFirst()->rLink;
		edge_Node1->data.friend_point = edge_Node2;
		edge_Node2->data.friend_point = edge_Node1;                                            //������ָ�븳ֵ

		++vertex1.degree;
		++vertex2.degree;
		++edge_count;               //�޸ļ���

	}
	else if (isVertex(v1_key) && !isVertex(v2_key)) {   //�ڵ�1���ڣ��ڵ�2�����ڣ���ӽڵ�2������
		addVertex(v2_key);
		addEdge(v1_key, v2_key, input_weight);
	}
	else if(!isVertex(v1_key) && isVertex(v2_key)){     //�ڵ�2���ڣ��ڵ�1�����ڣ���ӽڵ�2������
		addVertex(v1_key);
		addEdge(v1_key, v2_key, input_weight);
	}
	
}

template<class V, class W>
bool WUSGraph<V, W>::isEdge(V v1_key, V v2_key)
{
	V key = v1_key + v2_key;
	if (edge_hash.getValue(key) == pair<int, int>()) return 0;
	else return 1;

}

template<class V, class W>
void  WUSGraph<V, W>::removeVertex(V tar_key)
{
	if (!isVertex(tar_key)) return;
	//
	int locNum = vertex_hash.getValue(tar_key);     //�ҵ���Ӧ�ص�ı��
	DbListNode<int, Vertex<int, W>>* node = vertex_list.Search(locNum);   //�ɱ���ҵ�������еĽڵ�

	Vertex<int, W> v = node->data;

	DbLinkedList<int, Edge<int, W>> edgeList = v.EdgeList;              //�ɶ����ȡ���б�

	DbListNode<int, Edge<int, W>>* first = edgeList.getFirst();

	DbListNode<int, Edge<int, W>>* p = first->rLink;

	while (p != first)
	{
		//��ɾ��p�Ļ��ڵ�
		DbListNode<int, Edge<int, W>>* pfriend = p->data.friend_point;   //��ȡp�Ļ��ڵ�
		DbListNode<int, Vertex<int, W>>* neinode = p->data.vertex_point;  //��ȡ�ڽӶ���ڵ�

		neinode->data.degree--;    //��-1


		pfriend->lLink->rLink = pfriend->rLink;
		pfriend->rLink->lLink = pfriend->lLink;
		delete pfriend;

		//ɾ��p����p�ƶ�����һλ��
		DbListNode<int, Edge<int, W>>* pnext = p->rLink;   //����p����һλ��
		p->lLink->rLink = p->rLink;
		p->rLink->lLink = p->lLink;
		delete p;
		p = pnext;
	}

	vertex_array[locNum] = NULL;   //��Ӧ��������λ��Ϊ��
	vertex_count--;

	vertex_hash.Remove(tar_key);  //����ɢ���ж�Ӧ����ɾ��

	//ɾ�������б��е���Ӧ����
	node->lLink->rLink = node->rLink;
	node->rLink->lLink = node->lLink;
	delete node;





}

template<class V, class W>
W WUSGraph<V, W>::getWeight(V v1_key, V v2_key)
{
	if (!isEdge(v1_key, v2_key))
		return W();
	else
	{
		int v1Loc = vertex_hash.getValue(v1_key);            //��ȡv1������
		int v2Loc = vertex_hash.getValue(v2_key);            //��ȡv2������
		DbListNode<int, Vertex<int, W>>* node = vertex_list.Search(v1Loc);//��˫�����в���
		Vertex<int, W> Ver1 = node->data;//��ȡ�������
		DbLinkedList<int, Edge<int, W>> edgeList = Ver1.EdgeList;//��ȡ���������
		DbListNode<int, Edge<int, W>>* eNode = edgeList.Search(v2Loc);//���Ҷ�Ӧ�߽��
		Edge<int, W> edge = eNode->data;                       //��ȡ�߶���
		return edge.weight;
	}


}

template<class V, class W>
void WUSGraph<V, W>::Travel_Single_Bucket(V vertex_key)
{
	if (!isVertex(vertex_key)) return;
	int tar_No = this->vertex_hash.getValue(vertex_key);
	DbListNode<int, Vertex<int, W>>* tar_Node = this->vertex_list.Search(tar_No);
	Vertex<int, W> tar_vertex = tar_Node->data;
	DbLinkedList<int, Edge<int, W>> tar_edgelist = tar_vertex.EdgeList;           //�ҵ�Ŀ��ڵ��edgelist

	DbListNode<int, Edge<int, W>>* first = tar_edgelist.getFirst();
	DbListNode<int, Edge<int, W>>* index = first->rLink;                          //��ʼ������ָ��

	int count = 1;

	while (index!=NULL&&index != first) {

		cout << tar_No << "�ĵ�" << count++ << "���߽ڵ�ָ�� " << index->key;

		cout << "  ���Ļ��ָ��ָ�� " << index->data.friend_point->key << endl;

		index = index->rLink;
	}
}


template<class V, class W>
void  WUSGraph<V, W>::removeEdge(V v1_key, V v2_key)
{
	if (!isEdge(v1_key, v2_key)) return;

	//��ȡ������
	int v1Loc = vertex_hash.getValue(v1_key);
	int v2Loc = vertex_hash.getValue(v2_key);

	//�ڶ����б����ҵ�����������ڵ�
	DbListNode<int, Vertex<int, W>>* node1 = vertex_list.Search(v1Loc);
	DbListNode<int, Vertex<int, W>>* node2 = vertex_list.Search(v2Loc);

	node1->data.degree--;     //��-1
	node2->data.degree--;

	DbLinkedList<int, Edge<int, W>> edgeList = node1->data.EdgeList;


	//�ҵ����ڱ߽ڵ�
	DbListNode<int, Edge<int, W>>* edge_node1 = edgeList.Search(v2Loc);

	DbListNode<int, Edge<int, W>>* edge_node2 = edge_node1->data.friend_point;

	edge_node1->lLink->rLink = edge_node1->rLink;
	edge_node1->rLink->lLink = edge_node1->lLink;

	edge_node2->lLink->rLink = edge_node2->rLink;
	edge_node2->rLink->lLink = edge_node2->lLink;

	V key = v1_key + v2_key;

	edge_hash.Remove(key);  //��ɢ�б���ɾ����

	delete edge_node1;
	delete edge_node2;

	edge_count--;

}
