EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 7
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
L Connector_Generic:Conn_01x02 J5
U 1 1 60EEA812
P 1300 2450
F 0 "J5" H 1450 2450 50  0000 C CNN
F 1 "Conn_01x02" H 1650 2350 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Horizontal" H 1300 2450 50  0001 C CNN
F 3 "~" H 1300 2450 50  0001 C CNN
	1    1300 2450
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D1
U 1 1 60F07A86
P 9550 4650
F 0 "D1" V 9589 4532 50  0000 R CNN
F 1 "LED" V 9498 4532 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 9550 4650 50  0001 C CNN
F 3 "~" H 9550 4650 50  0001 C CNN
	1    9550 4650
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R5
U 1 1 60F07A8C
P 9550 4350
F 0 "R5" H 9620 4396 50  0000 L CNN
F 1 "360" H 9620 4305 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 9480 4350 50  0001 C CNN
F 3 "~" H 9550 4350 50  0001 C CNN
	1    9550 4350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR051
U 1 1 60F07A92
P 9550 4800
F 0 "#PWR051" H 9550 4550 50  0001 C CNN
F 1 "GND" H 9555 4627 50  0000 C CNN
F 2 "" H 9550 4800 50  0001 C CNN
F 3 "" H 9550 4800 50  0001 C CNN
	1    9550 4800
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR050
U 1 1 60F07C02
P 9550 4200
F 0 "#PWR050" H 9550 4050 50  0001 C CNN
F 1 "+3.3V" H 9565 4373 50  0000 C CNN
F 2 "" H 9550 4200 50  0001 C CNN
F 3 "" H 9550 4200 50  0001 C CNN
	1    9550 4200
	1    0    0    -1  
$EndComp
Text Notes 5650 1600 0    100  ~ 20
5V step-down converter
$Comp
L Device:R R4
U 1 1 60F0EDCE
P 6500 4350
F 0 "R4" H 6570 4396 50  0000 L CNN
F 1 "18k" H 6570 4305 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6430 4350 50  0001 C CNN
F 3 "~" H 6500 4350 50  0001 C CNN
	1    6500 4350
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 60F10A9C
P 6500 4750
F 0 "R6" H 6570 4796 50  0000 L CNN
F 1 "10k" H 6570 4705 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6430 4750 50  0001 C CNN
F 3 "~" H 6500 4750 50  0001 C CNN
	1    6500 4750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR052
U 1 1 60F10E65
P 6500 4900
F 0 "#PWR052" H 6500 4650 50  0001 C CNN
F 1 "GND" H 6505 4727 50  0000 C CNN
F 2 "" H 6500 4900 50  0001 C CNN
F 3 "" H 6500 4900 50  0001 C CNN
	1    6500 4900
	1    0    0    -1  
$EndComp
Text GLabel 6500 4200 1    50   Input ~ 0
SUPPLY
Wire Wire Line
	6500 4500 6500 4550
Wire Wire Line
	6500 4550 6550 4550
Connection ~ 6500 4550
Wire Wire Line
	6500 4550 6500 4600
Text HLabel 6550 4550 2    50   Output ~ 0
BATTERY_SENSE
Text Notes 5850 3650 0    100  ~ 20
Battery level sense
Text Notes 8850 3650 0    100  ~ 20
Power level indicator
$Comp
L Device:R R2
U 1 1 60F4ED8A
P 2050 2800
F 0 "R2" H 2120 2846 50  0000 L CNN
F 1 "1k" H 2120 2755 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1980 2800 50  0001 C CNN
F 3 "~" H 2050 2800 50  0001 C CNN
	1    2050 2800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 60F4F20A
P 2950 2550
F 0 "R1" H 3020 2596 50  0000 L CNN
F 1 "10k" H 3020 2505 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2880 2550 50  0001 C CNN
F 3 "~" H 2950 2550 50  0001 C CNN
	1    2950 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 60F4F69A
P 3350 3000
F 0 "R3" H 3420 3046 50  0000 L CNN
F 1 "1k" H 3420 2955 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3280 3000 50  0001 C CNN
F 3 "~" H 3350 3000 50  0001 C CNN
	1    3350 3000
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push_SPDT SW1
U 1 1 60F52713
P 3050 3350
F 0 "SW1" H 3600 3400 50  0000 C CNN
F 1 "SW_Push_SPDT" H 3600 3300 50  0000 C CNN
F 2 "sneak100_lib:ESP2010_90" H 3050 3350 50  0001 C CNN
F 3 "~" H 3050 3350 50  0001 C CNN
	1    3050 3350
	-1   0    0    -1  
