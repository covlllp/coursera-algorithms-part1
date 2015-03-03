#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;

const long NUM_BUCKETS = 273601 * 3;

struct Link {
	long value;
	Link* next;
	Link(long v) {
		value = v;
		next = NULL;
	}

	bool AddToEnd(Link* link);
	bool CheckChain(long v);
};

struct HashTable {
	Link* table [NUM_BUCKETS];

	bool AddValue(long v);
	bool FindValue(long v);
	long GetBucket(long v);
	long CountPairs(vector<long> set, long low, long high);
	long CountPairsVTwo(vector<long> set, long range);
};

void populate(string fileName, HashTable* hash, vector<long>& set);
void addToBoth(long val, HashTable* hash, vector<long>& set);




// ----------------------- MAIN FILE ----------------------- //

int main() {
	HashTable* hash = new HashTable();
	
	vector<long> set;
	cout << "populate set and hash" << endl;

	addToBoth(1, hash, set);
	addToBoth(2, hash, set);
	addToBoth(3, hash, set);
	addToBoth(4, hash, set);



	// populate("algo1-programming_prob-2sum.txt", hash, set);

	cout << "populating done, count pairs" << endl;

	long pairs = hash->CountPairs(set, 0, 10);
	// long pairs = hash->CountPairs(set, -100000, 100000);

	cout << "counting done, # of pairs is: " << pairs << endl;
	return (0);
}



// Link methods

bool Link::AddToEnd(Link* link_pt) {
	// return true if added, false if match found
	if (value == link_pt->value) return false;

	if (!next) next = link_pt;
	else next->AddToEnd(link_pt);
	return true;
}

bool Link::CheckChain(long v) {
	if (value == v) return true;
	else if (!next) return false;
	else return next->CheckChain(v);
}



// HashTable methods

long HashTable::GetBucket(long v) {
	return abs(v) % NUM_BUCKETS;
}


bool HashTable::AddValue(long v) {
	// return true if added, false if match found
	long bin = GetBucket(v);
	Link* link_pt = new Link(v);

	if (!table[bin]) {
		table[bin] = link_pt;
		return true;
	} else return table[bin]->AddToEnd(link_pt);
}

bool HashTable::FindValue(long v) {
	// Return true if value found, else return false
	long bin = GetBucket(v);
	if (!table[bin]) return false;
	else return table[bin]->CheckChain(v);
}

long HashTable::CountPairs(vector<long> set, long low, long high) {
	long count = 0;
	bool flag;

	for (long i = low; i <= high; i++) {
		flag = true;
		for (long j = 0; j < set.size() && flag; j++) {
			long setVal = set[j];
			long searchVal = i - setVal;
			if (FindValue(searchVal) && setVal != searchVal) {
				count++;
				flag = false;
			}
		}
	}
	return count;
}

long HashTable::CountPairsVTwo(vector<long> set, long range) {
	long count = 0;
	HashTable hashCounter;

	for (int i = 0; i < set.size(); ++i) {
		long val = -set[i];
		if (hashCounter.AddValue(val)) count++;
	}
}





// General methods
void populate(string fileName, HashTable* hash, vector<long>& set) {
	string str;
	ifstream infile;
	infile.open(fileName);
	while(getline(infile, str)) {
		long val = stol(str);
		addToBoth(val, hash, set);		
		// hash->AddValue(val);
		// set.push_back(val);
	}
	infile.close();
}

void addToBoth(long val, HashTable* hash, vector<long>& set) {
	hash->AddValue(val);
	set.push_back(val);
}
