#include <ros.h>
#include <std_msgs/UInt16.h>
#include <Adafruit_NeoPixel.h>
 

//Adafruit_NeoPixel pixels_1 = Adafruit_NeoPixel(64, 2, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel pixels_2 = Adafruit_NeoPixel(64, 3, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel pixels_3 = Adafruit_NeoPixel(64, 5, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(64*4, 6, NEO_GRB + NEO_KHZ800);

ros::NodeHandle  nh;

const unsigned int red[4] PROGMEM = {33279, 45457, 46497, 65409}; 
const unsigned int yellow[4] PROGMEM = {33279, 40337, 43413, 65409};  
const unsigned int green[4] PROGMEM =  {33279, 35249, 38297, 65409}; 


void light_helper(int light_msg, int count) { 
  const unsigned int* light_pattern; 

  switch (light_msg) {
    case 1: 
      light_pattern = red; 
      break; 
    case 2: 
      light_pattern = yellow; 
      break; 
    case 3: 
      light_pattern = green;  
      break; 
    case 0: 
      return;  
  }

  unsigned int elt; 
  for (byte i = 0; i < 4; ++i) {
    elt = pgm_read_word_near(light_pattern + i); 
    while (elt > 0) {
      if (elt % 2) {
        switch (light_msg){
          case 1:
              pixels.setPixelColor(count, pixels.Color(1, 0, 0));        
              break; 
          case 2:  
              pixels.setPixelColor(count, pixels.Color(1, 1, 0));     
              break; 
          case 3:   
              pixels.setPixelColor(count, pixels.Color(0, 1, 0)); 
              break; 
        }
      }
      elt = (unsigned int) elt >> 1; 
      count++; 
    }
  }
  
}

void messageCb( const std_msgs::UInt16& light_status){
    pixels.clear();
    unsigned int received = light_status.data; 
    int next_status; 
    for (int i = 0; i < 4; i++) {
      next_status = received % 4; 
      light_helper(next_status, 64*i); 
      received = received >> 2; 
      }
    pixels.show(); 
  }

ros::Subscriber<std_msgs::UInt16> sub("/light_controller/light_state", &messageCb );

void setup()
{
  pixels.begin(); 
  nh.initNode(); 
  nh.subscribe(sub); //the name of the topic from ros_light_controller
}

void loop() {
  nh.spinOnce(); 
  delay(10);
}
