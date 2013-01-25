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
 * Name        : PluginLoader.cpp
 * Author      : Georgi Todorov
 * Version     :
 * Created on  : Jan 1, 2012
 *
 * Copyright © 2013 Georgi Todorov  <terahz@geodar.com>
 */
#include "PluginLoader.h"

PluginLoader::PluginLoader() {

}

PluginLoader::~PluginLoader() {
	for (unsigned int i = 0; i < plugins.size(); i++){
		//printf("Destroying plugin %d, %s\n", i, plugins[i]->getName().c_str());
		plugin_destructor[i](plugins[i]);
	}

}
int PluginLoader::loadPlugins(const char *path) {
	int counter = 0;
	DIR *dp;
	struct dirent *dirp;
	char pluginpath[255];

	if ((dp = opendir(path)) == NULL) {
		perror("Could not open directory");
		return errno;
	}
	while ((dirp = readdir(dp)) != NULL) {
		std::string entry = dirp->d_name;
//		std::cout << "Checking entry " << dirp->d_name << std::endl;

		if (std::string::npos != entry.find("Plugin")) {
//			std::cout << "Possible plugin found. Let's try to load " << dirp->d_name << std::endl;
			snprintf(pluginpath, 255, "%s%s", path, entry.c_str());
			if (tryToAdd(pluginpath) == 0)
				counter++;
		}
	}
	closedir(dp);
	return counter;
}

int PluginLoader::tryToAdd(const char *file) {
	void *plugin_h = dlopen(file, RTLD_NOW);
	if (!plugin_h)
		std::cout << "Could not open plugin " << file << dlerror() << std::endl;

	create_t* create_plugin = (create_t*) dlsym(plugin_h, "create");
	destroy_t* destroy_plugin = (destroy_t*) dlsym(plugin_h, "destroy");

	if (!create_plugin || !destroy_plugin) {
		std::cout << "Could not load symbols for " << file << dlerror()
				<< std::endl;
		return 1;
	}

	AquariusPlugin * plugin = create_plugin();

	if (plugin) {
		plugins.push_back(plugin);
		plugin_destructor.push_back(destroy_plugin);
		return 0;
	} else
		std::cout << "Could not create object pointer  " << file << dlerror()
				<< std::endl;

	return 1;
}

std::vector<AquariusPlugin*> PluginLoader::getPlugins() {
	return plugins;
}
