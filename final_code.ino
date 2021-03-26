// Connect the port of the stepper motor driver
int outPorts[] = {14, 27, 26, 25};
#include <WiFi.h>
#include <HTTPClient.h>
#include <ESP32Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
Servo myservo; // create servo object to control a servo
int posVal = 0; // variable to store the servo position
int servoPin = 13; // Servo motor pin

#define SDA 33 //Define SDA pins
#define SCL 32

const char* ssid = "PollosHermanos";
const char* password = "*******";

String address= "http://165.227.76.232:3000/apg2165/running";



LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  Serial.begin(115200);

   WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
  
  Wire.begin(SDA, SCL); // attach the IIC pin
  lcd.init(); // LCD driver initialization
  lcd.backlight(); // Turn on the backlight
  lcd.setCursor(0,0); // Move the cursor to row 0, column 0
  lcd.print("Plane Start! "); // The print content is displayed on the LCD
  delay(2000);
  lcd.clear();
  myservo.setPeriodHertz(50); // standard 50 hz servo
  myservo.attach(servoPin, 500, 2500); // attaches the servo on servoPin to the servo
  // set pins to output
  for (int i = 0; i < 4; i++) {
  pinMode(outPorts[i], OUTPUT);
  }
}
void loop(){
    if((WiFi.status() == WL_CONNECTED)) {
    HTTPClient http;
    http.begin(address);
    Serial.println("Entered Loop");
    
    int httpCode = http.GET(); // start connection and send HTTP header
    if (httpCode == HTTP_CODE_OK) { 
        String response = http.getString();
        if (response.equals("false")) {
             delay(1000); 
        }
        else if(response.equals("true")) {
          runStory();
             
        }
        Serial.println("Response was: " + response);
    } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
    delay(500); // sleep for half of a second
  }



  

  

}


//These are part of the kinetic scultpure

void runStory() {
   lcd.setCursor(0,0); // Move the cursor to row 1, column 0
   lcd.print("Air Traffic Copy"); // The count is displayed every second
   delay(2000);
   lcd.clear();
   lcd.setCursor(0,0); // Move the cursor to row 1, column 0
   lcd.print("Pre-flight Test"); // The count is displayed every second
   delay(2000);
   lcd.clear();
   lcd.setCursor(0,0); // Move the cursor to row 1, column 0
   lcd.print("Throttle Test"); // The count is displayed every second
   delay(2000);
   lcd.clear();
   engineCheck();
   lcd.print("Looks Good"); // The count is displayed every second
   delay(2000);
   lcd.clear();
   lcd.print("Elevator Check"); // The count is displayed every second
   delay(2000);
   lcd.clear();
   elevatorCheck();
   lcd.print("Looks Good"); // The count is displayed every second
   delay(2000);
   lcd.clear();
   lcd.print("Take-Off Position"); // The count is displayed every second
   delay(2000);
   lcd.clear();
   takeOffMode();
   lcd.print("Full Throttle"); // The count is displayed every second
   delay(2000);
   lcd.clear();
   throttle();
   lcd.print("Lift-Off"); // The count is displayed every second
   delay(2000);
   lcd.clear();
   
}

void engineCheck() {
    // Rotate a full turn
  moveSteps(true, 32 * 64, 1);
  delay(1000);
  // Rotate a full turn towards another direction
  moveSteps(false, 32 * 64, 1);
  delay(1000);  
}

void elevatorCheck() {

  for ( int z = 0; z < 3; z++) {
        for (posVal = 20; posVal <= 110; posVal += 1) { // goes from 0 degrees to 180 degrees
          // in steps of 1 degree
          myservo.write(posVal); // tell servo to go to position in variable 'pos'
          delay(15); // waits 15ms for the servo to reach the position
          }
          for (posVal = 110; posVal >= 20; posVal -= 1) { // goes from 180 degrees to 0 degrees
          myservo.write(posVal); // tell servo to go to position in variable 'pos'
          delay(15); // waits 15ms for the servo to reach the position
          }
    
  }
  
  
}

void takeOffMode() {
  myservo.write(90); // tell servo to go to position in variable 'pos'
}

void throttle() {
    // Rotate a full turn
  moveAround(true, 4, 3);
  
}
//Suggestion: the motor turns precisely when the ms range is between 3 and 20
void moveSteps(bool dir, int steps, byte ms) {
for (unsigned long i = 0; i < steps; i++) {
moveOneStep(dir); // Rotate a step
delay(constrain(ms,3,20)); // Control the speed
}
}
void moveOneStep(bool dir) {
// Define a variable, use four low bit to indicate the state of port
static byte out = 0x01;
// Decide the shift direction according to the rotation direction
if (dir) { // ring shift left
  out != 0x08 ? out = out << 1 : out = 0x01;
} else { // ring shift right
  out != 0x01 ? out = out >> 1 : out = 0x08;
}
// Output singal to each port
  for (int i = 0; i < 4; i++) {
    digitalWrite(outPorts[i], (out & (0x01 << i)) ? HIGH : LOW);
  }
}
void moveAround(bool dir, int turns, byte ms){
  for(int i=0;i<turns;i++)
    moveSteps(dir,32*64,ms);
}
void moveAngle(bool dir, int angle, byte ms){
  moveSteps(dir,(angle*32*64/360),ms);
}
