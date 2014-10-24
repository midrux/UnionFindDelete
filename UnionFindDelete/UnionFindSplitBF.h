#pragma once
#include <set>
#include <vector>
#include <sstream>
using namespace std;

class UnionFindSplitBF{
public:
	UnionFindSplitBF(int N) : parent(N), rank(N) { for (int i = 0; i<N; i++) { parent[i] = i; rank[i] = 0; } }
	void Union(int x, int y){
		if (rank[x] < rank[y]) parent[x] = y;
		else if (rank[x] > rank[y]) parent[y] = x;
		else{
			parent[y] = x;
			rank[x]++;
		}
	}
	int Find(int x){ if (x != parent[x]) parent[x] = Find(parent[x]); return parent[x]; }
	void UnionSets(int x, int y){ Union(Find(x), Find(y)); }
	void Split(int x){
		int rx = Find(x);
		if (x != rx){
			for (int i = 0; i<parent.size(); i++)
				if (parent[i] == x) parent[i] = rx;
		}
		else{
			int replace = -1;
			for (int i = 0; i<parent.size(); i++){
				if (i == x) continue;
				if (parent[i] == x){
					if (replace == -1){
						replace = i;
						parent[i] = i;
					}
					else{
						parent[i] = replace;
					}
				}
			}
		}
		parent[x] = x;
	}
	void Display(){
		set< set<int> > forest = Forest();
		std::string result;
		for (auto current : forest){
			result += "( ";
			for (auto &element : current){
				stringstream ss; ss << element; string now = ss.str();
				result += now + " ";
			}
			result += ")\n";
		}
		cout << result;
	}

	vector<int> parent, rank;
	set<set<int> > Forest(){
		set<set<int> > ret;
		vector< set<int> > sets(parent.size());
		for (int i = 0; i<parent.size(); i++){
			sets[Find(i)].insert(i);
		}
		for (int i = 0; i<parent.size(); i++){
			if (!sets[i].empty())
				ret.insert(sets[i]);
		}
		return ret;
	}
	~UnionFindSplitBF(){};
};

