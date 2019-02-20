const express = require("express");
const bodyParser = require("body-parser");
const app = express();

let port = process.env.PORT;
if (port == null || port == "") {
  port = 8000;
}
let savedColor = '255,0,0'; //start red
let lastChanged = setTime(Date.now());
console.log(lastChanged);
function setTime(time) {
    const months = ["Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" ];
    const days = ["Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" ];
    const date = new Date(time);
    const clock =  date.toLocaleTimeString('it-IT');
    return days[date.getDay()] + ', ' + date.getDate() + ' ' + 
    months[date.getMonth()] + ' ' + date.getFullYear() + ' ' + 
    clock.slice(0, clock.length - 3) + ' GMT';
}
function getNumber (n) {
    switch(n) {
        case 'a' :
            return 10;
        case 'b' :
            return 11;
        case 'c' :
            return 12;
        case 'd' :
            return 13;
        case 'e' :
            return 14;
        case 'f' :
            return 15;
        default:
            return parseInt(n);
    }
}
function parseColor(color) {
    //takes out the hash tag of hexadecimal
    const noHash = color.slice(1, color.length);
    let newColor = '';
    if (noHash.length == 6) {
        //loops through set of each hexadecimal and turns it into decimals
        for (let i = 0; i < 6; i+=2) {
            let digit1 = getNumber(noHash.charAt(i));
            let digit2 = getNumber(noHash.charAt(i + 1));
            const product = (digit1 * 8) + digit2;
            newColor += product.toString();
            newColor += i != 4 ? ',' : '';
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
    lastChanged = setTime(Date.now());
    savedColor = parseColor(req.body);
    res.send(`You set color to rgb(${savedColor})`);
    res.end();
});
app.get("/getcolor", (req, res) => {
    res.set("Last-Modified", lastChanged);
    res.set("Content-Type", 'text/plain');
    console.log(savedColor);
    res.send(savedColor);
    res.end();
});
app.listen(port, () => {
    console.log("Server on port " + port);
})