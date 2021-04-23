// Project relevant to this script is available at:
// https://github.com/E1P3/MazeGame

#include <Arduino_LSM6DS3.h>

#define IR_LEFT 2
#define IR_RIGHT 3

float x, y, z;
float px, py, pz;
float angleX, angleY, angleZ;
float GyroErrorX;
float GyroErrorY;
float GyroErrorZ;
float elapsedTime, currentTime, previousTime;
float gyroOffset = 1.15;

int c;

void setup() {

  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);

  attachInterrupt(digitalPinToInterrupt(IR_LEFT), level, RISING); 
  attachInterrupt(digitalPinToInterrupt(IR_RIGHT), level, RISING);
  
  Serial.begin(9600);
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");

    while (1);
  }

  delay(500);
  computeError();
  
}

void loop() {
  

  if (IMU.gyroscopeAvailable()) {
    
    previousTime = currentTime;        // Previous time is stored before the actual time read
    currentTime = millis();            // Current time actual time read
    elapsedTime = (currentTime - previousTime) / 1000;
    
    IMU.readGyroscope(x, y, z);

    x = x + GyroErrorX;
    y = y + GyroErrorY;
    z = z + GyroErrorZ;

    angleX = angleX + x * elapsedTime * gyroOffset;
    angleY = angleY + y * elapsedTime * gyroOffset;
    angleZ = angleZ + z * elapsedTime * gyroOffset;

//    angleX = angleX + (px + (x - px)/2) * elapsedTime; 
//  angleY = angleY + (py + (y - py)/2) * elapsedTime; 
//  angleZ = angleZ + (pz + (z - pz)/2) * elapsedTime; 

    px = x;
    py = y;
    pz = z;

    Serial.print(angleX);
    Serial.print('/');
    Serial.print(angleY);
    Serial.print('/');
    Serial.println(angleZ);
    delay(50);
    
  }
}

void computeError(){
  
  noInterrupts();
  c = 0;
  // Read gyro values 200 times
  while (c < 200) {
    
    IMU.readGyroscope(x, y, z);
  
    // Sum all readings
    GyroErrorX = GyroErrorX - x;
    GyroErrorY = GyroErrorY - y;
    GyroErrorZ = GyroErrorZ - z;
    c++;
    delay(10);
  }
  //Divide the sum by 200 to get the error value
  GyroErrorX = GyroErrorX / 200;
  GyroErrorY = GyroErrorY / 200;
  GyroErrorZ = GyroErrorZ / 200;
  interrupts();

}

void level(){
  
  angleX = 0;
  angleY = 0;
  angleZ = 0;
}
