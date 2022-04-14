EESchema Schematic File Version 4
EELAYER 30 0
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
L Transistor_FET:IRF6716M Q4
U 1 1 624781F7
P 4400 6100
F 0 "Q4" H 4604 6146 50  0000 L CNN
F 1 "IRF520" H 4604 6055 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-262-3-1EP_Horizontal_TabDown" H 4400 6100 50  0001 C CIN
F 3 "https://www.infineon.com/dgdl/irf6716mpbf.pdf?fileId=5546d462533600a4015355ed15241a84" H 4400 6100 50  0001 L CNN
	1    4400 6100
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:IRF6716M Q5
U 1 1 62479911
P 5400 4250
F 0 "Q5" H 5604 4296 50  0000 L CNN
F 1 "IRF520" H 5604 4205 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-251-3-1EP_Horizontal_TabDown" H 5400 4250 50  0001 C CIN
F 3 "https://www.infineon.com/dgdl/irf6716mpbf.pdf?fileId=5546d462533600a4015355ed15241a84" H 5400 4250 50  0001 L CNN
	1    5400 4250
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:IRF6716M Q6
U 1 1 6247A17E
P 5400 4900
F 0 "Q6" H 5604 4946 50  0000 L CNN
F 1 "IRF520" H 5604 4855 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-251-3-1EP_Horizontal_TabDown" H 5400 4900 50  0001 C CIN
F 3 "https://www.infineon.com/dgdl/irf6716mpbf.pdf?fileId=5546d462533600a4015355ed15241a84" H 5400 4900 50  0001 L CNN
	1    5400 4900
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:IRF6716M Q8
U 1 1 6247BBBE
P 5400 6100
F 0 "Q8" H 5604 6146 50  0000 L CNN
F 1 "IRF520" H 5604 6055 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-262-3-1EP_Horizontal_TabDown" H 5400 6100 50  0001 C CIN
F 3 "https://www.infineon.com/dgdl/irf6716mpbf.pdf?fileId=5546d462533600a4015355ed15241a84" H 5400 6100 50  0001 L CNN
	1    5400 6100
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HC595 U1
U 1 1 62484D4E
P 3300 1350
F 0 "U1" H 3300 2131 50  0000 C CNN
F 1 "74HC595" H 3300 2040 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm_Socket" H 3300 1350 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn74hc595.pdf" H 3300 1350 50  0001 C CNN
	1    3300 1350
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x08 J3
U 1 1 6248A063
P 3900 1250
F 0 "J3" H 3980 1242 50  0000 L CNN
F 1 "Conn_01x08" H 3980 1151 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical" H 3900 1250 50  0001 C CNN
F 3 "~" H 3900 1250 50  0001 C CNN
	1    3900 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 2050 4150 2050
Wire Wire Line
	8100 2050 8100 3700
Wire Wire Line
	3300 2050 2900 2050
Wire Wire Line
	2750 2050 2750 3300
Wire Wire Line
	2750 3700 2900 3700
Connection ~ 3300 2050
Connection ~ 2750 3300
Wire Wire Line
	2750 3300 2750 3700
Wire Wire Line
	3300 5850 2750 5850
Connection ~ 2750 3700
Wire Wire Line
	2900 3200 2900 3700
Connection ~ 2900 3700
Wire Wire Line
	4150 3200 4150 3700
Connection ~ 4150 3700
Wire Wire Line
	5500 3200 5500 3700
Connection ~ 5500 3700
Wire Wire Line
	6800 3200 6800 3700
Connection ~ 6800 3700
Wire Wire Line
	6800 1550 6800 2050
Connection ~ 6800 2050
Wire Wire Line
	5500 1550 5500 2050
Connection ~ 5500 2050
Wire Wire Line
	4150 1550 4150 2050
Connection ~ 4150 2050
Wire Wire Line
	2900 1550 2900 2050
Connection ~ 2900 2050
Wire Wire Line
	2900 2050 2750 2050
Wire Wire Line
	3300 750  4000 750 
Wire Wire Line
	3300 750  2700 750 
Connection ~ 3300 750 
Wire Wire Line
	8050 2400 8050 750 
Wire Wire Line
	3300 4550 3300 3800
Wire Wire Line
	3300 3800 8050 3800
Wire Wire Line
	8050 3800 8050 2400
