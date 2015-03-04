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

// D3 will generate the colors for the nodes from a set of 20 colors
var color = d3.scale.category20b();

var totalSize = 0; 

// Setting start point in the center
var vis = d3.select("#chart").append("svg:svg")
    .attr("id", "mainsvg")
    .attr("width", width)
    .attr("height", height)
    .append("svg:g")
    .attr("id", "container")
    .attr("transform", "translate(" + width / 2 + "," + height / 2 + ")");

// The layout is a partitioned one to achieve the sunburst structure
var partition = d3.layout.partition()
    .size([2 * Math.PI, radius * radius])
    .value(function(d) {return d.size;});

// The arc for drawing the svg
var arc = d3.svg.arc()
    .startAngle(function(d) {return d.x;})
    .endAngle(function(d) {return d.x + d.dx;})
    .innerRadius(function(d) {return Math.sqrt(d.y);})
    .outerRadius(function(d) {return Math.sqrt(d.y + d.dy);});

// Calling the json function with the disk statistics
// Invoking from a JSON file
d3.json("./data.json", function(error, root) {
    visualize(root);
});

// The core visualization function
function visualize(root){
    clearHtml();
    initializeFilePathDisplay();
    //Bounding circle
    vis.append("svg:circle")
        .attr("r", radius)
        .style("opacity", 0);

    // Path building
    var path = vis.selectAll("path")
        .data(partition.nodes(root))
        .enter().append("svg:path")
        .attr("display", function(d) {return d.depth ? null : "none";})
        .attr("d", arc)
        .attr("fill-rule", "evenodd")
        .style("fill", function(d) {return color((d.children ? d : d.parent).name);})
        .style("opacity", 1)
        .on("mouseover", mouseover)
        .on("click", click)

    // Remove transparency if hovering out of the graph
    d3.select("#container").on("mouseleave", mouseleave);

    // Get total size of the tree = value of root node from partition
    totalSize = path.node().__data__.value;
}

function initializeFilePathDisplay() {
    // Add the svg area
    var trail = d3.select("#sequence").append("svg:svg")
        .attr("width", width)
        .attr("height", 50)
        .attr("id", "trail");

    // Add the label at the end, for the percentage
    trail.append("svg:text")
        .attr("id", "endlabel")
        .style("fill", "#000");
}

// Interactive: This will fade all elements except for the path leading to the node being hovered over
function mouseover(d){
    var readableMemory = convert(d.value);
    var percentage = (100 * d.value / totalSize).toPrecision(3);
    var percentageString = percentage + "%";
    if (percentage < 0.1) {
        percentageString = "< 0.1%";
    }

    d3.select("#size")
        .text(readableMemory);
    d3.select("#explanation")
        .style("visibility", "");

    var sequenceArray = getAncestors(d);
    updateFilePathDisplay(sequenceArray, percentageString);

    // Fade all parts
    d3.selectAll("path")
        .style("opacity", 0.3);

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
        .text(function(d) {return d.name;});

    // Set position for entering and updating nodes
    g.attr("transform", function(d, i) {
        return "translate(" + i * (fpd.width + fpd.spacing) + ", 0)";
    });

    // Remove exiting nodes
    g.exit().remove();

    // Update percentage at the end
    d3.select("#trail").select("#endlabel")
        .attr("x", (nodeArray.length + 0.5) * (fpd.width + fpd.spacing))
        .attr("y", fpd.height / 2)
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

// Interactive: When a node is clicked this will trigger
function click(d){
    //Create a backtraversal to get the name.
}

// Function to clear html
function clearHtml(){
    $('#container').empty();
}

// Readable memory display
function convert(bytes){
    var out;
    if(bytes <= 1024) out = bytes.toPrecision(3) + "B";
    else if (bytes <= 1024*1024) out = (bytes / 1024.0).toPrecision(3) + "KB";
    else if (bytes <= 1024*1024*1024) out = (bytes / (1024.0*1024.0)).toPrecision(3) + "MB";
    else out = (bytes / (1024.0*1024.0*1024.0)).toPrecision(3) + "GB";
    return out;
}
