EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 6 8
Title "Sneak100 Main Board V1.1"
Date "November 2021"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:+3.3V #PWR?
U 1 1 610BA2BC
P 5200 3550
AR Path="/60E04A74/610BA2BC" Ref="#PWR?"  Part="1" 
AR Path="/60E049FE/610BA2BC" Ref="#PWR081"  Part="1" 
F 0 "#PWR081" H 5200 3400 50  0001 C CNN
F 1 "+3.3V" V 5215 3678 50  0000 L CNN
F 2 "" H 5200 3550 50  0001 C CNN
F 3 "" H 5200 3550 50  0001 C CNN
	1    5200 3550
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 610BA2C2
P 5700 3550
AR Path="/60E04A74/610BA2C2" Ref="#PWR?"  Part="1" 
AR Path="/60E049FE/610BA2C2" Ref="#PWR082"  Part="1" 
F 0 "#PWR082" H 5700 3400 50  0001 C CNN
F 1 "+3.3V" V 5715 3678 50  0000 L CNN
F 2 "" H 5700 3550 50  0001 C CNN
F 3 "" H 5700 3550 50  0001 C CNN
	1    5700 3550
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 610BA2C8
P 5200 4150
AR Path="/60E04A74/610BA2C8" Ref="#PWR?"  Part="1" 
AR Path="/60E049FE/610BA2C8" Ref="#PWR085"  Part="1" 
F 0 "#PWR085" H 5200 4000 50  0001 C CNN
F 1 "+3.3V" V 5215 4278 50  0000 L CNN
F 2 "" H 5200 4150 50  0001 C CNN
F 3 "" H 5200 4150 50  0001 C CNN
	1    5200 4150
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 610BA2CE
P 5700 4150
AR Path="/60E04A74/610BA2CE" Ref="#PWR?"  Part="1" 
AR Path="/60E049FE/610BA2CE" Ref="#PWR086"  Part="1" 
F 0 "#PWR086" H 5700 4000 50  0001 C CNN
F 1 "+3.3V" V 5715 4278 50  0000 L CNN
F 2 "" H 5700 4150 50  0001 C CNN
F 3 "" H 5700 4150 50  0001 C CNN
	1    5700 4150
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 610BA2D4
P 5700 4050
AR Path="/60E04A74/610BA2D4" Ref="#PWR?"  Part="1" 
AR Path="/60E049FE/610BA2D4" Ref="#PWR084"  Part="1" 
F 0 "#PWR084" H 5700 3800 50  0001 C CNN
F 1 "GND" V 5705 3922 50  0000 R CNN
F 2 "" H 5700 4050 50  0001 C CNN
F 3 "" H 5700 4050 50  0001 C CNN
	1    5700 4050
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 610BA2DA
P 5200 4050
AR Path="/60E04A74/610BA2DA" Ref="#PWR?"  Part="1" 
AR Path="/60E049FE/610BA2DA" Ref="#PWR083"  Part="1" 
F 0 "#PWR083" H 5200 3800 50  0001 C CNN
F 1 "GND" V 5205 3922 50  0000 R CNN
F 2 "" H 5200 4050 50  0001 C CNN
F 3 "" H 5200 4050 50  0001 C CNN
	1    5200 4050
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 610BA2E0
P 5700 3450
AR Path="/60E04A74/610BA2E0" Ref="#PWR?"  Part="1" 
AR Path="/60E049FE/610BA2E0" Ref="#PWR080"  Part="1" 
F 0 "#PWR080" H 5700 3200 50  0001 C CNN
F 1 "GND" V 5705 3322 50  0000 R CNN
F 2 "" H 5700 3450 50  0001 C CNN
F 3 "" H 5700 3450 50  0001 C CNN
	1    5700 3450
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 610BA2E6
P 5200 3450
AR Path="/60E04A74/610BA2E6" Ref="#PWR?"  Part="1" 
AR Path="/60E049FE/610BA2E6" Ref="#PWR079"  Part="1" 
F 0 "#PWR079" H 5200 3200 50  0001 C CNN
F 1 "GND" V 5205 3322 50  0000 R CNN
F 2 "" H 5200 3450 50  0001 C CNN
F 3 "" H 5200 3450 50  0001 C CNN
	1    5200 3450
	0    1    1    0   
$EndComp
Text HLabel 5200 3650 0    50   Output ~ 0
READ_LL
Text HLabel 5700 3650 2    50   Output ~ 0
READ_FL
Text HLabel 5200 4250 0    50   Output ~ 0
READ_FR
Text HLabel 5700 4250 2    50   Output ~ 0
READ_RR
Text Notes 4800 2750 0    100  ~ 20
Proximity sensors
Text Notes 5200 2950 0    50   ~ 10
4x Proxima
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J11
U 1 1 6112C7F5
P 5400 3550
F 0 "J11" H 5450 3867 50  0000 C CNN
F 1 "Conn_02x03_Odd_Even" H 5450 3776 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x03_P2.54mm_Horizontal" H 5400 3550 50  0001 C CNN
F 3 "~" H 5400 3550 50  0001 C CNN
	1    5400 3550
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J12
U 1 1 6112D481
P 5400 4150
F 0 "J12" H 5450 4467 50  0000 C CNN
F 1 "Conn_02x03_Odd_Even" H 5450 4376 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x03_P2.54mm_Horizontal" H 5400 4150 50  0001 C CNN
F 3 "~" H 5400 4150 50  0001 C CNN
	1    5400 4150
	1    0    0    -1  
$EndComp
$EndSCHEMATC
