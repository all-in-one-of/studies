

/*
// append and count the number of chars streamed from http data response events
var http = require('http');
var url = process.argv[2];
var str_chars = '';
var num_chars = 0;

http.get(url, function(response){
    response.setEncoding('utf8');
    response.on("data", function (data) {
        str_chars += data;
        num_chars += data.length;
    });
    response.on("end", function (data) {
        console.log(num_chars);
        console.log(str_chars);
    });
    response.on("error", console.error);
}).on('error', console.error);

//Alternative method, using .pipe and the bl API
var http = require('http')  
var bl = require('bl')  

http.get(process.argv[2], function (response) {  
    response.pipe(bl(function (err, data) {  
        if (err)  return console.error(err)  
        data = data.toString()  
        console.log(data.length)  
        console.log(data)  
    }))    
})
*/

/*
//Use http get to stream response data to console log
var http = require('http');
var url = process.argv[2];
http.get(url, function(response){
    response.setEncoding('utf8');
    response.on("data", console.log);
    response.on("end", console.log);
    response.on("error", console.error);
}).on('error', console.error);
*/

/* 
// Use external Model to filter files in a given dir by ext
var filterFn = require('./mymodule');
filterFn(process.argv[2], process.argv[3], function(err, list){
   if (err) return console.error('There was an error: ', err);
   
   list.forEach(function(file) {
      console.log(file) 
   });
});
*/

/* 
// Filter files in a given dir by ext
var fs = require('fs');
var path = require('path');
var dir = process.argv[2]; 
var ext = '.'+process.argv[3]; 

fs.readdir(dir, function whenDoneReading(err, list) {
    if (err) return console.log(err);
    for(var i in list) {
        if (path.extname(list[i]) === ext)  console.log(list[i]);
    }
});
*/