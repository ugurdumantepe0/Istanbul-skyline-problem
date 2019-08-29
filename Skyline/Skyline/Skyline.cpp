

#include "stdafx.h"
#include<iostream>
#include<string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include "PriorityQueue.h"
using namespace std;

// edge of the building
enum Edge {Left,Right};

struct InputItem {
	Edge edge;
	int xCoor;
	int yCoor;
	int label;
	InputItem(Edge edgeIn, int x,int y,int lab):edge(edgeIn), xCoor(x),yCoor(y),label(lab){}
	friend std::ostream& operator<< (std::ostream& stream, const InputItem& input) {
		if (input.edge == Left)
			stream << "left ";
		else
			stream << "right ";

		stream << input.xCoor << " " << input.yCoor<< " "<<input.label ;
		return stream;
	}
};


struct less_than_key
{
	inline bool operator() (const InputItem& arg1, const InputItem& arg2)
	{
		if (arg1.xCoor < arg2.xCoor) {
			return true;
		}
		else if (arg1.xCoor == arg2.xCoor && arg1.edge == Right) {
			if (arg1.yCoor > arg2.yCoor)
				return true;
			else
				return false;

			return true;
		}
		else
		{
			return false;
		}
	}
};



int main()
{

	// vector for sorting inputs according to x coordinate.
	vector<InputItem> edges;


	string str;

	ifstream input("input.txt");

	int count, left, top, right;
	getline(input, str);
	count = stoi(str);

	int iLabel = 1;
	while (getline(input, str) && iLabel<(count+1)) {
		std::istringstream iss(str);
		iss >> left >> top >> right;
		
		edges.push_back(InputItem(Left, left, top, iLabel));
		edges.push_back(InputItem(Right, right, top, iLabel));

		iLabel++;
	}




	sort(edges.begin(), edges.end(), less_than_key());


	// allocate size 
	PriorityQueue<int> pq(iLabel*2);
	
	int currentMax = -1;
	for (int i = 0; i < edges.size(); ++i) {

		auto elem = edges[i];

		while (true) {
			elem = edges[i];
			if (!pq.labelExists(elem.label)) {

				pq.insert(elem.yCoor, elem.label);
			}
			else {
				pq.remove(elem.label);
			}
			if ((i + 1 == edges.size()) || (edges[i + 1].xCoor != edges[i].xCoor))
				break;
		++i;}
		if (!pq.isEmpty()) {
			if (currentMax != pq.getMax()) {
				if (currentMax == -1 && elem.xCoor > 0) {
					cout << "0 0" << endl;
				}				

				cout << elem.xCoor << " " << pq.getMax() << endl;

				currentMax = pq.getMax();
			}
		}

		// when right wall goes 0.
		else {
			cout << elem.xCoor << " " << 0 << endl;
			
		}
	}



	getchar();
    return 0;
}

