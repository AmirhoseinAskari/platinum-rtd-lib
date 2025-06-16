# Platinum RTD Library

High-accuracy temperature-resistance conversion utilities for platinum RTD sensors in C/C++

## 🔧 Features

- Supports platinum RTD sensor types: `PT50`, `PT100`, `PT200`, `PT500`, `PT1000`  
- Convert resistance (Ω) ↔ temperature (°C) using the Callendar–Van Dusen equation  
- Iterative Newton–Raphson method for temperature calculation  
- Temperature range: **-200°C to +850°C**, compliant with IEC 60751 standard  
- Lightweight, portable C code  
- **Developed with consideration of MISRA-C guidelines** for safety-critical and embedded systems  

## 🧪 API Reference

### `double RTD_CalculateResistance(uint16_t sensor_type, double temperature)`

Converts temperature (in °C) to RTD resistance (in ohms).  
Returns the resistance, or `RTD_CONVERSION_FAILED` if the temperature is out of range.

### `double RTD_CalculateTemperature(uint16_t sensor_type, double resistance, double initial_temperature_estimate)`

Converts RTD resistance (in ohms) to temperature (in °C) using iterative approximation.  
Returns the temperature, or `RTD_CONVERSION_FAILED` if the resistance is out of range or iteration fails.

## 💡 Example
An example showing how to use the library is provided in [`example/main.c`](./example/main.c). 

## 📌 RTD Sensor Types

| Sensor Type | Macro          |
|-------------|----------------|
| PT50        | `RTD_SENSOR_PT50`   |
| PT100       | `RTD_SENSOR_PT100`  |
| PT200       | `RTD_SENSOR_PT200`  |
| PT500       | `RTD_SENSOR_PT500`  |
| PT1000      | `RTD_SENSOR_PT1000` |

## 📜 License

This project is licensed under the [MIT License](./LICENSE).

## 👤 Author

**Amirhossein Askari**  
📧 theamiraskarii@gmail.com  
🔗 [GitHub Profile](https://github.com/AmirhoseinAskari)
