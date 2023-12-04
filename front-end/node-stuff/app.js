const express = require("express") 
const cors = require('cors');
const { request } = require("http");
const fs = require('fs');

const app =express();


app.use(cors({
    origin: 'http://localhost:8001',
    credentials: true,
}));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));


app.get("/ficnames", (req,res)=>{
    res.json({
        fic1: "smth" 
    });
});

let name ="";
app.post('/ficnames', (req, res) => {
    const ficname =  req.body;
    name = JSON.stringify(ficname).slice(2, JSON.stringify(ficname).length-5);
    console.log(name);
    fs.writeFile("./fictitles.txt", name, 'utf8', function (err) {
    if (err) {
        return console.log(err);
    }
    console.log("file written :D!");
}); 
  });


app.listen(8001, ()=>console.log("Server is running"))