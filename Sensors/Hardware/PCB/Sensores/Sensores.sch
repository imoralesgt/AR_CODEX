EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Control PID y adquisicion de datos de sensores"
Date "jeu. 02 avril 2015"
Rev "V1.0"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 "Diseño sensores : Saul Lopez"
$EndDescr
Text Label 8700 1100 0    60   ~ 0
1(Tx)
Text Label 8700 1200 0    60   ~ 0
0(Rx)
Text Label 8700 1300 0    60   ~ 0
Reset
Text Label 8700 1500 0    60   ~ 0
2
Text Label 8700 1600 0    60   ~ 0
3(**)
Text Label 8700 1700 0    60   ~ 0
I2C:SDA
Text Label 8700 1800 0    60   ~ 0
I2C:SCL
Text Label 8700 1900 0    60   ~ 0
6(**)
Text Label 8700 2000 0    60   ~ 0
7
Text Label 8700 2100 0    60   ~ 0
8
Text Label 8700 2200 0    60   ~ 0
9(**)
Text Label 8700 2300 0    60   ~ 0
10(**/SS)
Text Label 8700 2400 0    60   ~ 0
11(**/MOSI)
Text Label 8700 2500 0    60   ~ 0
12(MISO)
Text Label 10550 2500 0    60   ~ 0
13(SCK)
Text Label 10550 2200 0    60   ~ 0
A0:MSP-2107
Text Label 10550 2100 0    60   ~ 0
A1:MPX10DP
Text Label 10550 2000 0    60   ~ 0
A2
Text Label 10550 1900 0    60   ~ 0
A3
Text Label 10550 1800 0    60   ~ 0
A4
Text Label 10550 1700 0    60   ~ 0
A5
Text Label 10550 1600 0    60   ~ 0
A6
Text Label 10550 1500 0    60   ~ 0
A7
Text Label 10550 2300 0    60   ~ 0
AREF
Text Label 10550 1300 0    60   ~ 0
Reset
Text Notes 10800 1000 0    60   ~ 0
Holes
Text Notes 8500 575  0    60   ~ 0
Shield for Arduino Nano
Text Label 10250 950  1    60   ~ 0
Vin
Wire Notes Line
	8475 650  9675 650 
Wire Notes Line
	9675 650  9675 475 
$Comp
L Connector_Generic:Conn_01x01 P3
U 1 1 56D73ADD
P 10800 650
F 0 "P3" V 10900 650 50  0000 C CNN
F 1 "CONN_01X01" V 10900 650 50  0001 C CNN
F 2 "Socket_Arduino_Nano:1pin_Nano" H 10800 650 50  0001 C CNN
F 3 "" H 10800 650 50  0000 C CNN
	1    10800 650 
	0    -1   -1   0   
$EndComp
NoConn ~ 10800 850 
$Comp
L Connector_Generic:Conn_01x01 P4
U 1 1 56D73D86
P 10900 650
F 0 "P4" V 11000 650 50  0000 C CNN
F 1 "CONN_01X01" V 11000 650 50  0001 C CNN
F 2 "Socket_Arduino_Nano:1pin_Nano" H 10900 650 50  0001 C CNN
F 3 "" H 10900 650 50  0000 C CNN
	1    10900 650 
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 P5
U 1 1 56D73DAE
P 11000 650
F 0 "P5" V 11100 650 50  0000 C CNN
F 1 "CONN_01X01" V 11100 650 50  0001 C CNN
F 2 "Socket_Arduino_Nano:1pin_Nano" H 11000 650 50  0001 C CNN
F 3 "" H 11000 650 50  0000 C CNN
	1    11000 650 
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 P6
U 1 1 56D73DD9
P 11100 650
F 0 "P6" V 11200 650 50  0000 C CNN
F 1 "CONN_01X01" V 11200 650 50  0001 C CNN
F 2 "Socket_Arduino_Nano:1pin_Nano" H 11100 650 50  0001 C CNN
F 3 "" H 11100 650 50  0000 C CNN
	1    11100 650 
	0    -1   -1   0   