Connection ~ 8050 2400
Wire Wire Line
	3700 4750 3700 4250
Wire Wire Line
	3700 4250 4200 4250
Wire Wire Line
	3700 4850 4200 4850
Wire Wire Line
	4200 4850 4200 4900
Wire Wire Line
	3700 4950 4200 4950
Wire Wire Line
	4200 4950 4200 5500
Wire Wire Line
	3700 5050 4150 5050
Wire Wire Line
	4150 5050 4150 6100
Wire Wire Line
	4150 6100 4200 6100
Wire Wire Line
	3700 5150 3800 5150
Wire Wire Line
	3800 5150 3800 4000
Wire Wire Line
	3800 4000 5200 4000
Wire Wire Line
	5200 4000 5200 4250
Wire Wire Line
	3700 5250 3850 5250
Wire Wire Line
	3850 5250 3850 4550
Wire Wire Line
	3850 4550 5200 4550
Wire Wire Line
	3700 5350 3900 5350
Wire Wire Line
	3900 5350 3900 5150
Wire Wire Line
	3900 5150 5200 5150
Wire Wire Line
	5200 5150 5200 5500
Wire Wire Line
	3700 5450 3950 5450
Wire Wire Line
	3950 5450 3950 5750
Wire Wire Line
	3950 5750 5200 5750
Wire Wire Line
	5200 5750 5200 6100
Wire Wire Line
	4500 4450 5500 4450
Wire Wire Line
	5200 4900 5200 4550
Wire Wire Line
	4500 5100 5500 5100
Wire Wire Line
	5500 4450 5600 4450
Wire Wire Line
	5600 4450 5600 5100
Wire Wire Line
	5600 5100 5500 5100
Connection ~ 5500 4450
Connection ~ 5500 5100
Wire Wire Line
	4500 6300 5500 6300
Wire Wire Line
	5500 6300 5600 6300
Wire Wire Line
	5600 6300 5600 5700
Connection ~ 5500 6300
Connection ~ 5600 5100
Connection ~ 5600 5700
Wire Wire Line
	5600 5700 5600 5100
Wire Wire Line
	4500 4050 4500 3850
Wire Wire Line
	4500 3850 6450 3850
Wire Wire Line
	6450 3850 6450 4750
Wire Wire Line
	5500 4050 6400 4050
Wire Wire Line
	6400 4050 6400 4850
Wire Wire Line
	6400 4850 6450 4850
Wire Wire Line
	4500 4700 4500 4500
Wire Wire Line
	4500 4500 6350 4500
Wire Wire Line
	6350 4500 6350 4950
Wire Wire Line
	6350 4950 6450 4950
Wire Wire Line
	5500 4700 6300 4700
Wire Wire Line
	6300 4700 6300 5050
Wire Wire Line
	6300 5050 6450 5050
Wire Wire Line
	4500 5300 4500 5200
Wire Wire Line
	4500 5200 6300 5200
Wire Wire Line
	6300 5200 6300 5150
Wire Wire Line
	6300 5150 6450 5150
Wire Wire Line
	5500 5300 6350 5300
Wire Wire Line
	6350 5300 6350 5250
Wire Wire Line
	6350 5250 6450 5250
Wire Wire Line
	4500 5900 4500 5800
Wire Wire Line
	4500 5800 6250 5800
Wire Wire Line
	6250 5800 6250 5350
Wire Wire Line
	6250 5350 6450 5350
Wire Wire Line
	5500 5900 5500 5850
Wire Wire Line
	5500 5850 6450 5850
Wire Wire Line
	6450 5850 6450 5450
Wire Wire Line
	1900 750  2250 750 
Connection ~ 2650 750 
Wire Wire Line
	2900 1250 2700 1250
Wire Wire Line
	2700 1250 2700 750 
Connection ~ 2700 750 
Wire Wire Line
	2700 750  2650 750 
Wire Wire Line
	4150 1250 4000 1250
Wire Wire Line
	4000 1250 4000 750 
Connection ~ 4000 750 
Wire Wire Line
	5500 1250 5250 1250
Wire Wire Line
	5250 1250 5250 750 
Connection ~ 5250 750 
Wire Wire Line
	6800 1250 6600 1250
Wire Wire Line
	6600 1250 6600 750 
Connection ~ 6600 750 
Wire Wire Line
	6800 2900 6600 2900
