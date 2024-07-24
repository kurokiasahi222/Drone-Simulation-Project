// Web Sockets API for communication with the backend
let api = new WSApi();
var trip = [];
var helicopterID = 1;

// This method is called when the document is loaded
$(document).ready(function () {
    // hide the popup
    $("#popup").hide();

    // register a mouse click event that adds circles on an image
    $("#map").click(function (e) {
        if (trip.length < 2) {
            var posX = e.pageX - $(this).offset().left;
            var posY = e.pageY - $(this).offset().top;
            console.log("x: " + posX + " y: " + posY + "");
            $("#map").append(
                '<circle cx="' +
                posX +
                '" cy="' +
                posY +
                '" r="10" stroke="green" stroke-width="4" fill="yellow" />',
            );
            $("#map").html($("#map").html());
            trip.push([posX, posY]);
        } else {
            $("#map").empty();
            $("#map").append(
                '<circle cx="' +
                trip[0][0] +
                '" cy="' +
                trip[0][1] +
                '" r="10" stroke="green" stroke-width="4" fill="yellow" />',
            );
            var posX = e.pageX - $(this).offset().left;
            var posY = e.pageY - $(this).offset().top;
            $("#map").append(
                '<circle cx="' +
                posX +
                '" cy="' +
                posY +
                '" r="10" stroke="green" stroke-width="4" fill="blue" />',
            );
            $("#map").html($("#map").html());
            trip.insert(1, [[posX, posY]]);
        }
    });
});

// Web sockets event callback
api.onmessage = function (msg, data) {
    // handles events
    if ("event" in data) {
        console.log(data);
        if (data.event == "TripScheduled") {
            $("#popup").show();
            $("#popup").fadeOut(3000);
        }
    }
};

// This function schedules a trip and sends the command to the web sockets api.
function schedule() {
    var errorDiv = document.getElementById("nameError");
    var searchStrat = document.getElementById("search-strategy").value;
    //var searchStrat = "beeline";
    errorDiv.innerHTML = "";
    var name = $("#name").val();
    if (name == "") {
        errorDiv.innerHTML +=
            '<p style="color: red">[!] Error, missing name...</p>';
    }
    if (trip.length < 2) {
        errorDiv.innerHTML +=
            '<p style="color: red">[!] Error, missing pickup and drop off location ...</p>';
    }
    if (name != "" && trip.length >= 2) {
        var start = [
            trip[0][0] / $("#map").width(),
            1.0,
            trip[0][1] / $("#map").height(),
        ];
        var end = [
            trip[trip.length - 1][0] / $("#map").width(),
            1.0,
            trip[trip.length - 1][1] / $("#map").height(),
        ];
        console.log(start);
        var scale = 0.705;
        var min = {
            x: -2030.950927734375,
            y: 220.99996948242188,
            z: -1184.1085205078125,
        };
        var max = {
            x: 2249.523193359375,
            y: 286.9197998046875,
            z: 1261.8768310546875,
        };

        api.sendCommand("CreateEntity", {
            type: "robot",
            name: name,
            mesh: "assets/model/robot.glb",
            position: [
                (min.x + (max.x - min.x) * start[0]) * scale,
                254.665 * start[1],
                (min.z + (max.z - min.z) * start[2]) * scale,
            ],
            scale: [0.25, 0.25, 0.25],
            direction: [1, 0, 0],
            speed: 30.0,
            radius: 1.0,
            rotation: [0, 0, 0, 0],
        });
        api.sendCommand("ScheduleTrip", {
            name: name,
            start: [trip[0][0], trip[0][1]],
            end: [
                (min.x + (max.x - min.x) * end[0]) * scale,
                254.665 * end[1],
                (min.z + (max.z - min.z) * end[2]) * scale,
            ],
            search: searchStrat,
        });
        var details = name + ": ";
        for (var i = 0; i < trip.length; i++) {
            if (i != 0) {
                details += " ---> ";
            }
            details +=
                "(" + trip[i][0].toFixed(1) + ", " + trip[i][1].toFixed(1) + ")";
        }
        $("#list").append("<p class='trip'>" + details + "</p>");

        // reset the trip
        trip = [];
        $("#map").html("");
        $("#name").val("");
    }
}
var humanID = 1;
function addHuman() {
    api.sendCommand("CreateEntity", {
        type: "human",
        name: "Human-" + humanID,
        mesh: "assets/model/human.glb",
        position: [700, 290, 400],
        scale: [0.005, 0.005, 0.005],
        rotation: [0, 0, 0, 0],
        direction: [1, 0, 0],
        speed: 10.0,
        radius: 1.0,
        start: 2.0,
        duration: 2.0,
        offset: [0, -0.5, 0],
    });
    humanID += 1;
}

