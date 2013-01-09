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
 * Name        : ThermometerPlugin.cpp
 * Author      : Georgi Todorov <terahz@geodar.com>
 * Version     : 
 * Created on  : Jan 3, 2013
 *
 * Copyright © 2013 Georgi Todorov <terahz@geodar.com>
 */

#include "ThermometerPlugin.h"

ThermometerPlugin::ThermometerPlugin() {
	name_ = "Temperature";

	DIR *dirp;
	struct dirent *dp;
	dirp = opendir(BUSPATH);
	if (dirp == NULL) {
		perror("opendir failed");
	}

	for (;;) {
		errno = 0; /* To distinguish error from end-of-directory */
		dp = readdir(dirp);
		if (dp == NULL)
			break;
		if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0
				|| strcmp(dp->d_name, "w1_bus_master1") == 0)
			continue; /* Skip .  .. and w1_bus_master1 */
		addresses_.push_back(dp->d_name);
	}

	if (errno != 0)
		perror("readdir");
	if (closedir(dirp) == -1)
		perror("closedir");
}

ThermometerPlugin::~ThermometerPlugin() {
}

Wt::WContainerWidget * ThermometerPlugin::getSummary() {
	Wt::WContainerWidget *summaryContainer_ = new Wt::WContainerWidget();
	Wt::WString str = "Found {1} Probes";
	str.arg((int) addresses_.size());
	summaryContainer_->addWidget(new Wt::WText(str));
	return summaryContainer_;
}

Wt::WContainerWidget * ThermometerPlugin::getTab() {
	Wt::WContainerWidget *tabContainer_ = new Wt::WContainerWidget();
	Wt::WTable *tTable = new Wt::WTable(tabContainer_);
	unsigned int ii = 0;
	tTable = new Wt::WTable(tabContainer_);
	for (ii = 0; ii < addresses_.size(); ii++) {
		char ntitle[12];
		sprintf(ntitle, "Probe %d", ii + 1);
		try {
			Thermometer * t = new Thermometer(addresses_[ii].c_str(), ntitle);
			thermos_.push_back(t);
			tTable->elementAt((int) ii / 8, ii % 8)->addWidget(t);
		} catch (int e) {
			errno = e;
			perror("OOPS");
		}
	}
	refresh();

	return tabContainer_;
}

std::string ThermometerPlugin::getName() {
	return name_;
}

void ThermometerPlugin::refresh() {
	unsigned int ii = 0;
	Wt::WApplication *app = Wt::WApplication::instance();
	for (ii = 0; ii < thermos_.size(); ii++) {
		Thermometer *thermo = (Thermometer *) thermos_[ii];
		new boost::thread(
				boost::bind(&Thermometer::updateTemp, thermo, app));
	}
}

// the class factories
extern "C" AquariusPlugin* create() {
	return new ThermometerPlugin();
}

extern "C" void destroy(AquariusPlugin* p) {
	delete p;
}
