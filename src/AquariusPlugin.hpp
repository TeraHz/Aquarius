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
 * Name        : AquariusPlugin.hpp
 * Author      : Georgi Todorov
 * Version     :
 * Created on  : Jan 1, 2012
 *
 * Copyright © 2013 Georgi Todorov  <terahz@geodar.com>
 */

#ifndef _AQUARIUSPLUGIN_H
#define _AQUARIUSPLUGIN_H
#include <Wt/WContainerWidget>

class AquariusPlugin {
protected:

public:
//	AquariusPlugin(){}
	virtual ~AquariusPlugin(){};
	virtual Wt::WContainerWidget * getSummary() = 0;
	virtual Wt::WContainerWidget * getTab() = 0;
	virtual std::string getName() = 0;
	virtual void refresh() = 0;

};

// the types of the class factories
typedef AquariusPlugin* create_t();
typedef void destroy_t(AquariusPlugin*);

#endif /* _AQUARIUSPLUGIN_H */
