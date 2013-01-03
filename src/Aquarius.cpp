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
 * Name        : Aquarius.cpp
 * Author      : Georgi Todorov
 * Version     :
 * Created on  : Dec 30, 2012
 *
 * Copyright © 2012 Georgi Todorov  <terahz@geodar.com>
 */

#include "Aquarius.h"

Aquarius::Aquarius(const Wt::WEnvironment& env) :
		Wt::WApplication(env) {
	this->setCssTheme("polished");
	int pluginCount = 0;
	unsigned int ii = 0;
	pl = new PluginLoader();
	tabs = new Wt::WTabWidget(root());
	Wt::WContainerWidget * summaryContainer = new Wt::WContainerWidget();
	tabs->addTab(summaryContainer, "Summary");
	if (pl) {
		pluginCount = pl->loadPlugins("./");
		if (pluginCount > 0) {
			for (ii = 0; ii < pl->getPlugins().size(); ii++) {
				std::cout << "Loading plugin" << std::endl;
				AquariusPlugin * plugin = pl->getPlugins()[ii];
				tabs->addTab(plugin->getTab(), plugin->getName());
				summaryContainer->addWidget(plugin->getSummary());
			}
		}else{
			summaryContainer->addWidget(new Wt::WText("<h2> Awww, you don't have any plugins installed</h2>"));
		}
	}
	tabs->setCurrentIndex(0);

}

Aquarius::~Aquarius() {

}

Wt::WApplication *createApplication(const Wt::WEnvironment& env) {
	Aquarius *aq = new Aquarius(env);
	aq->setCssTheme("polished");
	return aq;
}

int main(int argc, char **argv) {
	return Wt::WRun(argc, argv, &createApplication);
}
