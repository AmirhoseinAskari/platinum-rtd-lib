/**
 * @file    platinum_rtd_sensor.c
 * @author  Amirhossein Askari
 * @version v1.0.0
 * @date    2025-05-13
 * @email   theamiraskarii@gmail.com
 * @see     https://github.com/AmirhoseinAskari
 * @brief   Conversion functions between temperature and resistance for platinum RTD sensors.
 * 
 * @details
 * This file implements conversion functions for platinum RTD sensors (e.g., PT50, PT100, PT200, PT500, PT1000),
 * using the Callendar–Van Dusen equation. It supports temperatures ranging from -200°C to +850°C.
 * These conversions are in accordance with the IEC 60751 standard where applicable.
 * 
 * @note
 * Ensure that the necessary RTD coefficients (e.g., @c RTD_A_COEFFICIENT) are defined before using these functions.
 * 
 * @warning
 * Ensure the sensor type and input values are valid before calling the functions.
 */


/* ------------------------------------- Includes ------------------------------------- */

#include "platinum_rtd_sensor.h"    ///< Header file for RTD sensor functions.



/* ------------------------------------- Functions ------------------------------------ */

/**
 * @brief Calculates RTD resistance from temperature.
 *
 * @details
 * Converts a temperature value (°C) to its corresponding resistance for a specified
 * RTD sensor type using the Callendar–Van Dusen equation.
 *
 * @param[in] sensor_type  The RTD sensor type. Supported values:
 *                         - @c RTD_SENSOR_PT50  
 *                         - @c RTD_SENSOR_PT100  
 *                         - @c RTD_SENSOR_PT200  
 *                         - @c RTD_SENSOR_PT500  
 *                         - @c RTD_SENSOR_PT1000
 * @param[in] temperature  Temperature in degrees Celsius. Must be in range -200°C to +850°C.
 *
 * @return Calculated resistance in ohms.
 *         Returns @c RTD_CONVERSION_FAILED if the input is invalid.
 *
 * @warning Ensure @p sensor_type is valid and @p temperature is within the supported range.
 */
double RTD_CalculateResistance(uint16_t sensor_type, double temperature)
{
    double resistance = RTD_CONVERSION_FAILED;      
    double temp_squared = 0.0, temp_cubed = 0.0;
    double resistance_at_zero = 0.0;
       
    if ( (temperature < -200.5) || (temperature > 850.5) )
    {
        resistance = RTD_CONVERSION_FAILED;
    }
    else
    {
        switch (sensor_type)
        {
            case RTD_SENSOR_PT50:
                resistance_at_zero = 50.0;
            break;
            case RTD_SENSOR_PT100:
                resistance_at_zero = 100.0;
            break;
            case RTD_SENSOR_PT200:
                resistance_at_zero = 200.0;
            break;
            case RTD_SENSOR_PT500:
                resistance_at_zero = 500.0;
            break;
            case RTD_SENSOR_PT1000:
                resistance_at_zero = 1000.0;
            break;
            default:      
                resistance = RTD_CONVERSION_FAILED;    
        }
        
        if (!resistance_at_zero)
        {
            resistance = RTD_CONVERSION_FAILED;
        }
        else
        {
            temp_squared = temperature * temperature;
            if (temperature >= 0.0)
            {
                resistance = resistance_at_zero * (1.0 + RTD_A_COEFFICIENT * temperature + RTD_B_COEFFICIENT * temp_squared);
            }
            else
            {
                temp_cubed = temp_squared * temperature;
                resistance = resistance_at_zero * (1.0 + RTD_A_COEFFICIENT * temperature + RTD_B_COEFFICIENT * temp_squared + RTD_C_COEFFICIENT * (temperature - 100.0) * temp_cubed);
            }
        }
    }
    return resistance;
}

