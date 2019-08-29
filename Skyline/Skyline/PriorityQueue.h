#pragma once

#include<vector>



// custom exception
class UnderFlowException : public std::runtime_error
{
public:
	UnderFlowException(char const* const message) throw() : std::runtime_error(message) {
		
	};
	virtual char const* what() const throw() {
		return	std::exception::what();
	};
};


using namespace std;
template <typename Comparable>
class PriorityQueue
{

private:


	// inner class for elements
	struct Item { Comparable value; int label; };

	int currentSize; // Number of elements in heap
	int locationSize; // number of elements in locations

	vector<Item> array;
	vector<int> locations;
public:



	explicit PriorityQueue(int capacity = 100) {
		array = vector<Item>( capacity );
		locations = vector<int>(capacity,-2);
		currentSize = 0;
		locationSize = 0;
	}

	// check if priority queue empty
	bool isEmpty() const {
		return currentSize == 0;
	};

	// get maximum element
	const Comparable & getMax() const {
		if (isEmpty())
			throw UnderFlowException("underflow");
		return array[1].value;
	};


	// insert height and label
	 void insert(const Comparable & x,int label)
	 {
		 if ((currentSize == array.size() - 1) || label>currentSize){
			 array.resize(array.size() * 2);
			 locations.resize(locations.size() * 2);

		 }

		 locationSize++;
		 if (locationSize < label)
			 locationSize = label + 1;
		 int hole = ++currentSize;
		 Item copy;
		 copy.value = x;
		 copy.label = label;

		 
		 array[0] = std::move(copy);
		 for (; x > array[hole / 2].value; hole /= 2) {
			 locations[array[hole / 2].label] = hole ;
			 array[hole] = std::move(array[hole / 2]);
			
		 }

		 array[hole] = std::move(array[0]);
		 locations[array[hole].label] = hole;

	 }



	// move the node down
	 void percolateDown(int hole)
	 {
		 int child;
		 Item tmp = std::move(array[hole]);
		 for (; hole * 2 <= currentSize; hole = child)
		 {
			 child = hole * 2;
			 if (child != currentSize && array[child + 1].value > array[child].value)
				++child;
			 if (array[child].value > tmp.value) {
				
				 array[hole] = std::move(array[child]);
				 if(locations[array[hole].label]!=-1)
					locations[array[hole].label] = hole;

			 }
			 else
				break;
		 }

		 array[hole] = std::move(tmp);

			
		 if (locations[array[hole].label] != -1)
		 {
			 locations[tmp.label] = hole;
		 }
	 }


	
	void makeEmpty() {
		while (currentSize > 0)
			deleteMin();
	}
			
	int getSize() {
		return currentSize;
	}


	// for debugging
	void dumpHeap() {
		cout << "items : ";
		for (int i = 1; i < currentSize + 1; ++i) {
			cout << array[i].value << " : " << array[i].label << "   ";
		}
		cout << endl << "locations : ";

		for (int i = 1; i < locationSize + 1; ++i) {
			cout << i<<" : "<< locations[i] << "   ";
		}
		cout << endl<<endl;
	}

	// check if label exists
	bool labelExists(int label) {
		if ((label > locations.size()) || (locations[label] < 0))
			return false;
		else
			return true;
	}
	

	void remove(int label) {

		
		int itemIndex = locations[label];

		if (-1 == itemIndex)
			throw UnderFlowException("this item doesn't exist");

		locations[array[itemIndex].label] = -1;

		array[itemIndex] = std::move(array[currentSize--]);


		percolateDown(itemIndex);


	}




	// redundant methods used during debugging

	private:


	void deleteMax()
	{
	cout << endl << " maximum deleted " << endl;

	if (isEmpty())
	throw UnderFlowException("underflow");

	locations[array[1].label] = -1;

	array[1] = std::move(array[currentSize--]);
	locations[array[1].label] = 1;

	percolateDown(1);
	}



	void removeNode(int p) {
		if(p>currentSize)			
				throw UnderFlowException("underflow");
		//cout << p << "th node is removed" << endl;
		array[p+1] = std::move(array[currentSize--]);

		percolateDown(p+1,false);

	}
	

	explicit PriorityQueue(const vector<Comparable> & items)
	: array(items.size() + 10), currentSize{ items.size() }
	{

	for (int i = 0; i < items.size(); ++i)
	array[i + 1].value = items[i];
	buildHeap();

	}


	
	
};

