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
 * Name        : PowerOutletPlugin.h
 * Author      : Georgi Todorov
 * Version     :
 * Created on  : Jan 1, 2013
 *
 * Copyright © 2013 Georgi Todorov  <terahz@geodar.com>
 */

#ifndef POPLUGIN_H_
#define POPLUGIN_H_
#include <Wt/WContainerWidget>
#include <Wt/WTable>
#include "MCP23008.h"
#include "PowerOutlet.h"
#include "AquariusPlugin.hpp"

class PowerOutletPlugin : public AquariusPlugin {
public:
	PowerOutletPlugin();
	virtual ~PowerOutletPlugin();
private:
	void setOutlet(int pin, int state);
	MCP23008 *powerDriver;
	PowerOutlet *pos[8];
	Wt::WTable *poTable;

};
#endif /* POPLUGIN_H_ */
