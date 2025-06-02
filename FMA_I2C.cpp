/**
 * FMA_I2C.cpp
 * 
 * This file contains code for using FMA_I2C sensors with Arduino bootloader
 * 
 *
 * ## Revision History
 * - v0.1: Initial file.
 *
 * @author George Brayshaw
 * @date 30/05/2025
 * @version 0.1
 */
//--------------------------------------------------------------------------------------------------
// Libraries
//--------------------------------------------------------------------------------------------------

#include <Wire.h> // I2C library
#include "FMA_I2C.h"

//--------------------------------------------------------------------------------------------------
// Global variables and object definitions
//--------------------------------------------------------------------------------------------------
HoneyWellFMA_I2C::HoneyWellFMA_I2C() {
    // Constructor
}

// Definition of calibration value
uint16_t calibration_offset = 0;
// sensor properties
const float FULL_SCALE = 16384.0;    // 14-bit range
const float FORCE_RANGE = 5.0;     // Max measurable force in Newtons

// init : Initialisation

void HoneyWellFMA_I2C::init(int address, char transfer_function) {
    // Set the I2C address and transfer function
    i2c_address = address;
    transfer_function = transfer_function;

    Wire.begin(); // Initialize I2C communication
    delay(3) // need to wait for the 3ms
}

// read_sensor : Reads the values of the sensor

float HoneyWellFMA_I2C::read_sensor() {
    // Read I2C communications
    Wire.beginTransmission(i2c_address);
    Wire.write(0);
    Wire.endTransmission();

    Wire.requestFrom(i2c_address, 2); // read the two bits 

    float sensor_value = 0.0;

    // get all the data off the wire
    if (Wire.available() >= 2){
        // obtain

        char msb = Wire.read(); // receives a byte as character 
        char lsb = Wire.read();
        // a couple of options that could be going on here
        /*
            1. merge first then mask out the ms two bits
            2. merge first then shift right (i.e. control are lsb's)
            3. shift both right (i.e. control are lsb of each byte)
            4. mask out the ms of each bit then merge
        */
       // implementation of option 1
       value = msb << 8 | lsb;
       value = value && 0x3FFF;

       // allow for the calibration offset
       sensor_value = convert_force(value) - calibration_offset;

    } else {
        // An error has occured
        Serial.println("Number of bytes available " + Wire.available());
    }

    return sensor_value;
}

// calibrate_sensor : Calibrate the sensor 

void HoneyWellFMA_I2C::calibrate_sensor(int iterations) {

    // reset the calibration offset
    calibration_offset = 0;

    float total = 0;
    for(int i=0; i< iterations; i++){
        // read the value from the sensor
        float value = read_sensor();

        // check for overflow

        if (total > __FLT_MAX__ - value){ // if total + value > _FLT_MAX_ then an overflow as occurred 
            Serial.println("An overflow has occurred");
        } else{
            total += value;
        }
    }

    // average over the iterations to find the offset value

    calibration_offset = total / iterations;

}

// transfer_function_A : 60% of full scale (20-80% range)

float HoneyWellFMA_I2C::transfer_function_A(uint16_t raw_data) {
    const float scale_factor = 0.6 / FORCE_RANGE; // 60% of full scale divided by force range
    const float offset = 0.2;         // 20% of full scale as offset
    
  // Convert raw output to percentage of 2^14 counts
  float percentage = raw_data / FULL_SCALE;

  // Apply transfer function to calculate force
  float applied_force = (percentage - offset) / scale_factor;

  return applied_force;
}

// transfer_function_C : 80% of full scale (10-90% range)

float HoneyWellFMA_I2C::transfer_function_C(uint16_t raw_data) {
    const float scale_factor = 0.8 / FORCE_RANGE; // 80% of full scale divided by force range
    const float offset = 0.1;         // 20% of full scale as offset    

    // Convert raw output to percentage of 2^14 counts
    float percentage = raw_data / FULL_SCALE;

    // Apply transfer function to calculate force
    float applied_force = (percentage - offset) / scale_factor;

    return applied_force;
}