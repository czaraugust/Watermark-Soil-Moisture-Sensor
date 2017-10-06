#include <math.h>       // Conversion equation from resistance to %
#include<OneWire.h>

// Setting up format for reading 3 soil sensors
#define NUM_READS 10    // Number of sensor reads for filtering

const int pinTemp1 = 2;

long buffer[NUM_READS];
int index;
const unsigned long tempo =600000; //10 minutos
/// @brief Structure to be used in percentage and resistance values matrix to be filtered (have to be in pairs)
typedef struct {
	int moisture; //!< Moisture
	long resistance; //!< Resistance
} values;

const long knownResistor = 4700;  // Constant value of known resistor in Ohms

int supplyVoltage;                // Measured supply voltage
int sensorVoltage;                // Measured sensor voltage

values valueOf[NUM_READS];        // Calculated moisture percentages and resistances to be sorted and filtered

int i;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(115200);

  //
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);


  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

    delay(500);
}

void loop()
{
	String s = "@";
  //Serial.print("TEMPERATURA: ");
  double temperature = getTemp(pinTemp1);

  //Serial.println(temperature);
	s += String(temperature);
	s+= "|";
  //Serial.println();
  ////////////SENSOR 1 ////////////

	measure(6,7,1);
	//Serial.print ("\t");
	//Serial.println (average());
	long read1 = average();

	measure(7,6,0);
	//Serial.print ("\t");
	//Serial.println (average());
	long read2= average();

	long sensor1 = (read1 + read2)/2;

	//Serial.print ("resistance1 bias =" );
	//Serial.println (read1-read2);
	//Serial.print ("sensor 1 bias compensated value = ");
	//Serial.println (sensor1);
  //Serial.print("PRESSÃO 1: ");

  //Serial.println(getPressao(sensor1, temperature));
	s += String(getPressao(sensor1, temperature));
	s += "|";
  delay(500);


  ////////////SENSOR 2/ ///////////

  measure(9,8,4);   //9,8,4
  //Serial.print ("\t");
  //Serial.println (average());
  long read3 = average();

  measure(8,9,3);   //8,9,3
  //Serial.print ("\t");
  //Serial.println (average());
  long read4 = average();

  long sensor2 = (read3 + read4)/2;

  //Serial.print ("resistance2 bias =" );
  //Serial.println (read3-read4);
  //Serial.print ("sensor 2 bias compensated value = ");
  //Serial.println (sensor2);
  //Serial.print("PRESSÃO 2: ");
  //Serial.println(getPressao(sensor2, temperature));
	s += String(getPressao(sensor2, temperature));
	Serial.println(s);
  //Serial.println();



  delay(tempo);


}

double getPressao (double resistencia, double temperatura){
double pressao =0;
resistencia = resistencia/1000;

  if(resistencia <= 1)
    {
      pressao = -20*(resistencia*(1+(0.018*(temperatura-24)))-0.55);
    }
  if (resistencia >1 && resistencia <=8)
    {
      pressao = ((-3.213*resistencia)-4.093)/(1-(0.009733)-(0.01205*temperatura));
    }
  if (resistencia >8)
    {
      pressao= -2.246 - (5.239*resistencia*(1+(0.018*(temperatura-24))))-0.06756*pow(resistencia,2)*pow(1+(0.018*(temperatura-24)),2);

    }
    return pressao;

}

void measure (int phase_b, int phase_a, int analog_input)
{
	// read sensor, filter, and calculate resistance value
	// Noise filter: median filter

	for (i=0; i<NUM_READS; i++) {

		// Read 1 pair of voltage values
		digitalWrite(phase_a, HIGH);                 // set the voltage supply on
		delayMicroseconds(25);
		supplyVoltage = analogRead(analog_input);   // read the supply voltage
		delayMicroseconds(25);
		digitalWrite(phase_a, LOW);                  // set the voltage supply off
		delay(1);

		digitalWrite(phase_b, HIGH);                 // set the voltage supply on
		delayMicroseconds(25);
		sensorVoltage = analogRead(analog_input);   // read the sensor voltage
		delayMicroseconds(25);
		digitalWrite(phase_b, LOW);                  // set the voltage supply off

		// Calculate resistance
		// the 0.5 add-term is used to round to the nearest integer
		// Tip: no need to transform 0-1023 voltage value to 0-5 range, due to following fraction
		long resistance = (knownResistor * (supplyVoltage - sensorVoltage ) / sensorVoltage) ;

		delay(1);
		addReading(resistance);
		//Serial.print (resistance);
		//Serial.print ("\t");
	}
}



// Averaging algorithm
void addReading(long resistance)
{
	buffer[index] = resistance;
	index++;
	if (index >= NUM_READS) {
		index = 0;
	}
}

long average()
{
	long sum = 0;
	for (int i = 0; i < NUM_READS; i++) {
		sum += buffer[i];
	}
	return (long)(sum / NUM_READS);
}

float getTemp(int sensor){
    OneWire ds(sensor);


    byte data[12];
    byte addr[8];

    if ( !ds.search(addr)) {
    //no more sensors on chain, reset search
    ds.reset_search();

    return -1000;
    }

    if ( OneWire::crc8( addr, 7) != addr[7]) {
    Serial.println("CRC is not valid!");
    return -1000;
    }

    if ( addr[0] != 0x10 && addr[0] != 0x28) {
    Serial.print("Device is not recognized");
    return -1000;
    }

    ds.reset();
    ds.select(addr);
    ds.write(0x44,1);

    byte present = ds.reset();
    ds.select(addr);
    ds.write(0xBE);


    for (int i = 0; i < 9; i++) {
    data[i] = ds.read();
    }

    ds.reset_search();

    byte MSB = data[1];
    byte LSB = data[0];

    float TRead = ((MSB << 8) | LSB);
    float Temperature = TRead / 16;

    return Temperature;

}
