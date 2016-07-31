// learnyounode exercise 13 of 13
// create an http server
// serve JSON data when it recieves a GET request to the path /api/parsetime
// requests will contain a query string with a key 'iso' and an ISO-format time
// eg: /api/parsetime?iso=2013-08-10T12:10:15.474Z 
// JSON should only contain 'hour', 'minute', 'second'

// Add second endpoint for the path /api/unixtime
// accepts the same query string but returns UNIX epock time in ms
// eg: { "unixtime": 1376136615474 } 

var http = require("http");
var url = require("url");
var json = require("JSON");

var server = http.createServer(function (request, response){
    var req_url = url.parse(request.url, true);
    
    response.writeHead(200, { 'Content-Type': 'application/json' })
    var url_query = req_url.search;
    var query_date = new Date(url_query.slice(5,url_query.length));

    if (req_url.pathname === '/api/parsetime') {
        var json_str = json.stringify({
            'hour':query_date.getHours(),
            'minute':query_date.getMinutes(), 
            'second':query_date.getSeconds(),
        });
        response.end( json_str );
    }

    if (req_url.pathname === '/api/unixtime') {
        var json_str = json.stringify({
            'unixtime':query_date.getTime()
        });
        response.end( json_str );
    }
    
   
    //req_stream.pipe(response);
});

//listen to the port number supplied

server.listen(process.argv[2]);