$EndComp
Text Notes 1850 1600 0    100  ~ 20
Power input menagement
Wire Wire Line
	2250 2350 2300 2350
Wire Wire Line
	2950 2700 2950 2750
Wire Wire Line
	2950 2750 3350 2750
Wire Wire Line
	3350 2750 3350 2850
Wire Wire Line
	3350 2750 3350 2650
Connection ~ 3350 2750
Wire Wire Line
	2950 2400 2950 2350
Connection ~ 2950 2350
Wire Wire Line
	2950 2350 3100 2350
$Comp
L power:GND #PWR048
U 1 1 60F76C10
P 2050 2950
F 0 "#PWR048" H 2050 2700 50  0001 C CNN
F 1 "GND" H 2055 2777 50  0000 C CNN
F 2 "" H 2050 2950 50  0001 C CNN
F 3 "" H 2050 2950 50  0001 C CNN
	1    2050 2950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR049
U 1 1 60F78854
P 2800 3500
F 0 "#PWR049" H 2800 3250 50  0001 C CNN
F 1 "GND" H 2805 3327 50  0000 C CNN
F 2 "" H 2800 3500 50  0001 C CNN
F 3 "" H 2800 3500 50  0001 C CNN
	1    2800 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 3500 2800 3450
Wire Wire Line
	2800 3450 2850 3450
$Comp
L power:GND #PWR040
U 1 1 60F7A03D
P 1550 2500
F 0 "#PWR040" H 1550 2250 50  0001 C CNN
F 1 "GND" H 1555 2327 50  0000 C CNN
F 2 "" H 1550 2500 50  0001 C CNN
F 3 "" H 1550 2500 50  0001 C CNN
	1    1550 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 2450 1550 2450
Wire Wire Line
	1550 2450 1550 2500
Text GLabel 3650 2350 2    50   Input ~ 0
SUPPLY
Wire Wire Line
	3250 3350 3350 3350
Wire Wire Line
	2850 3250 2800 3250
Wire Wire Line
	2800 3250 2800 3200
Wire Wire Line
	3350 3150 3350 3200
Wire Wire Line
	2800 3200 3350 3200
Connection ~ 3350 3200
Wire Wire Line
	3350 3200 3350 3350
$Comp
L Regulator_Linear:LM1117-3.3 U5
U 1 1 6104B338
P 9600 2250
F 0 "U5" H 9600 2492 50  0000 C CNN
F 1 "LM1117-3.3" H 9600 2401 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 9600 2250 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm1117.pdf" H 9600 2250 50  0001 C CNN
	1    9600 2250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C14
U 1 1 6104BD36
P 8800 2450
F 0 "C14" H 8450 2500 50  0000 L CNN
F 1 "100nF" H 8450 2400 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8838 2300 50  0001 C CNN
F 3 "~" H 8800 2450 50  0001 C CNN
	1    8800 2450
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C15
U 1 1 6104C514
P 9050 2450
F 0 "C15" H 9168 2496 50  0000 L CNN
F 1 "4.7uF" H 9168 2405 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-3216-18_Kemet-A" H 9088 2300 50  0001 C CNN
F 3 "~" H 9050 2450 50  0001 C CNN
	1    9050 2450
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C16
U 1 1 6104F3B9
P 10150 2450
F 0 "C16" H 9850 2500 50  0000 L CNN
F 1 "4.7uF" H 9850 2400 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-3216-18_Kemet-A" H 10188 2300 50  0001 C CNN
F 3 "~" H 10150 2450 50  0001 C CNN
	1    10150 2450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C17
U 1 1 6104FB23
P 10400 2450
F 0 "C17" H 10515 2496 50  0000 L CNN
F 1 "100nF" H 10515 2405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 10438 2300 50  0001 C CNN
F 3 "~" H 10400 2450 50  0001 C CNN
	1    10400 2450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR044