$EndComp
NoConn ~ 10900 850 
NoConn ~ 11000 850 
NoConn ~ 11100 850 
$Comp
L Connector_Generic:Conn_01x15 P1
U 1 1 56D73FAC
P 9550 1800
F 0 "P1" H 9550 2600 50  0000 C CNN
F 1 "Digital" V 9650 1800 50  0000 C CNN
F 2 "Socket_Arduino_Nano:Socket_Strip_Arduino_1x15" H 9550 1800 50  0001 C CNN
F 3 "" H 9550 1800 50  0000 C CNN
	1    9550 1800
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x15 P2
U 1 1 56D740C7
P 9950 1800
F 0 "P2" H 9950 2600 50  0000 C CNN
F 1 "Analog" V 10050 1800 50  0000 C CNN
F 2 "Socket_Arduino_Nano:Socket_Strip_Arduino_1x15" H 9950 1800 50  0001 C CNN
F 3 "" H 9950 1800 50  0000 C CNN
	1    9950 1800
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR01
U 1 1 56D7422C
P 9250 2600
F 0 "#PWR01" H 9250 2350 50  0001 C CNN
F 1 "GND" H 9250 2450 50  0000 C CNN
F 2 "" H 9250 2600 50  0000 C CNN
F 3 "" H 9250 2600 50  0000 C CNN
	1    9250 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	9350 1400 9250 1400
Wire Wire Line
	9250 1400 9250 2600
Wire Wire Line
	9350 1100 8700 1100
Wire Wire Line
	8700 1200 9350 1200
Wire Wire Line
	9350 1300 8700 1300
Wire Wire Line
	8700 1500 9350 1500
Wire Wire Line
	9350 1600 8700 1600
Wire Wire Line
	8700 1700 9350 1700
Wire Wire Line
	9350 1800 8700 1800
Wire Wire Line
	8700 1900 9350 1900
Wire Wire Line
	9350 2000 8700 2000
Wire Wire Line
	8700 2100 9350 2100
Wire Wire Line
	9350 2200 8700 2200
Wire Wire Line
	8700 2300 9350 2300
Wire Wire Line
	9350 2400 8700 2400
Wire Wire Line
	8700 2500 9350 2500
$Comp
L power:GND #PWR02
U 1 1 56D746ED
P 10250 2600
F 0 "#PWR02" H 10250 2350 50  0001 C CNN
F 1 "GND" H 10250 2450 50  0000 C CNN
F 2 "" H 10250 2600 50  0000 C CNN
F 3 "" H 10250 2600 50  0000 C CNN
	1    10250 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	10250 2600 10250 1200
Wire Wire Line
	10250 1200 10150 1200
Wire Wire Line
	10150 1100 10250 1100
Wire Wire Line
	10250 1100 10250 950 
$Comp
L power:+5V #PWR03
U 1 1 56D747E8
P 10350 950
F 0 "#PWR03" H 10350 800 50  0001 C CNN
F 1 "+5V" V 10350 1150 28  0000 C CNN
F 2 "" H 10350 950 50  0000 C CNN
F 3 "" H 10350 950 50  0000 C CNN
	1    10350 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	10350 950  10350 1400
Wire Wire Line
	10350 1400 10150 1400
$Comp
L power:+3V3 #PWR04
U 1 1 56D74854
P 10450 950
F 0 "#PWR04" H 10450 800 50  0001 C CNN
F 1 "+3.3V" V 10450 1150 28  0000 C CNN
F 2 "" H 10450 950 50  0000 C CNN
F 3 "" H 10450 950 50  0000 C CNN
	1    10450 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	10450 950  10450 2400
Wire Wire Line
	10450 2400 10150 2400
Wire Wire Line
	10550 1300 10150 1300
Wire Wire Line
	10150 1500 10550 1500
Wire Wire Line
	10550 1600 10150 1600
Wire Wire Line
	10550 1700 10150 1700
Wire Wire Line
	10150 1800 10550 1800
Wire Wire Line
	10550 1900 10150 1900
Wire Wire Line
	10550 2000 10150 2000
Wire Wire Line
	10150 2100 10550 2100
Wire Wire Line
	10550 2200 10150 2200
Wire Wire Line
	10550 2300 10150 2300
Wire Wire Line
	10150 2500 10550 2500
Wire Notes Line
	11200 1050 10650 1050
Wire Notes Line
	10650 1050 10650 500 
Wire Notes Line
	11200 2850 8450 2850
Wire Notes Line
	8450 2850 8450 500 
