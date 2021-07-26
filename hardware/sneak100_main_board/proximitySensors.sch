EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 7
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
L Analog_Switch:CD4051B U7
U 1 1 60E0E536
P 3100 4800
F 0 "U7" H 3500 5600 50  0000 C CNN
F 1 "CD4051B" H 3500 5500 50  0000 C CNN
F 2 "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm" H 3250 4050 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/cd4052b.pdf" H 3080 4900 50  0001 C CNN
	1    3100 4800
	1    0    0    -1  
$EndComp
$Comp
L Analog_Switch:CD4051B U8
U 1 1 60E0F4C1
P 7750 4800
F 0 "U8" H 8200 5600 50  0000 C CNN
F 1 "CD4051B" H 8200 5500 50  0000 C CNN
F 2 "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm" H 7900 4050 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/cd4052b.pdf" H 7730 4900 50  0001 C CNN
	1    7750 4800
	1    0    0    -1  
$EndComp
Text HLabel 2600 4300 0    50   Input ~ 0
ADD0
Text HLabel 2600 4400 0    50   Input ~ 0
ADD1
Text HLabel 2600 4500 0    50   Input ~ 0
ADD2
Text HLabel 7250 4300 0    50   Input ~ 0
ADD0
Text HLabel 7250 4400 0    50   Input ~ 0
ADD1
Text HLabel 7250 4500 0    50   Input ~ 0
ADD2
$Comp
L power:GND #PWR073
U 1 1 60E1F519
P 3100 5600
F 0 "#PWR073" H 3100 5350 50  0001 C CNN
F 1 "GND" H 3105 5427 50  0000 C CNN
F 2 "" H 3100 5600 50  0001 C CNN
F 3 "" H 3100 5600 50  0001 C CNN
	1    3100 5600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR074
U 1 1 60E212D3
P 7750 5600
F 0 "#PWR074" H 7750 5350 50  0001 C CNN
F 1 "GND" H 7755 5427 50  0000 C CNN
F 2 "" H 7750 5600 50  0001 C CNN
F 3 "" H 7750 5600 50  0001 C CNN
	1    7750 5600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR070
U 1 1 60E218A7
P 7200 4850
F 0 "#PWR070" H 7200 4600 50  0001 C CNN
F 1 "GND" H 7205 4677 50  0000 C CNN
F 2 "" H 7200 4850 50  0001 C CNN
F 3 "" H 7200 4850 50  0001 C CNN
	1    7200 4850
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR065
U 1 1 60E248E2
P 3200 4100
F 0 "#PWR065" H 3200 3950 50  0001 C CNN
F 1 "+3.3V" H 3215 4273 50  0000 C CNN
F 2 "" H 3200 4100 50  0001 C CNN
F 3 "" H 3200 4100 50  0001 C CNN
	1    3200 4100
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR067
U 1 1 60E24FA6
P 7850 4100
F 0 "#PWR067" H 7850 3950 50  0001 C CNN
F 1 "+3.3V" H 7865 4273 50  0000 C CNN
F 2 "" H 7850 4100 50  0001 C CNN
F 3 "" H 7850 4100 50  0001 C CNN
	1    7850 4100
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR069
U 1 1 60E25559
P 2000 4650
F 0 "#PWR069" H 2000 4500 50  0001 C CNN
F 1 "+3.3V" H 2015 4823 50  0000 C CNN
F 2 "" H 2000 4650 50  0001 C CNN
F 3 "" H 2000 4650 50  0001 C CNN
	1    2000 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 4700 2000 4700
Wire Wire Line
	2000 4700 2000 4650
Wire Wire Line
	3100 5600 3100 5550
Wire Wire Line
	3100 5550 3000 5550
Wire Wire Line
	3000 5550 3000 5500
Connection ~ 3100 5550
Wire Wire Line
	3100 5550 3100 5500
Wire Wire Line
	7650 5500 7650 5550
Wire Wire Line
	7650 5550 7750 5550
Wire Wire Line
	7750 5550 7750 5600
Wire Wire Line
	7750 5550 7750 5500
Connection ~ 7750 5550
Wire Wire Line
	7250 4800 7200 4800
Wire Wire Line
	7200 4800 7200 4850
