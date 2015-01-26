var fs = require('fs');

fs.readFile('QuickSort.txt', function(err, data) {
	if (err) throw(err);

	var set = data.toString().split('\n').map(function(str) {
		return str * 1;
	});

	// Implement the quicksort algorithm
	function quicksort (arr, lo, hi) {
		if (lo >= hi) return;
		var p = partition(arr, lo, hi);
		quicksort(arr, lo, p-1);
		quicksort(arr, p+1, hi);
	}

	function partition(arr, lo, hi) {
		var p = arr[lo];
		var pivot_ind = lo + 1;
		for (var i = pivot_ind; i < hi; i++) {
			if (arr[i] < p) {
				swap(arr, pivot_ind, i);
				pivot_ind++;
			}
		}
		swap(arr, pivot_ind, lo);
	}

	function swap (arr, a, b) {
		var temp = arr[b];
		arr[b] = arr[a];
		arr[a] = temp;
	}

	quicksort(set, 0, set.length);
	console.log(set);
});