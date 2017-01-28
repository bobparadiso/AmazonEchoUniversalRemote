// This #include statement was automatically added by the Particle IDE.
#include "IR_codes.h"

// This #include statement was automatically added by the Particle IDE.
#include "IR_tx.h"

void setup()
{
    setupIR_TX();

    Spark.function("IRCode", IRCode);
}

//
void sendCodeRepeated(const uint16_t *code)
{
    for (int i = 0; i < 3; i++)
    {
        sendCode(code);
        delayMicroseconds(8000);
    }
}

int codeToSend = -1;
void loop()
{
    if (codeToSend == -1)
        return;
        
    switch (codeToSend)
    {
        case 0: sendCode(IRsignal_tvMute); break;

        case 1:
            for (int i = 0; i < 5; i++)
            {
                sendCode(IRsignal_tvVolUp);
                delay(750);
            }
            break;

        case 2:
            for (int i = 0; i < 5; i++)
            {
                sendCode(IRsignal_tvVolDown);
                delay(750);
            }
            break;

        //entertainment system on
		case 3:
			for (int i = 0; i < 10; i++)
			{
				sendCode(IRsignal_tvPower);
				delayMicroseconds(8000);
			}
			delay(1000);
			sendCode(IRsignal_Cable_POWER);
			delay(8000);
			sendCode(IRsignal_Stereo_POWER);
			break;

        //entertainment system off 
		case 4:
			sendCode(IRsignal_Stereo_POWER);
			delay(3000);
			sendCode(IRsignal_Cable_POWER);
			delay(1000);
			for (int i = 0; i < 10; i++)
			{
				sendCode(IRsignal_tvPower);
				delayMicroseconds(8000);
			}
			break;
            
        case 5: sendCode(IRsignal_Fireplace_Power); break;
        case 6: sendCode(IRsignal_Fireplace_Heat); break;
        
        //877 80's
        case 7:
            for (int i = 0; i < 3; i++)
			sendCodeRepeated(IRsignal_tv_8);
			delay(750);
			sendCodeRepeated(IRsignal_tv_7);
			delay(750);
			sendCodeRepeated(IRsignal_tv_7);
            break;

        //878 70's
        case 8:
			sendCodeRepeated(IRsignal_tv_8);
			delay(750);
			sendCodeRepeated(IRsignal_tv_7);
			delay(750);
			sendCodeRepeated(IRsignal_tv_8);
            break;

        //879 oldies
        case 9:
			sendCodeRepeated(IRsignal_tv_8);
			delay(750);
			sendCodeRepeated(IRsignal_tv_7);
			delay(750);
			sendCodeRepeated(IRsignal_tv_9);
            break;
    }

    codeToSend = -1;
}

//triggered from Spark cloud
int IRCode(String command)
{
    int id = atoi(command);
    if (id >= 0 && id <= 100)
        codeToSend = id;

    return codeToSend;
}
