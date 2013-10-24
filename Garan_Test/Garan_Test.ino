/*
  Garan_Audio_Test

  Simple test code to play with Garan Audio Module's commands.
  Tested on MSP430 Value Line G2 Launchpad with Energia using msp430g2552

  Email: fox@mcuapps.com
*/

// constants won't change. They're used here to 
// set pin numbers:
const int buttonPin = PUSH2;     // the number of the pushbutton pin

void waitButton() {
  delay(1000);
  while (digitalRead(buttonPin) == HIGH) {}
}

unsigned char commandBuffer[10];

const unsigned char SINGLE_PLAY[]        = {0x04, 0x01, 0x00, 0x00, 0x01};  // NH NL
const unsigned char SEQUENCE_PLAY[]      = {0x04, 0x02, 0x00, 0x00, 0x02};  // NH NL
const unsigned char SINGLE_LOOP_PLAY[]   = {0x04, 0x03, 0x00, 0x00, 0x02};  // NH NL
const unsigned char SINGLE_PLAY_NAME[]   = {0x07, 0x04, 0x00, 0x31, 0x2E, 0x4D, 0x50, 0x33};  // Name must <= 12
const unsigned char SEQUENCE_PLAY_NAME[] = {0x07, 0x05, 0x00, 0x31, 0x2E, 0x4D, 0x50, 0x33};  // Name must <= 12
const unsigned char SINGLE_LOOP_NAME[]   = {0x07, 0x06, 0x00, 0x31, 0x2E, 0x4D, 0x50, 0x33};  // Name must <= 12
const unsigned char STOP[]               = {0x02, 0x07, 0x00};
const unsigned char PAUSE_PLAY[]         = {0x02, 0x08, 0x00};
const unsigned char NEXT[]               = {0x02, 0x09, 0x00};
const unsigned char LAST[]               = {0x02, 0x0A, 0x00};
const unsigned char VOLUME_ADD[]         = {0x02, 0x0B, 0x00};
const unsigned char VOLUME_SUBSTRACT[]   = {0x02, 0x0C, 0x00};
const unsigned char SET_VOLUME[]         = {0x03, 0x0D, 0x00, 0x05};  // Value
const unsigned char EQ_CHANGE[]          = {0x02, 0x0E, 0x00};
const unsigned char SET_EQ[]             = {0x03, 0x0F, 0x00, 0x01};  // Value

const unsigned char STANDBY_MODE[]       = {0x02, 0x10, 0x00};

const unsigned char GET_PLAYING_NAME[]   = {0x02, 0x21, 0x01};
const unsigned char GET_MUSIC_TOTALITY[] = {0x02, 0x22, 0x01};
const unsigned char GET_PLAYING_ORDER[]  = {0x02, 0x23, 0x01};
const unsigned char GET_TIME[]           = {0x02, 0x25, 0x01};
const unsigned char FEEDBACK_AT_END[]    = {0x03, 0xA0, 0x01, 0x01};
const unsigned char NO_FEEDBACK_AT_END[] = {0x03, 0xA0, 0x01, 0x00};
const unsigned char GET_VERSION[]        = {0x02, 0x80, 0x01};

void sendCommand(unsigned char command[]) {
  unsigned char checksum = 0;

  Serial.write(0x24);

  for (unsigned int i = 0; i <= command[0]; i++) {
    Serial.write(command[i]);
    checksum ^= command[i];
  }

  Serial.write(checksum);
}

void setup() {
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);     

  //Initialize serial and wait for port to open:
  Serial.begin(9600); 
} 

void loop() {
  waitButton();
  sendCommand((unsigned char *)GET_VERSION);

  waitButton();
  sendCommand((unsigned char *)SINGLE_PLAY);

  // This loop loops forever and does nothing
  while(true) { 
    continue; 
  }
}

