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
	vertex_hash.Insert(pair<V, int>(tar_key, index));   //加入顶点哈希表
	
	Vertex<int, W> newVertex(index);
	vertex_list.push_front(index, newVertex);           //加入顶点链表

	vertex_array[index++] = tar_key;                    //加入顶点记录数组

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
	if (node_No != 0) return vertex_list.Search(node_No)->data.degree; //找到则返回这个节点的degree
	else return 0;
	
}

template<class V, class W>
Neighbors<W, V> WUSGraph<V, W>::getNeighbors(V tar_key)
{
	Neighbors<int, W > m_neighbor;
	if (!isVertex(tar_key)) return m_neighbor;       //节点不存在
	int vertex_No = vertex_hash.getValue(tar_key);  //查找当前节点序号值
	DbListNode<int, Vertex<int, W>>* tar_Node = vertex_list.Search(vertex_No); //找到在链表找目标节点
	Vertex<int, W> tar_vertex = tar_Node->data;     //获取目标节点
	DbListNode<int, Edge<int, W>>* first = tar_vertex.EdgeList.getFirst();
	DbListNode<int, Edge<int, W>>* point_index = first->rLink;
	while (point_index != first) {    //遍历目标节点edge_list,将数据记录到m_neighbor中
		DbListNode<V, Vertex<V, W>>* vertex_temp = point_index->data.vertex_point;
		int key_temp = vertex_temp->data.data;
		Vertex<int, W> newvertex(key_temp);
		W weight_temp = point_index->data.weight;              //获取当前边节点指向的顶点序号和权值
	    
		m_neighbor.object.push_front(key_temp, newvertex);     
		m_neighbor.weight.push_front(weight_temp);            //加入到m_neighbor中
		
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
		edge_hash.Insert(pair<V, pair<int, int>>(v1_key + v2_key, pair<int, int>(v2_No, v1_No)));  //插入边哈希表中

		Edge<int, W> edge1;
		Edge<int, W> edge2;
		edge1.vertex_point = vertex_dbnode2;
		edge2.vertex_point = vertex_dbnode1;
		edge1.weight = input_weight;
		edge2.weight = input_weight;
		vertex1.EdgeList.push_front(v2_No, edge1);
		vertex2.EdgeList.push_front(v1_No, edge2);                                             //插入邻接表中

		DbListNode<int, Edge<int, W>>* edge_Node1 = vertex1.EdgeList.getFirst()->rLink;
		DbListNode<int, Edge<int, W>>* edge_Node2 = vertex2.EdgeList.getFirst()->rLink;
		edge_Node1->data.friend_point = edge_Node2;
		edge_Node2->data.friend_point = edge_Node1;                                            //给朋友指针赋值

		++vertex1.degree;
		++vertex2.degree;
		++edge_count;               //修改记数

	}
	else if (isVertex(v1_key) && !isVertex(v2_key)) {   //节点1存在，节点2不存在，添加节点2再连接
		addVertex(v2_key);
		addEdge(v1_key, v2_key, input_weight);
	}
	else if(!isVertex(v1_key) && isVertex(v2_key)){     //节点2存在，节点1不存在，添加节点2再连接
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
	int locNum = vertex_hash.getValue(tar_key);     //找到相应地点的编号
	DbListNode<int, Vertex<int, W>>* node = vertex_list.Search(locNum);   //由编号找到顶点表中的节点

	Vertex<int, W> v = node->data;

	DbLinkedList<int, Edge<int, W>> edgeList = v.EdgeList;              //由顶点获取边列表

	DbListNode<int, Edge<int, W>>* first = edgeList.getFirst();

	DbListNode<int, Edge<int, W>>* p = first->rLink;

	while (p != first)
	{
		//先删除p的伙伴节点
		DbListNode<int, Edge<int, W>>* pfriend = p->data.friend_point;   //获取p的伙伴节点
		DbListNode<int, Vertex<int, W>>* neinode = p->data.vertex_point;  //获取邻接顶点节点

		neinode->data.degree--;    //度-1


		pfriend->lLink->rLink = pfriend->rLink;
		pfriend->rLink->lLink = pfriend->lLink;
		delete pfriend;

		//删除p并将p移动至下一位置
		DbListNode<int, Edge<int, W>>* pnext = p->rLink;   //保留p的下一位置
		p->lLink->rLink = p->rLink;
		p->rLink->lLink = p->lLink;
		delete p;
		p = pnext;
	}

	vertex_array[locNum] = NULL;   //对应顶点数组位置为空
	vertex_count--;

	vertex_hash.Remove(tar_key);  //顶点散列中对应顶点删除

	//删除顶点列表中的相应顶点
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
		int v1Loc = vertex_hash.getValue(v1_key);            //获取v1顶点编号
		int v2Loc = vertex_hash.getValue(v2_key);            //获取v2顶点编号
		DbListNode<int, Vertex<int, W>>* node = vertex_list.Search(v1Loc);//在双链表中查找
		Vertex<int, W> Ver1 = node->data;//获取顶点对象
		DbLinkedList<int, Edge<int, W>> edgeList = Ver1.EdgeList;//获取顶点边链表
		DbListNode<int, Edge<int, W>>* eNode = edgeList.Search(v2Loc);//查找对应边结点
		Edge<int, W> edge = eNode->data;                       //获取边对象
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
	DbLinkedList<int, Edge<int, W>> tar_edgelist = tar_vertex.EdgeList;           //找到目标节点的edgelist

	DbListNode<int, Edge<int, W>>* first = tar_edgelist.getFirst();
	DbListNode<int, Edge<int, W>>* index = first->rLink;                          //初始化遍历指针

	int count = 1;

	while (index!=NULL&&index != first) {

		cout << tar_No << "的第" << count++ << "个边节点指向 " << index->key;

		cout << "  它的伙伴指针指向 " << index->data.friend_point->key << endl;

		index = index->rLink;
	}
}


template<class V, class W>
void  WUSGraph<V, W>::removeEdge(V v1_key, V v2_key)
{
	if (!isEdge(v1_key, v2_key)) return;

	//获取两点编号
	int v1Loc = vertex_hash.getValue(v1_key);
	int v2Loc = vertex_hash.getValue(v2_key);

	//在顶点列表中找到这两个顶点节点
	DbListNode<int, Vertex<int, W>>* node1 = vertex_list.Search(v1Loc);
	DbListNode<int, Vertex<int, W>>* node2 = vertex_list.Search(v2Loc);

	node1->data.degree--;     //度-1
	node2->data.degree--;

	DbLinkedList<int, Edge<int, W>> edgeList = node1->data.EdgeList;


	//找到所在边节点
	DbListNode<int, Edge<int, W>>* edge_node1 = edgeList.Search(v2Loc);

	DbListNode<int, Edge<int, W>>* edge_node2 = edge_node1->data.friend_point;

	edge_node1->lLink->rLink = edge_node1->rLink;
	edge_node1->rLink->lLink = edge_node1->lLink;

	edge_node2->lLink->rLink = edge_node2->rLink;
	edge_node2->rLink->lLink = edge_node2->lLink;

	V key = v1_key + v2_key;

	edge_hash.Remove(key);  //边散列表中删除该

	delete edge_node1;
	delete edge_node2;

	edge_count--;

}
