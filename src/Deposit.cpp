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
	m_targetLevel(target)
{
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

Deposit::~Deposit()
{
	if (m_intake != NULL) {
		delete m_intake;
	}

	if (m_outtake != NULL) {
		delete m_outtake;
	}
}

float Deposit::run()
{
// 	static uint32_t iteration = 0;
	float newLevel;
	float newAperture;
	vector<float> errors;
	Rules consecuents;
	vector<float> graph;

// 	++iteration;

// 	if (iteration % 600 == 0) {
	m_error = m_targetLevel - m_currentLevel;
// 	}

	errors = difusion(m_error);
	consecuents = inference(errors);
	graph = composition(consecuents);
	newAperture = conclusion(graph);
	
	m_intake->setAperture(newAperture);
	m_capacity += m_intake->flow() - m_outtake->flow();
	newLevel = m_capacity / 100;
	
	if (newLevel < 0) {
		throw new exception;
	}

	m_currentLevel = newLevel;
	return m_currentLevel;
}

const vector<float>& Deposit::difusion(float value)
{
	vector<float> values;
	values.resize(3);
	values[NEGATIVE] = findPoint(m_negative, value);
	values[ZERO] = findPoint(m_zero, value);
	values[POSITIVE] = findPoint(m_positive, value);

	return *new vector<float>(move(values));
}

const Deposit::Rules& Deposit::inference(const vector<float>& error)
{
	Rules rules;
	/*
	R1: Si el error es negativo cerrar la válvula de entrada
	R2: Si el error es cero cerrar la válvula de entrada
	R3: Si el error es positivo abrir la válvula de entrada
	*/
	for (int32_t i = -25; i <= 100; ++i) {
		rules._1.push_back(fmin(error[NEGATIVE], findPoint(m_closed, i)));
		rules._2.push_back(fmin(error[ZERO], findPoint(m_closed, i)));
		rules._3.push_back(fmin(error[POSITIVE], findPoint(m_open, i)));
	}

	return *new Rules(rules);
}

const vector<float>& Deposit::composition(const Rules& rules)
{
	vector<float> graph;
	
	for (int32_t i = -25; i <= 100; ++i) {
		graph.push_back(fmax(rules._1[i], fmax(rules._2[i], rules._3[i])));
	}
	
	return *new vector<float>(move(graph));
}

float Deposit::conclusion(const vector<float>& data)
{
	float centroid;
	float top;
	float bot;

	top = 0.0;
	bot = 0.0;

	int32_t i = 0;
	for (auto it : data) {
		top += it * (i++ - 25);
		bot += it;
	}

	centroid = top / bot;
	
	return centroid;
}

float Deposit::findPoint(const Deposit::Triangle& triangle, float point)
{
	if (point < triangle.botL || point > triangle.botR) {
		return 0.0;
	}

	if (point <= triangle.top) {
		return (point - triangle.botL) / (triangle.top - triangle.botL);
	} else {
		return (point - triangle.botR) / (triangle.top - triangle.botR);
	}
}

float Deposit::findPoint(const Deposit::TrapezoidL& trap, float point)
{
	if (point <= trap.topL) {
		return 1.0;
	} else if (point > trap.topL && point < trap.bot) {
		return (point - trap.bot) / (trap.topL - trap.bot);
	} else {
		return 0.0;
	}
}

float Deposit::findPoint(const Deposit::TrapezoidR& trap, float point)
{
	if (point >= trap.topR) {
		return 1.0;
	} else if (point > trap.bot && point < trap.topR) {
		return (point - trap.bot) / (trap.topR - trap.bot);
	} else {
		return 0.0;
	}
}