Wire Wire Line
	6600 2900 6600 2400
Connection ~ 6600 2400
Wire Wire Line
	5500 2900 5250 2900
Wire Wire Line
	5250 2900 5250 2400
Connection ~ 5250 2400
Wire Wire Line
	4150 2900 4000 2900
Wire Wire Line
	4000 2900 4000 2400
Connection ~ 4000 2400
Wire Wire Line
	2900 2900 2650 2900
Wire Wire Line
	2650 2900 2650 2400
Connection ~ 2650 2400
Wire Wire Line
	2750 5850 2750 5550
Wire Wire Line
	2900 5050 2800 5050
Wire Wire Line
	2800 5050 2800 3800
Wire Wire Line
	2800 3800 3300 3800
Connection ~ 3300 3800
Wire Wire Line
	2900 5350 2750 5350
Connection ~ 2750 5350
Wire Wire Line
	2750 5350 2750 3700
Wire Wire Line
	8150 700  8150 2100
Wire Wire Line
	8150 3900 2700 3900
Wire Wire Line
	2700 3900 2700 5250
Wire Wire Line
	2700 5250 2900 5250
Wire Wire Line
	2600 3100 2900 3100
Wire Wire Line
	4150 3100 4050 3100
Wire Wire Line
	4050 3100 4050 2100
Wire Wire Line
	4050 2100 5300 2100
Connection ~ 8150 2100
Wire Wire Line
	8150 2100 8150 3900
Wire Wire Line
	5500 3100 5300 3100
Wire Wire Line
	5300 3100 5300 2100
Connection ~ 5300 2100
Wire Wire Line
	5300 2100 6650 2100
Wire Wire Line
	6800 3100 6650 3100
Wire Wire Line
	6650 3100 6650 2100
Connection ~ 6650 2100
Wire Wire Line
	6650 2100 8150 2100
Connection ~ 4050 2100
Wire Wire Line
	2600 2100 2600 3100
Wire Wire Line
	3700 1850 4100 1850
Wire Wire Line
	4100 1850 4100 950 
Wire Wire Line
	4100 950  4150 950 
Wire Wire Line
	4950 1850 5450 1850
Wire Wire Line
	5450 1850 5450 950 
Wire Wire Line
	5450 950  5500 950 
Wire Wire Line
	6300 1850 6750 1850
Wire Wire Line
	6750 1850 6750 950 
Wire Wire Line
	6750 950  6800 950 
Wire Wire Line
	7600 1850 7600 2350
Wire Wire Line
	7600 2350 6800 2350
Wire Wire Line
	6800 2350 6800 2600
Wire Wire Line
	7600 3500 7600 3650
Wire Wire Line
	7600 3650 5450 3650
Wire Wire Line
	5450 3650 5450 2600
Wire Wire Line
	5450 2600 5500 2600
Wire Wire Line
	6300 3500 6300 3750
Wire Wire Line
	6300 3750 4100 3750
Wire Wire Line
	4100 3750 4100 2600
Wire Wire Line
	4100 2600 4150 2600
Wire Wire Line
	4950 3500 4950 3650
Wire Wire Line
	4950 3650 2850 3650
Wire Wire Line
	2850 3650 2850 2600
Wire Wire Line
	2850 2600 2900 2600
Wire Wire Line
	3700 3500 3700 4000
Wire Wire Line
	3700 4000 2900 4000
Wire Wire Line
	2900 4000 2900 4750
Wire Wire Line
	8250 650  8250 2200
Wire Wire Line
	8250 3950 2850 3950
Wire Wire Line
	2850 3950 2850 4950
Wire Wire Line
	2850 4950 2900 4950
Wire Wire Line
	2900 1450 2800 1450
Wire Wire Line
	2800 1450 2800 700 
Wire Wire Line
	2800 700  4050 700 
Wire Wire Line
	4150 1450 4050 1450
Wire Wire Line
	4050 1450 4050 700 
Connection ~ 4050 700 
Wire Wire Line
	5500 1450 5350 1450
Wire Wire Line
	5350 1450 5350 700 
Connection ~ 5350 700 
Wire Wire Line
	5350 700  6700 700 
Wire Wire Line
	6800 1450 6700 1450
Wire Wire Line
	6700 1450 6700 700 
Connection ~ 6700 700 
Wire Wire Line
	6700 700  8150 700 
