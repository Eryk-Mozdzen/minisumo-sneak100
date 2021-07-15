EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 7
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
L Sneak100_kicad:DRV8835 U1
U 1 1 60E779A3
P 3050 2450
F 0 "U1" H 3550 3000 50  0000 C CNN
F 1 "DRV8835" H 3550 2900 50  0000 C CNN
F 2 "Package_SON:WSON-12-1EP_3x2mm_P0.5mm_EP1x2.65_ThermalVias" H 2950 2900 50  0001 C CNN
F 3 "" H 2950 2900 50  0001 C CNN
	1    3050 2450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR014
U 1 1 60E79628
P 3000 3200
F 0 "#PWR014" H 3000 2950 50  0001 C CNN
F 1 "GND" H 3005 3027 50  0000 C CNN
F 2 "" H 3000 3200 50  0001 C CNN
F 3 "" H 3000 3200 50  0001 C CNN
	1    3000 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 3100 3000 3150
Wire Wire Line
	3000 3150 3100 3150
Wire Wire Line
	3100 3150 3100 3100
Wire Wire Line
	3000 3150 3000 3200
Connection ~ 3000 3150
$Comp
L power:GND #PWR013
U 1 1 60E7A01C
P 2100 3200
F 0 "#PWR013" H 2100 2950 50  0001 C CNN
F 1 "GND" H 2105 3027 50  0000 C CNN
F 2 "" H 2100 3200 50  0001 C CNN
F 3 "" H 2100 3200 50  0001 C CNN
	1    2100 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 2850 2200 2850
Wire Wire Line
	2100 2850 2100 3200
Text Notes 900  900  0    50   ~ 0
H-Bridge control mode:\nMODE = LOW -> IN/IN\nMODE = HIGH -> PHASE/ENBL
Wire Wire Line
	2200 2550 1900 2550
Wire Wire Line
	1900 2550 1900 2250
Wire Wire Line
	1900 2250 2200 2250
Wire Wire Line
	2200 2350 1800 2350
Wire Wire Line
	1800 2350 1800 2650
Wire Wire Line
	1800 2650 2200 2650
Text Notes 2350 1150 0    100  ~ 20
Left-Front motor
Text HLabel 1700 2250 0    50   Input ~ 0
LF_IN1
Text HLabel 1700 2350 0    50   Input ~ 0
LF_IN2
$Comp
L Device:C C1
U 1 1 60E81972
P 1800 1650
F 0 "C1" H 1915 1696 50  0000 L CNN
F 1 "100nF" H 1915 1605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1838 1500 50  0001 C CNN
F 3 "~" H 1800 1650 50  0001 C CNN
	1    1800 1650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR07
U 1 1 60E81C1F
P 1800 1800
F 0 "#PWR07" H 1800 1550 50  0001 C CNN
F 1 "GND" H 1805 1627 50  0000 C CNN
F 2 "" H 1800 1800 50  0001 C CNN
F 3 "" H 1800 1800 50  0001 C CNN
	1    1800 1800
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR03
U 1 1 60E820E2
P 1800 1500
F 0 "#PWR03" H 1800 1350 50  0001 C CNN
F 1 "+3.3V" H 1815 1673 50  0000 C CNN
F 2 "" H 1800 1500 50  0001 C CNN
F 3 "" H 1800 1500 50  0001 C CNN
	1    1800 1500
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR011
U 1 1 60E82845
P 3000 2000
F 0 "#PWR011" H 3000 1850 50  0001 C CNN
F 1 "+3.3V" H 3015 2173 50  0000 C CNN
F 2 "" H 3000 2000 50  0001 C CNN
F 3 "" H 3000 2000 50  0001 C CNN
	1    3000 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 60E87443
P 2350 1650
F 0 "C2" H 2465 1696 50  0000 L CNN
F 1 "100nF" H 2465 1605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2388 1500 50  0001 C CNN
F 3 "~" H 2350 1650 50  0001 C CNN
	1    2350 1650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 60E87449
P 2350 1800
F 0 "#PWR08" H 2350 1550 50  0001 C CNN
F 1 "GND" H 2355 1627 50  0000 C CNN
F 2 "" H 2350 1800 50  0001 C CNN
F 3 "" H 2350 1800 50  0001 C CNN
	1    2350 1800
	1    0    0    -1  
$EndComp
Text GLabel 2350 1500 1    50   Input ~ 0
SUPPLY
Wire Wire Line
	3800 2250 4250 2250
