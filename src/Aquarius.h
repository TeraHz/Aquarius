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
 * Name        : Aquarius.h
 * Author      : Georgi Todorov
 * Version     :
 * Created on  : Dec 30, 2012
 *
 * Copyright © 2012 Georgi Todorov  <terahz@geodar.com>
 */

#ifndef _AQUARIUS_H
#define _AQUARIUS_H
#include <Wt/WApplication>
#include <Wt/WEnvironment>
#include <Wt/WTable>
#include "LEDChannel.h"
#include "PowerOutlet.h"
#include "PCA9685.h"
#include "MCP23008.h"

class Aquarius : public Wt::WApplication
{
public:
    Aquarius(const Wt::WEnvironment& env);
    ~Aquarius();

private:
    void setPWM(int channel, int value);
    void setOutlet(int pin, int value);
    PCA9685 *pwmDriver;
    MCP23008 *powerDriver;
    LEDChannel *leds[16];
    PowerOutlet * pos[8];
    Wt::WTable *ledTable;
    Wt::WTable *poTable;
};

#endif

