#ifndef _UNION_FIND_DELETE_HPP
#define _UNION_FIND_DELETE_HPP

#pragma once
#include <map>
#include <unordered_map>
#include <set>
#include <climits>
#include <set>
#include <sstream>
template <typename T>
class UnionFindDelete{
public:
	//Constructor
	UnionFindDelete() : next_available(0) {};

	//Destructor
	~UnionFindDelete(){};

	//Add a new element 'value'
	//Returns the index assigned to the node 'value'
	unsigned int MakeSet(const T& value){
		if (map_node.size() == UINT_MAX)
			throw ("This data structure does not support more elements. Try delete some elements first\n");
		while (map_node.find(next_available) != map_node.end())
			next_available++;
		map_node.insert(std::make_pair(next_available, Node(value, next_available)));
		return next_available;
	}

	//Add a new element 'value', numbered 'index'
	void MakeSet(const T& value, unsigned int index){
		if (map_node.find(index) != map_node.end()){
			std::stringstream error_message;
			error_message << "Element with index : " << index << " already exists\n";
			throw (error_message.str().c_str());
		}
		map_node.insert(std::make_pair(index, Node(value, index)));
	}

	
	//Union sets containing Nodes represented by 'x' and 'y'
	void UnionSets(unsigned int x, unsigned int y){
		int set_x = FindSet(x);
		int set_y = FindSet(y);
		if (set_x != set_y)
			Link(set_x, set_y);
	}


	//Find the representant of a set
	unsigned int FindSet(unsigned int x){
		Node& node = GetNode(x);
		unsigned int parent = node.parent;
		if (parent != x)
			parent = FindSet(parent);
		return parent;
	}

	//Delete an element
	void Delete(unsigned int x){
		Node& node = GetNode(x);
		if (node.parent != x){
			Clean(node,x);
		}
		if (node.children != 0)
			node.marked_to_delete = true;
		else
			Free(x);
	}

	//Return all elements separated by sets
	std::set< std::set<T> > Forest(){
		std::map<unsigned int, std::set<T> > mapped_sets;

		for (auto it = map_node.begin(); it != map_node.end(); ++it){
			unsigned int cur = it->first;
			unsigned int root = FindSet(cur);
			Node& node = it->second;
			mapped_sets[root].insert(node.data);
		}

		std::set< std::set<T> > result;
		for (auto it = mapped_sets.begin(); it != mapped_sets.end(); ++it){
			result.insert(it->second);
		}
		return result;
	}

	//Display the forest
	void Display(){
		std::set< std::set<T> > forest = Forest();
		std::string result;
		for (auto current : forest){
			result += "( ";
			for (auto &element : current){
				string now = ToString(element);
				result += now + " ";
			}
			result += ")\n";
		}
		cout << result;
	}
	
private:

	struct Node{
		T data;
		unsigned int parent, rank, children;
		bool marked_to_delete;
		Node(const T& value, unsigned int _parent) : data(value), parent(_parent), rank(0), children(0), marked_to_delete(false) {}
	};

	//Link two elements numbered 'x' and 'y'
	void Link(unsigned int x, unsigned int y){
		if (x == y) return;
		Node &node_x = GetNode(x);
		Node &node_y = GetNode(y);
		unsigned int rank_x = node_x.rank;
		unsigned int rank_y = node_y.rank;
		if (rank_x > rank_y){
			node_y.parent = x;
			node_x.children += node_y.children + 1;
		}
		else{
			node_x.parent = y;
			node_y.children += node_x.children + 1;
			if (rank_x == rank_y)
				++rank_y;
		}
	}

	Node& GetNode(unsigned int x){
		auto it = map_node.find(x);
		return it->second;
	}

	//Clean element
	void Clean(unsigned int x){
		Node& node = GetNode(x);
		--node.children;
		if (node.parent != x){
			Clean(node.parent)
		}
		if (node.marked_to_delete && node.children == 0){
			Free(x);
		}
	}

	//Delete element: 
	//TODO: Check if elements are in the data-structures before (compare performance without checks)
	void Free(unsigned int x){
		if (map_node.find(x) != map_node.end())
			map_node.erase(x);
		else
			throw ("Tried to delete non-existant element\n");
	}

	//std::unordered_map<unsigned int, Node> map_node;
	std::map<unsigned int, Node> map_node;
	unsigned int next_available;

	//Dirty code to help display data (Check that operator >> is defined)
	template<typename T, typename = decltype(std::declval<std::ostream&>() << std::declval<T const&>())>
	std::string ToString(T const& t){
		std::ostringstream out;
		out << t;
		return out.str();
	}

	template<typename T, typename... Ignored>
	std::string ToString(T const& t, Ignored const&..., ...){
		static_assert(sizeof...(Ignored) == 0
			, "Incorrect usage: only one parameter allowed");
	std:string ret = "Can not print data. Is operator >> defined for the data type you are trying to print?";
		return ret;
	}
};



#endif