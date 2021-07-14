EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 7 7
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
L MCU_ST_STM32F4:STM32F405RGTx U?
U 1 1 60060D50
P 3950 3900
AR Path="/60060D50" Ref="U?"  Part="1" 
AR Path="/6004A52B/60060D50" Ref="U?"  Part="1" 
AR Path="/6100FE40/60060D50" Ref="U8"  Part="1" 
F 0 "U8" H 4750 5800 50  0000 C CNN
F 1 "STM32F405RGTx" H 4750 5700 50  0000 C CNN
F 2 "Package_QFP:LQFP-64_10x10mm_P0.5mm" H 3350 2200 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00037051.pdf" H 3950 3900 50  0001 C CNN
	1    3950 3900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60060D56
P 3850 5800
AR Path="/60060D56" Ref="#PWR?"  Part="1" 
AR Path="/6004A52B/60060D56" Ref="#PWR?"  Part="1" 
AR Path="/6100FE40/60060D56" Ref="#PWR0116"  Part="1" 
F 0 "#PWR0116" H 3850 5550 50  0001 C CNN
F 1 "GND" H 3855 5627 50  0000 C CNN
F 2 "" H 3850 5800 50  0001 C CNN
F 3 "" H 3850 5800 50  0001 C CNN
	1    3850 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 5700 3850 5750
Wire Wire Line
	3850 5750 3950 5750
Wire Wire Line
	3950 5750 3950 5700
Wire Wire Line
	3950 5750 4050 5750
Wire Wire Line
	4050 5750 4050 5700
Connection ~ 3950 5750
Wire Wire Line
	3850 5750 3850 5800
Connection ~ 3850 5750
$Comp
L power:+3.3V #PWR?
U 1 1 60060D64
P 3750 2000
AR Path="/60060D64" Ref="#PWR?"  Part="1" 
AR Path="/6004A52B/60060D64" Ref="#PWR?"  Part="1" 
AR Path="/6100FE40/60060D64" Ref="#PWR089"  Part="1" 
F 0 "#PWR089" H 3750 1850 50  0001 C CNN
F 1 "+3.3V" H 3765 2173 50  0000 C CNN
F 2 "" H 3750 2000 50  0001 C CNN
F 3 "" H 3750 2000 50  0001 C CNN
	1    3750 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 60060D6A
P 2900 3000
AR Path="/60060D6A" Ref="C?"  Part="1" 
AR Path="/6004A52B/60060D6A" Ref="C?"  Part="1" 
AR Path="/6100FE40/60060D6A" Ref="C18"  Part="1" 
F 0 "C18" H 3015 3046 50  0000 L CNN
F 1 "2.2uF" H 3015 2955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2938 2850 50  0001 C CNN
F 3 "~" H 2900 3000 50  0001 C CNN
	1    2900 3000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 60060D70
P 2450 3000
AR Path="/60060D70" Ref="C?"  Part="1" 
AR Path="/6004A52B/60060D70" Ref="C?"  Part="1" 
AR Path="/6100FE40/60060D70" Ref="C17"  Part="1" 
F 0 "C17" H 2565 3046 50  0000 L CNN
F 1 "2.2uF" H 2565 2955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2488 2850 50  0001 C CNN
F 3 "~" H 2450 3000 50  0001 C CNN
	1    2450 3000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60060D76
P 2900 3150
AR Path="/60060D76" Ref="#PWR?"  Part="1" 
AR Path="/6004A52B/60060D76" Ref="#PWR?"  Part="1" 
AR Path="/6100FE40/60060D76" Ref="#PWR093"  Part="1" 
F 0 "#PWR093" H 2900 2900 50  0001 C CNN
F 1 "GND" H 2905 2977 50  0000 C CNN
F 2 "" H 2900 3150 50  0001 C CNN
F 3 "" H 2900 3150 50  0001 C CNN
	1    2900 3150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60060D7C
P 2450 3150
AR Path="/60060D7C" Ref="#PWR?"  Part="1" 
AR Path="/6004A52B/60060D7C" Ref="#PWR?"  Part="1" 
AR Path="/6100FE40/60060D7C" Ref="#PWR092"  Part="1" 
F 0 "#PWR092" H 2450 2900 50  0001 C CNN
F 1 "GND" H 2455 2977 50  0000 C CNN
F 2 "" H 2450 3150 50  0001 C CNN
F 3 "" H 2450 3150 50  0001 C CNN
	1    2450 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 2800 2900 2800
Wire Wire Line
	2900 2800 2900 2850
