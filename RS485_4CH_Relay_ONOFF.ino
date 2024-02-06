/* Arduino Control Modbus Relay 4 Ch Using MAX485 Module
 *  
 * [Arduino UNO] [MAX485 TTLtoRS485] [Relay 4Ch]  
 * Serial OUT    Rx(2번)---RO(=Tx)    VCC
 * HIGH(5V)        (13번)--RE           B
 * RE+DE합쳐서          + --DE           A
 * Serial IN     Tx(3번)---DI(=Rx)    GND
 * 
 * RS485모듈의 RO핀은 output으로 TTL통신에 TX핀에 해당된다.
 * RS485모듈의 DI핀은 input으로 TTL통신에 RX에 해당된다.
 * RS485모듈의 RE+DE핀은 통신방향을 제어(direction control)하는데
 * 전송시 HIGH로(Transmit), 수신시 LOW로(Receive) 설정하여 통신을 주고 받는 역할을 한다. 
 * digitalWrite(modbus_Control, HIGH); 송신모드
 * digitalWrite(modbus_Control, LOW);  수신모드
 */

#include <SoftwareSerial.h>

#define modbus_RX       2
#define modbus_TX       3
#define modbus_Control    13

SoftwareSerial RS485(modbus_RX, modbus_TX); // RX, TX

/*** Relay *********/
byte DeviceID = 0x01;

// Relay 1
byte ON_relay_1[8]  = {DeviceID, 0x05, 0x00, 0x00, 0xFF, 0x00, 0x8C, 0x3A};
byte OFF_relay_1[8] = {DeviceID, 0x05, 0x00, 0x00, 0x00, 0x00, 0xCD, 0xCA};
// Relay 2 
byte ON_relay_2[8]  = {DeviceID, 0x05, 0x00, 0x01, 0xFF, 0x00, 0xDD, 0xFA};
byte OFF_relay_2[8] = {DeviceID, 0x05, 0x00, 0x01, 0x00, 0x00, 0x9C, 0x0A};
// Relay 3 
byte ON_relay_3[8]  = {DeviceID, 0x05, 0x00, 0x02, 0xFF, 0x00, 0x2D, 0xFA};
byte OFF_relay_3[8] = {DeviceID, 0x05, 0x00, 0x02, 0x00, 0x00, 0x6C, 0x0A};
// Relay 4 
byte ON_relay_4[8]  = {DeviceID, 0x05, 0x00, 0x03, 0xFF, 0x00, 0x7C, 0x3A};
byte OFF_relay_4[8] = {DeviceID, 0x05, 0x00, 0x03, 0x00, 0x00, 0x3D, 0xCA};
// Relay ALL 
byte ON_relay_ALL[10]  = {DeviceID, 0x0F, 0x00, 0x00, 0x00, 0x08, 0x01, 0xFF, 0xBE, 0xD5};
byte OFF_relay_ALL[10] = {DeviceID, 0x0F, 0x00, 0x00, 0x00, 0x08, 0x01, 0x00, 0xFE, 0x95};

int interval = 1000;

void setup() {
  Serial.begin(9600); 
  RS485.begin(9600);
  pinMode(modbus_Control, OUTPUT);
}

void loop() {
  digitalWrite(modbus_Control, HIGH);
  
  RS485.write(ON_relay_1, 8); // Serial.write(buf, len) len: 배열에서 전송될 바이트 수
  RS485.flush();         // Serial.flush() 나가는 직렬 데이터의 전송이 완료될 때까지 기다림
  delay(interval);
  
  RS485.write(ON_relay_2, 8);
  RS485.flush();
  delay(interval);
  
  RS485.write(ON_relay_3, 8);
  RS485.flush();
  delay(interval);
  
  RS485.write(ON_relay_4, 8);
  RS485.flush();
  delay(interval);
  
  RS485.write(OFF_relay_1, 8);
  RS485.flush();
  delay(interval);
  
  RS485.write(OFF_relay_2, 8);
  RS485.flush();
  delay(interval);
  
  RS485.write(OFF_relay_3, 8);
  RS485.flush();
  delay(interval);
  
  RS485.write(OFF_relay_4, 8);
  RS485.flush();
  delay(interval);
  
  RS485.write(ON_relay_ALL, 10);
  RS485.flush();
  delay(interval);
  
  RS485.write(OFF_relay_ALL, 10);
  RS485.flush();
  delay(interval);

}
