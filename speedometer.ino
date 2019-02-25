// this section adds the required libraries to the sketch
#include <SevSeg.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
// set recieve and transmit pins for GPS module
SoftwareSerial connection(2,3); //recieve-2 & transmit-3
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
  byte onesPins[] = {19,18,17,16,15,14,13,12}; // pin numbers for ones display
  byte tensPins[] = {11,10,9,8,7,6,5,4}; // pin numbers for tens display
  bool resistorsOnSeg = true; // tells the sevseg object each segment has an independent resistor
  // use of the previously defined variables to give information regarding each sevseg object
  // some variables can be used for both objects as they do not vary between the two
  onesDisp.begin(displayConfig, numDig, digitPins, onesPins, resistorsOnSeg);
  tensDisp.begin(displayConfig, numDig, digitPins, tensPins, resistorsOnSeg);
  // creates a serial connection between the board and the computer
  Serial.begin(9600);
  // creates a serial connection based on the software serial object
  // starts the connection between the board and the GPS module
  connection.begin(9600);
}

void loop() {
  // 
  while(connection.available()){
    gps.encode(connection.read()); // the data recieved over the serial connection is handled by the TinyGPS library
  }
  if(gps.speed.isUpdated()){
    int travelRate = gps.speed.mph();
    Serial.println(travelRate);
    setDisp(round(travelRate));
  }
}

void setDisp(int travelRate) {
  int ones = travelRate % 10;
  int tens = (travelRate/10) % 10;
  onesDisp.setNumber(ones);
  tensDisp.setNumber(tens);
  onesDisp.refreshDisplay();
  tensDisp.refreshDisplay();
}