Wire Wire Line
	4250 2250 4250 2550
Wire Wire Line
	4250 2550 3800 2550
Wire Wire Line
	3800 2350 4350 2350
Wire Wire Line
	4350 2350 4350 2650
Wire Wire Line
	4350 2650 3800 2650
Wire Wire Line
	4250 2250 4450 2250
Connection ~ 4250 2250
Wire Wire Line
	4350 2350 4450 2350
Connection ~ 4350 2350
Wire Wire Line
	1900 2250 1700 2250
Connection ~ 1900 2250
Wire Wire Line
	1800 2350 1700 2350
Connection ~ 1800 2350
$Comp
L Connector_Generic:Conn_01x06 J1
U 1 1 60E9010F
P 4550 1650
F 0 "J1" H 4630 1642 50  0000 L CNN
F 1 "Conn_01x06" H 4630 1551 50  0000 L CNN
F 2 "Connector_JST:JST_PH_S6B-PH-K_1x06_P2.00mm_Horizontal" H 4550 1650 50  0001 C CNN
F 3 "~" H 4550 1650 50  0001 C CNN
	1    4550 1650
	1    0    0    -1  
$EndComp
Text Label 4450 2250 0    50   ~ 0
LF_OUT1
Text Label 4450 2350 0    50   ~ 0
LF_OUT2
$Comp
L power:GND #PWR01
U 1 1 60E93D9C
P 4350 1450
F 0 "#PWR01" H 4350 1200 50  0001 C CNN
F 1 "GND" V 4355 1322 50  0000 R CNN
F 2 "" H 4350 1450 50  0001 C CNN
F 3 "" H 4350 1450 50  0001 C CNN
	1    4350 1450
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR05
U 1 1 60E94B77
P 4350 1750
F 0 "#PWR05" H 4350 1600 50  0001 C CNN
F 1 "+3.3V" V 4365 1878 50  0000 L CNN
F 2 "" H 4350 1750 50  0001 C CNN
F 3 "" H 4350 1750 50  0001 C CNN
	1    4350 1750
	0    -1   -1   0   
$EndComp
Text Label 4350 1950 2    50   ~ 0
LF_OUT1
Text Label 4350 1850 2    50   ~ 0
LF_OUT2
Text HLabel 4350 1650 0    50   Output ~ 0
LF_A
Text HLabel 4350 1550 0    50   Output ~ 0
LF_B
$Comp
L Sneak100_kicad:DRV8835 U2
U 1 1 60EAF5AA
P 7750 2450
F 0 "U2" H 8250 3000 50  0000 C CNN
F 1 "DRV8835" H 8250 2900 50  0000 C CNN
F 2 "Package_SON:WSON-12-1EP_3x2mm_P0.5mm_EP1x2.65_ThermalVias" H 7650 2900 50  0001 C CNN
F 3 "" H 7650 2900 50  0001 C CNN
	1    7750 2450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR016
U 1 1 60EAF5B0
P 7700 3200
F 0 "#PWR016" H 7700 2950 50  0001 C CNN
F 1 "GND" H 7705 3027 50  0000 C CNN
F 2 "" H 7700 3200 50  0001 C CNN
F 3 "" H 7700 3200 50  0001 C CNN
	1    7700 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 3100 7700 3150
Wire Wire Line
	7700 3150 7800 3150
Wire Wire Line
	7800 3150 7800 3100
Wire Wire Line
	7700 3150 7700 3200
Connection ~ 7700 3150
$Comp
L power:GND #PWR015
U 1 1 60EAF5BB
P 6800 3200
F 0 "#PWR015" H 6800 2950 50  0001 C CNN
F 1 "GND" H 6805 3027 50  0000 C CNN
F 2 "" H 6800 3200 50  0001 C CNN
F 3 "" H 6800 3200 50  0001 C CNN
	1    6800 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6800 2850 6900 2850
Wire Wire Line
	6800 2850 6800 3200
Wire Wire Line
	6900 2550 6600 2550
Wire Wire Line
	6600 2550 6600 2250
Wire Wire Line
	6600 2250 6900 2250
Wire Wire Line
	6900 2350 6500 2350
Wire Wire Line
	6500 2350 6500 2650
Wire Wire Line
	6500 2650 6900 2650
