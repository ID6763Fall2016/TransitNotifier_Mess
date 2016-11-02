EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:huzzah_PCB-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L CONN_01X10 P1
U 1 1 58083324
P 3800 3100
F 0 "P1" H 3800 3650 50  0000 C CNN
F 1 "CONN_01X10" V 3900 3100 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x10" H 3800 3100 50  0001 C CNN
F 3 "" H 3800 3100 50  0000 C CNN
	1    3800 3100
	1    0    0    -1  
$EndComp
Text GLabel 4500 3550 2    39   Input ~ 0
GND
$Comp
L CONN_01X10 P3
U 1 1 58083370
P 4300 3100
F 0 "P3" H 4300 3650 50  0000 C CNN
F 1 "CONN_01X10" V 4400 3100 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x10" H 4300 3100 50  0001 C CNN
F 3 "" H 4300 3100 50  0000 C CNN
	1    4300 3100
	-1   0    0    1   
$EndComp
Text GLabel 4500 3350 2    39   Input ~ 0
LED_V
Text GLabel 4500 3250 2    39   Input ~ 0
PIN15
Text GLabel 4500 3050 2    39   Input ~ 0
PIN0
Text GLabel 4500 2950 2    39   Input ~ 0
DATA
Text GLabel 4500 2850 2    39   Input ~ 0
CLOCK
Text GLabel 4500 3150 2    39   Input ~ 0
PIN2
Text GLabel 4500 2750 2    39   Input ~ 0
RX
Text GLabel 4500 2650 2    39   Input ~ 0
TX
Text GLabel 4500 3450 2    39   Input ~ 0
LD0
Text GLabel 3600 3550 0    39   Input ~ 0
GND
Text GLabel 3600 3450 0    39   Input ~ 0
VBat
Text GLabel 3600 3350 0    39   Input ~ 0
V33
Text GLabel 3600 3250 0    39   Input ~ 0
PIN13
Text GLabel 3600 3150 0    39   Input ~ 0
BTN_READ
Text GLabel 3600 3050 0    39   Input ~ 0
PIN14
Text GLabel 3600 2950 0    39   Input ~ 0
PIN16
Text GLabel 3600 2850 0    39   Input ~ 0
EN
Text GLabel 3600 2750 0    39   Input ~ 0
A
Text GLabel 3600 2650 0    39   Input ~ 0
RST
$Comp
L CONN_01X04 P4
U 1 1 58081E64
P 5450 3400
F 0 "P4" H 5450 3650 50  0000 C CNN
F 1 "CONN_01X04" V 5550 3400 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04" H 5450 3400 50  0001 C CNN
F 3 "" H 5450 3400 50  0000 C CNN
	1    5450 3400
	1    0    0    -1  
$EndComp
Text GLabel 5250 3250 0    39   Input ~ 0
LED_V
Text GLabel 5250 3550 0    39   Input ~ 0
GND
Text GLabel 5250 3450 0    39   Input ~ 0
DATA
Text GLabel 5250 3350 0    39   Input ~ 0
CLOCK
$Comp
L CONN_01X02 P2
U 1 1 5808F565
P 2400 3450
F 0 "P2" H 2400 3600 50  0000 C CNN
F 1 "CONN_01X02" V 2500 3450 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch3.96mm_Friction_Lock" H 2400 3450 50  0001 C CNN
F 3 "" H 2400 3450 50  0000 C CNN
	1    2400 3450
	-1   0    0    1   
$EndComp
Text GLabel 2600 3800 2    39   Input ~ 0
GND
Text GLabel 2600 3500 2    39   Input ~ 0
BTN_READ
Text GLabel 2600 3400 2    39   Input ~ 0
V33
$Comp
L R R1
U 1 1 58090028
P 2600 3650
F 0 "R1" V 2680 3650 50  0000 C CNN
F 1 "R" V 2600 3650 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM7mm" V 2530 3650 50  0001 C CNN
F 3 "" H 2600 3650 50  0000 C CNN
	1    2600 3650
	1    0    0    -1  
$EndComp
$EndSCHEMATC
