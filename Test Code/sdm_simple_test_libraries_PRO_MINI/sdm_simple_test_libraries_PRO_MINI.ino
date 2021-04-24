//REMEMBER! uncomment #define USE_HARDWARESERIAL
//in SDM_Config_User.h file if you want to use hardware uart

// So in Matt Little Example:
// Using a DDM unit with 8 bits, EVEN parity and 1 stop bit.
// This means software serial does not work, as it does not do EVEN parity.
// Need to install SoftwareSerialParity library
// This is NOT well documented.
// Need to install library folder into your arduino code folder.
// I've had to make changes to SDM.h and SDM.cpp to work with SoftwareSerialParity
// Need to check these changes and include them in my file.

// Need to convert the device ID (which is in decimal) into Hex.
// For example: 21 decimal is 15 HEX. Must call 0x15 as the device ID.


#include "SoftwareSerialParity.h"
#include "SDM.h"                                                                //import SDM library

#if defined ( USE_HARDWARESERIAL )                                              //for HWSERIAL

#if defined ( ESP8266 )                                                         //for ESP8266
SDM sdm(Serial1, SDM_UART_BAUD, NOT_A_PIN, SERIAL_8N1);                                  //config SDM
#elif defined ( ESP32 )                                                         //for ESP32
SDM sdm(Serial1, SDM_UART_BAUD, NOT_A_PIN, SERIAL_8N1, SDM_RX_PIN, SDM_TX_PIN);          //config SDM
#else                                                                           //for AVR
SDM sdm(Serial1, SDM_UART_BAUD, NOT_A_PIN);                                              //config SDM on Serial1 (if available!)
#endif

#else                                                                           //for SWSERIAL

//#include <SoftwareSerial.h>                                                     //import SoftwareSerial library
//#include "SoftwareSerialParity.h"

#if defined ( ESP8266 ) || defined ( ESP32 )                                    //for ESP
SoftwareSerial swSerSDM;                                                        //config SoftwareSerial
SDM sdm(swSerSDM, SDM_UART_BAUD, NOT_A_PIN, SWSERIAL_8N1, SDM_RX_PIN, SDM_TX_PIN);       //config SDM
#else                                                                           //for AVR
//SoftwareSerial swSerSDM(SDM_RX_PIN, SDM_TX_PIN);                                //config SoftwareSerial
SoftwareSerialParity swSerSDM(SDM_RX_PIN, SDM_TX_PIN);

SDM sdm(swSerSDM, SDM_UART_BAUD, DERE_PIN);                                             //config SDM
#endif

#endif

void setup() {
  Serial.begin(57600);                                                         //initialize serial
  sdm.begin();                                                                  //initialize SDM communication
  Serial.print("Tx: ");
  Serial.print(SDM_TX_PIN);
  Serial.print(" Rx: ");
  Serial.print(SDM_RX_PIN);
  Serial.print(" DERE: ");
  Serial.print(DERE_PIN);
  Serial.print(" at Baud: ");
  Serial.print(SDM_UART_BAUD);
  Serial.print(" CPU: ");
  Serial.println(F_CPU);

}

void loop() {

  Serial.print("Voltage:   ");
  Serial.print(sdm.readVal(DDM_PHASE_1_VOLTAGE, 0x15), 2);                            //display voltage
  Serial.println("V");
  Serial.println(sdm.getErrCode(true));
//  delay(2000);
//  Serial.print("Current:   ");
//  Serial.print(sdm.readVal(DDM_PHASE_1_CURRENT, 0x15), 2);                            //display current
//  Serial.println("A");
//  Serial.println(sdm.getErrCode(true));
//  delay(200);
//  Serial.print("Power:     ");
//  Serial.print(sdm.readVal(DDM_PHASE_1_POWER, 0x15), 2);                              //display power
//  Serial.println("W");
//  Serial.println(sdm.getErrCode(true));
//  delay(200);
//  Serial.print("Frequency: ");
//  Serial.print(sdm.readVal(DDM_FREQUENCY, 0x15), 2);                                  //display frequency
//  Serial.println("Hz");
//  Serial.println(sdm.getErrCode(true));

  delay(1000);                                                                  //wait a while before next loop
}
