#include <ros.h>
#include <std_msgs/Int8.h>
#include <Adafruit_NeoPixel.h>
 
// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            6
 
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      64


#define EMPTY 0 
#define RED 1 
#define GREEN 2
#define YELLOW 3


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


ros::NodeHandle  nh;

std_msgs::Int8 debug_message; 

void messageCb( const std_msgs::Int8& light_status){
  
  pixels.clear(); 
  for (int i = 0; i < NUMPIXELS; i++){
    switch (light_status.data){
      case EMPTY:
          break; 
      case RED:
          if ((i/8)%3 == 1) {
              pixels.setPixelColor(i, pixels.Color(1, 0, 0));}         
          break; 
      case YELLOW:  
          if (i%3 == 0) {
            pixels.setPixelColor(i, pixels.Color(1, 1, 0));     
          }
          break; 
      case GREEN:   
          if (i%5 == 0) {
            pixels.setPixelColor(i, pixels.Color(0, 1, 0));    
          } 
          break; }
    
    pixels.show(); }
}

ros::Subscriber<std_msgs::Int8> sub("/light_controller/light_state", &messageCb );

int delayval = 10; // delay for half a second
 
void setup()
{
  pixels.begin(); // This initializes the NeoPixel library.
  nh.initNode(); 
  nh.subscribe(sub); //the name of the topic from ros_light_controller
  //Serial.begin(9600);
}

void loop() {
  nh.spinOnce(); 
  delay(100);
}

 

/**
void setup(){
  pixels.begin(); 
}


void loop() {
 
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
 
  for(int i=0;i<NUMPIXELS;i++)
  {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(1,0,0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    //delay(delayval);
  }
  delay(1000);
  for(int i=0;i<NUMPIXELS;i++)
  {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,1,0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    //delay(delayval);
  }
  delay(1000);
  for(int i=0;i<NUMPIXELS;i++)
  {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,0,1)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    //delay(delayval);
  }
  delay(1000);
}
**/
