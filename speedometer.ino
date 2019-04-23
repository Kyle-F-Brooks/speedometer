// this section adds the required libraries to the sketch
#include <SevSeg.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
// set recieve and transmit pins for GPS module
SoftwareSerial connection(10,11); //recieve-10 & transmit-11
// creates GPS object to handle the data from the gps module
TinyGPSPlus gps;
// creates two seperate 7-segment objects, one object handling the tens and the other handling the ones
// two are created as the SevSeg library is written to handle single or quad digit displays
SevSeg onesDisp;
SevSeg tensDisp;

void setup() {  
  // sets up both displays
  byte displayConfig = COMMON_CATHODE; // sets the display type to common cathode
  byte numDig = 1; // tells the sevseg object how many digits it will be handling
  byte digitPins[] = {}; // set to an empty array as the object only controls a single digit
  // pin number format {A, B, C, D, E, F, G, DP} each letter relates to the segment on the display
  byte onesPins[] = {3,2,9,8,7,6,5,4}; // pin numbers for ones display
  byte tensPins[] = {19,18,17,16,15,14,12,13}; // pin numbers for tens display
  bool resistorsOnSeg = true; // tells the sevseg object each segment has an independent resistor
  // use of the previously defined variables to give information regarding each sevseg object
  // some variables can be used for both objects as they do not vary between the two
  onesDisp.begin(displayConfig, numDig, digitPins, onesPins, resistorsOnSeg);
  tensDisp.begin(displayConfig, numDig, digitPins, tensPins, resistorsOnSeg);
  // creates a serial connection between the board and the computer(only valid when the board is connected to a PC)
  Serial.begin(9600);
  // creates a serial connection based on the software serial object
  // starts the connection between the board and the GPS module
  connection.begin(9600);
}

void loop() {
  while(connection.available()){
    gps.encode(connection.read()); // the data recieved over the serial connection is handled by the TinyGPS library
    break; // allows check each time data is sent, it was getting stuck in this loop
  }
  // loop checks if location is updated, if true then it changes the values on the display
  // if the speed doesn't change, there is no need to set the displays differently
  if(gps.location.isUpdated()){
    int travelRate = gps.speed.mph(); // prints the value to connected laptop, allows for debugging
    setDisp(travelRate); // passes the speed to the function setDisp
  }
}

void setDisp(int travelRate) {
  // using % 10 returns remainder of travelRate/10
  int ones = travelRate % 10;
  int tens = (travelRate/10) % 10;
  // sets the new values on the displays
  onesDisp.setNumber(ones);
  tensDisp.setNumber(tens);
  onesDisp.refreshDisplay();
  tensDisp.refreshDisplay();
}