Text Notes 9650 1100 0    60   ~ 0
1
$Comp
L Amplifier_Operational:LM324 U1
U 3 1 5E92C446
P 2600 2050
F 0 "U1" H 2600 2417 50  0000 C CNN
F 1 "LM324" H 2600 2326 50  0000 C CNN
F 2 "" H 2550 2150 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2902-n.pdf" H 2650 2250 50  0001 C CNN
	3    2600 2050
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:LM324 U1
U 1 1 5E9300AF
P 5650 1000
F 0 "U1" H 5650 1367 50  0000 C CNN
F 1 "LM324" H 5650 1276 50  0000 C CNN
F 2 "" H 5600 1100 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2902-n.pdf" H 5700 1200 50  0001 C CNN
	1    5650 1000
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:LM324 U1
U 2 1 5E9312EE
P 5650 2250
F 0 "U1" H 5650 1883 50  0000 C CNN
F 1 "LM324" H 5650 1974 50  0000 C CNN
F 2 "" H 5600 2350 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2902-n.pdf" H 5700 2450 50  0001 C CNN
	2    5650 2250
	1    0    0    1   
$EndComp
$Comp
L Amplifier_Operational:LM324 U1
U 4 1 5E932DB1
P 7150 1600
F 0 "U1" H 7150 1967 50  0000 C CNN
F 1 "LM324" H 7150 1876 50  0000 C CNN
F 2 "" H 7100 1700 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2902-n.pdf" H 7200 1800 50  0001 C CNN
	4    7150 1600
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5E934850
P 1150 1550
F 0 "R?" H 1220 1596 50  0000 L CNN
F 1 "2k2" H 1220 1505 50  0000 L CNN
F 2 "" V 1080 1550 50  0001 C CNN
F 3 "~" H 1150 1550 50  0001 C CNN
	1    1150 1550
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR?
U 1 1 5E9357F2
P 1150 850
F 0 "#PWR?" H 1150 700 50  0001 C CNN
F 1 "+12V" H 1165 1023 50  0000 C CNN
F 2 "" H 1150 850 50  0001 C CNN
F 3 "" H 1150 850 50  0001 C CNN
	1    1150 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 1700 1150 1950
$Comp
L power:GND #PWR?
U 1 1 5E939024
P 1150 2650
F 0 "#PWR?" H 1150 2400 50  0001 C CNN
F 1 "GND" H 1155 2477 50  0000 C CNN
F 2 "" H 1150 2650 50  0001 C CNN
F 3 "" H 1150 2650 50  0001 C CNN
	1    1150 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 2650 1150 2550
Connection ~ 1150 1950
Wire Wire Line
	1150 1950 1150 2250
$Comp
L Transistor_BJT:2N3904 Q?
U 1 1 5E93AA28
P 3300 2050
F 0 "Q?" H 3490 2096 50  0000 L CNN
F 1 "2N3904" H 3490 2005 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 3500 1975 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3904.pdf" H 3300 2050 50  0001 L CNN
	1    3300 2050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5E93BE01
P 2100 2600
F 0 "R?" H 2170 2646 50  0000 L CNN
F 1 "1k5" H 2170 2555 50  0000 L CNN
F 2 "" V 2030 2600 50  0001 C CNN
F 3 "~" H 2100 2600 50  0001 C CNN
	1    2100 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 2150 2300 2150
$Comp
L power:GND #PWR?
U 1 1 5E93DF17
P 2100 2850
F 0 "#PWR?" H 2100 2600 50  0001 C CNN
F 1 "GND" H 2105 2677 50  0000 C CNN
F 2 "" H 2100 2850 50  0001 C CNN
F 3 "" H 2100 2850 50  0001 C CNN
	1    2100 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 2150 2100 2350
Wire Wire Line
	3100 2050 2900 2050
Wire Wire Line
	3400 2250 3400 2350
Wire Wire Line
	3400 2350 2100 2350
Connection ~ 2100 2350
Wire Wire Line
	2100 2350 2100 2450
Text GLabel 5100 900  0    50   Input ~ 0
-OutputMPS2107
Text GLabel 5100 2350 0    50   Input ~ 0
+OutputMPS2107
Wire Wire Line
	5350 900  5100 900 
Text GLabel 1750 1300 0    39   Input ~ 0
+OutputADP1101
Wire Wire Line
	1150 1950 2300 1950
Text GLabel 1750 1000 0    39   Input ~ 0
-OutputADP1101
$Comp
L Device:R R?
U 1 1 5E96B46E
P 6050 1200
F 0 "R?" H 6120 1246 50  0000 L CNN
F 1 "1k" H 6120 1155 50  0000 L CNN
F 2 "" V 5980 1200 50  0001 C CNN
F 3 "~" H 6050 1200 50  0001 C CNN
	1    6050 1200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5E96B7D0
P 6050 2050
F 0 "R?" H 6120 2096 50  0000 L CNN
F 1 "1k" H 6120 2005 50  0000 L CNN
F 2 "" V 5980 2050 50  0001 C CNN
F 3 "~" H 6050 2050 50  0001 C CNN
	1    6050 2050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5E96C15B
