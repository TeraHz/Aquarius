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
 * Name        : ThermometerPlugin.h
 * Author      : Georgi Todorov <terahz@geodar.com>
 * Version     : 
 * Created on  : Jan 3, 2013
 *
 * Copyright © 2013 Georgi Todorov <terahz@geodar.com>
 */

#ifndef THERMOMETERPLUGIN_H_
#define THERMOMETERPLUGIN_H_
#include <Wt/WContainerWidget>
#include <Wt/WTable>
#include <Wt/WText>
#include <Wt/WString>
#include <dirent.h>
#include <syslog.h>
#include <errno.h>
#include <vector>
#include "Thermometer.h"
#include "AquariusPlugin.hpp"

#define BUSPATH "/sys/bus/w1/devices/"

class ThermometerPlugin: public AquariusPlugin {
public:
	ThermometerPlugin();
	virtual ~ThermometerPlugin();
	Wt::WContainerWidget * getSummary();
	Wt::WContainerWidget * getTab();
	std::string getName();
	void refresh();
private:
	std::string name_;
	std::vector<std::string> addresses_;
	std::vector<Thermometer*> thermos_;

};

#endif /* THERMOMETERPLUGIN_H_ */
