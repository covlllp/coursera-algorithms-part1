var fs = require('fs');

fs.readFile('edges.txt', function(err, data) {
  if (err) throw new Error(err);

  var set = data.toString().split('\n');
  var size = set.shift(); set.pop();
  size = size.split(' ')[0] * 1;
  var graph = new Graph();

  set.forEach(function(edgeStr) {
    var arr = edgeStr.split(' ');
    graph.addEdge(arr);
  });

  console.log(graph.getMST(size));
});

var Graph = function() {
  this.data = {};
};

Graph.prototype.getMST = function (size) {
  var hash = {};
  hash[this.data[1].name] = 0;
  var mst = [];
  var p = new PQueue(this.data[1]);

  while (size - 1) {
    var edge = p.pullMin();
    if (!hash.hasOwnProperty(edge.node)) {
      hash[edge.node] = 0;
      size--;
      mst.push(edge);
      this.data[edge.node].edges.forEach(function(e) {
        p.queue.push(e);
      });
    }
  }

  return mst.reduce(function(prev, cur) {
    return prev + cur.len;
  }, 0);
};

Graph.prototype.addEdge = function (arr) {
  var a = arr[0] * 1;
  var b = arr[1] * 1;
  var len = arr[2] * 1;
  if (!this.data.hasOwnProperty(a)) this.data[a] = new Node(a);
  if (!this.data.hasOwnProperty(b)) this.data[b] = new Node(b);
  this.data[a].edges.push(new Edge(b, len));
  this.data[b].edges.push(new Edge(a, len));
};

var Node = function(name) {
  this.name = name;
  this.edges = [];
};

var Edge = function(a, len) {
  this.node = a;
  this.len = len;
};

var PQueue = function(node) {
  this.queue = node.edges;
};

PQueue.prototype.pullMin = function () {
  var min = Infinity;
  var minInd = Infinity;
  for (var i = 0; i < this.queue.length; i++) {
    var edge = this.queue[i];
    if (edge.len < min) {
      minInd = i;
      min = edge.len;
    }
  }
  return this.queue.splice(minInd, 1)[0];
};