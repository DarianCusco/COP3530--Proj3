//Used documentation from https://developer.mozilla.org/en-US/docs/Learn/JavaScript/Objects/JSON
(function() {
    fetch('../data/ufo_sightings.JSON')
    .then(response => response.json())
    .then(data => {
        // for (let groups in data) {
        //     console.log(groups);
        //     const temp = data[groups];
        //     temp.forEach(state => {
        //         console.log(state);
        //     })
        // }
        let groupNum = 0;
        document.getElementById('svgMap').addEventListener('load',function() {
            const svgFile = this.contentDocument;
            if (svgFile) { //if file loads properly
                for (let group in data) {
                    const state = data[group];
                    state.forEach(stateInfo => {
                        const lowerState = stateInfo.state.toLowerCase();
                        let currState = svgFile.querySelector(`.${lowerState}`);

                        if (lowerState === "dc") {currState = svgFile.querySelector(`.dccircle`);}

                        if (currState){
                            currState.style.fill = `${colorCategories[groupNum]}`;
                        }
                        else {
                            console.log(`Could not load ${currState}`);
                        }
                    })
                    groupNum++;
                }
            }
        })
    })
})()

//Stores diverging color scale
let colorCategories = ['#af0225', '#af0225', '#d31121', '#ec3023', '#fa5c2e', '#fd893c', '#feab4b', '#fec966', '#fee087', '#fff1a9']


