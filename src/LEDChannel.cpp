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
 * Name        : LEDChannel.cpp
 * Author      : Georgi Todorov
 * Version     :
 * Created on  : Dec 30, 2012
 *
 * Copyright © 2012 Georgi Todorov  <terahz@geodar.com>
 */
#include "LEDChannel.h"

using namespace Wt;

LEDChannel::LEDChannel(int channel, WContainerWidget *parent)
    : WContainerWidget(parent),
      channel_(channel)
{
    setContentAlignment(AlignCenter);
    WString title = WString("Channel {1}");
    title.arg(channel_);
    groupingBox_ = new WGroupBox(title, this);

    valueBox_ = new WSpinBox(groupingBox_);
    valueBox_->setRange(0,4095);
    valueBox_->valueChanged().connect(this, &LEDChannel::setPWM); 
    groupingBox_->addWidget(new Wt::WBreak());
    text_ = new WText(groupingBox_);
    text_->setText("<small>0 - off; 4095 - max</small>");
}

void LEDChannel::setPWM()
{
	pwm_.emit(channel_, valueBox_->value());
}
