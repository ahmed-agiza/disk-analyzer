// Dimentions of the doughnut
var width = 960,
    height = 450,
    radius = Math.min(width, height) / 2;

// Global Variables
var svg;
var readable;

// Doughnut build
var pie = d3.layout.pie()
    .sort(null)
	.value(function(d) {
		return d.value;
	});

// The arcs for the individual elements and the whoe shape
var arc = d3.svg.arc()
	.outerRadius(radius * 0.8)
	.innerRadius(radius * 0.4);

var outerArc = d3.svg.arc()
	.innerRadius(radius * 0.9)
	.outerRadius(radius * 0.9);

// Color set
var doughnutColor = d3.scale.category10();

// Test data
/*var testData = [
  {name: "A", value: 500},
  {name: "A", value: 1000},
  {name: "C", value: 200},
  {name: "D", value: 2500},
  {name: "E", value: 1500},
  {name: "F", value: 5000},
  {name: "H", value: 100},
  {name: "I", value: 1000},
  {name: "J", value: 1200},
  {name: "K", value: 1300},
];*/

// Test call

//visualize(testData);

 //applySettings(true);
 //visualize(testData);


function visualize(data) {
    hideProgress();
    initializeDoughnut();
    d3.select("#container").on("mouseleave", mouseleave);

	/* ------- PIE SLICES -------*/
	var slice = svg.select(".slices").selectAll("path.slice")
        .data(pie(data));
	slice.enter()
		.insert("path")
        .style("fill", function(d) { return doughnutColor(d.data.name); })
        .attr("class", "slice")
        .on("mouseover", mouseover);
	slice		
		.transition().duration(1000)
		.attrTween("d", function(d) {
			this._current = this._current || d;
            var interpolate = d3.interpolate({ data: {name: "dummy", value: 0}, value: 0, startAngle: 0, endAngle: 0, padAngle: 0 }, d);
			this._current = interpolate(0);
			return function(t) {
				return arc(interpolate(t));
			};
		})
	slice.exit()
		.remove();

	/* ------- TEXT LABELS -------*/
    var text = svg.select(".labels").selectAll("text")
        .data(pie(data));
	text.enter()
		.append("text")
		.attr("dy", ".35em")
		.text(function(d) {
            return d.data.name;
		});
	text.transition().duration(1000)
		.attrTween("transform", function(d) {
			this._current = this._current || d;
            var interpolate = d3.interpolate({ data: {name: "dummy", value: 0}, value: 0, startAngle: 0, endAngle: 0, padAngle: 0 }, d);
			this._current = interpolate(0);
			return function(t) {
				var d2 = interpolate(t);
				var pos = outerArc.centroid(d2);
				pos[0] = radius * (midAngle(d2) < Math.PI ? 1 : -1);
				return "translate("+ pos +")";
			};
		})
		.styleTween("text-anchor", function(d){
			this._current = this._current || d;
            var interpolate = d3.interpolate({ data: {name: "dummy", value: 0}, value: 0, startAngle: 0, endAngle: 0, padAngle: 0 }, d);
			this._current = interpolate(0);
			return function(t) {
				var d2 = interpolate(t);
				return midAngle(d2) < Math.PI ? "start":"end";
			};
		});
	text.exit()
		.remove();

	/* ------- SLICE TO TEXT POLYLINES -------*/
	var polyline = svg.select(".lines").selectAll("polyline")
        .data(pie(data));
	polyline.enter()
		.append("polyline");
	polyline.transition().duration(1000)
		.attrTween("points", function(d){
			this._current = this._current || d;
            var interpolate = d3.interpolate({ data: {name: "dummy", value: 0}, value: 0, startAngle: 0, endAngle: 0, padAngle: 0 }, d);
            this._current = interpolate(0);
            return function(t) {
				var d2 = interpolate(t);
				var pos = outerArc.centroid(d2);
				pos[0] = radius * 0.95 * (midAngle(d2) < Math.PI ? 1 : -1);
				return [arc.centroid(d2), outerArc.centroid(d2), pos];
			};			
		});
	polyline.exit()
		.remove();
}

function midAngle(d){
    return d.startAngle + (d.endAngle - d.startAngle)/2;
}

function mouseover(d){
    // Fade all parts
    d3.selectAll("path")
        .style("opacity", 0.3);

    // Show the hovered arc
    d3.selectAll("path")
        .filter(function(node) {
            return (node === d);
        })
        .style("opacity", 1);

    // Display value
    d3.select("#explanation")
        .text(readable ? convert(d.value, true) : d.value + " files")
        .style("visibility", "");
}

function mouseleave(){
    // Show the whole chart
    d3.selectAll("path")
        .transition()
        .duration(1000)
        .style("opacity", 1)
        .each("end", function() {
            d3.select(this).on("mouseover", mouseover);
        });

    d3.select("#explanation")
        .style("visibility", "hidden");
}

// Initialize Doughnut
function initializeDoughnut(){
    // Doughnut skeleton
    svg = d3.select("#chart")
        .append("svg")
        .append("g")
        .attr("id", "container")
    svg.append("g")
        .attr("class", "slices");
    svg.append("g")
        .attr("class", "labels");
    svg.append("g")
        .attr("class", "lines");

    // Location of the doughnut
    svg.attr("transform", "translate(" + width / 2 + "," + height / 2 + ")");
}

// Readable memory display
function convert(bytes, units){
    var out;
    if(bytes < 1000) out = bytes.toPrecision(3) + (units ? "B": "");
    else if (bytes < 1000*1000) out = (bytes / 1000.0).toPrecision(3) + (units ? "KB": "");
    else if (bytes < 1000*1000*1000) out = (bytes / (1000.0*1000.0)).toPrecision(3) + (units ? "MB": "");
    else out = (bytes / (1000.0*1000.0*1000.0)).toPrecision(3) + (units ? "GB": "");
    return out;
}

function applySettings(en){
    if (typeof en == "undefined") readable = true;
    else readable = en;
}
