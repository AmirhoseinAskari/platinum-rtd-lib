/**
 * @file    platinum_rtd_sensor.h
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


#ifndef _PLATINUM_RTD_SENSOR_H
#define _PLATINUM_RTD_SENSOR_H

#ifdef __cplusplus
extern "C" {
#endif


/* ------------------------------------- Includes ------------------------------------- */

#include <math.h>      ///< Standard C math functions
#include <stdint.h>    ///< Fixed-width integer types


/* ------------------------------------- Defines -------------------------------------- */

/** @name Callendar–Van Dusen Coefficients
 *  @{
 */
#define  RTD_A_COEFFICIENT  3.908302087e-3      /**< A coefficient (for all temperatures) */
#define  RTD_B_COEFFICIENT  -5.775000000e-7     /**< B coefficient (for all temperatures) */
#define  RTD_C_COEFFICIENT  -4.183010000e-12    /**< C coefficient (used only for T< 0°C) */
/** @} */


/** @name RTD Sensor Types
 *  @{
 */
#define  RTD_SENSOR_PT50    50      /**< PT50 RTD sensor   */
#define  RTD_SENSOR_PT100   100     /**< PT100 RTD sensor  */
#define  RTD_SENSOR_PT200   200     /**< PT200 RTD sensor  */
#define  RTD_SENSOR_PT500   500     /**< PT500 RTD sensor  */
#define  RTD_SENSOR_PT1000  1000    /**< PT1000 RTD sensor */
/** @} */


/** @brief Return value indicating that the conversion has failed */
#define  RTD_CONVERSION_FAILED  -1.0e6    /**< Conversion failure return value */


/* ------------------------------------ Prototype ------------------------------------- */
      
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
double RTD_CalculateResistance(uint16_t sensor_type, double temperature);

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
double RTD_CalculateTemperature(uint16_t sensor_type, double resistance, double initial_temperature_estimate);


#ifdef __cplusplus
}
#endif


#endif  /* platinum_rtd_sensor.h */
