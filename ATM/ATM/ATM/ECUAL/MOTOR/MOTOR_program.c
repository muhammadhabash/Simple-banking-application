#include "MOTOR.h"

uint8_t Motor_Init(uint8_t u8_MotorId)
{
	switch(u8_MotorId)
	{
		case MOTOR_ID_01:
			DIO_SetPinDirection(MOTOR_01_DIR_PORT,MOTOR_01_DIR_PIN01, OUTPUT);
			DIO_SetPinDirection(MOTOR_01_DIR_PORT,MOTOR_01_DIR_PIN02, OUTPUT);
			DIO_SetPinDirection(MOTOR_01_DIR_PORT,MOTOR_01_ENABLE_PIN, OUTPUT);
			DIO_SetPinValue(MOTOR_01_DIR_PORT, MOTOR_01_DIR_PIN01, LOW);
			DIO_SetPinValue(MOTOR_01_DIR_PORT, MOTOR_01_DIR_PIN02, LOW);
			DIO_SetPinValue(MOTOR_01_DIR_PORT, MOTOR_01_ENABLE_PIN, LOW);
			return MOTOR_ERROR_OK;
			break;
		case MOTOR_ID_02:
			DIO_SetPinDirection(MOTOR_02_DIR_PORT,MOTOR_02_DIR_PIN01,OUTPUT);
			DIO_SetPinDirection(MOTOR_02_DIR_PORT,MOTOR_02_DIR_PIN02,OUTPUT);
			DIO_SetPinValue(MOTOR_02_DIR_PORT, MOTOR_02_DIR_PIN01,LOW);
			DIO_SetPinValue(MOTOR_02_DIR_PORT,MOTOR_02_DIR_PIN02, LOW);
			return MOTOR_ERROR_OK;
			break;
		default:
			return MOTOR_ERROR_NOK;
	}

}
uint8_t Motor_setDirection(uint8_t u8_MotorId, uint8_t u8_MotorDirection)
{
	switch(u8_MotorId)
	{
		case MOTOR_ID_01:
			if(u8_MotorDirection == FORWARD)
			{
				DIO_SetPinValue(MOTOR_01_DIR_PORT , MOTOR_01_DIR_PIN01, LOW);
				DIO_SetPinValue(MOTOR_01_DIR_PORT , MOTOR_01_DIR_PIN02, HIGH);
			}
			else if(BACKWARD)
			{
				DIO_SetPinValue(MOTOR_01_DIR_PORT , MOTOR_01_DIR_PIN01, HIGH);
				DIO_SetPinValue(MOTOR_01_DIR_PORT , MOTOR_01_DIR_PIN02, LOW);
			}
			else
			{
				DIO_SetPinValue(MOTOR_01_DIR_PORT , MOTOR_01_DIR_PIN01, LOW);
				DIO_SetPinValue(MOTOR_01_DIR_PORT , MOTOR_01_DIR_PIN02, LOW);				
			}
			return MOTOR_ERROR_OK;
			break;
		case MOTOR_ID_02:
			if(u8_MotorDirection == FORWARD)
			{
				DIO_SetPinValue(MOTOR_02_DIR_PORT , MOTOR_02_DIR_PIN01, LOW);
				DIO_SetPinValue(MOTOR_02_DIR_PORT , MOTOR_02_DIR_PIN02, HIGH);
			}
			else
			{
				DIO_SetPinValue(MOTOR_02_DIR_PORT , MOTOR_02_DIR_PIN01, HIGH);
				DIO_SetPinValue(MOTOR_02_DIR_PORT , MOTOR_02_DIR_PIN02, LOW);
			}
			return MOTOR_ERROR_OK;
			break;
		default:
			return MOTOR_ERROR_NOK;
			break;
	}
	return MOTOR_ERROR_NOK;
}
uint8_t Motor_Move(uint8_t MotorId, uint8_t u8_MotorDirection,uint8_t u8_MotorPower)
{
	switch(MotorId)
	{
		case MOTOR_ID_01:
			Motor_setDirection(MotorId,u8_MotorDirection);
			return MOTOR_ERROR_OK;
			break;
		case MOTOR_ID_02:
			Motor_setDirection(MotorId,u8_MotorDirection);
			return MOTOR_ERROR_OK;
			break;
		default:
			return MOTOR_ERROR_NOK;
	}
	
}
uint8_t MoveAllMotors(uint8_t u8_Motor01Direction,uint8_t u8_Motor02Direction,uint8_t u8_MotorsPower)
{
	Motor_setDirection(MOTOR_ID_01,u8_Motor01Direction);
	Motor_setDirection(MOTOR_ID_02,u8_Motor02Direction);
	return MOTOR_ERROR_OK;

}
uint8_t motorOn(uint8_t MotorId, uint8_t u8_MotorDirection)
{
	switch(MotorId)
	{
		case MOTOR_ID_01:
			Motor_setDirection(MotorId,u8_MotorDirection);
			DIO_SetPinValue(MOTOR_01_DIR_PORT, MOTOR_01_ENABLE_PIN, HIGH);
			return MOTOR_ERROR_OK;
			break;
		case MOTOR_ID_02:
			Motor_setDirection(MotorId,u8_MotorDirection);
			return MOTOR_ERROR_OK;
			break;
		default:
			return MOTOR_ERROR_NOK;
	}
	
}
uint8_t motorOff(uint8_t MotorId, uint8_t u8_MotorDirection)
{
	switch(MotorId)
	{
		case MOTOR_ID_01:
			Motor_setDirection(MotorId,u8_MotorDirection);
			DIO_SetPinValue(MOTOR_01_DIR_PORT, MOTOR_01_ENABLE_PIN, LOW);
			return MOTOR_ERROR_OK;
			break;
		case MOTOR_ID_02:
			Motor_setDirection(MotorId,u8_MotorDirection);
			return MOTOR_ERROR_OK;
			break;
		default:
			return MOTOR_ERROR_NOK;
	}
	
}