P 6450 1000
F 0 "R?" V 6243 1000 50  0000 C CNN
F 1 "10k" V 6334 1000 50  0000 C CNN
F 2 "" V 6380 1000 50  0001 C CNN
F 3 "~" H 6450 1000 50  0001 C CNN
	1    6450 1000
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5E96C6BC
P 7150 1000
F 0 "R?" V 6943 1000 50  0000 C CNN
F 1 "10k" V 7034 1000 50  0000 C CNN
F 2 "" V 7080 1000 50  0001 C CNN
F 3 "~" H 7150 1000 50  0001 C CNN
	1    7150 1000
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5E96CADD
P 6400 2250
F 0 "R?" V 6193 2250 50  0000 C CNN
F 1 "10k" V 6284 2250 50  0000 C CNN
F 2 "" V 6330 2250 50  0001 C CNN
F 3 "~" H 6400 2250 50  0001 C CNN
	1    6400 2250
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5E96CEF9
P 6700 2450
F 0 "R?" H 6630 2404 50  0000 R CNN
F 1 "10k" H 6630 2495 50  0000 R CNN
F 2 "" V 6630 2450 50  0001 C CNN
F 3 "~" H 6700 2450 50  0001 C CNN
	1    6700 2450
	-1   0    0    1   
$EndComp
Wire Wire Line
	6550 2250 6700 2250
Wire Wire Line
	6700 2250 6700 2300
Wire Wire Line
	6850 1700 6700 1700
Wire Wire Line
	6700 1700 6700 2250
Connection ~ 6700 2250
Wire Wire Line
	6700 1500 6700 1000
Wire Wire Line
	6700 1000 6600 1000
Connection ~ 6700 1000
Wire Wire Line
	6700 1500 6850 1500
Wire Wire Line
	6700 1000 7000 1000
Wire Wire Line
	7300 1000 7600 1000
Wire Wire Line
	7600 1000 7600 1600
Wire Wire Line
	7600 1600 7450 1600
Wire Wire Line
	6300 1000 6050 1000
Wire Wire Line
	6050 1050 6050 1000
Connection ~ 6050 1000
Wire Wire Line
	6050 1000 5950 1000
Wire Wire Line
	6050 2200 6050 2250
Wire Wire Line
	6250 2250 6050 2250
$Comp
L Device:R_POT RV?
U 1 1 5E982248
P 5800 1600
F 0 "RV?" H 5731 1646 50  0000 R CNN
F 1 "5k" H 5731 1555 50  0000 R CNN
F 2 "" H 5800 1600 50  0001 C CNN
F 3 "~" H 5800 1600 50  0001 C CNN
	1    5800 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 1450 5800 1350
Wire Wire Line
	5800 1350 6050 1350
Wire Wire Line
	5250 1350 5250 1100
Wire Wire Line
	5250 1100 5350 1100
Wire Wire Line
	5100 2350 5350 2350
Wire Wire Line
	5350 2150 5200 2150
Wire Wire Line
	5200 2150 5200 1800
Wire Wire Line
	5200 1800 6050 1800
Wire Wire Line
	6050 1800 6050 1900
Wire Wire Line
	5950 1600 6050 1600
Wire Wire Line
	6050 1600 6050 1800
Connection ~ 6050 1800
Wire Wire Line
	5950 2250 6050 2250
Connection ~ 6050 2250
$Comp
L Device:R_POT RV?
U 1 1 5E997BAF
P 7250 2450
F 0 "RV?" H 7180 2404 50  0000 R CNN
F 1 "100k" H 7180 2495 50  0000 R CNN
F 2 "" H 7250 2450 50  0001 C CNN
F 3 "~" H 7250 2450 50  0001 C CNN
	1    7250 2450
	-1   0    0    1   
$EndComp
$Comp
L power:-12V #PWR?
U 1 1 5E998D94
P 7250 2150
F 0 "#PWR?" H 7250 2250 50  0001 C CNN
F 1 "-12V" H 7265 2323 50  0000 C CNN
F 2 "" H 7250 2150 50  0001 C CNN
F 3 "" H 7250 2150 50  0001 C CNN
	1    7250 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 2150 7250 2300
$Comp
L power:GND #PWR?
U 1 1 5E99C72C
P 7250 2700
F 0 "#PWR?" H 7250 2450 50  0001 C CNN
F 1 "GND" H 7255 2527 50  0000 C CNN
F 2 "" H 7250 2700 50  0001 C CNN
F 3 "" H 7250 2700 50  0001 C CNN
	1    7250 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 2700 7250 2600
