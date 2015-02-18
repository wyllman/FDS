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

#include "Deposit.h"
#include "Valve.h"

#include <cstdlib>
#include <cmath>
#include <exception>
#include <iostream>

using namespace std;

Deposit::Deposit(float level, float target, float in, float out) :
	m_currentLevel(level),
	m_targetLevel(target) {
	m_intake = new Valve(in, 0);
	m_outtake = new Valve(out, 100);
	m_capacity = m_currentLevel * m_BASE * m_BASE;
	m_error = m_targetLevel - m_currentLevel;

	m_negative.topL = -10;
	m_negative.bot = 0;

	m_zero.botL = -5;
	m_zero.top = 0;
	m_zero.botR = 5;

	m_positive.bot = 0;
	m_positive.topR = 10;

	m_open.bot = 0;
	m_open.topR = 50;

	m_closed.botL = -25;
	m_closed.top = 0;
	m_closed.botR = 25;
}

Deposit::~Deposit() {
	if (m_intake != NULL) {
		delete m_intake;
	}

	if (m_outtake != NULL) {
		delete m_outtake;
	}
}

float Deposit::run() {
	static uint32_t iteration = 0;
	float newLevel;
	float newAperture;
	vector<float> error;
	vector<float> data;

	++iteration;

	if (iteration % 1800 == 0) {
		m_error = m_targetLevel - m_currentLevel;
// 		cout << "error level: " << m_error << endl;
	}

	error = difusion(m_error);
// 	cout << "difusion" << endl;
// 	for (auto it : error) {
// 		cout << it << endl;
// 	}
	data = inference(error);
// 	cout << "inference" << endl;
// 	for (auto it : data) {
// 		cout << it << endl;
// 	}

	newAperture = conclusion(data);
// 	cout << "Setting aperture to " << newAperture << endl;
	m_intake->setAperture(conclusion(data));
// 	cout << "Capacity before flow: " << m_capacity << endl;
	m_capacity += m_intake->flow() - m_outtake->flow();
// 	cout << "Capacity after flow: " << m_capacity << endl;
	newLevel = m_capacity / 100;
// 	cout << "New level: " << newLevel << endl;
// 	cin.get();

	if (newLevel < 0) {
		throw new exception;
	}

	m_currentLevel = newLevel;
	return m_currentLevel;
}

const vector<float>& Deposit::difusion(float value) {
	vector<float> values;
	values.resize(3);
	values[0] = findPoint(m_negative, value);
	values[1] = findPoint(m_zero, value);
	values[2] = findPoint(m_positive, value);
	for (auto it : values) {
		cout << it << endl;
	}
	cin.get();

	return *new vector<float>(values);
}

const vector<float>& Deposit::inference(const vector<float>& error) {
	vector<float> what;
	float max;

	for (int32_t i = -25; i <= 100; ++i) {
		max = fmax(findPoint(m_closed, i), findPoint(m_open, i));

		if (i <= 25) {
			what.push_back(fmin(error[0], fmin(error[1], max)));
		} else {
			what.push_back(fmin(error[2], max));
		}
	}

	return *new vector<float>(what);
}

float Deposit::conclusion(const vector<float>& data) {
	float centroid;
	float top;
	float bot;

	top = 0;
	bot = 0;

	int32_t i = 0;
	for (auto it : data) {
		top += it * (i++ - 25);
		bot += it;
	}

	centroid = top / bot;
	return centroid;
}

float Deposit::findPoint(const Deposit::Triangle& triangle, float point) {
	if (point < triangle.botL || point > triangle.botR) {
		return 0.0;
	}

	if (point <= triangle.top) {
		return (point - triangle.botL) / (triangle.top - triangle.botL);
	} else {
		return (point - triangle.botR) / (triangle.top - triangle.botR);
	}
}

float Deposit::findPoint(const Deposit::TrapezoidL& trap, float point) {
	if (point <= trap.topL) {
		return 1.0;
	} else if (point > trap.topL && point < trap.bot) {
		return (point - trap.bot) / (trap.topL - trap.bot);
	} else {
		return 0.0;
	}
}

float Deposit::findPoint(const Deposit::TrapezoidR& trap, float point) {
	if (point >= trap.topR) {
		return 1.0;
	} else if (point > trap.bot && point < trap.topR) {
		return (point - trap.bot) / (trap.topR - trap.bot);
	} else {
		return 0.0;
	}
}