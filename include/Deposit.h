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
	
	static constexpr float m_BASE = 10.0; //!< Deposit size (Assumed square)
	float m_currentLevel; //!< Deposit water level in meters
	float m_targetLevel; //!< Deposit target water level in meters
	float m_capacity; //!< Deposit capacity in m³ (m_BASE^2 * m_currentLevel)
	Valve* m_intake; //!< Intake valve
	Valve* m_outtake; //!< Outtake valve
	float m_error; //!<
	
	TrapezoidL m_negative;
	TrapezoidR m_positive;
	Triangle m_zero;
	
	TrapezoidR m_open;
	Triangle m_closed;
	
	const std::vector<float>& difusion(float);
	const std::vector<float>& inference(const std::vector<float>&);
	float conclusion(const std::vector<float>&);
	
public:
	/**
	 * @fn CTOR
	 * @param level Water level in meters
	 * @param target Target water level in meters
	 * @param in Intake valve flow in m³/s
	 * @param out Outtake valve flow in m³/s
	 */
	Deposit(float, float, float, float);
	/**
	 * @fn DTOR
	 */
	~Deposit();
	/**
	 * @fn float level()
	 * @brief Deposit current level in meters.
	 */
	float level() { return m_currentLevel; }
	/**
	 * @fn float target()
	 * @brief Deposit target level in meters.
	 */
	float target() { return m_targetLevel; }
	/**
	 * @fn float run()
	 * @brief Runs the FDS
	 * 
	 * This methos runs all the steps required for a fuzzy decision system
	 * and returns the resulting water level.
	 */
	float run();
	/**
	 * @fn float findPoint(const Triangle&, float)
	 * @param triangle The defined triangle figure of the inference.
	 * @param point The point which truth value is to be calculated.
	 * @return The truth value of the point.
	 */
	float findPoint(const Triangle&, float);
	/**
	 * @fn float findPoint(const TrapezoidL&, float)
	 * @param trap The defined left leaned trapezoid figure of the inference.
	 * @param point The point which truth value is to be calculated.
	 * @return The truth value of the point.
	 */
	float findPoint(const TrapezoidL&, float);
	/**
	 * @fn float findPoint(const TrapezoidR&, float)
	 * @param trap The defined right leaned trapezoid figure of the inference.
	 * @param point The point which truth value is to be calculated.
	 * @return The truth value of the point.
	 */
	float findPoint(const TrapezoidR&, float);
};

#endif // DEPOSIT_H
