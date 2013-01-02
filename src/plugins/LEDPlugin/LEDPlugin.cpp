/*
 * LEDPlugin.cpp
 *
 *  Created on: Jan 1, 2013
 *      Author: terahz
 */

#include "LEDPlugin.h"

LEDPlugin::LEDPlugin() {
	int ii;
	pwmDriver = new PCA9685(1,0x40);
	this->addWidget(new Wt::WText("<h2>LED Channels:</h2>"));
	ledTable = new Wt::WTable(this);
	for (ii = 0; ii < 16; ii++) {
		LEDChannel *led = new LEDChannel(ii + 1);
		leds[ii] = led;
		led->valueChanged().connect(this, &LEDPlugin::setPWM);
		if (ii < 8)
			ledTable->elementAt(0, ii)->addWidget(led);
		else
			ledTable->elementAt(1, ii - 8)->addWidget(led);
	}
}

LEDPlugin::~LEDPlugin() {
	delete pwmDriver;
}

void LEDPlugin::setPWM(int channel, int value)
{
    pwmDriver->setPWM(channel,value);
}
// the class factories

extern "C" AquariusPlugin* create() {
    return new LEDPlugin();
}

extern "C" void destroy(AquariusPlugin* p) {
    delete p;
}
