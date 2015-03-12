// Test Data
/*var testData = [
  {name: "AAAAAAAAAAAAAAAAAAAAAAAA", value: 500},
  {name: "BAA", value: 10000},
  {name: "BAA", value: 200},
  {name: "DAA", value: 2500},
  {name: "EAA", value: 1500},
  {name: "FAA", value: 5000},
  {name: "GAA", value: 5000},
  {name: "HAA", value: 100},
  {name: "IAA", value: 1000},
  {name: "JAA", value: 1200},
  {name: "KAA", value: 1300},
  {name: "LAA", value: 500},
  {name: "MAA", value: 1000},
  {name: "NAA", value: 200},
  {name: "OAA", value: 2500},
  {name: "PAA", value: 1500},
  {name: "QAA", value: 5000},
  {name: "RAA", value: 100},
  {name: "SAA", value: 1000},
  {name: "TAA", value: 1200},
  {name: "UAA", value: 1300}
];*/

// Global variables
var svg;
var barData;
var units;
var readable;

// The margins of the bar chart
var margin = {top: 50, right: 20, bottom: 110, left: 110},
    width = 900 - margin.left - margin.right,
    height = 500 - margin.top - margin.bottom;

// Scale generators
var x = d3.scale.ordinal()
    .rangeRoundBands([0, width], .1, 1);
var y = d3.scale.linear()
    .range([height, 0]);

// Axis generators
var xAxis = d3.svg.axis()
    .scale(x)
    .tickFormat(function(d) {return d.substr(0, d.length-6).length > 13 ? d.substr(0, d.length-6).substr(0, 12)+".." : d.substr(0, d.length-6);})
    .orient("bottom");

var yAxis = d3.svg.axis()
    .scale(y)
    .orient("left");

// Sort timeout
var sortTimeout = function() {
    setTimeout(function() {
        d3.select("input").property("checked", true).each(change);
    }, 500);
}

// TEST CALL
// applySettings(true);
// visualize(testData);

function visualize(data){
    barData = data;
    hideProgress();
    initializeBar();

    // Plotting the data
    svg.selectAll(".bar")
        .data(barData)
        .enter().append("rect")
        .attr("class", "bar")
        .attr("x", function(d) {return x(d.name);})
        .attr("width", x.rangeBand())
        .attr("y", function(d) {return y(readable ? convert(d.value, units) : d.value);})
        .attr("height", function(d) {return height - y(readable ? convert(d.value, units): d.value);});

    d3.select("input").on("change", change);
    sortTimeout();
}

function change() {
  clearTimeout(sortTimeout);

  // Copy-on-write since tweens are evaluated after a delay.
  var x0 = x.domain(barData.sort(this.checked
      ? function(a, b) {return b.value - a.value;}
      : function(a, b) {return d3.ascending(a.name, b.name);})
      .map(function(d) {return d.name;}))
      .copy();

  var transition = svg.transition().duration(750),
      delay = function(d, i) {return i * 50;};

  transition.selectAll(".bar")
      .delay(delay)
      .attr("x", function(d) {return x0(d.name);});

  transition.select(".x.axis")
      .call(xAxis)
      .selectAll("g")
      .delay(delay)
      .selectAll("text")
      .style("text-anchor", "end")
      .attr("dx", "-.8em")
      .attr("dy", ".15em")
      .attr("transform", function(d) {
          return "rotate(-90)"
      });
}

function initializeBar(){
    var max = findMax(barData);
    units = configureScale(max);

    // Skeleton for the chart
    svg = d3.select("#chart").append("svg")
        .attr("width", width + margin.left + margin.right)
        .attr("height", height + margin.top + margin.bottom)
        .append("g")
        .attr("transform", "translate(" + margin.left + "," + margin.top + ")");

    // Defining the domain of the graph
    x.domain(barData.map(function(d){return d.name;}));
    y.domain([0, readable ? convert(max, units) : max]);

    // Plotting axis
    svg.append("g")
        .attr("class", "x axis")
        .attr("transform", "translate(0," + height + ")")
        .call(xAxis)
        .selectAll("text")
        .style("text-anchor", "end")
        .attr("dx", "-.8em")
        .attr("dy", ".15em")
        .attr("transform", function(d) {
            return "rotate(-90)"
        });

    svg.append("g")
        .attr("class", "y axis")
        .call(yAxis)
        .append("text")
        .attr("transform", "rotate(-90)")
        .attr("y", 6)
        .attr("dy", ".71em")
        .style("text-anchor", "end")
        .text(readable ? ("Value / " + units) : "Files");
}

// Selecting appropriate scale
function configureScale(max){
    if(max < 1000) return "B";
    else if (max < 1000*1000) return "KB";
    else return "MB";
}

// Find Maximum value
function findMax(data){
    var max = 0;
    for(var i=0; i<data.length; i++){
        if (data[i].value > max) max = data[i].value;
        barData[i].name = barData[i].name + Math.floor(100000 + Math.random() * 900000);
    }
    return max;
}

// Convert to scale
function convert(bytes, un){
    switch(un){
    case "B": return bytes;
    case "KB": return (bytes / 1000.0).toPrecision(3);
    case "MB": return (bytes / (1000.0*1000.0)).toPrecision(3);
    }
}

function applySettings(en){
    if (typeof en == "undefined") readable = true;
    else readable = en;
}
