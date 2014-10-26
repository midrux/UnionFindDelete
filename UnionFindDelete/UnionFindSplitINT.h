#ifndef _UNION_FIND_SPLIT_HPP
#define _UNION_FIND_SPLIT_HPP

#pragma once
#include <vector>
#include <set>
#include<stack>
using namespace std;
class UnionFindSplitINT
{
public:
	UnionFindSplitINT(int N);
	~UnionFindSplitINT();
	int Find(int z);
	void UnionSets(int x, int y);
	void Separate(int z);
	int FindLeaveSlow(int node);
	int FindLeave(int node);
private:
	vector<int> parent, rank, pointer, manager;
	vector<set<int> > children;
	void Union(int x, int y);

};

#endif