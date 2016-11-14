var redSlider;
var greenSlider;
var blueSlider;
var redVal;
var greenVal;
var blueVal;
var button;


function setup() {
  var canvas = createCanvas(400, 400);
  redSlider = createSlider(0, 255, 0);
  redSlider.position(10, 10);
  redSlider.style('width', '370px');
  redSlider.addClass('red');
  greenSlider = createSlider(0, 255, 0);
  greenSlider.position(10, 80);
  greenSlider.style('width', '370px');
  blueSlider = createSlider(0, 255, 0);
  blueSlider.position(10, 160);
  blueSlider.style('width', '370px');
  button = createButton('Submit Color');
  button.position(10, 240);
  button.mousePressed(sendHTTP);
}

function draw() {
  redVal = redSlider.value();
  greenVal = greenSlider.value();
  blueVal = blueSlider.value();
  background(redVal, greenVal, blueVal);
}

function sendHTTP(){
  var light = new XMLHttpRequest();
  light.open("POST", "http://job271.itp.io:9999/color/r/"+redVal+"/g/"+greenVal+"/b/"+blueVal);
  light.send();
}