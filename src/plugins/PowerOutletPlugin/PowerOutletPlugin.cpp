/*
 * LEDPlugin.cpp
 *
 *  Created on: Jan 1, 2013
 *      Author: terahz
 */

#include "PowerOutletPlugin.h"

PowerOutletPlugin::PowerOutletPlugin() {
	int ii;
	powerDriver = new MCP23008(1,0x20);
	this->addWidget(new Wt::WText("<h2>Power Outlets:</h2>"));
	poTable = new Wt::WTable(this);
    for (ii=0; ii<8; ii++){
           PowerOutlet *po = new PowerOutlet(ii+1);
           pos[ii] = po;
           po->setSelected(powerDriver->get(ii+1));
           po->valueChanged().connect(this, &PowerOutletPlugin::setOutlet);
           poTable->elementAt(0, ii)->addWidget(po);
        }
}

PowerOutletPlugin::~PowerOutletPlugin() {
	delete powerDriver;
}

void PowerOutletPlugin::setOutlet(int pin, int state)
{
	powerDriver->set(pin, state);
}
// the class factories

extern "C" AquariusPlugin* create() {
    return new PowerOutletPlugin();
}

extern "C" void destroy(AquariusPlugin* p) {
    delete p;
}