Text HLabel 7250 4700 0    50   Output ~ 0
RX_READ
Text HLabel 2000 4800 0    50   Input ~ 0
TX_ENABLE
$Comp
L Device:R R16
U 1 1 60E455C0
P 2050 5000
F 0 "R16" H 2120 5046 50  0000 L CNN
F 1 "4k7" H 2120 4955 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1980 5000 50  0001 C CNN
F 3 "~" H 2050 5000 50  0001 C CNN
	1    2050 5000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR072
U 1 1 60E46C69
P 2050 5150
F 0 "#PWR072" H 2050 4900 50  0001 C CNN
F 1 "GND" H 2055 4977 50  0000 C CNN
F 2 "" H 2050 5150 50  0001 C CNN
F 3 "" H 2050 5150 50  0001 C CNN
	1    2050 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 4800 2050 4800
Wire Wire Line
	2050 4800 2050 4850
Wire Wire Line
	2050 4800 2000 4800
Connection ~ 2050 4800
Text Label 3600 4600 0    50   ~ 0
TX_OUT1
Text Label 3600 4700 0    50   ~ 0
TX_OUT2
Text Label 3600 4800 0    50   ~ 0
TX_OUT3
Text Label 3600 4900 0    50   ~ 0
TX_OUT4
NoConn ~ 3600 5200
NoConn ~ 3600 5300
Text Label 8250 4600 0    50   ~ 0
RX_IN1
Text Label 8250 4700 0    50   ~ 0
RX_IN2
Text Label 8250 4800 0    50   ~ 0
RX_IN3
Text Label 8250 4900 0    50   ~ 0
RX_IN4
NoConn ~ 8250 5200
NoConn ~ 8250 5300
Text Notes 2200 1450 0    50   ~ 0
IR led current resistor calculations:\n\ntarget current: I = 100mA\ninput voltage: U = 3.3V\nforward voltage: Uf = 1.7V\n\nR = (U-Uf)/I\nR = (3.3 - 1.7)/0.1 = 16ohm -> 20ohm
$Comp
L power:GND #PWR058
U 1 1 60ED3093
P 6000 3050
F 0 "#PWR058" H 6000 2800 50  0001 C CNN
F 1 "GND" H 6005 2877 50  0000 C CNN
F 2 "" H 6000 3050 50  0001 C CNN
F 3 "" H 6000 3050 50  0001 C CNN
	1    6000 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R7
U 1 1 60ED4A70
P 6000 2400
F 0 "R7" H 6070 2446 50  0000 L CNN
F 1 "10k" H 6070 2355 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5930 2400 50  0001 C CNN
F 3 "~" H 6000 2400 50  0001 C CNN
	1    6000 2400
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR050
U 1 1 60ED4A76
P 6000 2250
F 0 "#PWR050" H 6000 2100 50  0001 C CNN
F 1 "+3.3V" H 6015 2423 50  0000 C CNN
F 2 "" H 6000 2250 50  0001 C CNN
F 3 "" H 6000 2250 50  0001 C CNN
	1    6000 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 2650 6000 2600
Wire Wire Line
	6000 2600 5950 2600
Connection ~ 6000 2600
Wire Wire Line
	6000 2600 6000 2550
Text Label 5950 2600 2    50   ~ 0
RX_IN1
$Comp
L power:GND #PWR054
U 1 1 60EE410D
P 1550 3050
F 0 "#PWR054" H 1550 2800 50  0001 C CNN
F 1 "GND" H 1555 2877 50  0000 C CNN
F 2 "" H 1550 3050 50  0001 C CNN
F 3 "" H 1550 3050 50  0001 C CNN
	1    1550 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D2
U 1 1 60EE272F
P 1550 2900
F 0 "D2" V 1589 2782 50  0000 R CNN
F 1 "SFH4550" V 1498 2782 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 1550 2900 50  0001 C CNN
F 3 "~" H 1550 2900 50  0001 C CNN
	1    1550 2900
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R11
U 1 1 60EE4F46
P 1550 2600
F 0 "R11" H 1620 2646 50  0000 L CNN
F 1 "20" H 1620 2555 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1480 2600 50  0001 C CNN
F 3 "~" H 1550 2600 50  0001 C CNN
	1    1550 2600
	1    0    0    -1  