Wire Wire Line
	2900 1150 2850 1150
Wire Wire Line
	2850 1150 2850 650 
Wire Wire Line
	2850 650  3950 650 
Wire Wire Line
	4150 1150 3950 1150
Wire Wire Line
	3950 1150 3950 650 
Connection ~ 3950 650 
Wire Wire Line
	3950 650  5400 650 
Wire Wire Line
	5500 1150 5400 1150
Wire Wire Line
	5400 1150 5400 650 
Connection ~ 5400 650 
Wire Wire Line
	5400 650  6650 650 
Wire Wire Line
	6800 1150 6650 1150
Wire Wire Line
	6650 1150 6650 650 
Connection ~ 6650 650 
Wire Wire Line
	6650 650  8250 650 
Wire Wire Line
	2800 2200 2800 2800
Wire Wire Line
	2800 2800 2900 2800
Connection ~ 8250 2200
Wire Wire Line
	8250 2200 8250 3950
Wire Wire Line
	4150 2800 3950 2800
Wire Wire Line
	3950 2800 3950 2200
Connection ~ 3950 2200
Wire Wire Line
	3950 2200 2800 2200
Wire Wire Line
	5500 2800 5350 2800
Wire Wire Line
	5350 2800 5350 2200
Connection ~ 5350 2200
Wire Wire Line
	5350 2200 3950 2200
Wire Wire Line
	6800 2800 6700 2800
Wire Wire Line
	6700 2800 6700 2200
Wire Wire Line
	5350 2200 6700 2200
Connection ~ 6700 2200
Wire Wire Line
	6700 2200 8250 2200
Wire Wire Line
	4050 700  5350 700 
Wire Wire Line
	4000 750  4550 750 
Wire Wire Line
	4150 2050 4550 2050
Wire Wire Line
	5250 750  5900 750 
Wire Wire Line
	5500 2050 5900 2050
Wire Wire Line
	6600 750  7200 750 
Wire Wire Line
	6800 2050 7200 2050
Wire Wire Line
	6600 2400 7200 2400
Wire Wire Line
	6800 3700 7200 3700
Wire Wire Line
	5250 2400 5900 2400
Wire Wire Line
	5500 3700 5900 3700
Wire Wire Line
	4000 2400 4550 2400
Wire Wire Line
	4150 3700 4550 3700
Wire Wire Line
	2650 2400 3300 2400
Wire Wire Line
	2900 3700 3300 3700
$Comp
L Connector_Generic:Conn_01x08 J5
U 1 1 627E694B
P 5150 1250
F 0 "J5" H 5230 1242 50  0000 L CNN
F 1 "Conn_01x08" H 5230 1151 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical" H 5150 1250 50  0001 C CNN
F 3 "~" H 5150 1250 50  0001 C CNN
	1    5150 1250
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x08 J7
U 1 1 627F43DB
P 6500 1250
F 0 "J7" H 6580 1242 50  0000 L CNN
F 1 "Conn_01x08" H 6580 1151 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical" H 6500 1250 50  0001 C CNN
F 3 "~" H 6500 1250 50  0001 C CNN
	1    6500 1250
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x08 J10
U 1 1 628021CA
P 7800 1250
F 0 "J10" H 7880 1242 50  0000 L CNN
F 1 "Conn_01x08" H 7880 1151 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical" H 7800 1250 50  0001 C CNN
F 3 "~" H 7800 1250 50  0001 C CNN
	1    7800 1250
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x08 J11
U 1 1 6281DE99
P 7800 2900
F 0 "J11" H 7880 2892 50  0000 L CNN
F 1 "Conn_01x08" H 7880 2801 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical" H 7800 2900 50  0001 C CNN
F 3 "~" H 7800 2900 50  0001 C CNN
	1    7800 2900
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x08 J8
U 1 1 6282B702
P 6500 2900
F 0 "J8" H 6580 2892 50  0000 L CNN
F 1 "Conn_01x08" H 6580 2801 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical" H 6500 2900 50  0001 C CNN
F 3 "~" H 6500 2900 50  0001 C CNN
	1    6500 2900
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x08 J6
U 1 1 62839350
P 5150 2900
F 0 "J6" H 5230 2892 50  0000 L CNN
F 1 "Conn_01x08" H 5230 2801 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical" H 5150 2900 50  0001 C CNN
F 3 "~" H 5150 2900 50  0001 C CNN
	1    5150 2900
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x08 J4
U 1 1 62846F37
P 3900 2900
F 0 "J4" H 3980 2892 50  0000 L CNN
F 1 "Conn_01x08" H 3980 2801 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical" H 3900 2900 50  0001 C CNN
F 3 "~" H 3900 2900 50  0001 C CNN
	1    3900 2900
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x08 J9
U 1 1 62854B74
P 6650 5050
F 0 "J9" H 6730 5042 50  0000 L CNN
F 1 "Conn_01x08" H 6730 4951 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical" H 6650 5050 50  0001 C CNN
F 3 "~" H 6650 5050 50  0001 C CNN
	1    6650 5050
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J1
U 1 1 628648FD
P 1850 4050
F 0 "J1" H 1930 4042 50  0000 L CNN
F 1 "Conn_01x04" H 1930 3951 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 1850 4050 50  0001 C CNN
F 3 "~" H 1850 4050 50  0001 C CNN
	1    1850 4050
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x08 J2
U 1 1 628765FC
P 1850 5000
F 0 "J2" H 1930 4992 50  0000 L CNN
F 1 "Conn_01x08" H 1930 4901 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical" H 1850 5000 50  0001 C CNN
F 3 "~" H 1850 5000 50  0001 C CNN
	1    1850 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 4050 1600 4050