Text Notes 7050 1150 0    100  ~ 20
Right-Front motor
Text HLabel 6400 2250 0    50   Input ~ 0
RF_IN1
Text HLabel 6400 2350 0    50   Input ~ 0
RF_IN2
$Comp
L Device:C C3
U 1 1 60EAF5CC
P 6500 1650
F 0 "C3" H 6615 1696 50  0000 L CNN
F 1 "100nF" H 6615 1605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6538 1500 50  0001 C CNN
F 3 "~" H 6500 1650 50  0001 C CNN
	1    6500 1650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 60EAF5D2
P 6500 1800
F 0 "#PWR09" H 6500 1550 50  0001 C CNN
F 1 "GND" H 6505 1627 50  0000 C CNN
F 2 "" H 6500 1800 50  0001 C CNN
F 3 "" H 6500 1800 50  0001 C CNN
	1    6500 1800
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR04
U 1 1 60EAF5D8
P 6500 1500
F 0 "#PWR04" H 6500 1350 50  0001 C CNN
F 1 "+3.3V" H 6515 1673 50  0000 C CNN
F 2 "" H 6500 1500 50  0001 C CNN
F 3 "" H 6500 1500 50  0001 C CNN
	1    6500 1500
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR012
U 1 1 60EAF5DE
P 7700 2000
F 0 "#PWR012" H 7700 1850 50  0001 C CNN
F 1 "+3.3V" H 7715 2173 50  0000 C CNN
F 2 "" H 7700 2000 50  0001 C CNN
F 3 "" H 7700 2000 50  0001 C CNN
	1    7700 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 60EAF5E4
P 7050 1650
F 0 "C4" H 7165 1696 50  0000 L CNN
F 1 "100nF" H 7165 1605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7088 1500 50  0001 C CNN
F 3 "~" H 7050 1650 50  0001 C CNN
	1    7050 1650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR010
U 1 1 60EAF5EA
P 7050 1800
F 0 "#PWR010" H 7050 1550 50  0001 C CNN
F 1 "GND" H 7055 1627 50  0000 C CNN
F 2 "" H 7050 1800 50  0001 C CNN
F 3 "" H 7050 1800 50  0001 C CNN
	1    7050 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 2250 8950 2250
Wire Wire Line
	8950 2250 8950 2550
Wire Wire Line
	8950 2550 8500 2550
Wire Wire Line
	8500 2350 9050 2350
Wire Wire Line
	9050 2350 9050 2650
Wire Wire Line
	9050 2650 8500 2650
Wire Wire Line
	8950 2250 9150 2250
Connection ~ 8950 2250
Wire Wire Line
	9050 2350 9150 2350
Connection ~ 9050 2350
Wire Wire Line
	6600 2250 6400 2250
Connection ~ 6600 2250
Wire Wire Line
	6500 2350 6400 2350
Connection ~ 6500 2350
$Comp
L Connector_Generic:Conn_01x06 J2
U 1 1 60EAF600
P 9250 1650
F 0 "J2" H 9330 1642 50  0000 L CNN
F 1 "Conn_01x06" H 9330 1551 50  0000 L CNN
F 2 "Connector_JST:JST_PH_S6B-PH-K_1x06_P2.00mm_Horizontal" H 9250 1650 50  0001 C CNN
F 3 "~" H 9250 1650 50  0001 C CNN
	1    9250 1650
	1    0    0    -1  
$EndComp
Text Label 9150 2250 0    50   ~ 0
RF_OUT1
Text Label 9150 2350 0    50   ~ 0
RF_OUT2
$Comp
L power:GND #PWR02
U 1 1 60EAF608
P 9050 1450
F 0 "#PWR02" H 9050 1200 50  0001 C CNN
F 1 "GND" V 9055 1322 50  0000 R CNN
F 2 "" H 9050 1450 50  0001 C CNN
F 3 "" H 9050 1450 50  0001 C CNN
	1    9050 1450
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR06
U 1 1 60EAF60E
P 9050 1750
F 0 "#PWR06" H 9050 1600 50  0001 C CNN
F 1 "+3.3V" V 9065 1878 50  0000 L CNN
F 2 "" H 9050 1750 50  0001 C CNN
F 3 "" H 9050 1750 50  0001 C CNN
	1    9050 1750
	0    -1   -1   0   
$EndComp
Text Label 9050 1950 2    50   ~ 0
RF_OUT1
Text Label 9050 1850 2    50   ~ 0
RF_OUT2
Text HLabel 9050 1650 0    50   Output ~ 0
RF_A
Text HLabel 9050 1550 0    50   Output ~ 0
RF_B
$Comp
L Sneak100_kicad:DRV8835 U3
U 1 1 60EB4F00
P 2950 5350
F 0 "U3" H 3450 5900 50  0000 C CNN
F 1 "DRV8835" H 3450 5800 50  0000 C CNN
F 2 "Package_SON:WSON-12-1EP_3x2mm_P0.5mm_EP1x2.65_ThermalVias" H 2850 5800 50  0001 C CNN
F 3 "" H 2850 5800 50  0001 C CNN
	1    2950 5350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR030
