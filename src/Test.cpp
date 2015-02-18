/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2014  Juan Hernández Hernández <janukato@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "Test.h"
#include "Deposit.h"
#include "gnuplot-iostream.h"

#include <iostream>

using namespace std;

Test::Test(Deposit& deposit, uint32_t seconds) :
    m_deposit(&deposit),
	m_runningTime(seconds)
	{

}

Test::~Test() {

}

void Test::run() {
	for (uint32_t i = 0; i <= m_runningTime; ++i) {
		float level;
		level = m_deposit->run();
		cout << i << ": " << level << "m" << endl;
		m_levels.push_back(level);
	}
}

void Test::plot() {
	Gnuplot gp;
	
	gp << "set xlabel 'T(s)'\n";
	gp << "set ylabel 'A(m)'\n";
	gp << "plot '-' with lines title 'water level'\n";
	
	gp.send1d(m_levels);
}