Wire Wire Line
	1600 4050 1600 3450
Wire Wire Line
	1600 3450 2250 3450
Connection ~ 2250 750 
Wire Wire Line
	2250 750  2400 750 
Wire Wire Line
	1650 4700 1550 4700
Wire Wire Line
	1550 4700 1550 4500
Wire Wire Line
	1550 4500 2400 4500
Wire Wire Line
	2400 4500 2400 750 
Connection ~ 2400 750 
Wire Wire Line
	2400 750  2650 750 
Wire Wire Line
	1650 4800 1500 4800
Wire Wire Line
	1500 4800 1500 4450
Wire Wire Line
	1500 4450 2500 4450
Wire Wire Line
	2500 4450 2500 3300
Connection ~ 2500 3300
Wire Wire Line
	2500 3300 2750 3300
Wire Wire Line
	1650 4900 1300 4900
Wire Wire Line
	1650 5000 1250 5000
Wire Wire Line
	1250 5000 1250 4700
$Comp
L 74xx:74HC595 U4
U 1 1 62942C86
P 4550 1350
F 0 "U4" H 4550 2131 50  0000 C CNN
F 1 "74HC595" H 4550 2040 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm_Socket" H 4550 1350 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn74hc595.pdf" H 4550 1350 50  0001 C CNN
	1    4550 1350
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HC595 U6
U 1 1 62957D45
P 5900 1350
F 0 "U6" H 5900 2131 50  0000 C CNN
F 1 "74HC595" H 5900 2040 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm_Socket" H 5900 1350 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn74hc595.pdf" H 5900 1350 50  0001 C CNN
	1    5900 1350
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HC595 U8
U 1 1 6296C386
P 7200 1350
F 0 "U8" H 7200 2131 50  0000 C CNN
F 1 "74HC595" H 7200 2040 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm_Socket" H 7200 1350 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn74hc595.pdf" H 7200 1350 50  0001 C CNN
	1    7200 1350
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HC595 U9
U 1 1 629816BB
P 7200 3000
F 0 "U9" H 7200 3781 50  0000 C CNN
F 1 "74HC595" H 7200 3690 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm_Socket" H 7200 3000 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn74hc595.pdf" H 7200 3000 50  0001 C CNN
	1    7200 3000
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HC595 U7
U 1 1 62995E03
P 5900 3000
F 0 "U7" H 5900 3781 50  0000 C CNN
F 1 "74HC595" H 5900 3690 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm_Socket" H 5900 3000 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn74hc595.pdf" H 5900 3000 50  0001 C CNN
	1    5900 3000
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HC595 U5
U 1 1 629AA915
P 4550 3000
F 0 "U5" H 4550 3781 50  0000 C CNN
F 1 "74HC595" H 4550 3690 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm_Socket" H 4550 3000 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn74hc595.pdf" H 4550 3000 50  0001 C CNN
	1    4550 3000
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HC595 U2
U 1 1 629BF544
P 3300 3000
F 0 "U2" H 3300 3781 50  0000 C CNN
F 1 "74HC595" H 3300 3690 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm_Socket" H 3300 3000 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn74hc595.pdf" H 3300 3000 50  0001 C CNN
	1    3300 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 1200 1900 750 
