#include "mbed.h"
#include "MPL3115A2.h"
 
I2C i2c(p28, p27);       // sda, scl
 
// Comment out all of the references to 'pc' on this page if you don't have the 
// serial debug driver for your mbed board installed on your computer. If you do,
// I personally like to use Putty as the terminal window to capture debug messages.
RawSerial pc(USBTX, USBRX); // tx, rx
 
// Again, remove the '&pc' parameter is you're not debugging.
MPL3115A2 sensor(&i2c, &pc);
 
DigitalOut myled(LED1);     // Sanity check to make sure the program is working.
DigitalOut powerPin(p21);   // <-- I powered the sensor from a pin. You don't have to.
 
int main() {
    
    powerPin = 1;
    wait_ms(300);
 
    pc.printf("** MPL3115A2 SENSOR **\r\n");
    sensor.init();
 
    Altitude a;
    Temperature t;
    Pressure p;
    
    // Offsets for Dacula, GA
    sensor.setOffsetAltitude(83);
    sensor.setOffsetTemperature(20);
    sensor.setOffsetPressure(-32);
    
    while(1) 
    {
        sensor.readAltitude(&a);
        sensor.readTemperature(&t);
        
        sensor.setModeStandby();
        sensor.setModeBarometer();
        sensor.setModeActive();
        sensor.readPressure(&p);
        
        pc.printf("Altitude: %sft, Temp: %sdegF, Pressure: %sPa\r\n", a.print(), t.print(), p.print());
        
        sensor.setModeStandby();
        sensor.setModeAltimeter();
        sensor.setModeActive();
        
        wait(1.0);
    }
}