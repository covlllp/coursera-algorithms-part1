var fs = require('fs');

fs.readFile('QuickSort.txt', function(err, data) {
	if (err) throw(err);

	var set = data.toString().split('\n').map(function(str) {
		return str * 1;
	});

	// set = [9,8,7,   6,5,4,   3,2,1];
	// set = [1,2,3,4,5,6];
	// Implement the quicksort algorithm
	function quicksort_first (arr, lo, hi) {
		if (lo >= hi) return;
		comps += hi - lo - 1;
		// var p = partition(arr, lo, hi, lo);
		var p = partition(arr, lo, hi, lo);
		quicksort_first(arr, lo, p);
		quicksort_first(arr, p+1, hi);
	}

	function quicksort_end (arr, lo, hi) {
		if (lo >= hi) return;
		comps += hi - lo - 1;
		// var p = partition(arr, lo, hi, lo);
		var p = partition(arr, lo, hi, hi - 1);
		quicksort_end(arr, lo, p);
		quicksort_end(arr, p+1, hi);
	}

	function quicksort_med_of_three (arr, lo, hi) {
		if (lo >= hi) return;
		comps += hi - lo - 1;
		// var p = partition(arr, lo, hi, lo);
		// var p = partition(arr, lo, hi, hi - 1);
		var lo_val = arr[lo];
		var hi_val = arr[hi - 1];
		var mid = lo + Math.floor((hi - lo - 1)/2);
		var mid_val = arr[mid];
		var med;
		if (lo_val > mid_val) {
			if (mid_val > hi_val) med = mid;
			else if (lo_val > hi_val) med = hi - 1;
			else med = lo;
		} else {
			if (lo_val > hi_val) med = lo;
			else if (mid_val > hi_val) med = hi - 1;
			else med = mid;
		}
		// console.log([lo_val, hi_val, mid_val]);
		// console.log('med is:', arr[med]);
		var p = partition(arr, lo, hi, med);

		quicksort_med_of_three(arr, lo, p);
		quicksort_med_of_three(arr, p+1, hi);
	}

	function partition(arr, lo, hi, swap_ind) {
		swap(arr, lo, swap_ind);
		var p = arr[lo];
		var pivot_ind = lo + 1;
		for (var i = pivot_ind; i < hi; i++) {
			if (arr[i] < p) {
				swap(arr, pivot_ind, i);
				pivot_ind++;
			}
		}
		swap(arr, pivot_ind - 1, lo);
		return pivot_ind - 1;
	}

	function swap (arr, a, b) {
		var temp = arr[b];
		arr[b] = arr[a];
		arr[a] = temp;
	}

	var comps = 0;
	var new_set = set.slice();
	quicksort_first(new_set, 0, new_set.length);
	console.log('first ind:', comps);

	comps = 0;
	new_set = set.slice();
	quicksort_end(new_set, 0, new_set.length);
	console.log('end ind:', comps);

	comps = 0;
	new_set = set.slice();
	quicksort_med_of_three(new_set, 0, new_set.length);
	console.log('median ind:', comps);
	// console.log(set);
	// console.log(comps);
});