Wire Wire Line
	4050 2100 2600 2100
Wire Wire Line
	2250 3450 2250 750 
Wire Wire Line
	2650 750  2650 2400
$Comp
L 74xx:74HC595 U3
U 1 1 629D4374
P 3300 5150
F 0 "U3" H 3300 5931 50  0000 C CNN
F 1 "74HC595" H 3300 5840 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm_Socket" H 3300 5150 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn74hc595.pdf" H 3300 5150 50  0001 C CNN
	1    3300 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 5700 5600 5700
Wire Wire Line
	5500 5700 4500 5700
Connection ~ 5500 5700
$Comp
L Transistor_FET:IRF6716M Q7
U 1 1 6247ADBC
P 5400 5500
F 0 "Q7" H 5604 5546 50  0000 L CNN
F 1 "IRF520" H 5604 5455 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-262-3-1EP_Horizontal_TabDown" H 5400 5500 50  0001 C CIN
F 3 "https://www.infineon.com/dgdl/irf6716mpbf.pdf?fileId=5546d462533600a4015355ed15241a84" H 5400 5500 50  0001 L CNN
	1    5400 5500
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic_MountingPin:Conn_01x05_MountingPin J13
U 1 1 62A6B50E
P 1500 1400
F 0 "J13" H 1588 1272 50  0000 L CNN
F 1 "Conn_01x05_MountingPin" H 1588 1363 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x05_P2.54mm_Vertical" H 1500 1400 50  0001 C CNN
F 3 "~" H 1500 1400 50  0001 C CNN
	1    1500 1400
	-1   0    0    1   
$EndComp
Wire Wire Line
	1700 1200 1900 1200
Wire Wire Line
	1700 1300 2550 1300
Wire Wire Line
	2550 1300 2550 2050
Wire Wire Line
	2550 2050 2750 2050
Connection ~ 2750 2050
Wire Wire Line
	2900 950  2000 950 
Wire Wire Line
	2000 950  2000 1400
Wire Wire Line
	2000 1400 1700 1400
Wire Wire Line
	2850 1150 2150 1150
Wire Wire Line
	2150 1150 2150 1600
Wire Wire Line
	2150 1600 1700 1600
Connection ~ 2850 1150
Wire Wire Line
	1900 1450 1900 1500
Wire Wire Line
	1900 1500 1700 1500
Text Label 1800 1400 0    50   ~ 0
Data
Text Label 1700 1600 0    50   ~ 0
Clock
Wire Wire Line
	1900 1450 2800 1450
Connection ~ 2800 1450
Text Label 1700 1500 0    50   ~ 0
Latch
Text Label 1750 1300 0    50   ~ 0
GND
Text Label 1700 1200 0    50   ~ 0
VCC
$Comp
L Connector_Generic:Conn_01x02 J12
U 1 1 62A6E703
P 950 4700
F 0 "J12" H 868 4375 50  0000 C CNN
F 1 "Conn_01x02" H 868 4466 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical" H 950 4700 50  0001 C CNN
F 3 "~" H 950 4700 50  0001 C CNN
	1    950  4700
	-1   0    0    1   
$EndComp
Wire Wire Line
	1250 4250 1650 4250
Wire Wire Line
	1300 4150 1650 4150
Wire Wire Line
	1650 3300 1650 3950
Wire Wire Line
	1650 3300 2500 3300
Text Label 1700 3900 0    50   ~ 0
GND
Text Label 1550 4050 0    50   ~ 0
VCC
Text Label 1350 4150 0    50   ~ 0
SDA
Text Label 1400 4250 0    50   ~ 0
SCL
Text Label 1550 4700 0    50   ~ 0
VCC
Text Label 1500 4800 0    50   ~ 0
GND
Text Label 1350 4900 0    50   ~ 0
SDA
Text Label 1250 5000 0    50   ~ 0
SCL
Wire Wire Line
	1150 4600 1300 4600
Connection ~ 1300 4600
Wire Wire Line
	1300 4600 1300 4150
