#include <Arduino_FreeRTOS.h>

int LEDs[] = {
	2,
	3,
	4,
	5,
	6,
	7,
	8
};

void TaskDigitalRead( void *pvParameters );
void TaskAnalogRead( void *pvParameters );

void setup() {
	Serial.begin(9600);
	
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
	}

	xTaskCreateStatic(
		TaskDigitalRead
		,  (const portCHAR *)"DigitalRead"	// A name just for humans
		,  128	// This stack size can be checked & adjusted by reading the Stack Highwater
		,  NULL
		,  2	// Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
		,  NULL );

	xTaskCreateStatic(
		TaskAnalogRead
		,  (const portCHAR *) "AnalogRead"
		,  128	// Stack size
		,  NULL
		,  1	// Priority
		,  NULL );
}

void loop() {}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskDigitalRead( void *pvParameters __attribute__((unused)) ) {
	uint8_t pushButton = 2;

	pinMode(pushButton, INPUT);

	for (;;) {
		int buttonState = digitalRead(pushButton);

		Serial.println(buttonState);

		vTaskDelay(1);	// one tick delay (15ms) in between reads for stability
	}
}

void TaskAnalogRead( void *pvParameters __attribute__((unused)) ) {
	for (;;) {
		int sensorValue = analogRead(A0);

		Serial.println(sensorValue);

		vTaskDelay(1);
	}
}

