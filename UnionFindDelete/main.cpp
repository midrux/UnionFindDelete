#include <iostream>
#include <vector>
#include "UnionFindDelete.hpp"
using namespace std;


int main(){
	UnionFindDelete<int> B;
	for (int i = 0; i < 10; i++){
		B.MakeSet(i,i);
	}
	B.UnionSets(0, 1);
	B.UnionSets(2, 3);
	B.Display();
	
	return 0;
}