$EndComp
Text Label 1550 2450 1    50   ~ 0
TX_OUT1
$Comp
L power:GND #PWR055
U 1 1 60EF4EEA
P 2100 3050
F 0 "#PWR055" H 2100 2800 50  0001 C CNN
F 1 "GND" H 2105 2877 50  0000 C CNN
F 2 "" H 2100 3050 50  0001 C CNN
F 3 "" H 2100 3050 50  0001 C CNN
	1    2100 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D3
U 1 1 60EF4EF0
P 2100 2900
F 0 "D3" V 2139 2782 50  0000 R CNN
F 1 "SFH4550" V 2048 2782 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 2100 2900 50  0001 C CNN
F 3 "~" H 2100 2900 50  0001 C CNN
	1    2100 2900
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R12
U 1 1 60EF4EF6
P 2100 2600
F 0 "R12" H 2170 2646 50  0000 L CNN
F 1 "20" H 2170 2555 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2030 2600 50  0001 C CNN
F 3 "~" H 2100 2600 50  0001 C CNN
	1    2100 2600
	1    0    0    -1  
$EndComp
Text Label 2100 2450 1    50   ~ 0
TX_OUT2
$Comp
L power:GND #PWR056
U 1 1 60EF5BFB
P 2650 3050
F 0 "#PWR056" H 2650 2800 50  0001 C CNN
F 1 "GND" H 2655 2877 50  0000 C CNN
F 2 "" H 2650 3050 50  0001 C CNN
F 3 "" H 2650 3050 50  0001 C CNN
	1    2650 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D4
U 1 1 60EF5C01
P 2650 2900
F 0 "D4" V 2689 2782 50  0000 R CNN
F 1 "SFH4550" V 2598 2782 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 2650 2900 50  0001 C CNN
F 3 "~" H 2650 2900 50  0001 C CNN
	1    2650 2900
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R13
U 1 1 60EF5C07
P 2650 2600
F 0 "R13" H 2720 2646 50  0000 L CNN
F 1 "20" H 2720 2555 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2580 2600 50  0001 C CNN
F 3 "~" H 2650 2600 50  0001 C CNN
	1    2650 2600
	1    0    0    -1  
$EndComp
Text Label 2650 2450 1    50   ~ 0
TX_OUT3
$Comp
L power:GND #PWR057
U 1 1 60EF6854
P 3200 3050
F 0 "#PWR057" H 3200 2800 50  0001 C CNN
F 1 "GND" H 3205 2877 50  0000 C CNN
F 2 "" H 3200 3050 50  0001 C CNN
F 3 "" H 3200 3050 50  0001 C CNN
	1    3200 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D5
U 1 1 60EF685A
P 3200 2900
F 0 "D5" V 3239 2782 50  0000 R CNN
F 1 "SFH4550" V 3148 2782 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 3200 2900 50  0001 C CNN
F 3 "~" H 3200 2900 50  0001 C CNN
	1    3200 2900
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R14
U 1 1 60EF6860
P 3200 2600
F 0 "R14" H 3270 2646 50  0000 L CNN
F 1 "20" H 3270 2555 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3130 2600 50  0001 C CNN
F 3 "~" H 3200 2600 50  0001 C CNN
	1    3200 2600
	1    0    0    -1  
$EndComp
Text Label 3200 2450 1    50   ~ 0
TX_OUT4
$Comp
L Device:C C16
U 1 1 60F1A0B6
P 3950 3950
F 0 "C16" H 4065 3996 50  0000 L CNN
F 1 "100nF" H 4065 3905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3988 3800 50  0001 C CNN
F 3 "~" H 3950 3950 50  0001 C CNN
	1    3950 3950
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR063
U 1 1 60F1B962
P 3950 3800
F 0 "#PWR063" H 3950 3650 50  0001 C CNN
F 1 "+3.3V" H 3965 3973 50  0000 C CNN
F 2 "" H 3950 3800 50  0001 C CNN
F 3 "" H 3950 3800 50  0001 C CNN
	1    3950 3800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR066