Wire Wire Line
	3250 2700 2450 2700
Wire Wire Line
	2450 2700 2450 2850
$Comp
L Device:C C?
U 1 1 60060D8C
P 2200 2500
AR Path="/60060D8C" Ref="C?"  Part="1" 
AR Path="/6004A52B/60060D8C" Ref="C?"  Part="1" 
AR Path="/6100FE40/60060D8C" Ref="C16"  Part="1" 
F 0 "C16" H 2315 2546 50  0000 L CNN
F 1 "100nF" H 2315 2455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2238 2350 50  0001 C CNN
F 3 "~" H 2200 2500 50  0001 C CNN
	1    2200 2500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60060D92
P 2200 2650
AR Path="/60060D92" Ref="#PWR?"  Part="1" 
AR Path="/6004A52B/60060D92" Ref="#PWR?"  Part="1" 
AR Path="/6100FE40/60060D92" Ref="#PWR091"  Part="1" 
F 0 "#PWR091" H 2200 2400 50  0001 C CNN
F 1 "GND" H 2205 2477 50  0000 C CNN
F 2 "" H 2200 2650 50  0001 C CNN
F 3 "" H 2200 2650 50  0001 C CNN
	1    2200 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 2300 2200 2300
Wire Wire Line
	2200 2300 2200 2350
Wire Wire Line
	2200 2300 2150 2300
Connection ~ 2200 2300
$Comp
L Device:R R?
U 1 1 60060D9D
P 2200 2100
AR Path="/60060D9D" Ref="R?"  Part="1" 
AR Path="/6004A52B/60060D9D" Ref="R?"  Part="1" 
AR Path="/6100FE40/60060D9D" Ref="R20"  Part="1" 
F 0 "R20" H 2270 2146 50  0000 L CNN
F 1 "4k7" H 2270 2055 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2130 2100 50  0001 C CNN
F 3 "~" H 2200 2100 50  0001 C CNN
	1    2200 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 2300 2200 2250
$Comp
L power:+3.3V #PWR?
U 1 1 60060DA4
P 2200 1950
AR Path="/60060DA4" Ref="#PWR?"  Part="1" 
AR Path="/6004A52B/60060DA4" Ref="#PWR?"  Part="1" 
AR Path="/6100FE40/60060DA4" Ref="#PWR088"  Part="1" 
F 0 "#PWR088" H 2200 1800 50  0001 C CNN
F 1 "+3.3V" H 2215 2123 50  0000 C CNN
F 2 "" H 2200 1950 50  0001 C CNN
F 3 "" H 2200 1950 50  0001 C CNN
	1    2200 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 2000 3750 2050
Wire Wire Line
	3750 2050 3850 2050
Wire Wire Line
	3850 2050 3850 2100
Connection ~ 3750 2050
Wire Wire Line
	3750 2050 3750 2100
Wire Wire Line
	3850 2050 3950 2050
Wire Wire Line
	3950 2050 3950 2100
Connection ~ 3850 2050
Wire Wire Line
	3950 2050 4050 2050
Wire Wire Line
	4050 2050 4050 2100
Connection ~ 3950 2050
Wire Wire Line
	4050 2050 4150 2050
Wire Wire Line
	4150 2050 4150 2100
Connection ~ 4050 2050
$Comp
L power:+3.3VADC #PWR?
U 1 1 60060DB8
P 4250 2100
AR Path="/60060DB8" Ref="#PWR?"  Part="1" 
AR Path="/6004A52B/60060DB8" Ref="#PWR?"  Part="1" 
AR Path="/6100FE40/60060DB8" Ref="#PWR090"  Part="1" 
F 0 "#PWR090" H 4400 2050 50  0001 C CNN
F 1 "+3.3VADC" H 4265 2273 50  0000 C CNN
F 2 "" H 4250 2100 50  0001 C CNN
F 3 "" H 4250 2100 50  0001 C CNN
	1    4250 2100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 60060DBE
P 8000 5400
AR Path="/60060DBE" Ref="C?"  Part="1" 
AR Path="/6004A52B/60060DBE" Ref="C?"  Part="1" 
AR Path="/6100FE40/60060DBE" Ref="C23"  Part="1" 
F 0 "C23" H 8115 5446 50  0000 L CNN
F 1 "100nF" H 8115 5355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8038 5250 50  0001 C CNN
F 3 "~" H 8000 5400 50  0001 C CNN
	1    8000 5400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60060DC4