U 1 1 60EB4F06
P 2900 6100
F 0 "#PWR030" H 2900 5850 50  0001 C CNN
F 1 "GND" H 2905 5927 50  0000 C CNN
F 2 "" H 2900 6100 50  0001 C CNN
F 3 "" H 2900 6100 50  0001 C CNN
	1    2900 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 6000 2900 6050
Wire Wire Line
	2900 6050 3000 6050
Wire Wire Line
	3000 6050 3000 6000
Wire Wire Line
	2900 6050 2900 6100
Connection ~ 2900 6050
$Comp
L power:GND #PWR029
U 1 1 60EB4F11
P 2000 6100
F 0 "#PWR029" H 2000 5850 50  0001 C CNN
F 1 "GND" H 2005 5927 50  0000 C CNN
F 2 "" H 2000 6100 50  0001 C CNN
F 3 "" H 2000 6100 50  0001 C CNN
	1    2000 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 5750 2100 5750
Wire Wire Line
	2000 5750 2000 6100
Wire Wire Line
	2100 5450 1800 5450
Wire Wire Line
	1800 5450 1800 5150
Wire Wire Line
	1800 5150 2100 5150
Wire Wire Line
	2100 5250 1700 5250
Wire Wire Line
	1700 5250 1700 5550
Wire Wire Line
	1700 5550 2100 5550
Text Notes 2250 4050 0    100  ~ 20
Left-Back motor
Text HLabel 1600 5150 0    50   Input ~ 0
LB_IN1
Text HLabel 1600 5250 0    50   Input ~ 0
LB_IN2
$Comp
L Device:C C5
U 1 1 60EB4F22
P 1700 4550
F 0 "C5" H 1815 4596 50  0000 L CNN
F 1 "100nF" H 1815 4505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1738 4400 50  0001 C CNN
F 3 "~" H 1700 4550 50  0001 C CNN
	1    1700 4550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR022
U 1 1 60EB4F28
P 1700 4700
F 0 "#PWR022" H 1700 4450 50  0001 C CNN
F 1 "GND" H 1705 4527 50  0000 C CNN
F 2 "" H 1700 4700 50  0001 C CNN
F 3 "" H 1700 4700 50  0001 C CNN
	1    1700 4700
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR018
U 1 1 60EB4F2E
P 1700 4400
F 0 "#PWR018" H 1700 4250 50  0001 C CNN
F 1 "+3.3V" H 1715 4573 50  0000 C CNN
F 2 "" H 1700 4400 50  0001 C CNN
F 3 "" H 1700 4400 50  0001 C CNN
	1    1700 4400
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR027
U 1 1 60EB4F34
P 2900 4900
F 0 "#PWR027" H 2900 4750 50  0001 C CNN
F 1 "+3.3V" H 2915 5073 50  0000 C CNN
F 2 "" H 2900 4900 50  0001 C CNN
F 3 "" H 2900 4900 50  0001 C CNN
	1    2900 4900
	1    0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 60EB4F3A
P 2250 4550
F 0 "C6" H 2365 4596 50  0000 L CNN
F 1 "100nF" H 2365 4505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2288 4400 50  0001 C CNN
F 3 "~" H 2250 4550 50  0001 C CNN
	1    2250 4550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR023
U 1 1 60EB4F40
P 2250 4700
F 0 "#PWR023" H 2250 4450 50  0001 C CNN
F 1 "GND" H 2255 4527 50  0000 C CNN
F 2 "" H 2250 4700 50  0001 C CNN
F 3 "" H 2250 4700 50  0001 C CNN
	1    2250 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 5150 4150 5150
Wire Wire Line
	4150 5150 4150 5450
Wire Wire Line
	4150 5450 3700 5450
Wire Wire Line
	3700 5250 4250 5250
Wire Wire Line
	4250 5250 4250 5550
Wire Wire Line
	4250 5550 3700 5550
Wire Wire Line
	4150 5150 4350 5150
Connection ~ 4150 5150
Wire Wire Line
	4250 5250 4350 5250
Connection ~ 4250 5250
Wire Wire Line
	1800 5150 1600 5150
