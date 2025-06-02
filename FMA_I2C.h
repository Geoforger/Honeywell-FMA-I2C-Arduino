/**
 * FMA_I2C.h
 * 
 * This header file contains code for using the FMAMSDXX005WC2C3 sensor with Arduino bootloader
 *
 *
 * ## Revision History
 * - v0.1: Initial file.
 *
 * @author George Brayshaw
 * @date 30/05/2025
 * @version 0.1
 */
#ifndef __FMAMSDXX005WC2C3_H__
#define __FMAMSDXX005WC2C3_H__

//--------------------------------------------------------------------------------------------------
// Enumerations and Typedefs
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Object Declarations and object definitions
//--------------------------------------------------------------------------------------------------
class HoneyWellFMA_I2C 
{
  public:
    HoneyWellFMA_I2C();
    void init(int address, char transfer_function); // Set the I2C address and transfer function on init
    float read_sensor();
    void calibrate_sensor(int iterations); // Calibrate the sensor across a number of iterations

  private:
    float transfer_function_A(uint16_t raw_data); // Transfer function A: 60% of full scale (20-80% range)
    float transfer_function_C(uint16_t raw_data); // Transfer function B: 80% of full scale (10-90% range)

    float calibration_offset = 0.0; // Calibration offset for the sensor
    uint16_t raw_force_data = 0;

    const float output_max = 13107; // %80 of 14 bit data.
    const float output_min = 3276;  // %20 of 14 bit data.
    char transfer_function; // Transfer function to use (A or C)
    int i2c_address; // I2C address of the sensor
};

#endif