P 8000 5550
AR Path="/60060DC4" Ref="#PWR?"  Part="1" 
AR Path="/6004A52B/60060DC4" Ref="#PWR?"  Part="1" 
AR Path="/6100FE40/60060DC4" Ref="#PWR0111"  Part="1" 
F 0 "#PWR0111" H 8000 5300 50  0001 C CNN
F 1 "GND" H 8005 5377 50  0000 C CNN
F 2 "" H 8000 5550 50  0001 C CNN
F 3 "" H 8000 5550 50  0001 C CNN
	1    8000 5550
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 60060DCA
P 8000 5250
AR Path="/60060DCA" Ref="#PWR?"  Part="1" 
AR Path="/6004A52B/60060DCA" Ref="#PWR?"  Part="1" 
AR Path="/6100FE40/60060DCA" Ref="#PWR0106"  Part="1" 
F 0 "#PWR0106" H 8000 5100 50  0001 C CNN
F 1 "+3.3V" H 8015 5423 50  0000 C CNN
F 2 "" H 8000 5250 50  0001 C CNN
F 3 "" H 8000 5250 50  0001 C CNN
	1    8000 5250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 60060DD0
P 8450 5400
AR Path="/60060DD0" Ref="C?"  Part="1" 
AR Path="/6004A52B/60060DD0" Ref="C?"  Part="1" 
AR Path="/6100FE40/60060DD0" Ref="C24"  Part="1" 
F 0 "C24" H 8565 5446 50  0000 L CNN
F 1 "100nF" H 8565 5355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8488 5250 50  0001 C CNN
F 3 "~" H 8450 5400 50  0001 C CNN
	1    8450 5400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60060DD6
P 8450 5550
AR Path="/60060DD6" Ref="#PWR?"  Part="1" 
AR Path="/6004A52B/60060DD6" Ref="#PWR?"  Part="1" 
AR Path="/6100FE40/60060DD6" Ref="#PWR0112"  Part="1" 
F 0 "#PWR0112" H 8450 5300 50  0001 C CNN
F 1 "GND" H 8455 5377 50  0000 C CNN
F 2 "" H 8450 5550 50  0001 C CNN
F 3 "" H 8450 5550 50  0001 C CNN
	1    8450 5550
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 60060DDC
P 8450 5250
AR Path="/60060DDC" Ref="#PWR?"  Part="1" 
AR Path="/6004A52B/60060DDC" Ref="#PWR?"  Part="1" 
AR Path="/6100FE40/60060DDC" Ref="#PWR0107"  Part="1" 
F 0 "#PWR0107" H 8450 5100 50  0001 C CNN
F 1 "+3.3V" H 8465 5423 50  0000 C CNN
F 2 "" H 8450 5250 50  0001 C CNN
F 3 "" H 8450 5250 50  0001 C CNN
	1    8450 5250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 60060DE2
P 8900 5400
AR Path="/60060DE2" Ref="C?"  Part="1" 
AR Path="/6004A52B/60060DE2" Ref="C?"  Part="1" 
AR Path="/6100FE40/60060DE2" Ref="C25"  Part="1" 
F 0 "C25" H 9015 5446 50  0000 L CNN
F 1 "100nF" H 9015 5355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8938 5250 50  0001 C CNN
F 3 "~" H 8900 5400 50  0001 C CNN
	1    8900 5400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60060DE8
P 8900 5550
AR Path="/60060DE8" Ref="#PWR?"  Part="1" 
AR Path="/6004A52B/60060DE8" Ref="#PWR?"  Part="1" 
AR Path="/6100FE40/60060DE8" Ref="#PWR0113"  Part="1" 
F 0 "#PWR0113" H 8900 5300 50  0001 C CNN
F 1 "GND" H 8905 5377 50  0000 C CNN
F 2 "" H 8900 5550 50  0001 C CNN
F 3 "" H 8900 5550 50  0001 C CNN
	1    8900 5550
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 60060DEE
P 8900 5250
AR Path="/60060DEE" Ref="#PWR?"  Part="1" 
AR Path="/6004A52B/60060DEE" Ref="#PWR?"  Part="1" 
AR Path="/6100FE40/60060DEE" Ref="#PWR0108"  Part="1" 
F 0 "#PWR0108" H 8900 5100 50  0001 C CNN
F 1 "+3.3V" H 8915 5423 50  0000 C CNN
F 2 "" H 8900 5250 50  0001 C CNN
F 3 "" H 8900 5250 50  0001 C CNN
	1    8900 5250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 60060DF4
