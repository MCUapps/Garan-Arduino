/*
  Garan_Audio_Test

  Simple test code to play with Garan Audio Module's commands.

  Email: fox@mcuapps.com
*/

#include <SoftwareSerial.h>

#if !defined(__MSP430_CPU__)
SoftwareSerial player(2, 3); // RX, TX
#else
SoftwareSerial player(P1_4, P1_5); // RX, TX
#endif

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

unsigned char commandBuff[13];

inline void buildCommand(unsigned char len, unsigned char cmd) {
  commandBuff[0] = len;
  commandBuff[1] = cmd;
}

unsigned char *singlePlay(unsigned int number) {
  buildCommand(0x04, 0x01);
  commandBuff[3] = number >> 8;
  commandBuff[4] = number;

  return commandBuff;
}

unsigned char *sequencePlay(unsigned int number) {
  buildCommand(0x04, 0x02);
  commandBuff[3] = number >> 8;
  commandBuff[4] = number;

  return commandBuff;
}

unsigned char *singleLoopPlay(unsigned int number) {
  buildCommand(0x04, 0x02);
  commandBuff[3] = number >> 8;
  commandBuff[4] = number;

  return commandBuff;
}

unsigned char *singlePlayName(String name) {
  name.toCharArray((char *)&commandBuff[3], name.length() + 1);
  buildCommand(name.length() + 2, 4);

  return commandBuff;
}

unsigned char *sequencePlayName(String name) {
  name.toCharArray((char *)&commandBuff[3], name.length() + 1);
  buildCommand(name.length() + 2, 5);

  return commandBuff;
}

unsigned char *singleLoopName(String name) {
  name.toCharArray((char *)&commandBuff[3], name.length() + 1);
  buildCommand(name.length() + 2, 6);

  return commandBuff;
}

unsigned char *setVolume(unsigned char volume) {
  buildCommand(0x03, 0x0D);
  commandBuff[3] = volume;

  return commandBuff;
}

void sendCommand(unsigned char command[]) {
  unsigned char checksum = 0;

  player.write(0x24);
  Serial.print(String(0x24, HEX) + ' ');

  for (unsigned int i = 0; i <= command[0]; i++) {
    player.write(command[i]);
    Serial.print(String(command[i], HEX) + ' ');
    checksum ^= command[i];
  }
  player.write(checksum);
  Serial.print(String(checksum, HEX) + '\n');
}

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600); 

#if !defined(__MSP430_CPU__)
  // wait for USB CDC serial port to connect.  Arduino Leonardo only
  while (!Serial) {
  }
#endif
  Serial.println("Console is ready!");
 
  player.begin(9600);

  // this byte must be 0
  commandBuff[2] = 0;
} 

void loop() {
  if (Serial.available()) {
    switch(Serial.read()) {
      case '1':
        sendCommand(singlePlay(1));
        break;
      case '2':
        sendCommand(singlePlay(2));
        break;
      case '3':
        sendCommand(singlePlay(3));
        break;
      case '4':
        sendCommand(singlePlayName("01.mp3"));
        break;
      case '5':
        sendCommand(sequencePlayName("01.mp3"));
        break;
      case '6':
        sendCommand(singleLoopName("01.mp3"));
        break;
      case '9':
        sendCommand(setVolume(15));
        break;
      case '0':
        sendCommand(setVolume(0));
        break;      
      case 'n':
        sendCommand((unsigned char *)NEXT);
        break;
      case 'l':
        sendCommand((unsigned char *)LAST);
        break;
      case 't':
        sendCommand((unsigned char *)GET_MUSIC_TOTALITY);
        break;
      case 'v':
        sendCommand((unsigned char *)GET_VERSION);
        break;
      case ']':
        sendCommand((unsigned char *)VOLUME_ADD);
        break;
      case '[':
        sendCommand((unsigned char *)VOLUME_SUBSTRACT);
        break; 
      default:
        Serial.println("This key maps to none.");     
    }
  }

  if (player.available()) {
    unsigned char recvByte = player.read();
    if (recvByte == 0x24) Serial.println();

    Serial.print(String(recvByte, HEX) + " ");
  }
}

