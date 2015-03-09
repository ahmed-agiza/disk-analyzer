// Progress circle dimentions
var width = 960,
    height = 500,
    τ = 2 * Math.PI;

// Interval
var interval;

// Arc definition
var arc = d3.svg.arc()
    .innerRadius(180)
    .outerRadius(240);

// Initialize the location of progress circle
var svg = d3.select("#chart").append("svg")
    .attr("width", width)
    .attr("height", height)
    .append("g")
    .attr("transform", "translate(" + width / 2 + "," + height / 2 + ")")

// The background
var background = svg.append("path")
    .datum({startAngle:0, endAngle: τ})
    .style("fill", "#ddd")
    .attr("d", arc);

// The foreground
var foreground = svg.append("path")
    .datum({startAngle:0, endAngle: 0.127 * τ})
    .style("fill", "grey")
    .attr("d", arc);

// Test call
//showProgress();

// Test call
//hideProgress();

// Interpolation to rotate the arc (progressing effect)
function arcTween(transition) {
    transition.attrTween("d", function(d) {
    var interpolate = d3.interpolate(d.endAngle, d.endAngle+0.5);
    var inter = d3.interpolate(d.startAngle, d.startAngle+0.5);
    return function(t) {
        d.endAngle = interpolate(t);
        d.startAngle = inter(t);
        return arc(d);
    };
  });
}

// Wrapper calling function
function showProgress(){
    interval = setInterval(function() {
        foreground.transition()
            .duration(90)
            .call(arcTween);
    }, 50);
}

// Wrapper function to stop the progress circle
function hideProgress(){
    clearInterval(interval);
    $('#chart').empty();
}
