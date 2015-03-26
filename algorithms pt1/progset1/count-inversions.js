var fs = require("fs");

fs.readFile('IntegerArray.txt', function(err, data) {
	if (err) return console.log(err);

	var set = data.toString().split("\n").map(function(str) {
		return parseInt(str);
	});

	// var set = [1, 3, 5, 2, 4, 6, 0, 7];
	console.log("start");
	// var node = sort_count(new Node(set, 0));
	// console.log(node.arr);
	// console.log(node.inv); 

	function sort_count(node) {
		var arr = node.arr
		var length = arr.length;
		if (length <= 1) return node;
		var mid = Math.ceil(length / 2);
		var head = arr.slice(0, mid);
		var tail = arr.slice(mid, length);
		var nodeX = sort_count(new Node(head, 0));
		var nodeY = sort_count(new Node(tail, 0));
		var nodeZ = merge_and_count_split(nodeX.arr, nodeY.arr);
		return new Node(nodeZ.arr,
			nodeX.inv + nodeY.inv + nodeZ.inv);
	}

	function merge_and_count_split(head, tail) {
		var count = 0;
		var arr = [];
		var head_ind = 0;
		var tail_ind = 0;
		while (head_ind < head.length && tail_ind < tail.length) {
			var head_val = head[head_ind];
			var tail_val = tail[tail_ind];
			if (head_val < tail_val) {
				arr.push(head_val);
				head_ind++;
			} else {
				arr.push(tail_val);
				tail_ind++;
				count += head.length - head_ind;
			}
		}
		while (head_ind < head.length) {
			arr.push(head[head_ind]);
			head_ind++;
		}
		while (tail_ind < tail.length) {
			arr.push(tail[tail_ind]);
			tail_ind++;
		}


		return new Node(arr, count);
	}

	var node = sort_count(new Node(set, 0));
	console.log(node.inv);
	// console.log(node.arr);
	console.log("done");
});

function Node(arr, inversions) {
	this.arr = arr;
	this.inv = inversions;
}