var fs = require('fs');

fs.readFile('Median.txt', function(err, data) {
	if (err) throw (err);
	data = data.toString().split('\n').map(function(str) {
		return str * 1;
	});
	data.pop();
	var set = new Set();
	var count = 0;
	while (data.length) {
		set.add(data.shift());
		count += set.getMedian();
	}
	console.log('answer is:', count % 10000);
});

var Set = function() {
	this.minHeap = new Heap(true);
	this.maxHeap = new Heap(false);
};

Set.prototype.size = function() {
	return this.minHeap.size() + this.maxHeap.size();
};

Set.prototype.add = function(val) {
	var lowMed = this.minHeap.peek();
	if (!lowMed || val < lowMed) {
		this.maxHeap.push(val);
	} else {
		this.minHeap.push(val);
	}

	var sizeGoal = Math.floor((this.size() + 1) / 2);
	if (this.maxHeap.size() < sizeGoal) {
		this.maxHeap.push(this.minHeap.pop());
	} else if (this.maxHeap.size() > sizeGoal) {
		this.minHeap.push(this.maxHeap.pop());
	}


	// var highMed = this.minHeap.peek();
	// if (!lowMed || val < lowMed) {
	// 	if (this.size() % 2) this.minHeap.push(this.maxHeap.pop());
	// 	this.maxHeap.push(val);
	// } else {
	// 	if (!(this.size() % 2)) this.maxHeap.push(this.minHeap.pop());
	// 	this.minHeap.push(val);
	// }
};

Set.prototype.getMedian = function() {
	return this.maxHeap.peek();
};

var Heap = function(bool) {
	// true indicates min, false indicates max
	this.data = [];
	this.type = bool;
};

Heap.prototype.size = function() {
	return this.data.length;
};

Heap.prototype.push = function(val) {
	this.data.push(val);
	this.bubbleUp(this.data.length - 1);
};

Heap.prototype.pop = function() {
	this.swap(0, this.data.length - 1);
	var val = this.data.pop();
	this.bubbleDown(0);
	return val;
};

Heap.prototype.peek = function() {
	if (!this.size()) return null;
	return this.data[0];
};

Heap.prototype.swap = function(ind_a, ind_b) {
	var temp = this.data[ind_a];
	this.data[ind_a] = this.data[ind_b];
	this.data[ind_b] = temp;
};

Heap.prototype.bubbleUp = function(ind) {
	if (!ind) return;	// index is root
	var parent_ind = Math.floor((ind - 1) / 2);
	var val = this.data[ind];
	var parentVal = this.data[parent_ind];
	if ((this.type && val < parentVal) || (!this.type &&val > parentVal)) {
		this.swap(ind, parent_ind);
		this.bubbleUp(parent_ind);
	}
};

Heap.prototype.bubbleDown = function(ind) {
	var firstInd = ind * 2 + 1;
	if (firstInd >= this.size()) return;
	var secondInd = firstInd + 1;
	if (secondInd >= this.size()) secondInd = firstInd;
	var firstChild = this.data[firstInd];
	var secondChild = this.data[secondInd];
	var childInd = ((this.type && firstChild < secondChild) ||
					!this.type && firstChild > secondChild)
						? firstInd : secondInd;
	if ((this.type && this.data[ind] < this.data[childInd]) ||
		(!this.type && this.data[ind] > this.data[childInd])) return;
	this.swap(ind, childInd);
	this.bubbleDown(childInd);
};