Wire Wire Line
	6700 2600 6700 2750
Wire Wire Line
	6700 2750 6950 2750
Wire Wire Line
	6950 2750 6950 2450
Wire Wire Line
	6950 2450 7100 2450
$Comp
L Amplifier_Operational:LM324 U1
U 5 1 5E9AFCEF
P 8050 2150
F 0 "U1" H 8008 2196 50  0000 L CNN
F 1 "LM324" H 8008 2105 50  0000 L CNN
F 2 "" H 8000 2250 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2902-n.pdf" H 8100 2350 50  0001 C CNN
	5    8050 2150
	1    0    0    -1  
$EndComp
Wire Notes Line
	7750 1150 8400 1150
Wire Notes Line
	7750 1850 6900 1850
Wire Notes Line
	4300 600  4300 3150
Wire Notes Line
	6900 1850 6900 3150
Text Notes 4350 3050 0    89   Italic 18
AMPLIFICADOR DE INSTRUMENTACION
Text Notes 2500 2900 0    89   Italic 18
FUENTE DE CORRIENTE
Text Notes 2500 3100 0    89   Italic 18
Y SENSOR MSP-2107
Wire Notes Line
	2400 3150 2400 2650
Wire Notes Line
	2400 2650 4300 2650
Wire Notes Line
	4300 2850 6900 2850
Text Notes 7550 3050 2    73   Italic 0
V_Offset
Text Notes 8350 2550 1    73   Italic 0
ALIMENTACION
$Comp
L power:+12V #PWR?
U 1 1 5EA23918
P 7950 1700
F 0 "#PWR?" H 7950 1550 50  0001 C CNN
F 1 "+12V" H 8050 1800 50  0000 C CNN
F 2 "" H 7950 1700 50  0001 C CNN
F 3 "" H 7950 1700 50  0001 C CNN
	1    7950 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7950 1700 7950 1850
$Comp
L power:-12V #PWR?
U 1 1 5EA274A7
P 7950 2600
F 0 "#PWR?" H 7950 2700 50  0001 C CNN
F 1 "-12V" H 7850 2700 50  0000 C CNN
F 2 "" H 7950 2600 50  0001 C CNN
F 3 "" H 7950 2600 50  0001 C CNN
	1    7950 2600
	-1   0    0    1   
$EndComp
Wire Wire Line
	7950 2450 7950 2600
$Comp
L Connector:RJ45 J1
U 1 1 5E946656
P 1300 4050
F 0 "J1" H 1357 4717 50  0000 C CNN
F 1 "RJ45" H 1357 4626 50  0000 C CNN
F 2 "" V 1300 4075 50  0001 C CNN
F 3 "~" V 1300 4075 50  0001 C CNN
	1    1300 4050
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR?
U 1 1 5E95752A
P 1850 3400
F 0 "#PWR?" H 1850 3250 50  0001 C CNN
F 1 "+12V" H 1865 3573 50  0000 C CNN
F 2 "" H 1850 3400 50  0001 C CNN
F 3 "" H 1850 3400 50  0001 C CNN
	1    1850 3400
	1    0    0    -1  
$EndComp
$Comp
L power:-12V #PWR?
U 1 1 5E957E28
P 2050 3400
F 0 "#PWR?" H 2050 3500 50  0001 C CNN
F 1 "-12V" H 2065 3573 50  0000 C CNN
F 2 "" H 2050 3400 50  0001 C CNN
F 3 "" H 2050 3400 50  0001 C CNN
	1    2050 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 3400 1850 3650
Wire Wire Line
	1850 3650 1700 3650
$Comp
L power:GND #PWR?
U 1 1 5E965AE2
P 2550 4100
F 0 "#PWR?" H 2550 3850 50  0001 C CNN
F 1 "GND" H 2555 3927 50  0000 C CNN
F 2 "" H 2550 4100 50  0001 C CNN
F 3 "" H 2550 4100 50  0001 C CNN
	1    2550 4100
	1    0    0    -1  
$EndComp
Text Label 2050 4050 0    50   ~ 0
I2C:SCL
Wire Wire Line
	2050 4050 1950 4050
Wire Wire Line
	1700 4150 1950 4150
Wire Wire Line
	1950 4150 1950 4050
Connection ~ 1950 4050
Wire Wire Line
	1950 4050 1700 4050
