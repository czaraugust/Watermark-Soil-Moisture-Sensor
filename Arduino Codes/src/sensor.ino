// #include <math.h>
// #include<OneWire.h>
//
//
// //SENSORES DE TEMPERATURA
// const int pinTemp1 = 2;
//
//
// const int analogInPin1 = A0;  // Analog input pin that the gypsum sensor is attached to
// const int analogInPin2 = A1;  // Analog input pin that the gypsum sensor is attached to
// int sensorvalue3 = 0;        // value read from gypsum sensor
// int sensorvalue4 = 0;        // value read from sensor supply
// int unsigned long avsensorvalue3 = 0;
// int unsigned long avsensorvalue4 = 0;
// int sensorvoltage2 = 0;
// int supplyvoltage2 = 0;
// long resistorValue2 = 0;
//
//
// const int analogInPin3 = A3;
// const int analogInPin4 = A4;
// int sensorvalue1 = 0;        // value read from gypsum sensor
// int sensorvalue2 = 0;        // value read from sensor supply
// int unsigned long avsensorvalue1 = 0;
// int unsigned long avsensorvalue2 = 0;
// int sensorvoltage1 = 0;
// int supplyvoltage1 = 0;
// long resistorValue1 = 0;
//
// int NUM_READS = 10;
//
// double  resistencia1 = 0;
// double  resistencia2 = 0;
// double pressao =0;
//
// int B = 0;
// int unsigned long moisture_pct = 0;
//
//
// double teta =0;
// double tetar=0.200;
// double tetas = 0.581;
// double alfa = 0.484;
// double n =1.276;
// double m = 1 - (1/n);
//
// double getHumi(double resistencia, int sensor){
// double temp = getTemp(sensor);
// pressao = getPressao(resistencia, temp);
// teta = tetar + ((tetas-tetar)/pow(1+ pow(alfa*abs(pressao), n), m));
// double norm2 = (teta -tetar)/(tetas-tetar);
// return norm2;
//
// }
//
// void setup() {
//   // initialize serial communications at 9600 bps:
//   Serial.begin(9600);
//
//   //
//   pinMode(6, OUTPUT);
//   pinMode(7, OUTPUT);
//
//
//   pinMode(8, OUTPUT);
//   pinMode(9, OUTPUT);
//
//     delay(500);
// }
//
// void loop() {
//
// // read sensor, average, and calculate resistance value
//
//     // Noise filter
//   // averaging filter
//   avsensorvalue1 = 0;
//   avsensorvalue2 = 0;
//   avsensorvalue3 = 0;
//   avsensorvalue4 = 0;
//
// for (B=0; B< NUM_READS; B++) {
//
//  // Read input 1 values
//
//   digitalWrite(7, HIGH);   // set the voltage supply on
//   delay(10);
//   sensorvalue4 = analogRead(analogInPin1);
//   digitalWrite(7, LOW);    // set the voltage supply off
//
//    delay(10);
//
//    digitalWrite(6, HIGH);   // set the voltage supply on
//    delay(10);
//    sensorvalue3 = analogRead(analogInPin1);
//    digitalWrite(6, LOW);    // set the voltage supply off
//
//   avsensorvalue4 = avsensorvalue4 + sensorvalue4;
//   avsensorvalue3 = avsensorvalue3 + sensorvalue3;
//
//
//
//
//
//
//
//
//   digitalWrite(8, HIGH);   // set the voltage supply on
//   delay(10);
//   sensorvalue2 = analogRead(analogInPin3);
//   digitalWrite(8, LOW);
//
//   delay(10);
//
//   digitalWrite(9, HIGH);   // set the voltage supply on
//   delay(10);
//   sensorvalue1 = analogRead(analogInPin3);
//   digitalWrite(9, LOW);    // set the voltage supply off
//
//   avsensorvalue1 = avsensorvalue1 + sensorvalue1;
//   avsensorvalue2 = avsensorvalue2 + sensorvalue2;
//
//
//
//
//   }
//
//   avsensorvalue4 = avsensorvalue4 / NUM_READS;
//   avsensorvalue3 = avsensorvalue3 / NUM_READS;
//   avsensorvalue2 = avsensorvalue2 / NUM_READS;
//   avsensorvalue1 = avsensorvalue1 / NUM_READS;
//
//
//   float sensorvoltage1 = avsensorvalue1 * 4.88 / 1023.0;
//   float supplyvoltage1 = avsensorvalue2 * 4.88 / 1023.0;
//
//   float sensorvoltage2 = avsensorvalue3 * 4.88 / 1023.0;
//   float supplyvoltage2 = avsensorvalue4 * 4.88 / 1023.0;
//
//
//
//
//
//
//       resistorValue2 = (4655 / sensorvoltage2) * (supplyvoltage2 - sensorvoltage2);
//       resistencia2 = resistorValue2/1000.0000;
//
//
//       resistorValue1 = (4700 / sensorvoltage1) * (supplyvoltage1 - sensorvoltage1);
//       resistencia1 = resistorValue1/1000.0000;
//
//
//
// /*  double umidade1 = getHumi(resistencia2,pinTemp1);
//   int inteiroumi1 = umidade1;
//   int fracaoumi1 = (umidade1 - inteiroumi1)*100;
//   Serial.println(umidade1);
//   Serial.println("SENSOR 1");
//   imprimir (resistencia2, pinTemp1);
//
//   double umidade2 = getHumi(resistencia1,pinTemp1);
//   int inteiroumi2 = umidade2;
//   int fracaoumi2 = (umidade2 - inteiroumi2)*100;
//   Serial.println(" ");*/
//
//
//  Serial.print("PRESSAO 1: ");
//  Serial.print(getPressao(resistencia2, getTemp(pinTemp1)));
//   Serial.print(" PRESSAO 2: ");
//  Serial.print(getPressao(resistencia1, getTemp(pinTemp1)));
//
//
//
//   Serial.print(" TEMPRERATURA: ");
//  Serial.println(getTemp(pinTemp1));
// //  Serial.println("TEMPERATURA 2");
//  //Serial.println(getTemp(pinTemp1));
//
//
//
//
//   delay(3000);
//
// }
//
//  void imprimir (double resistencia, int sensor){
//     Serial.print("Resistencia = ");
//     Serial.println(resistencia,3);
//     double temp = getTemp(sensor);
//     Serial.print("Temperatura = ");
//     Serial.println(temp);
//     pressao = getPressao(resistencia, temp);
//     Serial.print("Pressao kPa = ");
//     Serial.println(pressao);
//     teta = tetar + ((tetas-tetar)/pow(1+ pow(alfa*abs(pressao), n), m));
//     Serial.print("Teta [0-1] = ");
//     Serial.println(teta);
//     double norm1 = pow(1+ pow(alfa*abs(pressao), n), -m);
//     double norm2 = (teta -tetar)/(tetas-tetar);
//     Serial.print("Normalizacao 1 [0-1] = ");
//     Serial.println(norm1);
//     Serial.print("Normalizacao 2 [0-1] = ");
//     Serial.println(norm2);
//     Serial.println("");
//     //CALIBRAGEM http://www.kimberly.uidaho.edu/water/swm/Calibration_Watermark2.htm
//
//
//   }
//
//
//
//
// double getPressao (double resistencia, double temperatura){
//
//   if(resistencia <= 1)
//     {
//       pressao = -20*(resistencia*(1+(0.018*(temperatura-24)))-0.55);
//     }
//   if (resistencia >1 && resistencia <=8)
//     {
//       pressao = ((-3.213*resistencia)-4.093)/(1-(0.009733)-(0.01205*temperatura));
//     }
//   if (resistencia >8)
//     {
//       pressao= -2.246 - (5.239*resistencia*(1+(0.018*(temperatura-24))))-0.06756*pow(resistencia,2)*pow(1+(0.018*(temperatura-24)),2);
//
//     }
//     return pressao;
//
//
// }
// float getTemp(int sensor){
// OneWire ds(sensor);
//
//
// byte data[12];
// byte addr[8];
//
// if ( !ds.search(addr)) {
// //no more sensors on chain, reset search
// ds.reset_search();
//
// return -1000;
// }
//
// if ( OneWire::crc8( addr, 7) != addr[7]) {
// Serial.println("CRC is not valid!");
// return -1000;
// }
//
// if ( addr[0] != 0x10 && addr[0] != 0x28) {
// Serial.print("Device is not recognized");
// return -1000;
// }
//
// ds.reset();
// ds.select(addr);
// ds.write(0x44,1);
//
// byte present = ds.reset();
// ds.select(addr);
// ds.write(0xBE);
//
//
// for (int i = 0; i < 9; i++) {
// data[i] = ds.read();
// }
//
// ds.reset_search();
//
// byte MSB = data[1];
// byte LSB = data[0];
//
// float TRead = ((MSB << 8) | LSB);
// float Temperature = TRead / 16;
//
// return Temperature;
//
// }