Connection ~ 1800 5150
Wire Wire Line
	1700 5250 1600 5250
Connection ~ 1700 5250
$Comp
L Connector_Generic:Conn_01x06 J3
U 1 1 60EB4F56
P 4450 4550
F 0 "J3" H 4530 4542 50  0000 L CNN
F 1 "Conn_01x06" H 4530 4451 50  0000 L CNN
F 2 "Connector_JST:JST_PH_S6B-PH-K_1x06_P2.00mm_Horizontal" H 4450 4550 50  0001 C CNN
F 3 "~" H 4450 4550 50  0001 C CNN
	1    4450 4550
	1    0    0    -1  
$EndComp
Text Label 4350 5150 0    50   ~ 0
LB_OUT1
Text Label 4350 5250 0    50   ~ 0
LB_OUT2
$Comp
L power:GND #PWR017
U 1 1 60EB4F5E
P 4250 4350
F 0 "#PWR017" H 4250 4100 50  0001 C CNN
F 1 "GND" V 4255 4222 50  0000 R CNN
F 2 "" H 4250 4350 50  0001 C CNN
F 3 "" H 4250 4350 50  0001 C CNN
	1    4250 4350
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR021
U 1 1 60EB4F64
P 4250 4650
F 0 "#PWR021" H 4250 4500 50  0001 C CNN
F 1 "+3.3V" V 4265 4778 50  0000 L CNN
F 2 "" H 4250 4650 50  0001 C CNN
F 3 "" H 4250 4650 50  0001 C CNN
	1    4250 4650
	0    -1   -1   0   
$EndComp
Text Label 4250 4850 2    50   ~ 0
LB_OUT1
Text Label 4250 4750 2    50   ~ 0
LB_OUT2
Text HLabel 4250 4550 0    50   Output ~ 0
LB_A
Text HLabel 4250 4450 0    50   Output ~ 0
LB_B
$Comp
L Sneak100_kicad:DRV8835 U4
U 1 1 60EC1812
P 7750 5400
F 0 "U4" H 8250 5950 50  0000 C CNN
F 1 "DRV8835" H 8250 5850 50  0000 C CNN
F 2 "Package_SON:WSON-12-1EP_3x2mm_P0.5mm_EP1x2.65_ThermalVias" H 7650 5850 50  0001 C CNN
F 3 "" H 7650 5850 50  0001 C CNN
	1    7750 5400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR032
U 1 1 60EC1818
P 7700 6150
F 0 "#PWR032" H 7700 5900 50  0001 C CNN
F 1 "GND" H 7705 5977 50  0000 C CNN
F 2 "" H 7700 6150 50  0001 C CNN
F 3 "" H 7700 6150 50  0001 C CNN
	1    7700 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 6050 7700 6100
Wire Wire Line
	7700 6100 7800 6100
Wire Wire Line
	7800 6100 7800 6050
Wire Wire Line
	7700 6100 7700 6150
Connection ~ 7700 6100
$Comp
L power:GND #PWR031
U 1 1 60EC1823
P 6800 6150
F 0 "#PWR031" H 6800 5900 50  0001 C CNN
F 1 "GND" H 6805 5977 50  0000 C CNN
F 2 "" H 6800 6150 50  0001 C CNN
F 3 "" H 6800 6150 50  0001 C CNN
	1    6800 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6800 5800 6900 5800
Wire Wire Line
	6800 5800 6800 6150
Wire Wire Line
	6900 5500 6600 5500
Wire Wire Line
	6600 5500 6600 5200
Wire Wire Line
	6600 5200 6900 5200
Wire Wire Line
	6900 5300 6500 5300
Wire Wire Line
	6500 5300 6500 5600
Wire Wire Line
	6500 5600 6900 5600
Text Notes 7050 4100 0    100  ~ 20
Right-Back motor
Text HLabel 6400 5200 0    50   Input ~ 0
RB_IN1
Text HLabel 6400 5300 0    50   Input ~ 0
RB_IN2
$Comp
L Device:C C7
U 1 1 60EC1834
P 6500 4600
F 0 "C7" H 6615 4646 50  0000 L CNN
F 1 "100nF" H 6615 4555 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6538 4450 50  0001 C CNN
F 3 "~" H 6500 4600 50  0001 C CNN
	1    6500 4600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR025
