
import GraphGenerator from './graphGenerator';
const jsonData= {GraphGenerator};
const jsonString = JSON.stringify(jsonData);


const fs = require('fs');
fs.writeFile("./foo.txt", jsonString, 'utf8', function (err) {
    if (err) {
        return console.log(err);
    }
    console.log("file saved!");
}); 