U 1 1 61050D58
P 8800 2600
F 0 "#PWR044" H 8800 2350 50  0001 C CNN
F 1 "GND" H 8805 2427 50  0000 C CNN
F 2 "" H 8800 2600 50  0001 C CNN
F 3 "" H 8800 2600 50  0001 C CNN
	1    8800 2600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR045
U 1 1 610513D3
P 9050 2600
F 0 "#PWR045" H 9050 2350 50  0001 C CNN
F 1 "GND" H 9055 2427 50  0000 C CNN
F 2 "" H 9050 2600 50  0001 C CNN
F 3 "" H 9050 2600 50  0001 C CNN
	1    9050 2600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR046
U 1 1 61051726
P 10150 2600
F 0 "#PWR046" H 10150 2350 50  0001 C CNN
F 1 "GND" H 10155 2427 50  0000 C CNN
F 2 "" H 10150 2600 50  0001 C CNN
F 3 "" H 10150 2600 50  0001 C CNN
	1    10150 2600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR047
U 1 1 61051BAB
P 10400 2600
F 0 "#PWR047" H 10400 2350 50  0001 C CNN
F 1 "GND" H 10405 2427 50  0000 C CNN
F 2 "" H 10400 2600 50  0001 C CNN
F 3 "" H 10400 2600 50  0001 C CNN
	1    10400 2600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR043
U 1 1 61051F07
P 9600 2550
F 0 "#PWR043" H 9600 2300 50  0001 C CNN
F 1 "GND" H 9605 2377 50  0000 C CNN
F 2 "" H 9600 2550 50  0001 C CNN
F 3 "" H 9600 2550 50  0001 C CNN
	1    9600 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	9900 2250 10150 2250
Wire Wire Line
	10150 2250 10150 2300
Wire Wire Line
	10150 2250 10400 2250
Wire Wire Line
	10400 2250 10400 2300
Connection ~ 10150 2250
Wire Wire Line
	9300 2250 9050 2250
Wire Wire Line
	9050 2250 9050 2300
Wire Wire Line
	9050 2250 8800 2250
Wire Wire Line
	8800 2250 8800 2300
Connection ~ 9050 2250
$Comp
L power:+5V #PWR038
U 1 1 6105897D
P 8800 2200
F 0 "#PWR038" H 8800 2050 50  0001 C CNN
F 1 "+5V" H 8815 2373 50  0000 C CNN
F 2 "" H 8800 2200 50  0001 C CNN
F 3 "" H 8800 2200 50  0001 C CNN
	1    8800 2200
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR039
U 1 1 61059578
P 10400 2200
F 0 "#PWR039" H 10400 2050 50  0001 C CNN
F 1 "+3.3V" H 10415 2373 50  0000 C CNN
F 2 "" H 10400 2200 50  0001 C CNN
F 3 "" H 10400 2200 50  0001 C CNN
	1    10400 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	10400 2250 10400 2200
Connection ~ 10400 2250
Wire Wire Line
	8800 2250 8800 2200
Connection ~ 8800 2250
Text Notes 8900 1600 0    100  ~ 20
3.3V LDO regulator
Text Notes 5000 6150 0    50   ~ 10
Voltage divider calculations:\n\nU_in max = 8.4V\nU_out max = 3V\n\nU_out = U_in * R2/(R1+R2)\nU_out * (R1+R2) = U_in * R2\nU_out * R1+ U_out * R2 = U_in * R2\nU_out * R1 = (U_in - U_out) * R2\nR1 = R2 * (U_in - U_out)/U_out\n\nassume R2 = 10k\n\nR1 = 10000 * (8.4 - 3)/3 = 18 kohm\n
Text Notes 8800 6100 0    50   ~ 10
Power leds current resistor calculations:\n\ntarget current: I = 5mA\ninput voltage: U1= 3.3V\nforward voltage: Uf = 1.6V\n\nR = (U-Uf)/I\nR_3.3V = (3.3 -1.6)/0.005 = 340 ohm -> 360 ohm
$Comp
L Device:C C13
U 1 1 60FF72EC
P 6000 2400
F 0 "C13" H 6115 2446 50  0000 L CNN
F 1 "33uF" H 6115 2355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6038 2250 50  0001 C CNN
F 3 "~" H 6000 2400 50  0001 C CNN
	1    6000 2400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR041
