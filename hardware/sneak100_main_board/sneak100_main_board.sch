EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 7
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 3150 3500 1300 2150
U 60E0491A
F0 "interface" 50
F1 "interface.sch" 50
F2 "BUTTON1" O R 4450 3600 50 
F3 "BUTTON2" O R 4450 3700 50 
F4 "LED1" I R 4450 3900 50 
F5 "LED2" I R 4450 4000 50 
F6 "LED3" I R 4450 4100 50 
F7 "USB_DP" B R 4450 5000 50 
F8 "USB_DM" B R 4450 4900 50 
F9 "BLUETOOTH_RX" I R 4450 4300 50 
F10 "BLUETOOTH_TX" O R 4450 4400 50 
F11 "I2C_SDA" B R 4450 4700 50 
F12 "I2C_SCL" B R 4450 4600 50 
F13 "MODULE_START" O R 4450 5400 50 
F14 "MODULE_KILL" O R 4450 5500 50 
F15 "RECEIVER_OUT" O R 4450 5200 50 
$EndSheet
$Sheet
S 6900 1900 1350 2000
U 60E0499A
F0 "motors" 50
F1 "motors.sch" 50
F2 "LF_IN1" I L 6900 2000 50 
F3 "LF_IN2" I L 6900 2100 50 
F4 "LF_A" O L 6900 2200 50 
F5 "LF_B" O L 6900 2300 50 
F6 "RF_IN1" I L 6900 2500 50 
F7 "RF_IN2" I L 6900 2600 50 
F8 "RF_A" O L 6900 2700 50 
F9 "RF_B" O L 6900 2800 50 
F10 "LB_IN1" I L 6900 3000 50 
F11 "LB_IN2" I L 6900 3100 50 
F12 "LB_A" O L 6900 3200 50 
F13 "LB_B" O L 6900 3300 50 
F14 "RB_IN1" I L 6900 3500 50 
F15 "RB_IN2" I L 6900 3600 50 
F16 "RB_A" O L 6900 3700 50 
F17 "RB_B" O L 6900 3800 50 
$EndSheet
$Sheet
S 3150 1900 1300 1100
U 60E04AFA
F0 "power" 50
F1 "power.sch" 50
F2 "BATTERY_SENSE" O R 4450 2450 50 
$EndSheet
$Sheet
S 6900 4200 1350 600 
U 60E049FE
F0 "proximitySensors" 50
F1 "proximitySensors.sch" 50
F2 "RX_READ" O L 6900 4700 50 
F3 "TX_ENABLE" I L 6900 4600 50 
F4 "ADD0" I L 6900 4300 50 
F5 "ADD1" I L 6900 4400 50 
F6 "ADD2" I L 6900 4500 50 
$EndSheet
$Sheet
S 6900 5150 1350 500 
U 60E04A74
F0 "lineSensors" 50
F1 "lineSennsors.sch" 50
F2 "READ_LL" O L 6900 5250 50 
F3 "READ_LM" O L 6900 5350 50 
F4 "READ_RM" O L 6900 5450 50 
F5 "READ_RR" O L 6900 5550 50 
$EndSheet
$Sheet
S 4900 1900 1500 3750
U 6100FE40
F0 "controller" 50
F1 "controller.sch" 50
F2 "RESET" I L 4900 3700 50 
F3 "RF_A" I R 6400 2700 50 
F4 "RF_B" I R 6400 2800 50 
F5 "USART2_TX" O L 4900 4300 50 
F6 "USART2_RX" I L 4900 4400 50 
F7 "LB_A" I R 6400 3200 50 
F8 "LB_B" I R 6400 3300 50 
F9 "I2C3_SCL" B L 4900 4600 50 
F10 "USB_DM" B L 4900 4900 50 
F11 "USB_DP" B L 4900 5000 50 
F12 "USER_LED1" O L 4900 3900 50 
F13 "LB_IN1" O R 6400 3000 50 
F14 "LB_IN2" O R 6400 3100 50 
F15 "PROXIMITY_ADD0" O R 6400 4300 50 
F16 "PROXIMITY_ADD1" O R 6400 4400 50 
F17 "PROXIMITY_ADD2" O R 6400 4500 50 
F18 "RB_A" I R 6400 3700 50 
F19 "RB_B" I R 6400 3800 50 
F20 "RB_IN1" O R 6400 3500 50 
F21 "RB_IN2" O R 6400 3600 50 
F22 "RF_IN1" O R 6400 2500 50 
F23 "RF_IN2" O R 6400 2600 50 
F24 "LF_IN1" O R 6400 2000 50 
F25 "LF_IN2" O R 6400 2100 50 
F26 "LINE_LL" I R 6400 5250 50 
F27 "LINE_LM" I R 6400 5350 50 
F28 "LINE_RM" I R 6400 5450 50 
F29 "LINE_RR" I R 6400 5550 50 
F30 "BATTERY_SENSE" I L 4900 2450 50 
F31 "PROXIMITY_RX_READ" I R 6400 4700 50 
F32 "LF_A" I R 6400 2200 50 
F33 "LF_B" I R 6400 2300 50 
F34 "PROXIMITY_TX_ENABLE" O R 6400 4600 50 
F35 "I2C3_SDA" B L 4900 4700 50 
F36 "USER_LED2" O L 4900 4000 50 
F37 "USER_LED3" O L 4900 4100 50 
F38 "USER_BUTTON" I L 4900 3600 50 
F39 "MODULE_START" I L 4900 5400 50 
F40 "MODULE_KILL" I L 4900 5500 50 
F41 "RECEIVER_OUT" I L 4900 5200 50 
$EndSheet
Wire Wire Line
	6400 2000 6900 2000
