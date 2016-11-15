var redSlider;
var greenSlider;
var blueSlider;
var redVal;
var greenVal;
var blueVal;
var button;
var lightBrightness;
var brightnessSlider;

function setup() {
  var canvas = createCanvas(400, 400);
  
  //sliders
  redSlider = createSlider(0, 255, 0);
  redSlider.position(10, 10);
  redSlider.style('width', '255px');
  
  greenSlider = createSlider(0, 255, 0);
  greenSlider.position(10, 60);
  greenSlider.style('width', '255px');
  
  blueSlider = createSlider(0, 255, 0);
  blueSlider.position(10, 110);
  blueSlider.style('width', '255px');
  
  brightnessSlider = createSlider(0, 255, 0);
  brightnessSlider.position(10, 260);
  brightnessSlider.style('width', '255px');
  
  //'submit' buttons
  button = createButton('Submit Color');
  button.position((width / 3), 160);
  button.mousePressed(sendAllData);
  
  button = createButton('Submit Brightness');
  button.position((width / 3), 310);
  button.mousePressed(sendAllData);
}

function draw() {
  // use RGB slider values to set background color
  redVal = redSlider.value();
  greenVal = greenSlider.value();
  blueVal = blueSlider.value();
  background(redVal, greenVal, blueVal);
  
  // slider labels and brightness slider value
  fill(100, 100, 100);
  textSize(32);
  text("R", 300, 30);
  text("G", 300, 80);
  text("B", 300, 130);
  text(brightnessSlider.value(), 300, 280);
}

function sendAllData() {
  var newReq = new XMLHttpRequest();
  newReq.open("POST", "http://job271.itp.io:9999/color/r/"+redVal+"/g/"+greenVal+"/b/"+blueVal+"/l/"+lightBrightness);
  newReq.send();
}
