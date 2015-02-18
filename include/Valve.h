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

#ifndef VALVE_H
#define VALVE_H

class Valve {
private:
	float m_flow; //!< Valve flow at max aperture
	float m_aperture; //!< Valve aperture as a percentage
public:
	/**
	 * @brief CTOR
	 * @param flow Sets the valve flow at max aperture (m³/s)
	 * @param aperture Sets the initial aperture
	 */
	Valve(float, float);
	~Valve();
	/**
	 * @fn float flow()
	 * @brief Current flow through the valve
	 * @return flow in (m³/s)
	 */
	float flow();
	/**
	 * @fn setAperture(float)
	 * @brief Sets the aperture of the valve
	 * @param ap aperture value [-25,100]
	 */
	void setAperture(float);
};

#endif // VALVE_H