Wire Wire Line
	6400 2100 6900 2100
Wire Wire Line
	6400 2200 6900 2200
Wire Wire Line
	6400 2300 6900 2300
Wire Wire Line
	6400 2500 6900 2500
Wire Wire Line
	6400 2600 6900 2600
Wire Wire Line
	6400 2700 6900 2700
Wire Wire Line
	6400 2800 6900 2800
Wire Wire Line
	6400 3000 6900 3000
Wire Wire Line
	6400 3100 6900 3100
Wire Wire Line
	6400 3200 6900 3200
Wire Wire Line
	6400 3300 6900 3300
Wire Wire Line
	6400 3500 6900 3500
Wire Wire Line
	6400 3600 6900 3600
Wire Wire Line
	6400 3700 6900 3700
Wire Wire Line
	6400 3800 6900 3800
Wire Wire Line
	6400 4300 6900 4300
Wire Wire Line
	6400 4400 6900 4400
Wire Wire Line
	6400 4500 6900 4500
Wire Wire Line
	6400 4600 6900 4600
Wire Wire Line
	6400 4700 6900 4700
Wire Wire Line
	6400 5250 6900 5250
Wire Wire Line
	6400 5350 6900 5350
Wire Wire Line
	6400 5450 6900 5450
Wire Wire Line
	6400 5550 6900 5550
Wire Wire Line
	4450 3600 4900 3600
Wire Wire Line
	4450 3700 4900 3700
Wire Wire Line
	4450 3900 4900 3900
Wire Wire Line
	4450 4000 4900 4000
Wire Wire Line
	4450 4100 4900 4100
Wire Wire Line
	4900 4900 4450 4900
Wire Wire Line
	4900 5000 4450 5000
Wire Wire Line
	4900 4300 4450 4300
Wire Wire Line
	4900 4400 4450 4400
Wire Wire Line
	4900 4600 4450 4600
Wire Wire Line
	4900 4700 4450 4700
Wire Wire Line
	4450 5400 4900 5400
Wire Wire Line
	4450 5500 4900 5500
Wire Wire Line
	4450 5200 4900 5200
Wire Wire Line
	4450 2450 4900 2450
$EndSCHEMATC