Text Label 2050 4250 0    50   ~ 0
I2C:SDA
Wire Wire Line
	1950 4250 1700 4250
Wire Wire Line
	1700 4350 1950 4350
Wire Wire Line
	1950 4350 1950 4250
Wire Wire Line
	2050 4250 1950 4250
Connection ~ 1950 4250
Wire Wire Line
	2050 3400 2050 3850
Wire Wire Line
	2050 3850 1700 3850
Wire Wire Line
	1700 3750 2550 3750
Wire Wire Line
	2550 3750 2550 3950
Wire Wire Line
	2550 3950 1700 3950
Text Notes 900  4700 0    89   ~ 18
INTERFAZ DE COMUNICACION
Wire Wire Line
	2550 4100 2550 3950
Connection ~ 2550 3950
$Comp
L Amplifier_Operational:LM324 U2
U 1 1 5E9B90AC
P 1850 5200
F 0 "U2" H 1850 5567 50  0000 C CNN
F 1 "LM324" H 1850 5476 50  0000 C CNN
F 2 "" H 1800 5300 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2902-n.pdf" H 1900 5400 50  0001 C CNN
	1    1850 5200
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:LM324 U2
U 2 1 5E9BA2E6
P 1850 6700
F 0 "U2" H 1850 6333 50  0000 C CNN
F 1 "LM324" H 1850 6424 50  0000 C CNN
F 2 "" H 1800 6800 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2902-n.pdf" H 1900 6900 50  0001 C CNN
	2    1850 6700
	1    0    0    1   
$EndComp
$Comp
L Amplifier_Operational:LM324 U2
U 4 1 5E9BB48C
P 3400 5950
F 0 "U2" H 3400 6317 50  0000 C CNN
F 1 "LM324" H 3400 6226 50  0000 C CNN
F 2 "" H 3350 6050 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2902-n.pdf" H 3450 6150 50  0001 C CNN
	4    3400 5950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5E9D1A4B
P 2300 5450
F 0 "R?" H 2370 5496 50  0000 L CNN
F 1 "1k" H 2370 5405 50  0000 L CNN
F 2 "" V 2230 5450 50  0001 C CNN
F 3 "~" H 2300 5450 50  0001 C CNN
	1    2300 5450
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5E9D20A9
P 2300 6500
F 0 "R?" H 2370 6546 50  0000 L CNN
F 1 "1k" H 2370 6455 50  0000 L CNN
F 2 "" V 2230 6500 50  0001 C CNN
F 3 "~" H 2300 6500 50  0001 C CNN
	1    2300 6500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5E9D2721
P 2950 7000
F 0 "R?" H 3020 7046 50  0000 L CNN
F 1 "10k" H 3020 6955 50  0000 L CNN
F 2 "" V 2880 7000 50  0001 C CNN
F 3 "~" H 2950 7000 50  0001 C CNN
	1    2950 7000
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5E9D2F2C
P 2650 6700
F 0 "R?" V 2443 6700 50  0000 C CNN
F 1 "10k" V 2534 6700 50  0000 C CNN
F 2 "" V 2580 6700 50  0001 C CNN
F 3 "~" H 2650 6700 50  0001 C CNN
	1    2650 6700
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5E9D374F
P 2650 5200
F 0 "R?" V 2443 5200 50  0000 C CNN
F 1 "10k" V 2534 5200 50  0000 C CNN
F 2 "" V 2580 5200 50  0001 C CNN
F 3 "~" H 2650 5200 50  0001 C CNN
	1    2650 5200
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5E9D402D
P 3350 5200
F 0 "R?" V 3143 5200 50  0000 C CNN
F 1 "10k" V 3234 5200 50  0000 C CNN
F 2 "" V 3280 5200 50  0001 C CNN
F 3 "~" H 3350 5200 50  0001 C CNN
	1    3350 5200
	0    1    1    0   
$EndComp
Wire Wire Line
	2150 5200 2300 5200
Wire Wire Line
	2800 5200 2950 5200
Wire Wire Line
	3500 5200 3750 5200
Wire Wire Line
	3750 5200 3750 5950
Wire Wire Line
	3750 5950 3700 5950
Wire Wire Line
	3100 5850 2950 5850
Wire Wire Line
	2950 5850 2950 5200
Connection ~ 2950 5200
Wire Wire Line
	2950 5200 3200 5200
Wire Wire Line
	3100 6050 2950 6050
Wire Wire Line
	2950 6050 2950 6700
Wire Wire Line
	2800 6700 2950 6700
Connection ~ 2950 6700
Wire Wire Line
	2950 6700 2950 6850
