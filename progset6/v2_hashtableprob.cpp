#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;

const long NUM_BUCKETS = 273601 * 3;
const long Tmax = 10000;
const long Tmin = -10000;
// const long Tmax = 20;
// const long Tmin = -20;
const long W = Tmax - Tmin;

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

	bool AddValue(long v, bool flag);
	bool FindValue(long v);
	long GetBucket(long v, bool flag);
	long CountPairs(vector<long> set);
	void CheckIndex(long &count, long val, long bin, HashTable &tempTable);

};

void populate(string fileName, HashTable* hash, vector<long>& set);
void addToBoth(long val, HashTable* hash, vector<long>& set);




// ----------------------- MAIN FILE ----------------------- //

int main() {
	HashTable* hash = new HashTable();

	vector<long> set;
	cout << "populate set and hash" << endl;

	// addToBoth(-5, hash, set);
	// addToBoth(2, hash, set);
	// addToBoth(6, hash, set);
	// addToBoth(20, hash, set);



	populate("algo1-programming_prob-2sum.txt", hash, set);

	cout << "populating done, count pairs" << endl;

	long pairs = hash->CountPairs(set);

	cout << "counting done, # of pairs is: " << pairs << endl;
	return (0);
}



// Link methods

bool Link::AddToEnd(Link* link_pt) {
	// return true if added, false if match found
	if (value == link_pt->value) return false;

	if (!next) {
		next = link_pt;
		return true;
	} else return next->AddToEnd(link_pt);
}

bool Link::CheckChain(long v) {
	if (value == v) return true;
	else if (!next) return false;
	else return next->CheckChain(v);
}



// HashTable methods

long HashTable::GetBucket(long v, bool flag) {
	// if true, use funny bucket. else, just get normal bucket
	if (flag) return (abs(v) / W) % NUM_BUCKETS;
	else return abs(v) % NUM_BUCKETS;
}


bool HashTable::AddValue(long v, bool flag) {
	// return true if added, false if match found
	long bin = GetBucket(v, flag);
	Link* link_pt = new Link(v);

	if (!table[bin]) {
		table[bin] = link_pt;
		return true;
	} else return table[bin]->AddToEnd(link_pt);
}

bool HashTable::FindValue(long v) {
	// Return true if value found, else return false
	long bin = GetBucket(v, false);
	if (!table[bin]) return false;
	else return table[bin]->CheckChain(v);
}

long HashTable::CountPairs(vector<long> set) {
	HashTable tempTable;
	long count = 0;
	for (long j = 0; j < set.size(); j++) {
		long val = set[j];
		long searchBin = abs(val) / W % NUM_BUCKETS;

		// cout << "val is " << val <<  endl;

		CheckIndex(count, val, searchBin, tempTable);
		CheckIndex(count, val, searchBin + 1, tempTable);
	}
	return count;
}

void HashTable::CheckIndex(long &count, long val, long bin, HashTable &tempTable) {
	// cout << "searchBin is " << bin <<  endl;

	Link* link;
	if (!table[bin]) return;
	link = table[bin];
	while (link) {
		long check = link->value;
		long sum = check + val;

		// cout << "checking " << check << ", sum is " << sum << endl;
		// cout << "bool checks: ";
		// cout << (check != val);
		// cout << (sum >= Tmin);
		// cout << (sum <= Tmax) << endl;

		if (check != val && sum >= Tmin && sum <= Tmax) {
			if (tempTable.AddValue(sum, false)) {
				// cout << "added " << sum << endl;
				count++;
			}
		}
		link = link->next;
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
	}
	infile.close();
}

void addToBoth(long val, HashTable* hash, vector<long>& set) {
	hash->AddValue(val, true);
	set.push_back(val);
}
