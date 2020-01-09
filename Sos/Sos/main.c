/*
 * Sos.c
 *
 * Created: 31-Dec-19 11:27:23 AM
 * Author : LENOVO
 */ 


#include "Firmware/os/os.h"
#include "app/app.h"


int main(void)
{
    /* Init. */
	Str_AdcConfig channel_confg = {ADC_INTERNAL_VOLTAGE, SENSOR_CHANNEL_NUMBER};
	APP_init(&channel_confg);
	SOS_init();
	/* Measure temp. */
	Str_SosTask_t task1 = {0, PRIODIC_TASK, 1000, APP_measureTemp};
	SOS_CreateTask(&task1);

	/* Run OS. */
	SOS_Run();
}

