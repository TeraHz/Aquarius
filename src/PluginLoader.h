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
 * Name        : PluginLoader.h
 * Author      : Georgi Todorov
 * Version     :
 * Created on  : Jan 1, 2012
 *
 * Copyright © 2013 Georgi Todorov  <terahz@geodar.com>
 */

#ifndef PLUGINLOADER_H_
#define PLUGINLOADER_H_
#include <dlfcn.h>
#include <syslog.h>
#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
#include <errno.h>
#include "AquariusPlugin.hpp"

class PluginLoader {
public:
	PluginLoader();
	virtual ~PluginLoader();
	int loadPlugins(const char *path);
	std::vector<AquariusPlugin*> getPlugins();
private:
	int tryToAdd(const char *file);
	std::vector<AquariusPlugin*> plugins;

};

#endif /* PLUGINLOADER_H_ */
