/*
 * LEDPlugin.cpp
 *
 *  Created on: Jan 1, 2013
 *      Author: terahz
 */

#include "PowerOutletPlugin.h"

PowerOutletPlugin::PowerOutletPlugin() {
	powerDriver = new MCP23008(1,0x20);
	name_ = "Power Outlets";
}

PowerOutletPlugin::~PowerOutletPlugin() {
	delete powerDriver;
}

void PowerOutletPlugin::setOutlet(int pin, int state)
{
	powerDriver->set(pin, state);
}

Wt::WContainerWidget * PowerOutletPlugin::getSummary() {
	Wt::WContainerWidget *summaryContainer_ = new Wt::WContainerWidget();
	summaryContainer_->addWidget(new Wt::WText("Power Outlet summary widget"));
	return summaryContainer_;
}

Wt::WContainerWidget * PowerOutletPlugin::getTab() {
	Wt::WContainerWidget *tabContainer_ = new Wt::WContainerWidget();
	Wt::WTable *poTable = new Wt::WTable(tabContainer_);
	int ii;
		poTable = new Wt::WTable(tabContainer_);
	    for (ii=0; ii<8; ii++){
	           PowerOutlet *po = new PowerOutlet(ii+1);
	           po->setSelected(powerDriver->get(ii+1));
	           po->valueChanged().connect(this, &PowerOutletPlugin::setOutlet);
	           poTable->elementAt(0, ii)->addWidget(po);
	        }
	return tabContainer_;
}

std::string PowerOutletPlugin::getName() {
	return name_;
}

void PowerOutletPlugin::refresh(){

}

// the class factories
extern "C" AquariusPlugin* create() {
    return new PowerOutletPlugin();
}

extern "C" void destroy(AquariusPlugin* p) {
    delete p;
}
