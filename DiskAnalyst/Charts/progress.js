// Progress circle dimentions
var pwidth = 960,
    pheight = 500,
    τ = 2 * Math.PI;

// Interval
var interval;

// Global
var foreground;

// Arc definition
var progressArc = d3.svg.arc()
    .innerRadius(180)
    .outerRadius(240);

// Test call
showProgress();

// Test call
//hideProgress();

function initialize(){
    // Initialize the location of progress circle
    var progressSvg = d3.select("#chart").append("svg")
        .attr("width", pwidth)
        .attr("height", pheight)
        .append("g")
        .attr("transform", "translate(" + pwidth / 2 + "," + pheight / 2 + ")")

    // The background
    var background = progressSvg.append("path")
        .datum({startAngle:0, endAngle: τ})
        .style("fill", "#ddd")
        .attr("d", progressArc);

    // The foreground
    foreground = progressSvg.append("path")
        .datum({startAngle:0, endAngle: 0.127 * τ})
        .style("fill", "grey")
        .attr("d", progressArc);
}

// Interpolation to rotate the arc (progressing effect)
function arcTweenProgress(transition) {
    transition.attrTween("d", function(d) {
    var interpolateEnd = d3.interpolate(d.endAngle, d.endAngle+0.5);
    var interpolateStart = d3.interpolate(d.startAngle, d.startAngle+0.5);
    return function(t) {
        d.endAngle = interpolateEnd(t);
        d.startAngle = interpolateStart(t);
        return progressArc(d);
    };
  });
}

// Wrapper calling function
function showProgress(){
    $('#chart').empty();
    initialize();
    interval = setInterval(function() {
        foreground.transition()
            .duration(90)
            .call(arcTweenProgress);
    }, 50);
}

// Wrapper function to stop the progress circle
function hideProgress(){
    clearInterval(interval);
    $('#chart').empty();
}