U 1 1 60F1BF31
P 3950 4100
F 0 "#PWR066" H 3950 3850 50  0001 C CNN
F 1 "GND" H 3955 3927 50  0000 C CNN
F 2 "" H 3950 4100 50  0001 C CNN
F 3 "" H 3950 4100 50  0001 C CNN
	1    3950 4100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C15
U 1 1 60F1EDF8
P 8550 3900
F 0 "C15" H 8665 3946 50  0000 L CNN
F 1 "100nF" H 8665 3855 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8588 3750 50  0001 C CNN
F 3 "~" H 8550 3900 50  0001 C CNN
	1    8550 3900
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR062
U 1 1 60F1EDFE
P 8550 3750
F 0 "#PWR062" H 8550 3600 50  0001 C CNN
F 1 "+3.3V" H 8565 3923 50  0000 C CNN
F 2 "" H 8550 3750 50  0001 C CNN
F 3 "" H 8550 3750 50  0001 C CNN
	1    8550 3750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR064
U 1 1 60F1EE04
P 8550 4050
F 0 "#PWR064" H 8550 3800 50  0001 C CNN
F 1 "GND" H 8555 3877 50  0000 C CNN
F 2 "" H 8550 4050 50  0001 C CNN
F 3 "" H 8550 4050 50  0001 C CNN
	1    8550 4050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR059
U 1 1 60F34699
P 6750 3050
F 0 "#PWR059" H 6750 2800 50  0001 C CNN
F 1 "GND" H 6755 2877 50  0000 C CNN
F 2 "" H 6750 3050 50  0001 C CNN
F 3 "" H 6750 3050 50  0001 C CNN
	1    6750 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R8
U 1 1 60F3469F
P 6750 2400
F 0 "R8" H 6820 2446 50  0000 L CNN
F 1 "10k" H 6820 2355 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6680 2400 50  0001 C CNN
F 3 "~" H 6750 2400 50  0001 C CNN
	1    6750 2400
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR051
U 1 1 60F346A5
P 6750 2250
F 0 "#PWR051" H 6750 2100 50  0001 C CNN
F 1 "+3.3V" H 6765 2423 50  0000 C CNN
F 2 "" H 6750 2250 50  0001 C CNN
F 3 "" H 6750 2250 50  0001 C CNN
	1    6750 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6750 2650 6750 2600
Wire Wire Line
	6750 2600 6700 2600
Connection ~ 6750 2600
Wire Wire Line
	6750 2600 6750 2550
Text Label 6700 2600 2    50   ~ 0
RX_IN2
$Comp
L power:GND #PWR060
U 1 1 60F35A4C
P 7500 3050
F 0 "#PWR060" H 7500 2800 50  0001 C CNN
F 1 "GND" H 7505 2877 50  0000 C CNN
F 2 "" H 7500 3050 50  0001 C CNN
F 3 "" H 7500 3050 50  0001 C CNN
	1    7500 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R9
U 1 1 60F35A52
P 7500 2400
F 0 "R9" H 7570 2446 50  0000 L CNN
F 1 "10k" H 7570 2355 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7430 2400 50  0001 C CNN
F 3 "~" H 7500 2400 50  0001 C CNN
	1    7500 2400
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR052
U 1 1 60F35A58
P 7500 2250
F 0 "#PWR052" H 7500 2100 50  0001 C CNN
F 1 "+3.3V" H 7515 2423 50  0000 C CNN
F 2 "" H 7500 2250 50  0001 C CNN
F 3 "" H 7500 2250 50  0001 C CNN
	1    7500 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 2650 7500 2600
Wire Wire Line
	7500 2600 7450 2600
Connection ~ 7500 2600
Wire Wire Line
	7500 2600 7500 2550
Text Label 7450 2600 2    50   ~ 0
RX_IN3
$Comp
L power:GND #PWR061
U 1 1 60F38E59
P 8250 3050
F 0 "#PWR061" H 8250 2800 50  0001 C CNN
F 1 "GND" H 8255 2877 50  0000 C CNN
F 2 "" H 8250 3050 50  0001 C CNN
F 3 "" H 8250 3050 50  0001 C CNN
	1    8250 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R10