P 9350 5400
AR Path="/60060DF4" Ref="C?"  Part="1" 
AR Path="/6004A52B/60060DF4" Ref="C?"  Part="1" 
AR Path="/6100FE40/60060DF4" Ref="C26"  Part="1" 
F 0 "C26" H 9465 5446 50  0000 L CNN
F 1 "100nF" H 9465 5355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 9388 5250 50  0001 C CNN
F 3 "~" H 9350 5400 50  0001 C CNN
	1    9350 5400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60060DFA
P 9350 5550
AR Path="/60060DFA" Ref="#PWR?"  Part="1" 
AR Path="/6004A52B/60060DFA" Ref="#PWR?"  Part="1" 
AR Path="/6100FE40/60060DFA" Ref="#PWR0114"  Part="1" 
F 0 "#PWR0114" H 9350 5300 50  0001 C CNN
F 1 "GND" H 9355 5377 50  0000 C CNN
F 2 "" H 9350 5550 50  0001 C CNN
F 3 "" H 9350 5550 50  0001 C CNN
	1    9350 5550
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 60060E00
P 9350 5250
AR Path="/60060E00" Ref="#PWR?"  Part="1" 
AR Path="/6004A52B/60060E00" Ref="#PWR?"  Part="1" 
AR Path="/6100FE40/60060E00" Ref="#PWR0109"  Part="1" 
F 0 "#PWR0109" H 9350 5100 50  0001 C CNN
F 1 "+3.3V" H 9365 5423 50  0000 C CNN
F 2 "" H 9350 5250 50  0001 C CNN
F 3 "" H 9350 5250 50  0001 C CNN
	1    9350 5250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 60060E06
P 9800 5400
AR Path="/60060E06" Ref="C?"  Part="1" 
AR Path="/6004A52B/60060E06" Ref="C?"  Part="1" 
AR Path="/6100FE40/60060E06" Ref="C27"  Part="1" 
F 0 "C27" H 9915 5446 50  0000 L CNN
F 1 "4.7uF" H 9915 5355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 9838 5250 50  0001 C CNN
F 3 "~" H 9800 5400 50  0001 C CNN
	1    9800 5400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60060E0C
P 9800 5550
AR Path="/60060E0C" Ref="#PWR?"  Part="1" 
AR Path="/6004A52B/60060E0C" Ref="#PWR?"  Part="1" 
AR Path="/6100FE40/60060E0C" Ref="#PWR0115"  Part="1" 
F 0 "#PWR0115" H 9800 5300 50  0001 C CNN
F 1 "GND" H 9805 5377 50  0000 C CNN
F 2 "" H 9800 5550 50  0001 C CNN
F 3 "" H 9800 5550 50  0001 C CNN
	1    9800 5550
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 60060E12
P 9800 5250
AR Path="/60060E12" Ref="#PWR?"  Part="1" 
AR Path="/6004A52B/60060E12" Ref="#PWR?"  Part="1" 
AR Path="/6100FE40/60060E12" Ref="#PWR0110"  Part="1" 
F 0 "#PWR0110" H 9800 5100 50  0001 C CNN
F 1 "+3.3V" H 9815 5423 50  0000 C CNN
F 2 "" H 9800 5250 50  0001 C CNN
F 3 "" H 9800 5250 50  0001 C CNN
	1    9800 5250
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 60060E18
P 8500 3200
AR Path="/60060E18" Ref="#PWR?"  Part="1" 
AR Path="/6004A52B/60060E18" Ref="#PWR?"  Part="1" 
AR Path="/6100FE40/60060E18" Ref="#PWR094"  Part="1" 
F 0 "#PWR094" H 8500 3050 50  0001 C CNN
F 1 "+3.3V" H 8515 3373 50  0000 C CNN
F 2 "" H 8500 3200 50  0001 C CNN
F 3 "" H 8500 3200 50  0001 C CNN
	1    8500 3200
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 60060E1E
P 8500 3750
AR Path="/60060E1E" Ref="C?"  Part="1" 
AR Path="/6004A52B/60060E1E" Ref="C?"  Part="1" 
AR Path="/6100FE40/60060E1E" Ref="C19"  Part="1" 
F 0 "C19" H 8615 3796 50  0000 L CNN
F 1 "1uF" H 8615 3705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8538 3600 50  0001 C CNN
F 3 "~" H 8500 3750 50  0001 C CNN
	1    8500 3750
	1    0    0    -1  
