/*
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * Name        : Thermometer.cpp
 * Author      : Georgi Todorov <terahz@geodar.com>
 * Version     : 
 * Created on  : Jan 3, 2013
 *
 * Copyright © 2013 Georgi Todorov <terahz@geodar.com>
 */

#include "Thermometer.h"

using namespace Wt;

Thermometer::Thermometer(const char* address, char* name,
		Wt::WContainerWidget *parent) :
		WContainerWidget(parent) {
	address_ = strdup(address);
	name_ = strdup(name);
	dev = new DS18B20(address_);
	temperature_ = Wt::WString("{1} &deg;");
	temperature_.arg("0");
	temptext_ = new Wt::WText(temperature_);
	groupingBox_ = new WGroupBox(name, this);
	groupingBox_->addWidget(temptext_);
}

Thermometer::~Thermometer() {
	delete dev;
}

float Thermometer::getTemp() {
	return dev->getTemp();
}
uint8_t Thermometer::getUnits() {
	return dev->getUnits();

}
void Thermometer::setUnits(uint8_t u) {
	dev->setUnits(u);
}
std::string Thermometer::getName() {
	return name_;
}
void Thermometer::updateTemp(Wt::WApplication *app) {
	temperature_ = Wt::WString("{1} &deg;");
	char tmp[] = "000.000";
	sprintf(tmp, "%3.3f", getTemp());
	temperature_.arg(tmp);
	Wt::WApplication::UpdateLock uiLock(app);
	if (uiLock) {
		temptext_->setText(temperature_);
		app->triggerUpdate();
		printf("Update triggered for %s\n", temperature_.toUTF8().c_str());
	}

}