U 1 1 60FF77C3
P 6000 2550
F 0 "#PWR041" H 6000 2300 50  0001 C CNN
F 1 "GND" H 6005 2377 50  0000 C CNN
F 2 "" H 6000 2550 50  0001 C CNN
F 3 "" H 6000 2550 50  0001 C CNN
	1    6000 2550
	1    0    0    -1  
$EndComp
Text GLabel 5950 2200 0    50   Input ~ 0
SUPPLY
$Comp
L Sneak100_kicad:S9V11F5 U6
U 1 1 61014AE3
P 6650 2300
F 0 "U6" H 6650 2665 50  0000 C CNN
F 1 "S9V11F5" H 6650 2574 50  0000 C CNN
F 2 "sneak100_lib:S9V11F5_module" H 6650 2650 50  0001 C CNN
F 3 "" H 6650 2650 50  0001 C CNN
	1    6650 2300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR042
U 1 1 6101E52E
P 6650 2550
F 0 "#PWR042" H 6650 2300 50  0001 C CNN
F 1 "GND" H 6655 2377 50  0000 C CNN
F 2 "" H 6650 2550 50  0001 C CNN
F 3 "" H 6650 2550 50  0001 C CNN
	1    6650 2550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR037
U 1 1 61020CAB
P 7100 2150
F 0 "#PWR037" H 7100 2000 50  0001 C CNN
F 1 "+5V" H 7115 2323 50  0000 C CNN
F 2 "" H 7100 2150 50  0001 C CNN
F 3 "" H 7100 2150 50  0001 C CNN
	1    7100 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 2200 7100 2200
Wire Wire Line
	7100 2200 7100 2150
Wire Wire Line
	6250 2200 6000 2200
Wire Wire Line
	6000 2200 6000 2250
Wire Wire Line
	6000 2200 5950 2200
Connection ~ 6000 2200
Wire Wire Line
	1500 2350 1800 2350
Wire Wire Line
	3550 2350 3600 2350
$Comp
L Sneak100_kicad:AO4407 Q1
U 1 1 6111B142
P 2050 2350
F 0 "Q1" V 2545 2350 50  0000 C CNN
F 1 "AO4407" V 2450 2350 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 2550 2500 50  0001 C CNN
F 3 "" H 2550 2500 50  0001 C CNN
	1    2050 2350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2250 2250 2300 2250
Wire Wire Line
	2300 2250 2300 2350
Connection ~ 2300 2350
Wire Wire Line
	2300 2350 2950 2350
Wire Wire Line
	2250 2150 2300 2150
Wire Wire Line
	2300 2150 2300 2250
Connection ~ 2300 2250
Wire Wire Line
	2250 2050 2300 2050
Wire Wire Line
	2300 2050 2300 2150
Connection ~ 2300 2150
Wire Wire Line
	1850 2250 1800 2250
Wire Wire Line
	1800 2250 1800 2350
Connection ~ 1800 2350
Wire Wire Line
	1800 2350 1850 2350
Wire Wire Line
	1850 2150 1800 2150
Wire Wire Line
	1800 2150 1800 2250
Connection ~ 1800 2250
$Comp
L Sneak100_kicad:AO4407 Q2
U 1 1 6112F3E3
P 3350 2350
F 0 "Q2" V 3845 2350 50  0000 C CNN
F 1 "AO4407" V 3750 2350 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 3850 2500 50  0001 C CNN
F 3 "" H 3850 2500 50  0001 C CNN
	1    3350 2350
	0    1    -1   0   
$EndComp
Wire Wire Line
	3550 2250 3600 2250
Wire Wire Line
	3600 2250 3600 2350
Wire Wire Line
	3550 2150 3600 2150
Wire Wire Line
	3600 2150 3600 2250
Connection ~ 3600 2250
Wire Wire Line
	3150 2250 3100 2250
Wire Wire Line
	3100 2250 3100 2350
Connection ~ 3100 2350
Wire Wire Line
	3100 2350 3150 2350
Wire Wire Line
	3150 2150 3100 2150
Wire Wire Line
	3100 2150 3100 2250
Connection ~ 3100 2250
Wire Wire Line
	3150 2050 3100 2050
Wire Wire Line
	3100 2050 3100 2150
Connection ~ 3100 2150
Wire Wire Line
	3600 2350 3650 2350
Connection ~ 3600 2350
$EndSCHEMATC
