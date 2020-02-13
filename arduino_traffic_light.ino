#include <ros.h>
#include <light_controller/light_command.h>
#include <Adafruit_NeoPixel.h>
 
// Which pin on the Arduino is connected to the NeoPixels?
#define PIN_1            6
#define PIN_2            5
 
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      64

Adafruit_NeoPixel pixels_1 = Adafruit_NeoPixel(NUMPIXELS, PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_2 = Adafruit_NeoPixel(NUMPIXELS, PIN_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel all_pixels[2] = {pixels_1, pixels_2}; 

ros::NodeHandle  nh;

void light_helper(uint8_t status, Adafruit_NeoPixel& pixels, const light_controller::light_command& command) {
  pixels.clear(); 
  for (int i = 0; i < NUMPIXELS; i++){
    switch (status){
      case command.EMPTY:
          break; 
      case command.RED:
          if ((i/8)%4 == 2) { //rows
              pixels.setPixelColor(i, pixels.Color(1, 0, 0));}         
          break; 
      case command.YELLOW:  
          if (i%4 == 0) { //columns
            pixels.setPixelColor(i, pixels.Color(1, 1, 0));     
          }
          break; 
      case command.GREEN:   
          if (i%5 == 0) { // no pattern 
            pixels.setPixelColor(i, pixels.Color(0, 1, 0));    
          } 
          break; }
  }
  pixels.show(); 
}

void messageCb( const light_controller::light_command& light_status){
  for (Adafruit_NeoPixel pixels : all_pixels) {
    light_helper(light_status.light1_status, pixels, light_status); 
    light_helper(light_status.light2_status, pixels, light_status); 
    }
  }

ros::Subscriber<light_controller::light_command> sub("/light_controller/light_state", &messageCb );

int delayval = 10; // delay for half a second
 
void setup()
{
  pixels_1.begin(); // This initializes the NeoPixel library.
  pixels_2.begin(); 
  nh.initNode(); 
  nh.subscribe(sub); //the name of the topic from ros_light_controller
}

void loop() {
  nh.spinOnce(); 
  delay(delayval);
}
