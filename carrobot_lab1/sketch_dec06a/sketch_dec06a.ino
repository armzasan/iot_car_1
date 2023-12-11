

#include "LedMatrix.h"

#define NUMBER_OF_DEVICES 1
#define CS_PIN D4
LedMatrix ledMatrix = LedMatrix(NUMBER_OF_DEVICES, CS_PIN);
void setup()
{
ledMatrix.init();
ledMatrix.setIntensity(1); 
ledMatrix.setText("A r d u i n o A L L");
}
void loop()
{
ledMatrix.clear();
ledMatrix.scrollTextLeft();
ledMatrix.drawText();
ledMatrix.commit();
delay(200);
}
