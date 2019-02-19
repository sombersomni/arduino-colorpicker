const express = require("express");
const bodyParser = require("body-parser");
const app = express();

let port = process.env.PORT;
if (port == null || port == "") {
  port = 8000;
}
let savedColor = '255,0,0'; //start red

function parseColor(color) {
    const noHash = color.slice(1, color.length -1);
    let newColor = '';
    if (noHash.length == 6) {
        for (let i = 0; i < 6; i+=2) {
            let eachColor = noHash.slice(i, i + 2);
            eachColor += i != 4 ? ',' : '';
            newColor += eachColor;
        }
    }
    return newColor;
}
app.use(bodyParser.text());
app.use(express.static("public"));
app.get("/", (req, res) => {
    res.render("public");
});
app.post("/setcolor", (req, res) => {
    savedColor = parseColor(req.body);
    res.send(`Set color to rgb(${savedColor})`);
    res.end();
});
app.get("/getcolor", (req, res) => {
    res.send(savedColor);
    res.end();
});
app.listen(port, () => {
    console.log("Server on port " + port;
})