/**
 * @brief Calculates RTD temperature from measured resistance.
 *
 * @details
 * Computes the temperature (°C) corresponding to a given RTD resistance value,
 * using the Newton–Raphson method to iteratively solve the Callendar–Van Dusen equation.
 *
 * @param[in] sensor_type  The RTD sensor type. Supported values:
 *                         - @c RTD_SENSOR_PT50  
 *                         - @c RTD_SENSOR_PT100  
 *                         - @c RTD_SENSOR_PT200  
 *                         - @c RTD_SENSOR_PT500  
 *                         - @c RTD_SENSOR_PT1000
 * @param[in] resistance   Measured resistance in ohms.
 * @param[in] initial_temperature_estimate  Initial temperature guess (in degrees Celsius).
 *
 * @return Calculated temperature in degrees Celsius.
 *         Returns @c RTD_CONVERSION_FAILED if the input is invalid or the iteration fails to converge.
 *
 * @note    Accuracy depends significantly on the quality of the initial temperature estimate.
 * @warning Ensure @p sensor_type is valid and @p resistance is within the supported range.
 */
double RTD_CalculateTemperature(uint16_t sensor_type, double resistance, double initial_temperature_estimate)
{
    const uint16_t max_iterations = 1000U;
    const double tolerance = 1e-8;
    uint16_t iteration = 0U;       
    double resistance_at_zero = 0.0;
    double temperature_estimate = initial_temperature_estimate, new_temperature_estimate = 0.0;   
    double function_value = 0.0, derivative_value = 0.0, temp_squared = 0.0, temp_cubed = 0.0;
    double temperature = 0.0;
    
    switch (sensor_type)
    {
        case RTD_SENSOR_PT50:
            resistance_at_zero = 50.0;
            if ( (resistance < 9.2) || (resistance > 195.3) )
            {
                temperature = RTD_CONVERSION_FAILED;
            }
        break;
        case RTD_SENSOR_PT100:
            resistance_at_zero = 100.0;
            if ( (resistance < 18.3) || (resistance > 390.6) )
            {
                temperature = RTD_CONVERSION_FAILED;
            }
        break;
        case RTD_SENSOR_PT200:
            resistance_at_zero = 200.0;
            if ( (resistance < 36.5) || (resistance > 781.3) )
            {
                temperature = RTD_CONVERSION_FAILED;
            }
        break;
        case RTD_SENSOR_PT500:
            resistance_at_zero = 500.0;
            if ( (resistance < 91.5) || (resistance > 1953.0) )
            {
                temperature = RTD_CONVERSION_FAILED;
            }
        break;
        case RTD_SENSOR_PT1000:
            resistance_at_zero = 1000.0;
            if ( (resistance < 182.5) || (resistance > 3906.5) )
            {
                temperature = RTD_CONVERSION_FAILED;
            }
        break;
        default:   
            temperature = RTD_CONVERSION_FAILED;    
    }
       
    if (!temperature)
    {       
        while (iteration < max_iterations)
        {
            if (temperature_estimate >= 0.0)
            {
                function_value = resistance_at_zero * (1.0 + RTD_A_COEFFICIENT * temperature_estimate + RTD_B_COEFFICIENT * temperature_estimate * temperature_estimate) - resistance;
                derivative_value = resistance_at_zero * (RTD_A_COEFFICIENT + 2.0 * RTD_B_COEFFICIENT * temperature_estimate);
            }
            else
            {
                temp_squared = temperature_estimate * temperature_estimate;
                temp_cubed = temp_squared * temperature_estimate;
                function_value = resistance_at_zero * (1.0 + RTD_A_COEFFICIENT * temperature_estimate + RTD_B_COEFFICIENT * temp_squared + RTD_C_COEFFICIENT * (temperature_estimate - 100.0) * temp_cubed) - resistance;
                derivative_value = resistance_at_zero * (RTD_A_COEFFICIENT + 2.0 * RTD_B_COEFFICIENT * temperature_estimate + 3.0 * RTD_C_COEFFICIENT * temp_squared - 200.0 * RTD_C_COEFFICIENT * temperature_estimate + 300.0 * RTD_C_COEFFICIENT * temp_squared);
            }

            new_temperature_estimate = temperature_estimate - (function_value / derivative_value);

            if (fabs(new_temperature_estimate - temperature_estimate) < tolerance)
            {
                temperature = new_temperature_estimate;
                break;
            }

            temperature_estimate = new_temperature_estimate;
            iteration++;
        }
    }
    
    return temperature;
}


/* platinum_rtd_sensor.c */