$EndComp
$Comp
L Device:L L?
U 1 1 60060E24
P 8500 3350
AR Path="/60060E24" Ref="L?"  Part="1" 
AR Path="/6004A52B/60060E24" Ref="L?"  Part="1" 
AR Path="/6100FE40/60060E24" Ref="L1"  Part="1" 
F 0 "L1" H 8553 3396 50  0000 L CNN
F 1 "4.7uH" H 8553 3305 50  0000 L CNN
F 2 "Inductor_SMD:L_0805_2012Metric" H 8500 3350 50  0001 C CNN
F 3 "~" H 8500 3350 50  0001 C CNN
	1    8500 3350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60060E2A
P 8500 3900
AR Path="/60060E2A" Ref="#PWR?"  Part="1" 
AR Path="/6004A52B/60060E2A" Ref="#PWR?"  Part="1" 
AR Path="/6100FE40/60060E2A" Ref="#PWR0100"  Part="1" 
F 0 "#PWR0100" H 8500 3650 50  0001 C CNN
F 1 "GND" H 8505 3727 50  0000 C CNN
F 2 "" H 8500 3900 50  0001 C CNN
F 3 "" H 8500 3900 50  0001 C CNN
	1    8500 3900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60060E30
P 8950 3900
AR Path="/60060E30" Ref="#PWR?"  Part="1" 
AR Path="/6004A52B/60060E30" Ref="#PWR?"  Part="1" 
AR Path="/6100FE40/60060E30" Ref="#PWR0101"  Part="1" 
F 0 "#PWR0101" H 8950 3650 50  0001 C CNN
F 1 "GND" H 8955 3727 50  0000 C CNN
F 2 "" H 8950 3900 50  0001 C CNN
F 3 "" H 8950 3900 50  0001 C CNN
	1    8950 3900
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 60060E36
P 8950 3750
AR Path="/60060E36" Ref="C?"  Part="1" 
AR Path="/6004A52B/60060E36" Ref="C?"  Part="1" 
AR Path="/6100FE40/60060E36" Ref="C20"  Part="1" 
F 0 "C20" H 9065 3796 50  0000 L CNN
F 1 "100nF" H 9065 3705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8988 3600 50  0001 C CNN
F 3 "~" H 8950 3750 50  0001 C CNN
	1    8950 3750
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3VADC #PWR?
U 1 1 60060E3C
P 8950 3500
AR Path="/60060E3C" Ref="#PWR?"  Part="1" 
AR Path="/6004A52B/60060E3C" Ref="#PWR?"  Part="1" 
AR Path="/6100FE40/60060E3C" Ref="#PWR099"  Part="1" 
F 0 "#PWR099" H 9100 3450 50  0001 C CNN
F 1 "+3.3VADC" H 8965 3673 50  0000 C CNN
F 2 "" H 8950 3500 50  0001 C CNN
F 3 "" H 8950 3500 50  0001 C CNN
	1    8950 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8950 3550 8950 3500
Wire Wire Line
	8950 3550 8950 3600
Connection ~ 8950 3550
Wire Wire Line
	8500 3550 8500 3600
Wire Wire Line
	8500 3500 8500 3550
Connection ~ 8500 3550
Wire Wire Line
	8500 3550 8950 3550
$Comp
L Device:Crystal Y?
U 1 1 60060E49
P 1600 3850
AR Path="/60060E49" Ref="Y?"  Part="1" 
AR Path="/6004A52B/60060E49" Ref="Y?"  Part="1" 
AR Path="/6100FE40/60060E49" Ref="Y1"  Part="1" 
F 0 "Y1" H 1600 4118 50  0000 C CNN
F 1 "8MHz" H 1600 4027 50  0000 C CNN
F 2 "Crystal:Crystal_SMD_5032-2Pin_5.0x3.2mm" H 1600 3850 50  0001 C CNN
F 3 "~" H 1600 3850 50  0001 C CNN
	1    1600 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 60060E51
P 1350 4100
AR Path="/60060E51" Ref="C?"  Part="1" 
AR Path="/6004A52B/60060E51" Ref="C?"  Part="1" 
AR Path="/6100FE40/60060E51" Ref="C21"  Part="1" 
F 0 "C21" H 1465 4146 50  0000 L CNN
F 1 "20pF" H 1465 4055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1388 3950 50  0001 C CNN
F 3 "~" H 1350 4100 50  0001 C CNN
	1    1350 4100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 60060E57
