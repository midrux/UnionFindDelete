#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "UnionFindDelete.hpp"
#include "UnionFindSplitBF.h"
using namespace std;
using namespace std::chrono;

bool Test(int N, int Q, bool display_screen = false){
	//Create a UnionFindSplit structure (Brute-Force version)
	UnionFindSplitBF UFS(N);

	//Create a UnionFindDelete structure (Efficient version)
	UnionFindDelete<int> UFD;
	for (int i = 0; i < N; i++) UFD.MakeSet(i, i);

	for (int i = 0; i < Q; i++){
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> dis(0, N - 1);

		int p = rand() % 2, elem1 = dis(gen), elem2 = dis(gen);
		elem1 = rand() % N, elem2 = rand() % N;

		if (p == 0){
			//cout << "Union (" << elem1 << ", " << elem2 << ")" << endl;
			UFD.UnionSets(elem1, elem2);
			UFS.UnionSets(elem1, elem2);
		}
		else{

		}
		if (display_screen){
			cout << "UFD: \n";
			UFD.Display();
			cout << "UFS: \n";
			UFS.Display();
			cout << "\n*****************\n";
		}
		set<set<int> > forest_UFD = UFD.Forest();
		set<set<int> > forest_UFS = UFS.Forest();

		if (forest_UFD != forest_UFS){
			//system("PAUSE");
			return false;
		}
		else{
			//	B.Display2();
			//	B.Display();
			continue;
		}
	}
	return true;
}


void TestCorrectness(int MAX_ELEMS = 50){
	UnionFindDelete<int> B;
	for (int amount_elements = 1; amount_elements < MAX_ELEMS; amount_elements++){
		int queries = 5 * amount_elements;
		bool result = Test(amount_elements, queries);
		if (result){
			cout << "Test(" << amount_elements << ", " << queries << "): OK\n";
		}
		else{
			cout << "Test(" << amount_elements << ", " << queries << "): FAILED\n";
			getchar();
		}
	}
}

void TestPerformance(int N, int Q){
	UnionFindDelete<int> B;
	for (int i = 0; i < N; i++)
		B.MakeSet(i,i);

	char op;
	int cntDebug = 0;
	for (int i = 0; i<Q; i++){
		if (i % 10000 == 0) cout << "Operation: " << i << endl;
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> dis(0, N - 1);

		int p = rand() % 2, elem1 = dis(gen), elem2 = dis(gen);
		//elem1 = rand()%N, elem2 = rand()%N;
		if (p == 0 || i % 2 == 0){

			//cout << "Union (" << elem1 << ", " << elem2 << ")" << endl;
			B.UnionSets(elem1, elem2);
		}
		else{
			unsigned int who = B.FindSet(elem1);
			//cout << "Separate(" << elem1 << ")" << endl;
			//B.Separate(elem1);
		}
		//B.CheckInvariants();
	}
}


int main(){
	TestCorrectness(100);
	int elems, queries;
	
	
	cout << "Write: Amount of elements followed by amount of queries\n";
	while (cin >> elems >> queries){
		auto t0 = high_resolution_clock::now();
		TestPerformance(elems,queries);
		auto t1 = high_resolution_clock::now();
		cout << "Test(" << elems << ", " << queries << "): " << std::chrono::duration_cast<milliseconds>(t1 - t0).count() << "msec\n";
	}
	return 0;
}