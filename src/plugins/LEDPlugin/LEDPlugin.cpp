/*
 * LEDPlugin.cpp
 *
 *  Created on: Jan 1, 2013
 *      Author: terahz
 */

#include "LEDPlugin.h"

LEDPlugin::LEDPlugin() {
	pwmDriver = new PCA9685(1, 0x40);
	name_ = "LED";
}

LEDPlugin::~LEDPlugin() {
	delete pwmDriver;
}

void LEDPlugin::setPWM(int channel, int value) {
	pwmDriver->setPWM(channel, value);
}

Wt::WContainerWidget * LEDPlugin::getSummary() {
	Wt::WContainerWidget *summaryContainer_ = new Wt::WContainerWidget();
	summaryContainer_->addWidget(new Wt::WText("LED summary widget"));
	return summaryContainer_;
}

Wt::WContainerWidget * LEDPlugin::getTab() {
	Wt::WContainerWidget *tabContainer_ = new Wt::WContainerWidget();
	Wt::WTable *ledTable = new Wt::WTable(tabContainer_);
	uint8_t ii;
		for (ii = 0; ii < 16; ii++) {
			LEDChannel *led = new LEDChannel(ii + 1);
			led->setValue(pwmDriver->getPWM(ii+1));
			led->valueChanged().connect(this,&LEDPlugin::setPWM);
			if (ii < 8)
				ledTable->elementAt(0, ii)->addWidget(led);
			else
				ledTable->elementAt(1, ii - 8)->addWidget(led);
		}
	return tabContainer_;
}

std::string LEDPlugin::getName() {
	return name_;
}

// the class factories

extern "C" AquariusPlugin* create() {
	return new LEDPlugin();
}

extern "C" void destroy(AquariusPlugin* p) {
	delete p;
}
