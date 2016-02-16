
//////////
/////////  All Serial Handling Code,
/////////  It's Changeable with the 'serialVisual' variable
/////////  Set it to 'true' or 'false' when it's declared at start of code.
/////////

void serialOutput() {  // Decide How To Output Serial.
  if (serialVisual == true) {
    arduinoSerialMonitorVisual('-', Signal);   // goes to function that makes Serial Monitor Visualizer
  } else {
    //sendDataToSerial('S', Signal);     // goes to sendDataToSerial function
  }
}


//  Decides How To OutPut BPM and IBI Data
void serialOutputWhenBeatHappens() {
  if (serialVisual == true) {           //  Code to Make the Serial Monitor Visualizer Work
    Serial.print("*** Heart-Beat Happened *** ");  //ASCII Art Madness
    Serial.print("BPM: ");
    Serial.print(BPM);
    Serial.print("  ");
  } else {
    sendDataToSerial('B', BPM);  // send heart rate with a 'B' prefix
    sendDataToSerial('Q', IBI);  // send time between beats with a 'Q' prefix
  }
  sendDataToSerial('L', love_counter);

  //LED light feed for emit herat mark.
  if (love_counter < 7) {
    ledFadeRates[0] = 64;
    //    digitalWrite(ledPin1, HIGH);    // Blink LED, we got a beat.
    //    digitalWrite(ledPin2, LOW);    // Blink LED, we got a beat.
    //    digitalWrite(ledPin3, LOW);    // Blink LED, we got a beat.
  } else if (love_counter < 12) {
    ledFadeRates[0] = 64;
    ledFadeRates[1] = 128;
    //    digitalWrite(ledPin1, HIGH);    // Blink LED, we got a beat.
    //    digitalWrite(ledPin2, HIGH);    // Blink LED, we got a beat.
    //    digitalWrite(ledPin3, LOW);    // Blink LED, we got a beat.
  } else if (love_counter >= 12) {
    ledFadeRates[0] = 64;
    ledFadeRates[1] = 128;
    ledFadeRates[2] = 255;
    //    digitalWrite(ledPin1, HIGH);    // Blink LED, we got a beat.
    //    digitalWrite(ledPin2, HIGH);    // Blink LED, we got a beat.
    //    digitalWrite(ledPin3, HIGH);    // Blink LED, we got a beat.
  }



}



//  Sends Data to Pulse Sensor Processing App, Native Mac App, or Third-party Serial Readers.
void sendDataToSerial(char symbol, int data ) {
  Serial.print(symbol);

  Serial.println(data);
}


//  Code to Make the Serial Monitor Visualizer Work
void arduinoSerialMonitorVisual(char symbol, int data ) {
  const int sensorMin = 0;      // sensor minimum, discovered through experiment
  const int sensorMax = 1024;    // sensor maximum, discovered through experiment

  int sensorReading = data;
  // map the sensor range to a range of 12 options:
  int range = map(sensorReading, sensorMin, sensorMax, 0, 11);

  // do something different depending on the
  // range value:
  switch (range) {
    case 0:
      Serial.println("");     /////ASCII Art Madness
      break;
    case 1:
      Serial.println("---");
      break;
    case 2:
      Serial.println("------");
      break;
    case 3:
      Serial.println("---------");
      break;
    case 4:
      Serial.println("------------");
      break;
    case 5:
      Serial.println("--------------|-");
      break;
    case 6:
      Serial.println("--------------|---");
      break;
    case 7:
      Serial.println("--------------|-------");
      break;
    case 8:
      Serial.println("--------------|----------");
      break;
    case 9:
      Serial.println("--------------|----------------");
      break;
    case 10:
      Serial.println("--------------|-------------------");
      break;
    case 11:
      Serial.println("--------------|-----------------------");
      break;

  }
}


