#include "BUZZER_cfg.h"
#include "BUZZER.h"

void BUZZER_en(void)
{
	DIO_SetPinDirection(BUZZER_PORT, BUZZER_PIN, OUTPUT);
}

void BUZZER_on(void)
{
	DIO_SetPinValue(BUZZER_PORT, BUZZER_PIN, HIGH);
}

void BUZZER_off(void)
{
	DIO_SetPinValue(BUZZER_PORT, BUZZER_PIN, LOW);
}