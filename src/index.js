// Referenced https://developer.mozilla.org/en-US/docs/Learn/JavaScript/Client-side_web_APIs/Manipulating_documents
//for assisting in DOM manipulation
(function() {
    function binsMap(svgFile) { //function that fills map using bins
        fetch('../data/ufo_sightings.JSON')  // Fetch JSON objects
            .then(response => response.json())
            .then(data => {
                let groupNum = 0; // Each number corresponds with a color
                if (svgFile) { // If file loads properly
                    for (let group in data) { // Gets group name (Ex. "Group 1")
                        const state = data[group];  // Gets states groups
                        state.forEach(stateInfo => {  // For each state in their groups
                            const lowerState = stateInfo.state.toLowerCase(); // Makes state abbreviations lowercase for svg file
                            let currState = svgFile.querySelector(`.${lowerState}`); // Selects state in map

                            if (lowerState === "dc") {
                                currState = svgFile.querySelector(`.dccircle`); // Edge case for DC
                            }

                            if (currState) {
                                currState.style.fill = `${colorCategories[groupNum]}`; // Fills state with designated color
                            } else {
                                console.log(`Could not load ${currState}`); // For testing purposes
                            }
                            const titleEl = currState.querySelector('title');
                            titleEl.textContent = `${stateInfo.state} ${stateInfo.count}`; // Adds title and count to map when hovering
                            groupCS = document.getElementById('colorwheel');
                        });
                        groupNum++;
                    }
                }
            });
    }

    document.getElementById('svgMap').addEventListener('load', function() { //Gets map for page
        const svgFile = this.contentDocument;
        if (svgFile) {
            binsMap(svgFile); //fills page on start

            // Event listener for the switch button
            switchButton.addEventListener("change", (event) => {
                if (!event.target.checked) { // If slider is unchecked
                    binsMap(svgFile);
                } else { //If slider is then checked
                }
            });
        }
    });
})();

//Stores diverging color scale
//Got values from https://bennettfeely.com/scales/
let colorCategories = ['#af0225', '#af0225', '#d31121', '#ec3023', '#fa5c2e', '#fd893c', '#feab4b', '#fec966', '#fee087', '#fff1a9']

for (let i = 1; i < colorCategories.length + 1; i++) {
    document.getElementById(`gr${i}`).style.backgroundColor = colorCategories[10 - i]; //sets table header to designated color
}

let switchButton = document.getElementById("switch-button");

function hashTableMap(svgFile) {
    // let AL = svgFile.getElementById(".al"); //selects state in map
    if (svgFile) {console.log("hello");}
    const AL = document.querySelector('.al');
    if (AL) {console.log("byeee")}
    AL.setAttribute('fill', 'red');
    AL.style.fill = "blue";
    console.log("in function");
}

function switchMaps(svgFile) {
    switchButton.addEventListener("change", (event) => {
        if (event.target.checked) { //If switch button is on 
            console.log("Button ON");
            hashTableMap(svgFile);
        }
    })
    
    console.log();
}