P 1850 4100
AR Path="/60060E57" Ref="C?"  Part="1" 
AR Path="/6004A52B/60060E57" Ref="C?"  Part="1" 
AR Path="/6100FE40/60060E57" Ref="C22"  Part="1" 
F 0 "C22" H 1965 4146 50  0000 L CNN
F 1 "20pF" H 1965 4055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1888 3950 50  0001 C CNN
F 3 "~" H 1850 4100 50  0001 C CNN
	1    1850 4100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60060E5D
P 1350 4250
AR Path="/60060E5D" Ref="#PWR?"  Part="1" 
AR Path="/6004A52B/60060E5D" Ref="#PWR?"  Part="1" 
AR Path="/6100FE40/60060E5D" Ref="#PWR0102"  Part="1" 
F 0 "#PWR0102" H 1350 4000 50  0001 C CNN
F 1 "GND" H 1355 4077 50  0000 C CNN
F 2 "" H 1350 4250 50  0001 C CNN
F 3 "" H 1350 4250 50  0001 C CNN
	1    1350 4250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60060E63
P 1850 4250
AR Path="/60060E63" Ref="#PWR?"  Part="1" 
AR Path="/6004A52B/60060E63" Ref="#PWR?"  Part="1" 
AR Path="/6100FE40/60060E63" Ref="#PWR0103"  Part="1" 
F 0 "#PWR0103" H 1850 4000 50  0001 C CNN
F 1 "GND" H 1855 4077 50  0000 C CNN
F 2 "" H 1850 4250 50  0001 C CNN
F 3 "" H 1850 4250 50  0001 C CNN
	1    1850 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 3850 1850 3850
Wire Wire Line
	1850 3850 1850 3950
Connection ~ 1850 3850
Wire Wire Line
	1450 3850 1350 3850
Wire Wire Line
	1350 3850 1350 3950
Connection ~ 1350 3850
Wire Wire Line
	3250 3500 1350 3500
Wire Wire Line
	1350 3500 1350 3850
Wire Wire Line
	3250 3600 1850 3600
Wire Wire Line
	1850 3600 1850 3850
$Comp
L power:+3.3V #PWR098
U 1 1 60244917
P 6900 3400
F 0 "#PWR098" H 6900 3250 50  0001 C CNN
F 1 "+3.3V" V 6915 3528 50  0000 L CNN
F 2 "" H 6900 3400 50  0001 C CNN
F 3 "" H 6900 3400 50  0001 C CNN
	1    6900 3400
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR096
U 1 1 60244911
P 6900 3300
F 0 "#PWR096" H 6900 3150 50  0001 C CNN
F 1 "+3.3V" V 6915 3428 50  0000 L CNN
F 2 "" H 6900 3300 50  0001 C CNN
F 3 "" H 6900 3300 50  0001 C CNN
	1    6900 3300
	0    1    1    0   
$EndComp
NoConn ~ 6900 3200
NoConn ~ 6900 3100
NoConn ~ 6400 3500
$Comp
L power:GND #PWR097
U 1 1 60244908
P 6400 3400
F 0 "#PWR097" H 6400 3150 50  0001 C CNN
F 1 "GND" V 6405 3272 50  0000 R CNN
F 2 "" H 6400 3400 50  0001 C CNN
F 3 "" H 6400 3400 50  0001 C CNN
	1    6400 3400
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR095
U 1 1 60244902
P 6400 3300
F 0 "#PWR095" H 6400 3050 50  0001 C CNN
F 1 "GND" V 6405 3172 50  0000 R CNN
F 2 "" H 6400 3300 50  0001 C CNN
F 3 "" H 6400 3300 50  0001 C CNN
	1    6400 3300
	0    1    1    0   
$EndComp
$Comp
L Connector_Generic:Conn_02x05_Counter_Clockwise MCU1
U 1 1 602448FA
P 6600 3300
F 0 "MCU1" H 6650 3717 50  0000 C CNN
F 1 "Conn_02x05_Counter_Clockwise" H 6650 3626 50  0000 C CNN
F 2 "Connector_IDC:IDC-Header_2x05_P2.54mm_Vertical" H 6600 3300 50  0001 C CNN
F 3 "~" H 6600 3300 50  0001 C CNN
	1    6600 3300
	1    0    0    -1  
