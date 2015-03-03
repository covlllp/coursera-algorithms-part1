var fs = require('fs');

fs.readFile('dijkstraData.txt', function(err, data) {
	if (err) throw (err);
	var graph = new Graph();
	graph.populate(data);

	var dist_map = graph.findShortestPaths();

	printInd(dist_map, 7);
	printInd(dist_map, 37);
	printInd(dist_map, 59);
	printInd(dist_map, 82);
	printInd(dist_map, 99);
	printInd(dist_map, 115);
	printInd(dist_map, 133);
	printInd(dist_map, 165);
	printInd(dist_map, 188);
	printInd(dist_map, 197);
});


function printInd (map, ind) {
	console.log('shortest distance for\t', ind, ' \tis\t', map[ind]);
}

var Node = function(name, edge_arr) {
	this.name = name;
	this.edges = edge_arr;
};

var Edge = function(node, distance) {
	this.node = node;
	this.dist = distance;
};

var Path = function(node, distance) {
	this.node = node;
	this.dist = distance;
};

var Graph = function() {
	this.nodes = {};
};

var Pqueue = function() {
	this.queue = [];
};

Pqueue.prototype.enqueue = function(path) {
	this.queue.push(path);
};

Pqueue.prototype.dequeue = function() {
	var min = Infinity;
	var ind = Infinity;
	for (var i = 0; i < this.queue.length; i++) {
		var path = this.queue[i];
		if (path.dist < min) {
			ind = i;
			min = path.dist;
		}
	}
	var temp = this.queue.splice(ind, 1);
	return temp[0];
};


Graph.prototype.populate = function(data) {
	var self = this;
	data.toString().split('\n')
	.forEach(function(line) {
		var line_arr = line.split('\t');
		var name = line_arr.shift() * 1;
		var edges = line_arr.map(function(str) {
			var str_arr = str.split(',');
			return new Edge(str_arr[0] * 1,str_arr[1] * 1);
		});
		edges.pop();
		self.nodes[name] = new Node(name, edges);
	});
};

Graph.prototype.findShortestPaths = function() {
	var dist_map = {};	// key refers to node, val = shortest distance
	var count = 0;		// if count reaches 200, end loop
	var queue = new Pqueue();
	queue.enqueue(new Path(1, 0));

	while (count < 200) {
		var path = queue.dequeue();
		var name = path.node;
		var dist = path.dist;
		
		if (!dist_map.hasOwnProperty(name)) {
			dist_map[name] = dist;
			count++;
			var node = this.nodes[name];
			node.edges.forEach(function(edge) {
				if (!dist_map.hasOwnProperty(edge.node)) {
					queue.enqueue(new Path(edge.node, dist + edge.dist));
				}
			});
		}
	}
	return dist_map;
};