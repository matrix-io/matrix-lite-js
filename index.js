// note that the compiled addon is placed under following path
const matrix = require('./build/Release/addon');

// `Hello` function returns a string, so we have to console.log it!
//console.log(matrix.Hello());
matrix.Led({"red":1, "blue":1, "green": 0, "white": 0});

setTimeout(()=>{
  matrix.Led({"red":0, "blue":1, "green": 1, "white": 0});
},1000);