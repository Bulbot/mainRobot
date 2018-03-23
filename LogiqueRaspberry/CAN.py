# Written by TVD , bULBot Robotics Club
# Implementation of CAN Protocol for Raspberry Pi
# 23/03/2018

# ID's

CAN_ID_Rasp = 0x01
CAN_ID_PROP = 0x02
CAN_ID_DIST = 0x03
CAN_ID_Actions = 0x04 


#Globals

	# Actions

Act_Action = 0
Act_Wait = 1
Act_Error = 2

	
	# Propulsion

## Add comments
Prop_Translation = 0x00
Prop_Rotation = 0x01
Prop_Stop_Now = 0x02
Prop_Enable = 0x03
Prop_Disable = 0x04
Prop_Test = 0x05
Prop_Set_Duty_Cycle = 0x06
Prop_Goto_XY = 0x07
Prop_Goto_XYalpha = 0x08
Prop_Set_Pos_X = 0x09
Prop_Set_Pos_Y = 0x0A
Prop_Set_Pos_Alpha = 0x0B

Prop_Set_Pos = 0x12 #Wtf la valeur

Prop_Patinage_On_Off = 0x0D
Prop_Patinage_Off = 0
Prop_Patinage_On = 1

Prop_Add_Obstacle = 0x0E
Prop_Remove_Obstacle = 0x0F
Prop_Is_Obstacle_In_Map=0x10

Co_Prop_Status = CAN_ID_PROP*0x10 + 0
Co_Prop_Patinage = CAN_ID_PROP*0x10 + 1
Co_Prop_Pos = CAN_ID_PROP*0x10 + 2
Co_Prop_Is_Obstacle = CAN_ID_PROP*0x10 + 3
Co_Prop_Rel_Csg = CAN_ID_PROP*0x10 + 4
Co_Prop_Rel_Odo = CAN_ID_PROP*0x10 + 5



# Functions






