#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

int imu=0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

}

void loop() {
  mpu6050.update();
  imu=mpu6050.getRawAccX();
  Serial.print("RawX : ");
  Serial.print(imu);

  static float x_0 = 53.51; //Initial rawx value
  float x_1;//First rawx value
  float p_1;//First estimation error value
  static float p_0 = 100;// Estimation error initial value
  const float q = 7;//Noise constant
  const float r = 70;//Measurement error constant
  float k;//Kalman gain
  float x_est;//Updated rawx value
  float p_2;//Updated estimation error value

  x_1 = x_0;//Determining the initial value using the initial rawx value
  p_1 = p_0 + q;//Determining first estimation error value using initial estimation error and noise constant

  k = p_1/(p_1 + r);//Kalman gain calculation
  
  x_est = x_1 + k*(imu - x_1);//Updating rawx value and estimation error
  p_2 = (1-k)*p_1;

  Serial.print(" Est Rawx : ");
  Serial.print(x_2);

//Creating feedback
  x_0 = x_est;
  p_0 = p_2;

}
