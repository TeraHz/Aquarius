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
	pl = new PluginLoader();
	tabs = new Wt::WTabWidget(root());
	tabs->currentChanged().connect(this, &Aquarius::updateTab);
}

Aquarius::~Aquarius() {
}

void Aquarius::load() {
	Wt::WContainerWidget * summaryContainer = new Wt::WContainerWidget();
	int pluginCount = 0;
	unsigned int ii = 0;
	tabs->addTab(summaryContainer, "Summary");
	if (pl) {
		pluginCount = pl->loadPlugins("./");
		if (pluginCount > 0) {
			for (ii = 0; ii < pl->getPlugins().size(); ii++) {
				std::cout << "Loading plugin" << std::endl;
				AquariusPlugin * plugin = pl->getPlugins()[ii];
				printf("Adding tab %d %s\n", ii, plugin->getName().c_str());
				plugins.push_back(plugin);
				tabs->addTab(plugin->getTab(), plugin->getName());
				summaryContainer->addWidget(plugin->getSummary());

			}
		} else {
			summaryContainer->addWidget(
					new Wt::WText(
							"<h2> Awww, you don't have any plugins installed</h2>"));
		}
	}
	tabs->setCurrentIndex(0);
}

void Aquarius::updateTab(int tab) {
	if (tab > 0) {
		printf("Updating tab %d %s\n", tab,
				plugins[tab - 1]->getName().c_str());
		plugins[tab - 1]->refresh();
	}
}

Wt::WApplication *createApplication(const Wt::WEnvironment& env) {
	Aquarius *aq = new Aquarius(env);
	Wt::WOverlayLoadingIndicator * loading = new Wt::WOverlayLoadingIndicator();
	aq->setLoadingIndicator(loading);
	aq->setCssTheme("polished");
	aq->loadingIndicator()->widget()->show();
	aq->load();
	aq->loadingIndicator()->widget()->hide();

	return aq;
}

int main(int argc, char **argv) {
	return Wt::WRun(argc, argv, &createApplication);
}
