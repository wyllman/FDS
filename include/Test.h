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

#ifndef TEST_H
#define TEST_H

#include <vector>
#include <cstdint>

class Deposit;

class Test {
private:
	Deposit *m_deposit;
	uint32_t m_runningTime;
	std::vector<float> m_levels;
public:
	/**
	 * @fn CTOR
	 * @param deposit Deposit object to be tested
	 * @param seconds Simulation duration
	 */
    Test(Deposit&, uint32_t);
	~Test();
	void run();
	void plot();
};

#endif // TEST_H
