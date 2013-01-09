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
 * Name        : Thermometer.h
 * Author      : Georgi Todorov <terahz@geodar.com>
 * Version     : 
 * Created on  : Jan 3, 2013
 *
 * Copyright © 2013 Georgi Todorov <terahz@geodar.com>
 */

#ifndef THERMOMETER_H_
#define THERMOMETER_H_

#include <Wt/WContainerWidget>
#include <Wt/WGroupBox>
#include <Wt/WApplication>
#include <Wt/WText>
#include <Wt/WString>
#include <Wt/WTimer>
#include <boost/thread.hpp>
#include <DS18B20.h>

class Thermometer: public Wt::WContainerWidget {
public:
	Thermometer(const char *, char *, Wt::WContainerWidget *parent = 0);

	virtual ~Thermometer();
	uint8_t getUnits();
	void setUnits(uint8_t);
	float getTemp();
	std::string getName();
	void setName(std::string);
	void updateTemp(Wt::WApplication *app);
private:
	Wt::WString temperature_;
	char* address_;
	char* name_;
	Wt::WGroupBox *groupingBox_;
	DS18B20 *dev;
	Wt::WText * temptext_;
};

#endif /* THERMOMETER_H_ */
