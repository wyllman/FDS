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

#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <stdint.h>
#include <vector>

class Valve;

class Deposit {
private:
	struct Triangle {
		int32_t botL;
		int32_t top;
		int32_t botR;
	};
	
	struct TrapezoidL {
		int32_t topL;
		int32_t bot;
	};
	
	struct TrapezoidR {
		int32_t bot;
		int32_t topR;
	};
	
	float m_currentLevel;
	float m_targetLevel;
	float m_capacity;
	Valve* m_intake;
	Valve* m_outtake;
	float m_error;
	
	TrapezoidL m_negative;
	TrapezoidR m_positive;
	Triangle m_zero;
	
	TrapezoidR m_open;
	Triangle m_closed;
	
	const std::vector<float>& difusion(float);
	const std::vector<float>& inference(const std::vector<float>&);
	float conclusion(const std::vector<float>&);
	
public:
	Deposit(float, float, float, float);
	~Deposit();
	float level() { return m_currentLevel; }
	void setLevel(float);
	float target() { return m_targetLevel; }
	void setTarget(float);
	float run();
	float findPoint(const Triangle&, float);
	float findPoint(const TrapezoidL&, float);
	float findPoint(const TrapezoidR&, float);
};

#endif // DEPOSIT_H