U 1 1 60F38E5F
P 8250 2400
F 0 "R10" H 8320 2446 50  0000 L CNN
F 1 "10k" H 8320 2355 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 8180 2400 50  0001 C CNN
F 3 "~" H 8250 2400 50  0001 C CNN
	1    8250 2400
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR053
U 1 1 60F38E65
P 8250 2250
F 0 "#PWR053" H 8250 2100 50  0001 C CNN
F 1 "+3.3V" H 8265 2423 50  0000 C CNN
F 2 "" H 8250 2250 50  0001 C CNN
F 3 "" H 8250 2250 50  0001 C CNN
	1    8250 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 2650 8250 2600
Wire Wire Line
	8250 2600 8200 2600
Connection ~ 8250 2600
Wire Wire Line
	8250 2600 8250 2550
Text Label 8200 2600 2    50   ~ 0
RX_IN4
Text Notes 2300 1900 0    100  ~ 20
Transmitters
Text Notes 7550 1900 0    100  ~ 20
Receivers
$Comp
L Device:D_Photo D6
U 1 1 60EA6CC1
P 5750 4450
F 0 "D6" V 5654 4608 50  0000 L CNN
F 1 "SFH203" V 5745 4608 50  0000 L CNN
F 2 "" H 5700 4450 50  0001 C CNN
F 3 "~" H 5700 4450 50  0001 C CNN
	1    5750 4450
	0    1    1    0   
$EndComp
$Comp
L Device:R R15
U 1 1 60EA97EA
P 5750 4800
F 0 "R15" H 5820 4846 50  0000 L CNN
F 1 "200k" H 5820 4755 50  0000 L CNN
F 2 "" V 5680 4800 50  0001 C CNN
F 3 "~" H 5750 4800 50  0001 C CNN
	1    5750 4800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR071
U 1 1 60EAB75A
P 5750 4950
F 0 "#PWR071" H 5750 4700 50  0001 C CNN
F 1 "GND" H 5755 4777 50  0000 C CNN
F 2 "" H 5750 4950 50  0001 C CNN
F 3 "" H 5750 4950 50  0001 C CNN
	1    5750 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 4550 5750 4600
Wire Wire Line
	5750 4600 5700 4600
Connection ~ 5750 4600
Wire Wire Line
	5750 4600 5750 4650
$Comp
L power:+3.3V #PWR068
U 1 1 60EC949D
P 5750 4250
F 0 "#PWR068" H 5750 4100 50  0001 C CNN
F 1 "+3.3V" H 5765 4423 50  0000 C CNN
F 2 "" H 5750 4250 50  0001 C CNN
F 3 "" H 5750 4250 50  0001 C CNN
	1    5750 4250
	1    0    0    -1  
$EndComp
NoConn ~ 8250 5100
NoConn ~ 8250 5000
NoConn ~ 3600 5100
NoConn ~ 3600 5000
$Comp
L Device:Q_Photo_NPN_EC Q3
U 1 1 60F8770C
P 5900 2850
F 0 "Q3" H 6091 2896 50  0000 L CNN
F 1 "SFH-313FA" H 6091 2805 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 6100 2950 50  0001 C CNN
F 3 "~" H 5900 2850 50  0001 C CNN
	1    5900 2850
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_Photo_NPN_EC Q4
U 1 1 60F996E5
P 6650 2850
F 0 "Q4" H 6841 2896 50  0000 L CNN
F 1 "SFH-313FA" H 6841 2805 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 6850 2950 50  0001 C CNN
F 3 "~" H 6650 2850 50  0001 C CNN
	1    6650 2850
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_Photo_NPN_EC Q5
U 1 1 60F99E21
P 7400 2850
F 0 "Q5" H 7591 2896 50  0000 L CNN
F 1 "SFH-313FA" H 7591 2805 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 7600 2950 50  0001 C CNN
F 3 "~" H 7400 2850 50  0001 C CNN
	1    7400 2850
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_Photo_NPN_EC Q6
U 1 1 60F9A2D9
P 8150 2850
F 0 "Q6" H 8341 2896 50  0000 L CNN
F 1 "SFH-313FA" H 8341 2805 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 8350 2950 50  0001 C CNN
F 3 "~" H 8150 2850 50  0001 C CNN
	1    8150 2850
	1    0    0    -1  
$EndComp
Text Notes 5100 3950 0    50   ~ 0
układ testowy, wymagane dalsze próby
$EndSCHEMATC
