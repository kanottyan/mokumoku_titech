
/*  Pulse Sensor Amped 1.4    by Joel Murphy and Yury Gitman   http://www.pulsesensor.com

  ----------------------  Notes ----------------------  ----------------------
  This code:
  1) Blinks an LED to User's Live Heartbeat   PIN 13
  2) Fades an LED to User's Live HeartBeat
  3) Determines BPM
  4) Prints All of the Above to Serial

  Read Me:
  https://github.com/WorldFamousElectronics/PulseSensor_Amped_Arduino/blob/master/README.md
  ----------------------       ----------------------  ----------------------
*/

#include <Servo.h>
Servo myservo; //サーボ用のオブジェクトを作成
int angle; //サーボの角度を格納するための変数

//  Variables
int pulsePin = 0;                 // Pulse Sensor purple wire connected to analog pin 0
int blinkPin = 12;                // pin to blink led at each beat
int fadePin = 5;                  // pin to do fancy classy fading blink at each beat
int fadeRate = 0;                 // used to fade LED on with PWM on fadePin
int love_counter = 0;             // count dokidoki number aganist target girl

//pin variables for heart mark.
int ledPin1 = 6;
int ledPin2 = 2;
int ledPin3 = 4;
int ledPins[3] = { 6, 10, A3 };
int ledFadeRates[3];

// Volatile Variables, used in the interrupt service routine!
volatile int BPM;                   // int that holds raw Analog in 0. updated every 2mS
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded!
volatile boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat".
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.

// Regards Serial OutPut  -- Set This Up to your needs
static boolean serialVisual = false;   // Set to 'false' by Default.  Re-set to 'true' to see Arduino Serial Monitor ASCII Visual Pulse

//SerialはINPUTとOUTPUTのやり取り.引き数は一秒間の通信回数.
void setup() {
  pinMode(blinkPin, OUTPUT);        // pin that will blink to your heartbeat!
  pinMode(fadePin, OUTPUT);         // pin that will fade to your heartbeat!

  pinMode(ledPins[0], OUTPUT);
  pinMode(ledPins[1], OUTPUT);
  pinMode(ledPins[2], OUTPUT);
  Serial.begin(115200);             // we agree to talk fast!
  interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS
  // IF YOU ARE POWERING The Pulse Sensor AT VOLTAGE LESS THAN THE BOARD VOLTAGE,
  // UN-COMMENT THE NEXT LINE AND APPLY THAT VOLTAGE TO THE A-REF PIN
  //   analogReference(EXTERNAL);

  myservo.attach(9); //デジタル9番ピンをサーボの角度命令出力ピンとして設定
  angle = 80;
  myservo.write(angle);
  analogWrite(ledPins[0], 0);    // Blink LED, we got a beat.
  analogWrite(ledPins[1], 0);    // Blink LED, we got a beat.
  analogWrite(ledPins[2], 0);
  delay(5000);
}


//  Where the Magic Happens
void loop() {

  serialOutput() ;
  //  int filter_flag = 0;

  //  filter_flag = filter_noise();
  //check if there are noise when turn on switch
  //  sendDataToSerial('B', BPM);

  //  if ( filter_flag == 1 ) {

  if (QS == true) {  // A Heartbeat Was Found
    // BPM and IBI have been Determined
    // Quantified Self "QS" true when arduino finds a heartbeat
    //check dokidoki_value
    //remove noise
    //      if ( BPM > 50 && BPM < 140) {
    // if the girl is dokidoking, count up dokidoki_counter
    //        if (BPM > 100) {
    //          love_counter += 1;
    //        }
    //      }

    //sendDataToSerial('N', IBITotal);
    //if dokidoki counter become max, light up LED
    //      if (love_counter >= 5) {


    // Set 'fadeRate' Variable to 255 to fade LED with pulse
    serialOutputWhenBeatHappens();   // A Beat Happened, Output that to serial.
    QS = false;                      // reset the Quantified Self flag for next time

    //omatsu 2016.2.13 20:31
    if ( BPM > 50 && BPM < 160) {
      if (BPM > 100) {
        love_counter ++;
        digitalWrite(blinkPin, HIGH);    // Blink LED, we got a beat.
        fadeRate = 255;         // Makes the LED Fade Effect Happen
      } else {
        love_counter = 0;
      }

      if (love_counter >= 12) {
        angle = 0;
        myservo.write(angle);
      }
    } else if (BPM <= 50) {
      if (love_counter > 0) {
        love_counter -= 1;
      }
    }

  }



  ledFadeToBeat();                      // Makes the LED Fade Effect Happen
  delay(20);                             //  take a break
}

void ledFadeToBeat() {
  fadeRate -= 15;                         //  set LED fade value
  fadeRate = constrain(fadeRate, 0, 255); //  keep LED fade value from going into negative numbers!
  analogWrite(fadePin, fadeRate);         //  fade LED


  for (int i = 0; i < 3; i++) {
    ledFadeRates[i] -= 15;
    ledFadeRates[i] = constrain(ledFadeRates[i], 0, 255);
    analogWrite(ledPins[i], ledFadeRates[i]);
  }
}