$EndComp
Text HLabel 6400 3100 0    50   Input ~ 0
RESET
Text Label 4650 3600 0    50   ~ 0
SWDIO
Text Label 4650 3700 0    50   ~ 0
SWCLK
Text Label 6400 3200 2    50   ~ 0
SWDIO
Text Label 6900 3500 0    50   ~ 0
SWCLK
Text Notes 3550 1650 0    100  ~ 20
uController
Text HLabel 4650 2300 2    50   Input ~ 0
RF_A
Text HLabel 4650 2400 2    50   Input ~ 0
RF_B
Text HLabel 4650 2500 2    50   Output ~ 0
USART2_TX
Text HLabel 4650 2600 2    50   Input ~ 0
USART2_RX
NoConn ~ 4650 2700
NoConn ~ 4650 2800
Text HLabel 4650 2900 2    50   Input ~ 0
LB_A
Text HLabel 4650 3000 2    50   Input ~ 0
LB_B
Text HLabel 4650 3100 2    50   BiDi ~ 0
I2C3_SCL
NoConn ~ 4650 3200
NoConn ~ 4650 3300
Text HLabel 4650 3400 2    50   BiDi ~ 0
USB_DM
Text HLabel 4650 3500 2    50   BiDi ~ 0
USB_DP
Text HLabel 4650 3800 2    50   Output ~ 0
USER_LED1
Text HLabel 4650 4000 2    50   Output ~ 0
LB_IN1
Text HLabel 4650 4100 2    50   Output ~ 0
LB_IN2
Text HLabel 4650 4300 2    50   Output ~ 0
PROXIMITY_ADD0
Text HLabel 4650 4400 2    50   Output ~ 0
PROXIMITY_ADD1
Text HLabel 4650 4500 2    50   Output ~ 0
PROXIMITY_ADD2
Text HLabel 4650 4600 2    50   Input ~ 0
RB_A
Text HLabel 4650 4700 2    50   Input ~ 0
RB_B
Text HLabel 4650 4800 2    50   Output ~ 0
RB_IN1
Text HLabel 4650 4900 2    50   Output ~ 0
RB_IN2
Text HLabel 4650 5000 2    50   Output ~ 0
RF_IN1
Text HLabel 4650 5100 2    50   Output ~ 0
RF_IN2
NoConn ~ 4650 5200
NoConn ~ 4650 5300
Text HLabel 4650 5400 2    50   Output ~ 0
LF_IN1
Text HLabel 4650 5500 2    50   Output ~ 0
LF_IN2
Text HLabel 3250 3800 0    50   Input ~ 0
RECEIVER_OUT
Text HLabel 3250 4000 0    50   Input ~ 0
LINE_LL
Text HLabel 3250 4100 0    50   Input ~ 0
LINE_LM
Text HLabel 3250 4200 0    50   Input ~ 0
LINE_RM
Text HLabel 3250 4300 0    50   Input ~ 0
LINE_RR
Text HLabel 3250 4400 0    50   Input ~ 0
BATTERY_SENSE
Text HLabel 3250 4500 0    50   Input ~ 0
PROXIMITY_RX_READ
Text HLabel 3250 4600 0    50   Input ~ 0
LF_A
Text HLabel 3250 4700 0    50   Input ~ 0
LF_B
Text HLabel 3250 4800 0    50   Output ~ 0
PROXIMITY_TX_ENABLE
Text HLabel 3250 4900 0    50   BiDi ~ 0
I2C3_SDA
Text HLabel 3250 5000 0    50   Output ~ 0
USER_LED2
Text HLabel 3250 5100 0    50   Output ~ 0
USER_LED3
Text HLabel 3250 5200 0    50   Input ~ 0
USER_BUTTON
Text HLabel 3250 5300 0    50   Input ~ 0
MODULE_START
Text HLabel 3250 5400 0    50   Input ~ 0
MODULE_KILL
NoConn ~ 3250 5500
$Comp
L Device:R R22
U 1 1 60EC7763
P 6400 4900
F 0 "R22" V 6300 4750 50  0000 C CNN
F 1 "4k7" V 6300 5050 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6330 4900 50  0001 C CNN
F 3 "~" H 6400 4900 50  0001 C CNN
	1    6400 4900
	0    1    1    0   
$EndComp
$Comp
L Device:R R21
U 1 1 60EC6A3C
P 6400 4650
F 0 "R21" V 6300 4500 50  0000 C CNN
F 1 "4k7" V 6300 4800 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6330 4650 50  0001 C CNN
F 3 "~" H 6400 4650 50  0001 C CNN
	1    6400 4650
	0    1    1    0   
