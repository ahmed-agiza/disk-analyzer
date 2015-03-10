// Sunburst dimentions: Depends on the QtWebView
var width = 750;
var height = 600;
var radius = Math.min(width, height) / 2;

// File path graphically
var fpd = {
    width: 100,
    height: 30,
    spacing: 3,
    tail: 10
};

// Set in applySettings
var graphNavigation;
var color;
var opacity;
var readable;
var units;

// Global variables
var path;
var vis;
var totalSize = 0;

// The layout is a partitioned one to achieve the sunburst structure
var partition = d3.layout.partition()
    //.size([2 * Math.PI, radius * radius])
    .value(function(d) {return d.size;})
    .sort(function(a,b){
        if(a.hasOwnProperty("dummy")) return 1;
        else if(b.hasOwnProperty("dummy")) return -1;
        else return b.value < a.value ? -1 : b.value > a.value ? 1 : b.value >= a.value ? 0 : NaN;
});

// Scaling generators
var x = d3.scale.linear()
    .range([0, 2 * Math.PI]);

var y = d3.scale.sqrt()
    .range([0, radius]);

// The arc for drawing the svg (Interpolating ARC)
var arc = d3.svg.arc()
    .startAngle(function(d) { return Math.max(0, Math.min(2 * Math.PI, x(d.x))); })
    .endAngle(function(d) { return Math.max(0, Math.min(2 * Math.PI, x(d.x + d.dx))); })
    .innerRadius(function(d) { return Math.max(0, y(d.y)); })
    .outerRadius(function(d) { return Math.max(0, y(d.y + d.dy)); });

// The core visualization function
function visualize(root){
    hideProgress();
    initializeSunburst();
    applySettings();
    clearChart();
    initializeFilePathDisplay();

    //Bounding circle
    vis.append("svg:circle")
        .attr("r", radius)
        .style("opacity", 0);

    // Calculation optimization
    var nodes = partition.nodes(root)
        .filter(function(d) {
            return (d.dx > 0.005); // 0.005 radians = 0.29 degrees
        });

    // Path building
    path = vis.data([root]).selectAll("path")
        .data(nodes)
        .enter().append("svg:path")
        .filter(function(d){
            return (!d.hasOwnProperty("dummy"));
        })
        .attr("display", function(d) {
            if (!d.depth){
                d3.select("#root")
                    .text(d.name);
            }
            return true;
        })
        .attr("d", arc)
        .attr("fill-rule", "evenodd")
        .style("fill", function(d) {return color((d.children ? d : d.parent).name);})
        .style("opacity", 1)
        .on("mouseover", mouseover)
        .on("dblclick", dblclick)

    // Remove transparency if hovering out of the graph
    d3.select("#container").on("mouseleave", mouseleave);

    // Get total size of the tree = value of root node from partition
    totalSize = path.node().__data__.value;
}

function initializeSunburst(){
    // Setting start point in the center
    vis = d3.select("#chart").append("svg:svg")
        .attr("id", "mainsvg")
        .attr("width", width)
        .attr("height", height)
        .append("svg:g")
        .attr("id", "container")
        .attr("transform", "translate(" + width / 2 + "," + height / 2 + ")");
}

function initializeFilePathDisplay() {
    // Add the svg area
    var trail = d3.select("#sequence").append("svg:svg")
        .attr("width", width)
        .attr("height", 100)
        .attr("id", "trail");

    // Add the label at the end, for the percentage
    trail.append("svg:text")
        .attr("id", "endlabel")
        .style("fill", "#000");
}

// Interactive: This will fade all elements except for the path leading to the node being hovered over
function mouseover(d){
    var readableMemory = convert(d.value, units);
    var percentage = (100 * d.value / totalSize).toPrecision(3);
    var percentageString = percentage + "%";
    if (percentage < 0.1) {
        percentageString = "< 0.1%";
    }

    d3.select("#size")
        .text(readable ? readableMemory : d.value);
    d3.select("#explanation")
        .style("visibility", "");

    var sequenceArray = getAncestors(d);
    updateFilePathDisplay(sequenceArray, percentageString);

    // Fade all parts
    d3.selectAll("path")
        .style("opacity", opacity);

    // Then highlight only those that are an ancestor of the current segment
    vis.selectAll("path")
        .filter(function(node) {
            return (sequenceArray.indexOf(node) >= 0);
        })
        .style("opacity", 1);
}

// Gets the ancestors of the current node, where path is from highest to lowest
function getAncestors(node) {
    var path = [];
    var current = node;
    while (current.parent) {
        path.unshift(current);
        current = current.parent;
    }
    return path;
}

