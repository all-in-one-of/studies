    
/* Filter files in a given dir by ext
var fs = require('fs');
var path = require('path');
module.exports = function(dir, ext, callback){
    
    fs.readdir(dir, function(err, list) {
        
        if (err) return callback(err);
            
        //filter data by ext    
        list = list.filter(function (file) {
            return path.extname(file) === "." + ext;
        });
        
        callback(null, list);
    });  
    
};
*/