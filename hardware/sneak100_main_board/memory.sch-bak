EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 7 8
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Memory_EEPROM:CAT24C256 U10
U 1 1 6195A1D8
P 5650 3800
F 0 "U10" H 5950 4200 50  0000 C CNN
F 1 "CAT24C256" H 5950 4100 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 5650 3800 50  0001 C CNN
F 3 "https://www.onsemi.cn/PowerSolutions/document/CAT24C256-D.PDF" H 5650 3800 50  0001 C CNN
	1    5650 3800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0114
U 1 1 6195B7D4
P 5650 4100
F 0 "#PWR0114" H 5650 3850 50  0001 C CNN
F 1 "GND" H 5655 3927 50  0000 C CNN
F 2 "" H 5650 4100 50  0001 C CNN
F 3 "" H 5650 4100 50  0001 C CNN
	1    5650 4100
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0120
U 1 1 6195B94D
P 5650 3500
F 0 "#PWR0120" H 5650 3350 50  0001 C CNN
F 1 "+3.3V" H 5665 3673 50  0000 C CNN
F 2 "" H 5650 3500 50  0001 C CNN
F 3 "" H 5650 3500 50  0001 C CNN
	1    5650 3500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0121
U 1 1 6195C02D
P 5200 3950
F 0 "#PWR0121" H 5200 3700 50  0001 C CNN
F 1 "GND" H 5205 3777 50  0000 C CNN
F 2 "" H 5200 3950 50  0001 C CNN
F 3 "" H 5200 3950 50  0001 C CNN
	1    5200 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 3900 5200 3900
Wire Wire Line
	5200 3900 5200 3950
Wire Wire Line
	5250 3800 5200 3800
Wire Wire Line
	5200 3800 5200 3900
Connection ~ 5200 3900
Wire Wire Line
	5250 3700 5200 3700
Wire Wire Line
	5200 3700 5200 3800
Connection ~ 5200 3800
Text Notes 3250 4300 0    50   ~ 0
I2C slave address: 1010 (A2) (A1) (A0)\ncurrent address: 0b01010000 = 0x50\n0x50 lsh 1 = 0xA0
$Comp
L power:GND #PWR0122
U 1 1 6195DABA
P 6100 3950
F 0 "#PWR0122" H 6100 3700 50  0001 C CNN
F 1 "GND" H 6105 3777 50  0000 C CNN
F 2 "" H 6100 3950 50  0001 C CNN
F 3 "" H 6100 3950 50  0001 C CNN
	1    6100 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 3900 6100 3900
Wire Wire Line
	6100 3900 6100 3950
Text HLabel 6050 3800 2    50   Input ~ 0
SCL
Text HLabel 6050 3700 2    50   Input ~ 0
SDA
Text Notes 6350 4300 0    50   ~ 0
write protect:\nlow -> normal operation\nhigh -> memory protected against write operations
Text Notes 4900 2950 0    100  ~ 20
non-volatile memory
Text Notes 5300 3100 0    50   ~ 10
24C256 eeprom chip
$EndSCHEMATC
