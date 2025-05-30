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

void HoneyWellFMA_I2C::init(int address, char transfer_function) {
    // Set the I2C address and transfer function
    i2c_address = address;
    transfer_function = transfer_function;

    Wire.begin(); // Initialize I2C communication
}

float HoneyWellFMA_I2C::read_sensor() {

}

void HoneyWellFMA_I2C::calibrate_sensor(int iterations) {

}

float HoneyWellFMA_I2C::transfer_function_A(uint16_t raw_data) {
    
}

float HoneyWellFMA_I2C::transfer_function_C(uint16_t raw_data) {
    
}