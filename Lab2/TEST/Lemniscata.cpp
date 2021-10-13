#include <iostream>
#include <cmath>
#include "Lemniscata.h"
#include <exception>

Lemniscata_Bernoulli::Lemniscata::Lemniscata (double distance) {
	if (distance <= 0) {
		throw std::invalid_argument("Invalid value");
	} else {
		d = distance;
	}
}

void Lemniscata_Bernoulli::Lemniscata::SetDistance (double distance) {
	if (distance <= 0) {
		throw std::invalid_argument("Invalid value");
	} else {
		d = distance;
	}
}

double Lemniscata_Bernoulli::Lemniscata::Calculate_U (double angle) const {
	return sqrt(tan(PI/4 - angle));
}

double Lemniscata_Bernoulli::Lemniscata::Calculate_P (double angle) const {
	return sqrt(2*pow(d, 2)*cos(2*angle));
}

double Lemniscata_Bernoulli::Lemniscata::Find_X (double angle) const {
	return d*sqrt(2)*((Calculate_U(angle) + pow(Calculate_U(angle), 3))/((1 + pow(Calculate_U(angle), 4))));
}

double Lemniscata_Bernoulli::Lemniscata::Find_Y (double angle) const {
	return d*sqrt(2)*((Calculate_U(angle) - pow(Calculate_U(angle), 3))/((1 + pow(Calculate_U(angle), 4))));
}

double Lemniscata_Bernoulli::Lemniscata::DistanceToTheCenter (double angle) const {
	angle = 180*angle/PI;
	double x;
	double y;
	x = Find_X(angle);
	y = Find_Y(angle);
	return sqrt(x*x + y*y);
}

double Lemniscata_Bernoulli::Lemniscata::Area (void) const {
	return 2*pow(d, 2);
}

double Lemniscata_Bernoulli::Lemniscata::AreaOfTheSector (double angle) const {
	angle = 180*angle/PI;
	return sin(2*angle)*pow(d, 2)/2;
}

double Lemniscata_Bernoulli::Lemniscata::RadiusOfCurvature_ByAngle (double angle) const {
	angle = 180*angle/PI;
	return (2*pow(d, 2)/3)/Calculate_P(angle);
}

double Lemniscata_Bernoulli::Lemniscata::RadiusOfCurvature_ByLength (double length) const {
	if (length <= 0 || length > (d*sqrt(2))) {
		throw std::invalid_argument("Invalid value");
	} else {
		return (2*pow(d, 2)/(3*length));
	}
}