$EndComp
Text HLabel 6250 4900 0    50   BiDi ~ 0
I2C3_SDA
Text HLabel 6250 4650 0    50   BiDi ~ 0
I2C3_SCL
$Comp
L power:+3.3V #PWR0104
U 1 1 60ED2B0A
P 6550 4650
F 0 "#PWR0104" H 6550 4500 50  0001 C CNN
F 1 "+3.3V" V 6565 4778 50  0000 L CNN
F 2 "" H 6550 4650 50  0001 C CNN
F 3 "" H 6550 4650 50  0001 C CNN
	1    6550 4650
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR0105
U 1 1 60ED346A
P 6550 4900
F 0 "#PWR0105" H 6550 4750 50  0001 C CNN
F 1 "+3.3V" V 6565 5028 50  0000 L CNN
F 2 "" H 6550 4900 50  0001 C CNN
F 3 "" H 6550 4900 50  0001 C CNN
	1    6550 4900
	0    1    1    0   
$EndComp
Text Label 3250 2500 2    50   ~ 0
BOOT0
Text Label 4650 4200 0    50   ~ 0
BOOT1
$Comp
L Switch:SW_SPST SW2
U 1 1 60F020E5
P 7000 1550
F 0 "SW2" H 7200 1800 50  0000 C CNN
F 1 "SW_SPST" H 7200 1700 50  0000 C CNN
F 2 "Button_Switch_THT:SW_DIP_SPSTx01_Slide_9.78x4.72mm_W7.62mm_P2.54mm" H 7000 1550 50  0001 C CNN
F 3 "~" H 7000 1550 50  0001 C CNN
	1    7000 1550
	1    0    0    -1  
$EndComp
Text Label 7300 1550 0    50   ~ 0
BOOT0
$Comp
L power:GND #PWR086
U 1 1 60F0A5CB
P 7250 1600
F 0 "#PWR086" H 7250 1350 50  0001 C CNN
F 1 "GND" H 7255 1427 50  0000 C CNN
F 2 "" H 7250 1600 50  0001 C CNN
F 3 "" H 7250 1600 50  0001 C CNN
	1    7250 1600
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR085
U 1 1 60F0A9B3
P 6750 1200
F 0 "#PWR085" H 6750 1050 50  0001 C CNN
F 1 "+3.3V" H 6765 1373 50  0000 C CNN
F 2 "" H 6750 1200 50  0001 C CNN
F 3 "" H 6750 1200 50  0001 C CNN
	1    6750 1200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R19
U 1 1 60F0B040
P 6750 1350
F 0 "R19" H 6820 1396 50  0000 L CNN
F 1 "4k7" H 6820 1305 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6680 1350 50  0001 C CNN
F 3 "~" H 6750 1350 50  0001 C CNN
	1    6750 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6750 1500 6750 1550
Wire Wire Line
	6750 1550 6800 1550
Wire Wire Line
	7200 1550 7250 1550
Wire Wire Line
	7250 1550 7250 1600
Connection ~ 7250 1550
Wire Wire Line
	7250 1550 7300 1550
Text Label 7850 1550 0    50   ~ 0
BOOT1
$Comp
L power:GND #PWR087
U 1 1 60F14427
P 7800 1600
F 0 "#PWR087" H 7800 1350 50  0001 C CNN
F 1 "GND" H 7805 1427 50  0000 C CNN
F 2 "" H 7800 1600 50  0001 C CNN
F 3 "" H 7800 1600 50  0001 C CNN
	1    7800 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7800 1600 7800 1550
Wire Wire Line
	7800 1550 7850 1550
$Comp
L power:GND #PWR?
U 1 1 60FDEFA0
P 1700 2350
AR Path="/60FDEFA0" Ref="#PWR?"  Part="1" 
AR Path="/6004A52B/60FDEFA0" Ref="#PWR?"  Part="1" 
AR Path="/6100FE40/60FDEFA0" Ref="#PWR0136"  Part="1" 
F 0 "#PWR0136" H 1700 2100 50  0001 C CNN
F 1 "GND" H 1705 2177 50  0000 C CNN
F 2 "" H 1700 2350 50  0001 C CNN
F 3 "" H 1700 2350 50  0001 C CNN
	1    1700 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 2350 1700 2300
Wire Wire Line
	1700 2300 1750 2300
$Comp
L Switch:SW_Push SW5
U 1 1 60FE5546
P 1950 2300
F 0 "SW5" H 1950 2585 50  0000 C CNN
F 1 "SW_Push" H 1950 2494 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_SPST_FSMSM" H 1950 2500 50  0001 C CNN
F 3 "~" H 1950 2500 50  0001 C CNN
	1    1950 2300
	1    0    0    -1  
$EndComp
$EndSCHEMATC