// Interactive: For fading effects
function mouseleave(d) {
    // Hide the filePathDisplay
    d3.select("#trail")
        .style("visibility", "hidden");

    // Deactivate all segments during transition
    d3.selectAll("path").on("mouseover", null);

    // Transition each segment to full opacity and then reactivate it
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

// Interactive: Dynamic update to the file path display
function updateFilePathDisplay(nodeArray, percentageString) {
    // Data join; key function combines name and depth (= position in sequence)
    var g = d3.select("#trail")
        .selectAll("g")
        .data(nodeArray, function(d) {return d.name + d.depth;});

    var entering = g.enter().append("svg:g");
    entering.append("svg:polygon")
        .attr("points", fpdPoints)
        .style("fill", function(d) {return color((d.children ? d : d.parent).name);});
    entering.append("svg:text")
        .attr("x", (fpd.width + fpd.tail) / 2)
        .attr("y", fpd.height / 2)
        .attr("dy", "0.35em")
        .attr("text-anchor", "middle")
        .text(function(d) {
            if (d.name.length <= 10)
                return d.name;
            else
                return d.name.substr(0, 10) + '..';
        });

    // Set position for entering and updating nodes
    g.attr("transform", function(d, i) {
        return "translate(" + (i%6) * (fpd.width + fpd.spacing) + ", " + Math.floor(i/6)*32 + ")";
    });

    // Remove exiting nodes
    g.exit().remove();

    // Update percentage at the end
    d3.select("#trail").select("#endlabel")
        .attr("x", ((nodeArray.length%6) + 0.5) * (fpd.width + fpd.spacing))
        .attr("y", (Math.floor(nodeArray.length/6)*32) + fpd.height / 2)
        .attr("dy", "0.35em")
        .attr("text-anchor", "middle")
        .text(percentageString);

    // Make the file path display visible if it is hidden
    d3.select("#trail")
        .style("visibility", "");
}

// Discription of file path entry as a set of points
function fpdPoints(d, i) {
    var points = [];
    points.push("0,0");
    points.push(fpd.width + ",0");
    points.push(fpd.width + fpd.tail + "," + (fpd.height / 2));
    points.push(fpd.width + "," + fpd.height);
    points.push("0," + fpd.height);
    if (i > 0) { // Don't include 6th vertex in the first entry
        points.push(fpd.tail + "," + (fpd.height / 2));
    }
    return points.join(" ");
}

// Interpolation to implement zooming
function arcTween(d) {
    var xd = d3.interpolate(x.domain(), [d.x, d.x + d.dx]),
        yd = d3.interpolate(y.domain(), [d.y, 1]),
        yr = d3.interpolate(y.range(), [d.y ? 20 : 0, radius]);
    return function(d, i) {
        return i
            ? function(t) { return arc(d); }
            : function(t) { x.domain(xd(t)); y.domain(yd(t)).range(yr(t)); return arc(d); };
    };
}

// Interactive: When a node is clicked this will trigger
function dblclick(d){
    if (!graphNavigation) return;

    d3.select("#root")
        .text(d.name);

    path.transition()
        .duration(750)
        .attrTween("d", arcTween(d));

    var p = getPath(d);
    mainWindow.navigateTo(p);
}

// Function to clear html
function clearChart(){
    $('#container').empty();

    x = d3.scale.linear()
        .range([0, 2 * Math.PI]);
    y = d3.scale.sqrt()
        .range([0, radius]);
}

// Get Readable path name to selected node
function getPath(node) {
    var path = '';
    var current = node;
    while (current.parent) {
        path = current.name + '/' + path;
        current = current.parent;
    }
    return path;
}

// Readable memory display
function convert(bytes, units){
    var out;
    if(bytes <= 1000) out = bytes.toPrecision(3) + (units ? "B": "");
    else if (bytes <= 1000*1000) out = (bytes / 1000.0).toPrecision(3) + (units ? "KB": "");
    else if (bytes <= 1000*1000*1000) out = (bytes / (1000.0*1000.0)).toPrecision(3) + (units ? "MB": "");
    else out = (bytes / (1000.0*1000.0*1000.0)).toPrecision(3) + (units ? "GB": "");
    return out;
}

// function to customize opacity, color, readable format, and units
function applySettings(op, clr, rd, un, gn){
    if (typeof op == "undefined") opacity = 0.3;
    else opacity = op;

    if (typeof clr == "undefined") color = d3.scale.category20b();
    else{
        switch(clr){
        case 1:
            color = d3.scale.category20b();
            break;
        case 2:
            color = d3.scale.category20();
            break;
        case 3:
            color = d3.scale.category20c();
            break;
        case 4:
            color = d3.scale.category10();
            break;
        }
    }

    if (typeof rd == "undefined") readable = true;
    else readable = rd;

    if (typeof un == "undefined") units = true;
    else units = un;

    if (typeof gn == "undefined") graphNavigation = true;
    else graphNavigation = gn;

}

// Calling the json function with the disk statistics (Calls json data from file)
// Invoking from a JSON file
/*d3.json("./data.json", function(error, root) {
    visualize(root);
});*/

// The arc for drawing the svg (OLD ARC)
/*var arc = d3.svg.arc()
    .startAngle(function(d) {return d.x;})
    .endAngle(function(d) {return (d.x + d.dx);})
    .innerRadius(function(d) {return Math.sqrt(d.y);})
    .outerRadius(function(d) {return Math.sqrt(d.y + d.dy);});*/
