#pragma once

namespace Lemniscata_Bernoulli {
	const double PI = 3.1415926535897932384626433832795;

	class Lemniscata {
	private:
		double Calculate_U (double angle) const;
		double Calculate_P (double angle) const;
		double Find_X (double angle) const;
		double Find_Y (double angle) const;
		double d;
	public:
		Lemniscata (double distance = 80);

		double GetDistance () const { return d; }
		void SetDistance (double distance = 5);

		double DistanceToTheCenter (double angle) const;
		double RadiusOfCurvature_ByAngle (double angle) const;
		double RadiusOfCurvature_ByLength (double length) const;
		double AreaOfTheSector (double angle) const;
		double Area (void) const;
	};
}
