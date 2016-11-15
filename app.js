var express = require('express');
var app = express();

var lightBulb = new Object();

app.use(express.static('public'));

app.post('/color/r/:rColor/g/:gColor/b/:bColor/l/:luminance', function(req, res){
  var data = req.params;
  lightBulb.redColor = data.rColor;
  lightBulb.greenColor = data.gColor;
  lightBulb.blueColor = data.bColor;
  lightBulb.luminance = data.luminance;
  res.send('red: ' + data.rColor + ' green: ' + data.gColor + ' blue: ' + data.bColor + ' luminance: ' + data.luminance);
});

app.get('/color', function(req, res){
  res.send(lightBulb);
});

app.listen(9999, function () {
  console.log('Example app listening on port 9999!');
})
