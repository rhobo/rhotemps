#include <dht.h>

dht DHT;

#define DHT11_PIN 2

void setup(){
  Serial.begin(38400,SERIAL_8E1);
  delay(1000);
  removeCursor();
  clearVFD(); // Clear text/chars, cursoer doesn't move.
  cursorReset();
  delay(100);
  Serial.write("Hello!              Grabbing temps&hum");
  delay(500);
  strobeVFDlol();
  strobeVFDlol();
  strobeVFDlol();
  strobeVFDlol();
  clearVFD();
  delay(100);
  cursorReset();
  Serial.print("Humidity: \t");
  Serial.write(0x0A);
  Serial.write(0x0D);
  Serial.print("Temperature: \t");
  lowestBright();
}

void loop(){
  // READ DATA
  //Serial.write("DHT11, \t");
  int chk = DHT.read11(DHT11_PIN);
  switch (chk)
  {
    case DHTLIB_OK:  
    //Serial.write("STATUS: OK \t"); 
    break;
    case DHTLIB_ERROR_CHECKSUM: 
    Serial.write("Checksum error,\t"); 
    break;
    case DHTLIB_ERROR_TIMEOUT: 
    Serial.write("Time out error,\t"); 
    break;
    default: 
    Serial.write("Unknown error,\t"); 
    break;
  }
  removeCursor();
  //clearVFD(); // Clear text/chars, cursoer doesn't move.
  cursorReset();
  delay(50);
  // DISPLAY DATA
  //Serial.print("Humidity:\t");
  Serial.write(0x1B);
  Serial.write(0x48);
  Serial.write(0x0C);
  Serial.print(DHT.humidity, 1);
  Serial.write(0x0A);
  Serial.write(0x0D);
  //
  Serial.write(0x1B);
  Serial.write(0x48);
  Serial.write(0x23);
  //Serial.print("Temperature:\t");
  Serial.println(Fahrenheit(DHT.temperature), 1);

  delay(950);
}

//Celsius to Fahrenheit conversion
double Fahrenheit(double celsius)
{
  return 1.8 * celsius + 32;
}

void strobeVFDlol(){
  lowestBright(); 
  delay(100);
  highestBright();
  delay(100);
}

//void testConvToHEX(){
//  String thisString = String("Hi I'm Poophead!", HEX);
//  return thisString;
//}

void lowestBright(){
  Serial.write(0x1B);// Escape char, required before control commands
  Serial.write(0x4C);// 'L' for luminance
  Serial.write(0x00);// 25% brightness  
}

void highestBright(){
  Serial.write(0x1B);
  Serial.write(0x4C);
  Serial.write(0xC0);// 100% brightness 
}

void removeCursor(){
  Serial.write(0x16); // Cursor not visibile.
}

void clearVFD(){
    Serial.write(0x0E); // Clear text chars, cursoer doesn't move.
}

void cursorReset(){
  Serial.write(0x0D);
  Serial.write(0x0C);
}

