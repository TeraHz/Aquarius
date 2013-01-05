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
 * Name        : PowerOutlet.cpp
 * Author      : Georgi Todorov
 * Version     :
 * Created on  : Jan 3, 2013
 *
 * Copyright © 2013 Georgi Todorov  <terahz@geodar.com>
 */
#include "PowerOutlet.h"

using namespace Wt;

PowerOutlet::PowerOutlet(int pin, WContainerWidget *parent) :
		WContainerWidget(parent), pin_(pin) {
	setContentAlignment(AlignCenter);
	WString title = WString("Outlet {1}");
	title.arg(pin);
	groupingBox_ = new WGroupBox(title, this);
	buttonBox_ = new Wt::WButtonGroup(this);

	Wt::WRadioButton *button;
	button = new Wt::WRadioButton("On", groupingBox_);
	new Wt::WBreak(groupingBox_);
	buttonBox_->addButton(button, On);

	button = new Wt::WRadioButton("Off", groupingBox_);
	new Wt::WBreak(groupingBox_);
	buttonBox_->addButton(button, Off);

	buttonBox_->checkedChanged().connect(this, &PowerOutlet::setOutlet);
	groupingBox_->addWidget(new Wt::WBreak());
}

void PowerOutlet::setOutlet() {
	state_.emit(pin_, buttonBox_->checkedId());
}

void PowerOutlet::setSelected(uint8_t state) {
	buttonBox_->setCheckedButton(buttonBox_->button(state));
}