Text Label 8250 1100 0    50   ~ 0
Clock
Text Label 8150 1250 0    50   ~ 0
Latch
Text Label 8050 1150 0    50   ~ 0
VCC
Text Label 7800 2050 0    50   ~ 0
GND
Wire Wire Line
	1300 4600 1300 4900
Wire Wire Line
	1250 4700 1150 4700
Connection ~ 1250 4700
Wire Wire Line
	1250 4700 1250 4250
$Comp
L Connector_Generic:Conn_01x06 J15
U 1 1 62C06FBC
P 1850 5950
F 0 "J15" H 1930 5942 50  0000 L CNN
F 1 "Conn_01x06" H 1930 5851 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x06_P2.54mm_Vertical" H 1850 5950 50  0001 C CNN
F 3 "~" H 1850 5950 50  0001 C CNN
	1    1850 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 5750 1650 5550
Wire Wire Line
	1650 5550 2750 5550
Connection ~ 2750 5550
Wire Wire Line
	2750 5550 2750 5350
$Comp
L Connector_Generic:Conn_01x06 J14
U 1 1 62C1F474
P 1450 6050
F 0 "J14" H 1368 5525 50  0000 C CNN
F 1 "Conn_01x06" H 1368 5616 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x06_P2.54mm_Vertical" H 1450 6050 50  0001 C CNN
F 3 "~" H 1450 6050 50  0001 C CNN
	1    1450 6050
	-1   0    0    1   
$EndComp
Connection ~ 1650 5750
Wire Wire Line
	4550 850  4550 750 
Connection ~ 4550 750 
Wire Wire Line
	4550 750  5250 750 
Wire Wire Line
	5900 750  6600 750 
Connection ~ 5900 750 
Connection ~ 7200 750 
Wire Wire Line
	7200 750  8050 750 
Wire Wire Line
	5900 2400 6600 2400
Connection ~ 5900 2400
Connection ~ 7200 2400
Wire Wire Line
	7200 2400 8050 2400
Wire Wire Line
	5250 2400 4550 2400
Connection ~ 4550 2400
Wire Wire Line
	3300 2400 4000 2400
Connection ~ 3300 2400
Wire Wire Line
	5900 3700 6800 3700
Connection ~ 5900 3700
Connection ~ 7200 3700
Wire Wire Line
	7200 3700 8100 3700
Wire Wire Line
	5500 3700 4550 3700
Connection ~ 4550 3700
Wire Wire Line
	4150 3700 3300 3700
Connection ~ 3300 3700
Wire Wire Line
	6800 2050 5900 2050
Connection ~ 7200 2050
Wire Wire Line
	7200 2050 8100 2050
Connection ~ 5900 2050
Wire Wire Line
	5500 2050 4550 2050
Connection ~ 4550 2050
$Comp
L Transistor_FET:IRF6716M Q3
U 1 1 62476C3C
P 4400 5500
F 0 "Q3" H 4604 5546 50  0000 L CNN
F 1 "IRF520" H 4604 5455 50  0000 L CNN
F 2 "Package_DirectFET:DirectFET_MX" H 4400 5500 50  0001 C CIN
F 3 "https://www.infineon.com/dgdl/irf6716mpbf.pdf?fileId=5546d462533600a4015355ed15241a84" H 4400 5500 50  0001 L CNN
	1    4400 5500
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:IRF6716M Q1
U 1 1 62472CCE
P 4400 4250
F 0 "Q1" H 4604 4296 50  0000 L CNN
F 1 "IRF520" H 4604 4205 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-262-3-1EP_Horizontal_TabDown" H 4400 4250 50  0001 C CIN
F 3 "https://www.infineon.com/dgdl/irf6716mpbf.pdf?fileId=5546d462533600a4015355ed15241a84" H 4400 4250 50  0001 L CNN
	1    4400 4250
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:IRF6716M Q2
U 1 1 624758E1
P 4400 4900
F 0 "Q2" H 4604 4946 50  0000 L CNN
F 1 "IRF520" H 4604 4855 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-262-3-1EP_Horizontal_TabDown" H 4400 4900 50  0001 C CIN
F 3 "https://www.infineon.com/dgdl/irf6716mpbf.pdf?fileId=5546d462533600a4015355ed15241a84" H 4400 4900 50  0001 L CNN
	1    4400 4900
	1    0    0    -1  
$EndComp
$EndSCHEMATC
