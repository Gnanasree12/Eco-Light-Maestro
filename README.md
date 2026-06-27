# 🌃 EcoLight Maestro – Time Intensity Adaptive Street Light Automation

An embedded systems project that automates street lighting based on **Real-Time Clock (RTC)** and **ambient light intensity (LDR)** using the **LPC2148 ARM7 Microcontroller**.

The system intelligently turns street lights ON only during nighttime and when the surrounding light intensity is low, thereby reducing unnecessary power consumption.

---

## 📌 Project Overview

EcoLight Maestro is an energy-efficient street lighting automation system developed using **Embedded C**. The project integrates multiple peripherals of the LPC2148 microcontroller, including:

* RTC (Real-Time Clock)
* ADC (Light Sensor Interface)
* LCD Display
* UART Communication
* Matrix Keypad
* External Interrupt (EINT0)

The system continuously monitors the current time and ambient light intensity to control street lights automatically.

---

## ✨ Features

* 🌙 Automatic street light control based on time and ambient light.
* ⏰ Real-Time Clock (RTC) based operation.
* 💡 LDR sensor for ambient light detection.
* 📟 16×2 LCD display for system status.
* ⌨️ Matrix keypad interface.
* 🔔 External Interrupt (EINT0) for RTC editing.
* 📡 UART0 serial monitoring.
* ⚡ Energy-efficient lighting automation.

---

## 🛠 Hardware Used

* LPC2148 ARM7 Microcontroller
* Light Dependent Resistor (LDR)
* 16×2 LCD Display
* Matrix Keypad
* LEDs (Street Lights)
* Push Button (External Interrupt)
* Power Supply

---

## 💻 Software Used

* Embedded C
* Keil µVision IDE
* Flash Magic
* Proteus Design Suite

---

## 📂 Project Structure

```
Eco-Light-Maestro/
│
├── Source Files
│   ├── main.c
│   ├── adc.c
│   ├── LCD.c
│   ├── delay.c
│   ├── kpm.c
│   ├── eint0.c
│   └── pin_connect_block.c
│
├── Header Files
│   ├── adc.h
│   ├── LCD.h
│   ├── delay.h
│   ├── kpm.h
│   ├── defines.h
│   └── ...
│
├── Documents
│   └── Project Report.pdf
│
├── Images
│   ├── Block_Diagram.png
│   ├── Circuit_Diagram.png
│   ├── Hardware_Setup.jpg
│   └── LCD_Output.jpg
│
└── README.md
```

---

## ⚙️ Working Principle

1. Initialize LCD, RTC, ADC, UART, Keypad, and GPIO.
2. Read current time from RTC.
3. Check whether the current time is between **6:00 PM and 6:00 AM**.
4. If it is nighttime:

   * Read LDR value using ADC.
   * Compare the ADC value with the threshold.
   * Turn ON street lights if the environment is dark.
5. Display system status on LCD.
6. Send monitoring information through UART.
7. Allow RTC modification using the keypad through an external interrupt.

---


## 🚀 Future Enhancements

* IoT-based remote monitoring
* Wi-Fi / GSM connectivity
* Mobile application support
* Automatic brightness control using PWM
* Cloud-based energy monitoring
* Solar-powered street lighting

---

## 👨‍💻 Author

**Chirasani Gnana sree**

B.Tech – Electronics and Communication Engineering (ECE)

Interested in Embedded Systems, IoT, VLSI, and AI.

---

## 📄 License

This project is intended for educational and learning purposes.
