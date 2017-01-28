#include "application.h"
#include "IR_tx.h"

#define IR_LED_PIN D2

//
void setupIR_TX()
{
    pinMode(IR_LED_PIN, OUTPUT);
}

// This procedure sends a given kHz pulse to the IRledPin 
// for a certain # of microseconds. We'll use this whenever we need to send codes
void pulseIR(uint16_t kHz, long microsecs)
{
	int waveLength = 1000 / kHz;
	int halfWaveLength = waveLength / 2;
	//Serial.println(waveLength);

	ATOMIC_BLOCK(){
    //timing critical block	
	while (microsecs > 0)
	{
	    pinSetFast(IR_LED_PIN);
		delayMicroseconds(halfWaveLength);
	    pinResetFast(IR_LED_PIN);
		delayMicroseconds(halfWaveLength);

		microsecs -= waveLength;
	}
    }
}

// 
void sendCode(const uint16_t *code)
{
	//Serial.println("\nSendCode");

	const uint16_t *pulse = code;
	uint16_t kHz = pgm_read_word(pulse++);
	while (true)
	{
		int on = pgm_read_word(pulse++);
		int off = pgm_read_word(pulse++);
		//    Serial.print("on:");
		//    Serial.println(on);
		pulseIR(kHz, on);
		delayMicroseconds(off);
		//    Serial.print("off:");
		//    Serial.println(off);
		if (off == 0)
			return;
	}
}
