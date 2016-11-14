var express = require('express');
var app = express();

var lightBulb = new Object();

app.use(express.static('public'));

app.post('/color/r/:rColor/g/:gColor/b/:bColor', function(req, res){
  var data = req.params;
  lightBulb.redColor = data.rColor;
  lightBulb.greenColor = data.gColor;
  lightBulb.blueColor = data.bColor;
  res.send('red: ' + data.rColor + ' green: ' + data.gColor + ' blue: ' + data.bColor);
});

app.get('/color', function(req, res){
  res.send(lightBulb);
});

/*
app.route('/book/:title')
  .get(function (req, res) {
    var data = req.params;
    res.send('Get book ' + data.title);
  })
  .post(function (req, res) {
    res.send('Add a book');
  })
  .put(function (req, res) {
    res.send('Update the book');
  })
*/

app.listen(9999, function () {
  console.log('Example app listening on port 9999!');
})
