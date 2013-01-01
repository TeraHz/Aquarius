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
 * Name        : PoweOutlet.h
 * Author      : Georgi Todorov
 * Version     :
 * Created on  : Dec 30, 2012
 *
 * Copyright © 2012 Georgi Todorov  <terahz@geodar.com>
 */

#ifndef _POWEROUTLET_H
#define _POWEROUTLET_H
#include <Wt/WContainerWidget>
#include <Wt/WGroupBox>
#include <Wt/WRadioButton>
#include <Wt/WButtonGroup>
#include <Wt/WSignal>
#include <Wt/WText>
#include <Wt/WBreak>
#include <inttypes.h>

class PowerOutlet : public Wt::WContainerWidget
{
public:
	PowerOutlet(const int pin, Wt::WContainerWidget *parent = 0);
    Wt::Signal<int,int>& valueChanged() { return state_; }

    void setSelected(uint8_t);
private:
    enum State { On = 1, Off = 0};
    Wt::WGroupBox     *groupingBox_;
    Wt::WButtonGroup   *buttonBox_;
    Wt::Signal<int,int>   state_;

    int               pin_;

    void setOutlet();
};

#endif