// ----------------------------------------------------------------
// Modification for CSCI 3081 HW4 Spring 2023
// Export data to CSV file

function exportData() {
    var fileName = $("#fileName").val();
    if (fileName.endsWith(".csv") == false) {
        alert("Your file must end with: .csv");
        return;
    }
    if (fileName == "") {
        errorDiv.innerHTML +=
            '<p style="color: red">[!] Error, missing file name...</p>';
    }
    api.sendCommand("ExportCSV", { name: fileName });
    let success = document.getElementById("sucess-export");
    success.innerHTML = "Sucesss!!! Successfully exported data to " + fileName;
    setTimeout(() => {
        success.innerHTML = "";
    }, 8000);
}

// This is a function for creating drones and robots automatically
function startExperiment() {
    // return a random number between min and max
    let getRandomArbitrary = (min, max) => {
        return Math.random() * (max - min) + min;
    };
    numdrones = document.getElementById("num-drones").value;
    numrobots = document.getElementById("num-robots").value;
    let searchStrat = document.getElementById("search-strategy-experiment").value;
    console.log(numdrones);
    console.log(numrobots);
    console.log(searchStrat);
    if (numdrones == "" || numdrones == "" || searchStrat == "") {
        console.log("You are missing required fields!");
        alert("Please select all the required fields to start the experiment!");
        return;
    }
    let trip = [];
    console.log(trip);
    let scale = 0.705;
    let min = {
        x: -2030.950927734375,
        y: 220.99996948242188,
        z: -1184.1085205078125,
    };
    var max = {
        x: 2249.523193359375,
        y: 286.9197998046875,
        z: 1261.8768310546875,
    };
    if (numdrones > 0 && numrobots > 0 && searchStrat != "") {
        // creat robots
        for (let i = 0; i < numrobots; i++) {
            for (let i = 0; i < 2; i++) {
                let posX = getRandomArbitrary(0, 1000);
                let posY = getRandomArbitrary(0, 600);
                trip.push([posX, posY]);
            }
            let start = [
                trip[0][0] / $("#map").width(),
                1.0,
                trip[0][1] / $("#map").height(),
            ];
            let end = [
                trip[trip.length - 1][0] / $("#map").width(),
                1.0,
                trip[trip.length - 1][1] / $("#map").height(),
            ];
            console.log(start);
            api.sendCommand("CreateEntity", {
                type: "robot",
                name: "Robot-" + i,
                mesh: "assets/model/robot.glb",
                position: [
                    (min.x + (max.x - min.x) * start[0]) * scale,
                    254.665 * start[1],
                    (min.z + (max.z - min.z) * start[2]) * scale,
                ],
                scale: [0.25, 0.25, 0.25],
                direction: [1, 0, 0],
                speed: 30.0,
                radius: 1.0,
                rotation: [0, 0, 0, 0],
            });
            api.sendCommand("ScheduleTrip", {
                name: "Robot-" + i,
                start: [trip[0][0], trip[0][1]],
                end: [
                    (min.x + (max.x - min.x) * end[0]) * scale,
                    254.665 * end[1],
                    (min.z + (max.z - min.z) * end[2]) * scale,
                ],
                search: searchStrat,
            });
            trip = [];
        }
        // Create drones
        let addDrones = (droneID) => {
            api.sendCommand("CreateEntity", {
                type: "drone",
                name: "Drone-" + droneID,
                mesh: "assets/model/drone.glb",
                position: [498.292, 270, -228.623],
                scale: [0.1, 0.1, 0.1],
                rotation: [0, 0, 0, 0],
                direction: [1, 0, 0],
                speed: 30.0,
                radius: 1.0,
                start: 2.0,
                duration: 2.0,
                offset: [0, 0.6, 0],
            });
        };
        for (let i = 1; i < numdrones; i++) {
            addDrones(i);
        }
        let details = name + ": ";
        for (let i = 0; i < trip.length; i++) {
            if (i != 0) {
                details += " ---> ";
            }
            details +=
                "(" + trip[i][0].toFixed(1) + ", " + trip[i][1].toFixed(1) + ")";
        }
        $("#list").append("<p class='trip'>" + details + "</p>");
    }
}