#include <UM7.h>

//Connect the RX pin on the UM7 to TX2 (pin 16) on the DUE
//Connect the TX pin on the UM7 to RX2 (pin 17) on the DUE

UM7 imu;

//#define Quaternion true
#define ypr true

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(115200);  //I used TX2, RX2 since TX1 and RX1 do not work well
  #ifdef Quaternion
    Serial2.write('s');
    Serial2.write('n');
    Serial2.write('p');
    Serial2.write(0x08);
    Serial2.write();
    Serial2.write();
  #endif
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