Wire Wire Line
	2500 6700 2300 6700
Wire Wire Line
	2300 6650 2300 6700
Wire Wire Line
	2150 6700 2300 6700
Connection ~ 2300 6700
Wire Wire Line
	2300 5300 2300 5200
Connection ~ 2300 5200
Wire Wire Line
	2300 5200 2500 5200
$Comp
L Device:R_POT RV?
U 1 1 5EA24B07
P 2050 6000
F 0 "RV?" H 1981 6046 50  0000 R CNN
F 1 "5k" H 1981 5955 50  0000 R CNN
F 2 "" H 2050 6000 50  0001 C CNN
F 3 "~" H 2050 6000 50  0001 C CNN
	1    2050 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 6000 2300 6000
Wire Wire Line
	2300 6000 2300 6250
Wire Wire Line
	2050 5850 2050 5600
Wire Wire Line
	2050 5600 2300 5600
Wire Wire Line
	2050 5600 1350 5600
Wire Wire Line
	1350 5600 1350 5300
Wire Wire Line
	1350 5300 1550 5300
Connection ~ 2050 5600
Wire Wire Line
	1550 6600 1350 6600
Wire Wire Line
	1350 6600 1350 6250
Wire Wire Line
	1350 6250 2300 6250
Connection ~ 2300 6250
Wire Wire Line
	2300 6250 2300 6350
Text Label 7600 800  0    50   ~ 0
A0:MSP-2107
Wire Wire Line
	7600 800  7600 1000
Connection ~ 7600 1000
Wire Notes Line
	850  600  8400 600 
Wire Notes Line
	850  3150 8400 3150
Wire Notes Line
	7750 1150 7750 3150
Wire Notes Line
	8400 3150 8400 600 
Text GLabel 1450 5100 0    39   Input ~ 0
+OutputMPX10DP
$Comp
L Amplifier_Operational:LM324 U2
U 3 1 5EAB3B47
P 3900 6750
F 0 "U2" H 3900 6383 50  0000 C CNN
F 1 "LM324" H 3900 6474 50  0000 C CNN
F 2 "" H 3850 6850 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2902-n.pdf" H 3950 6950 50  0001 C CNN
	3    3900 6750
	-1   0    0    1   
$EndComp
Wire Wire Line
	4200 6650 4350 6650
Wire Wire Line
	4350 6650 4350 6300
Wire Wire Line
	4350 6300 3450 6300
Wire Wire Line
	3450 6300 3450 6750
Wire Wire Line
	3450 6750 3600 6750
$Comp
L Device:R_POT RV?
U 1 1 5EACB33C
P 4550 6850
F 0 "RV?" H 4481 6896 50  0000 R CNN
F 1 "100k" H 4481 6805 50  0000 R CNN
F 2 "" H 4550 6850 50  0001 C CNN
F 3 "~" H 4550 6850 50  0001 C CNN
	1    4550 6850
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4400 6850 4200 6850
$Comp
L power:GND #PWR?
U 1 1 5EAD2EFC
P 4550 7100
F 0 "#PWR?" H 4550 6850 50  0001 C CNN
F 1 "GND" H 4555 6927 50  0000 C CNN
F 2 "" H 4550 7100 50  0001 C CNN
F 3 "" H 4550 7100 50  0001 C CNN
	1    4550 7100
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4550 7100 4550 7000
$Comp
L power:-12V #PWR?
U 1 1 5EADB84A
P 4550 6600
F 0 "#PWR?" H 4550 6700 50  0001 C CNN
F 1 "-12V" H 4565 6773 50  0000 C CNN
F 2 "" H 4550 6600 50  0001 C CNN
F 3 "" H 4550 6600 50  0001 C CNN
	1    4550 6600
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4550 6600 4550 6700
Wire Wire Line
	2950 7150 2950 7400
Wire Wire Line
	2950 7400 3450 7400
Wire Wire Line
	3450 7400 3450 6750
Connection ~ 3450 6750
Wire Wire Line
	2100 2750 2100 2850
Wire Notes Line
	4150 4950 4200 4950
Wire Notes Line
	4200 4950 4200 4900
Text Notes 1550 7600 0    89   Italic 18
AMPLIFICADOR DE INSTRUMENTACION
Wire Notes Line
	850  4750 5000 4750
Wire Notes Line
	5000 7650 850  7650
Wire Notes Line
	850  600  850  7650
Wire Notes Line
	2900 4750 2900 3150
Wire Notes Line
	4050 7650 4050 7450
