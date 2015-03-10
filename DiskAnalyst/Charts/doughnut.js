// Dimentions of the doughnut
var width = 960,
    height = 450,
    radius = Math.min(width, height) / 2;

// Doughnut skeleton
var svg = d3.select("#chart")
	.append("svg")
	.append("g")
svg.append("g")
	.attr("class", "slices");
svg.append("g")
	.attr("class", "labels");
svg.append("g")
	.attr("class", "lines");

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

// Location of the doughnut
svg.attr("transform", "translate(" + width / 2 + "," + height / 2 + ")");

// Return name
var key = function(d){ return d.data.name; };

// Color set
var doughnutColor = d3.scale.category10();

// Test data
var testData = [
  {name: "A", value: 500},
  {name: "B", value: 1000},
  {name: "C", value: 200},
  {name: "D", value: 2500},
  {name: "E", value: 1500},
  {name: "F", value: 5000},
  {name: "H", value: 100},
  {name: "I", value: 1000},
  {name: "J", value: 1200},
  {name: "K", value: 1300},
];

change(testData);

function change(data) {
	/* ------- PIE SLICES -------*/
	var slice = svg.select(".slices").selectAll("path.slice")
		.data(pie(data), key);
	slice.enter()
		.insert("path")
        .style("fill", function(d) { return doughnutColor(d.data.name); })
		.attr("class", "slice");
	slice		
		.transition().duration(1000)
		.attrTween("d", function(d) {
			this._current = this._current || d;
			var interpolate = d3.interpolate(this._current, d);
			this._current = interpolate(0);
			return function(t) {
				return arc(interpolate(t));
			};
		})
	slice.exit()
		.remove();

	/* ------- TEXT LABELS -------*/
	var text = svg.select(".labels").selectAll("text")
		.data(pie(data), key);
	text.enter()
		.append("text")
		.attr("dy", ".35em")
		.text(function(d) {
            return d.data.name;
		});
	text.transition().duration(1000)
		.attrTween("transform", function(d) {
			this._current = this._current || d;
			var interpolate = d3.interpolate(this._current, d);
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
			var interpolate = d3.interpolate(this._current, d);
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
		.data(pie(data), key);
	polyline.enter()
		.append("polyline");
	polyline.transition().duration(1000)
		.attrTween("points", function(d){
			this._current = this._current || d;
			var interpolate = d3.interpolate(this._current, d);
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
