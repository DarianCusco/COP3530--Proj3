// Referenced https://developer.mozilla.org/en-US/docs/Learn/JavaScript/Client-side_web_APIs/Manipulating_documents
//for assisting in DOM manipulation


//Used documentation to help with JSON objects from https://developer.mozilla.org/en-US/docs/Learn/JavaScript/Objects/JSON
(function() {
    fetch('../data/ufo_sightings.JSON')  //Used to fetch JSON objects
    .then(response => response.json())
    .then(data => {
        let groupNum = 0; //Each number corresponds with a color
        document.getElementById('svgMap').addEventListener('load',function() {
            const svgFile = this.contentDocument;
            if (svgFile) { //if file loads properly
                for (let group in data) { //Gets group name (Ex. "Group 1")
                    const state = data[group];  //Gets states groups
                    state.forEach(stateInfo => {  //For each state in their groups
                        const lowerState = stateInfo.state.toLowerCase(); //Makes state abbreviations lowercase for svg file
                        let currState = svgFile.querySelector(`.${lowerState}`); //selects state in map

                        if (lowerState === "dc") {currState = svgFile.querySelector(`.dccircle`);} //Was having issues with dc so I added edge case

                        if (currState){
                            currState.style.fill = `${colorCategories[groupNum]}`; //Filles state with designated color
                        }
                        else {
                            console.log(`Could not load ${currState}`); //For testing purposes
                        }
                        const titleEl = currState.querySelector('title'); 
                        titleEl.textContent = `${stateInfo.state} ${stateInfo.count}`; //Adds title and count to map when hovering
                        groupCS = document.getElementById('colorwheel');

                    })
                    groupNum++;
                }
            }
        })
    })
})()

//Stores diverging color scale
//Got values from https://bennettfeely.com/scales/
let colorCategories = ['#af0225', '#af0225', '#d31121', '#ec3023', '#fa5c2e', '#fd893c', '#feab4b', '#fec966', '#fee087', '#fff1a9']

for (let i = 1; i < colorCategories.length + 1; i++) {
    document.getElementById(`gr${i}`).style.backgroundColor = colorCategories[10 - i]; //sets table header to designated color
}