Wire Notes Line
	1550 7450 1550 7650
Wire Notes Line
	8400 2600 8250 2600
Wire Notes Line
	8250 2600 8250 1750
Wire Notes Line
	8250 1750 8400 1750
Wire Notes Line
	7750 2900 6900 2900
$Comp
L Device:D_Zener D?
U 1 1 5E933F49
P 1150 2400
F 0 "D?" V 1104 2479 50  0000 L CNN
F 1 "D_Zener_2.2V" V 1195 2479 50  0000 L CNN
F 2 "" H 1150 2400 50  0001 C CNN
F 3 "~" H 1150 2400 50  0001 C CNN
	1    1150 2400
	0    1    1    0   
$EndComp
Wire Wire Line
	5250 1350 5800 1350
Connection ~ 5800 1350
Wire Notes Line
	3300 6150 5000 6150
Wire Notes Line
	1550 7450 5000 7450
Text Notes 4200 7150 2    73   Italic 0
V_Offset
Text Notes 4200 7600 0    89   Italic 18
MPX10DP
Text Label 4150 5200 0    50   Italic 10
A1:MPX10DP
Wire Wire Line
	4150 5200 3750 5200
Connection ~ 3750 5200
Wire Notes Line
	3300 6150 3300 7450
$Comp
L MPX10DP:MPX10DP U4
U 1 1 5E9563D5
P 3650 3550
F 0 "U4" H 3270 3346 50  0000 R CNN
F 1 "MPX10DP" H 3270 3255 50  0000 R CNN
F 2 "" H 3650 3550 50  0001 C CNN
F 3 "" H 3650 3550 50  0001 C CNN
	1    3650 3550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E9578B8
P 3700 4200
F 0 "#PWR?" H 3700 3950 50  0001 C CNN
F 1 "GND" H 3705 4027 50  0000 C CNN
F 2 "" H 3700 4200 50  0001 C CNN
F 3 "" H 3700 4200 50  0001 C CNN
	1    3700 4200
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5E96E9BE
P 3700 3400
F 0 "#PWR?" H 3700 3250 50  0001 C CNN
F 1 "+3.3V" H 3715 3573 50  0000 C CNN
F 2 "" H 3700 3400 50  0001 C CNN
F 3 "" H 3700 3400 50  0001 C CNN
	1    3700 3400
	1    0    0    -1  
$EndComp
Text GLabel 4200 3700 2    50   Input ~ 0
+OutputMPX10DP
Text GLabel 4200 3850 2    50   Input ~ 0
-OutputMPX10DP
Wire Wire Line
	4200 3850 4100 3850
Wire Wire Line
	4200 3700 4100 3700
Wire Wire Line
	1450 5100 1550 5100
Text GLabel 1450 6800 0    39   Input ~ 0
-OutputMPX10DP
Wire Wire Line
	1450 6800 1550 6800
Wire Wire Line
	3700 4200 3700 4100
Wire Wire Line
	3700 3400 3700 3500
Wire Notes Line
	850  4500 5000 4500
Wire Notes Line
	5000 3150 5000 7650
Text Notes 3350 4700 0    89   ~ 18
SENSOR MPX10DP
$Comp
L AD1101:ADP1101 U?
U 1 1 5E9A0143
P 2700 1150
F 0 "U?" H 2700 1565 50  0000 C CNN
F 1 "ADP1101" H 2700 1474 50  0000 C CNN
F 2 "" H 2200 1100 50  0001 C CNN
F 3 "" H 2200 1100 50  0001 C CNN
	1    2700 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 1850 3400 1600
Wire Wire Line
	3650 1600 3400 1600
Text Notes 9000 2650 0    50   Italic 10
NOTA, QUEDA PEDIENTE EL CONTROLADOR A USAR.\n
Wire Wire Line
	1150 850  1150 1150
Wire Wire Line
	1850 1150 1150 1150
Connection ~ 1150 1150
Wire Wire Line
	1150 1150 1150 1400
Wire Wire Line
	1850 1000 1800 1000
Wire Wire Line
	1850 1300 1750 1300
Wire Wire Line
	1800 1000 1800 650 
Wire Wire Line
	1800 650  3650 650 
Wire Wire Line
	3650 650  3650 1000
Wire Wire Line
	3650 1000 3550 1000
Connection ~ 1800 1000
Wire Wire Line
	1800 1000 1750 1000
Wire Wire Line
	3550 1150 3650 1150
Wire Wire Line
	3650 1150 3650 1600
$EndSCHEMATC