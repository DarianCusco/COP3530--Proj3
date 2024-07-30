
let colorCategories = ["blue", "green", "yellow", "orange", "red"]


document.getElementById('svgMap').addEventListener('load', function() {
    const svgDoc = this.contentDocument;
    if (svgDoc) {
        const alabama = svgDoc.querySelector('.al');
        if (alabama) {
            alabama.style.fill = 'blue';
        } else {
            console.log('The path element for Alabama is not found in the SVG');
        }
    } else {
        console.log('Failed to load the SVG document');
    }
});