U 1 1 60EC183A
P 6500 4750
F 0 "#PWR025" H 6500 4500 50  0001 C CNN
F 1 "GND" H 6505 4577 50  0000 C CNN
F 2 "" H 6500 4750 50  0001 C CNN
F 3 "" H 6500 4750 50  0001 C CNN
	1    6500 4750
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR020
U 1 1 60EC1840
P 6500 4450
F 0 "#PWR020" H 6500 4300 50  0001 C CNN
F 1 "+3.3V" H 6515 4623 50  0000 C CNN
F 2 "" H 6500 4450 50  0001 C CNN
F 3 "" H 6500 4450 50  0001 C CNN
	1    6500 4450
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR028
U 1 1 60EC1846
P 7700 4950
F 0 "#PWR028" H 7700 4800 50  0001 C CNN
F 1 "+3.3V" H 7715 5123 50  0000 C CNN
F 2 "" H 7700 4950 50  0001 C CNN
F 3 "" H 7700 4950 50  0001 C CNN
	1    7700 4950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C8
U 1 1 60EC184C
P 7050 4600
F 0 "C8" H 7165 4646 50  0000 L CNN
F 1 "100nF" H 7165 4555 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7088 4450 50  0001 C CNN
F 3 "~" H 7050 4600 50  0001 C CNN
	1    7050 4600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR026
U 1 1 60EC1852
P 7050 4750
F 0 "#PWR026" H 7050 4500 50  0001 C CNN
F 1 "GND" H 7055 4577 50  0000 C CNN
F 2 "" H 7050 4750 50  0001 C CNN
F 3 "" H 7050 4750 50  0001 C CNN
	1    7050 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 5200 8950 5200
Wire Wire Line
	8950 5200 8950 5500
Wire Wire Line
	8950 5500 8500 5500
Wire Wire Line
	8500 5300 9050 5300
Wire Wire Line
	9050 5300 9050 5600
Wire Wire Line
	9050 5600 8500 5600
Wire Wire Line
	8950 5200 9150 5200
Connection ~ 8950 5200
Wire Wire Line
	9050 5300 9150 5300
Connection ~ 9050 5300
Wire Wire Line
	6600 5200 6400 5200
Connection ~ 6600 5200
Wire Wire Line
	6500 5300 6400 5300
Connection ~ 6500 5300
$Comp
L Connector_Generic:Conn_01x06 J4
U 1 1 60EC1868
P 9250 4600
F 0 "J4" H 9330 4592 50  0000 L CNN
F 1 "Conn_01x06" H 9330 4501 50  0000 L CNN
F 2 "Connector_JST:JST_PH_S6B-PH-K_1x06_P2.00mm_Horizontal" H 9250 4600 50  0001 C CNN
F 3 "~" H 9250 4600 50  0001 C CNN
	1    9250 4600
	1    0    0    -1  
$EndComp
Text Label 9150 5200 0    50   ~ 0
RB_OUT1
Text Label 9150 5300 0    50   ~ 0
RB_OUT2
$Comp
L power:GND #PWR019
U 1 1 60EC1870
P 9050 4400
F 0 "#PWR019" H 9050 4150 50  0001 C CNN
F 1 "GND" V 9055 4272 50  0000 R CNN
F 2 "" H 9050 4400 50  0001 C CNN
F 3 "" H 9050 4400 50  0001 C CNN
	1    9050 4400
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR024
U 1 1 60EC1876
P 9050 4700
F 0 "#PWR024" H 9050 4550 50  0001 C CNN
F 1 "+3.3V" V 9065 4828 50  0000 L CNN
F 2 "" H 9050 4700 50  0001 C CNN
F 3 "" H 9050 4700 50  0001 C CNN
	1    9050 4700
	0    -1   -1   0   
$EndComp
Text Label 9050 4900 2    50   ~ 0
RB_OUT1
Text Label 9050 4800 2    50   ~ 0
RB_OUT2
Text HLabel 9050 4600 0    50   Output ~ 0
RB_A
Text HLabel 9050 4500 0    50   Output ~ 0
RB_B
Text GLabel 3100 2000 1    50   Input ~ 0
SUPPLY
Text GLabel 7800 2000 1    50   Input ~ 0
SUPPLY
Text GLabel 7050 1500 1    50   Input ~ 0
SUPPLY
Text GLabel 2250 4400 1    50   Input ~ 0
SUPPLY
Text GLabel 3000 4900 1    50   Input ~ 0
SUPPLY
Text GLabel 7050 4450 1    50   Input ~ 0
SUPPLY
Text GLabel 7800 4950 1    50   Input ~ 0
SUPPLY
$EndSCHEMATC
