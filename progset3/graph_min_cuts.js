var fs = require('fs');

fs.readFile('kargerMinCut.txt', function(err, data) {
	if (err) throw(err);

	var nodes = data.toString().split('\n').map(function(str) {
		var obj = {};
		var str_arr = str.split('\t').map(function(val) {
			return val * 1;
		}).filter(function(val) {
			return val > 0;
		});
		obj.node = str_arr.shift();
		obj.edges = str_arr;
		return obj;
	});

	console.log(nodes);
});