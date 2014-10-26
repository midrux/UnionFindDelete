#include "UnionFindSplitINT.h"


UnionFindSplitINT::UnionFindSplitINT(int N) : parent(N), rank(N), pointer(N), manager(N), children(N){
	for (int i = 0; i<N; i++){ 
		parent[i] = pointer[i] = manager[i] = i; rank[i] = 0; 
	}
}


UnionFindSplitINT::~UnionFindSplitINT()
{
}


void UnionFindSplitINT::Union(int x, int y){
	if (x == y) return;
	if (rank[x] < rank[y]){
		parent[x] = y;
		children[y].insert(x);
	}
	else if (rank[x] > rank[y]){
		parent[y] = x;
		children[x].insert(y);
	}
	else{
		parent[y] = x;
		rank[x]++;
		children[x].insert(y);
	}
}

int UnionFindSplitINT::Find(int z){
	int x = manager[z];
	stack<int> branch;
	while (x != parent[x]){
		branch.push(x);
		x = parent[x];
	}
	while (!branch.empty()){
		int cur = branch.top(); branch.pop();
		int p = parent[cur];
		if (p != x){
			children[p].erase(cur);
		}
		if (parent[cur] != x){
			int p = parent[cur];
			children[p].erase(cur);
			children[x].insert(cur);
			parent[cur] = x;
		}
	}
	return x;
}

void UnionFindSplitINT::UnionSets(int x, int y){
	Union(Find(x), Find(y));
}

void UnionFindSplitINT::Separate(int z){
	int x = manager[z];
	int l = FindLeave(x);
	//int l =FindLeaveSlow(x);
	if (l == x){
		int p = parent[x];
		//First: If x is an isolated node, nothing to do
		if (p == x) return;

		//Second: Delete x from his parent's children
		children[p].erase(x);

		//Point to himself
		parent[x] = x; rank[x] = 0;
		children[x].clear();
	}
	else{
		//Swap (x, l)
		//Change elements pointed to:
		pointer[x] = pointer[l];
		manager[pointer[x]] = x;

		pointer[l] = z;
		manager[z] = l;

		Separate(z);
	}
}


int UnionFindSplitINT::FindLeaveSlow(int node){
	if (!children[node].empty())
		return FindLeaveSlow(*children[node].begin());
	return node;
}

int UnionFindSplitINT::FindLeave(int node){
	int p = parent[node];
	while (!children[node].empty()){
		children[parent[node]].erase(node);
		if (p != node){
			parent[node] = p;
			children[p].insert(node);
		}
		node = *children[node].begin();
	}
	children[parent[node]].erase(node);
	parent[node] = p;
	if (p != node)
		children[p].insert(node);
	return node;
}
