var fs = require('fs');

fs.readFile('jobs.txt', function(err, data) {
  if (err) throw new Error(err);

  // var jobs = new Data();
  var set = data.toString().split('\n');
  set.pop(); set.shift();

  set = set.map(function(job) {
    return new Job(job.split(' '));
  });
  var jobs = new Data(set);

  jobs.sort('scoreDiff');
  console.log(jobs.scheduleWeight());
  jobs.sort('scoreQuot');
  console.log(jobs.scheduleWeight());

});

var Data = function(arr) {
  this.data = arr;
};

Data.prototype.sort = function (key) {
  for (var i = 0; i < this.data.length; i++) {
    var minInd = i;
    var job = this.data[i];
    for (var j = i; j < this.data.length; j++) {
      if (job.comp(this.data[j], key) > 0) {
        minInd = j;
        job = this.data[j];
      }
    }
    this.swap(i, minInd);
  }
};

Data.prototype.scheduleWeight = function() {
  var sum = 0;
  this.data.reduce(function(prev, cur) {
    var totLength = prev + cur.len;
    sum += totLength * cur.weight;
    return totLength;
  }, 0);
  return sum;
};

Data.prototype.swap = function (a, b) {
  var temp = this.data[a];
  this.data[a] = this.data[b];
  this.data[b] = temp;
};

var Job = function(arr) {
  this.weight = arr[0] * 1;
  this.len = arr[1] * 1;
  this.scoreDiff = this.weight - this.len;
  this.scoreQuot = this.weight / this.len;
};

Job.prototype.comp = function (otherJob, key) {
  // negative if smaller, positive if larger
  var c = otherJob[key] - this[key];
  return c ? c : (this.weight > otherJob.weight ? -1 : 1);
};