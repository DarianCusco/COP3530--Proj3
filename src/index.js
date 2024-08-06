// Referenced https://developer.mozilla.org/en-US/docs/Learn/JavaScript/Client-side_web_APIs/Manipulating_documents
//for assisting in DOM manipulation
(function() {
    function binsMap(svgFile) { //function that fills map using bins
        fetch('../data/ufo_sightings_Bins.JSON')  // Fetch JSON objects
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
    function hashMap(svgFile) {
        fetch('../data/ufo_sightings_Hash.JSON')
            .then(response => response.json())
            .then(data => {
                if (svgFile) {
                    const sortedData = [];
                    for (let group in data) { //sorts hash function JSON by occurances
                        data[group].forEach(stateInfo => {
                            sortedData.push({
                                state: stateInfo.state,
                                count: stateInfo.count
                            });
                        });
                    }

                    sortedData.sort((a, b) => b.count - a.count);

                    sortedData.forEach((State) => { //resets map to grey for fill
                        const lowerState = State.state.toLowerCase(); //makes state string lowercase
                        let currState = svgFile.querySelector(`.${lowerState}`)

                        if (lowerState === "dc") {
                            currState = svgFile.querySelector(`.dccircle`);
                        }

                        if (currState) {
                            currState.style.fill = "grey";
                        }
                    })
                    
                    let groupNum = 0;
                    sortedData.forEach((stateInfo, index) => {
                        setTimeout(() => {
                            const lowerState = stateInfo.state.toLowerCase();
                            let currState = svgFile.querySelector(`.${lowerState}`); //selects state from map file

                            if (lowerState === "dc") {
                                currState = svgFile.querySelector(`.dccircle`); //had problems selecting DC 
                            }

                            if (currState) {
                                currState.style.fill = hashColorCategories[groupNum]; //Sets color designated to hash table
                                const titleEl = currState.querySelector('title');
                                titleEl.textContent = `${stateInfo.state} ${stateInfo.count}`;
                            } else {
                                console.log(`Could not load ${currState}`);
                            }
                            groupNum++;
                        }, index * 200); // Change 200 to a different value to adjust the delay between fills
                    });
                }
            });
    }
    function resetTable(isVisible) {
        const colorWheel = document.getElementById('colorwheel');
        const colorWheelTitle = document.getElementById("colorwheel-title")
        if (isVisible) {
            colorWheel.style.display = 'flex'; // Show the table
            colorWheelTitle.style.color = "black"; //Shows table text

        } else {
            colorWheel.style.display = 'none'; // Hide the table
            colorWheelTitle.style.color = "white"; //Hides table text
        }
    }


    document.getElementById('svgMap').addEventListener('load', function() { //Gets map for page
        const svgFile = this.contentDocument;
        if (svgFile) {
            binsMap(svgFile); //fills page on start

            // Event listener for the switch button
            switchButton.addEventListener("change", (event) => {
                if (!event.target.checked) { // If slider is unchecked
                    resetTable(true);
                    binsMap(svgFile);
                } else { 
                    resetTable(false);
                    hashMap(svgFile);
                }
            });
        }
    });
})();

//Stores diverging color scale
//Got values from https://bennettfeely.com/scales/
let colorCategories = ['#af0225', '#af0225', '#d31121', '#ec3023', '#fa5c2e', '#fd893c', '#feab4b', '#fec966', '#fee087', '#fff1a9'];

//Got these values from https://leonardocolor.io/scales.html#
let hashColorCategories = ["#002f61", "#003165", "#013469", "#01366e", "#023972", 
    "#033b76", "#043e7b", "#044080", "#054384", "#054588", "#05478c", "#064a91", 
    "#064c94", "#064e98", "#06519c", "#0653a1", "#0655a5", "#0657aa", "#055aaf", 
    "#055cb3", "#055eb7", "#0460bb", "#0362bf", "#0265c4", "#0267c8", "#0069cc", 
    "#016bd0", "#0b6dd2", "#126fd4", "#1871d6", "#1d73d7", "#2275d9", "#2677db", 
    "#2a79dd", "#2e7bdf", "#327de1", "#357fe3", "#3981e5", "#3c83e7", "#3f85e9", 
    "#4287eb", "#4689ed", "#488bef", "#4b8df1", "#4e8ff2", "#5190f4", "#5492f6", 
    "#5794f8", "#5996fa", "#5c98fc", "#5f9afe"];

for (let i = 1; i < colorCategories.length + 1; i++) {
    document.getElementById(`gr${i}`).style.backgroundColor = colorCategories[10 - i]; //sets table header to designated color
}

let switchButton = document.getElementById("switch-button"); //switch button on top of map
