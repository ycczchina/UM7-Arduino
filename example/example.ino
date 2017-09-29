#include <UM7.h>

//Connect the RX pin on the UM7 to TX1 (pin 18) on the DUE
//Connect the TX pin on the UM7 to RX1 (pin 19) on the DUE

UM7 imu;

//#define Quaternion true
#define ypr true

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200);
  #ifdef Quaternion
    Serial2.write('s');
    Serial2.write('n');
    Serial2.write('p');
    Serial2.write(0x08);
    Serial2.write();
    Serial2.write();
  #endif
  byte tx_data[20];
  tx_data[0] = 's';
  tx_data[1] = 'n';
  tx_data[2] = 'p';
  tx_data[3] = 0x80;// Packet Type byte
  tx_data[4] = 0x08;// Address of GET_FW_REVISION register
  tx_data[5] = 0x01;// Checksum high byte
  tx_data[6] = 0xFB;// Checksum low byte
  for(int i = 0; i < 7; i++){
    Serial2.write(tx_data[i]);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial2.available() > 0) {
    if (imu.encode(Serial2.read())) { 
      #ifdef ypr
        // Reads byte from buffer. Valid packet returns true.
        //roll, pitch, yaw, roll_rate, pitch_rate, yaw_rate;
        //To get the actual value, divide by 91.02222.
        Serial.print("roll = ");
        Serial.println(imu.roll/91.02222);
        Serial.print("pitch = ");
        Serial.println(imu.pitch/91.02222);
        Serial.print("yaw = ");
        Serial.println(imu.yaw/91.02222);
      #endif

      #ifdef Quaternion
        //To get the actual value, divide by 29789.09091.
        Serial.print("Q.w = ");
        Serial.println(imu.QW/29789.09091);
        Serial.print("Q.x = ");
        Serial.println(imu.QX/29789.09091);
        Serial.print("Q.y = ");
        Serial.println(imu.QY/29789.09091);
        Serial.print("Q.z = ");
        Serial.println(imu.QZ/29789.09091);
        //Serial.print("roll rate = ");
        //Serial.println(imu.roll_rate);
        //Serial.print("pitche rate = ");
        //Serial.println(imu.pitch_rate);
        //Serial.print("yaw rate = ");
        //Serial.println(imu.yaw_rate);
        #endif
    }
  }
}
