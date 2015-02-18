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

#include "Valve.h"

Valve::Valve(float flow, float aperture) :
	m_flow(flow),
	m_aperture(aperture) {

}

Valve::~Valve() {

}

float Valve::flow() {
	if (m_aperture > 0) {
		return m_flow * (m_aperture / 100);
	}

	return 0.0;
}

void Valve::setAperture(float ap) {
	if (ap >= -25 && ap <= 100) {
		m_aperture = ap;
	}
}
