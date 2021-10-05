#pragma once

namespace Lemniscata_Bernoulli {

	const double PI = 3.1415926535897932384626433832795;

	class Lemniscata {
	private:
		double d;
		double angle_in_rad;
	public:
		Lemniscata (double distance = 80, double angle = 0);

		double GetDistance () const { return d; }
		double GetAngle () const { return angle_in_rad; }
		double GetRadAngle () const { return 180*angle_in_rad/PI; }
		void SetDistance (double distance = 5);
		void SetAngle (double angle = 0.523); //30 grad

		double DistanceToTheCenter (double angle) const;
		double RadiusOfCurvature_ByAngle (double angle) const;
		double RadiusOfCurvature_ByLength (double length) const;
		double AreaOfTheSector (double angle) const;
		double Area (void) const;
		double Calculate_U (double angle) const;
		double Calculate_P (double angle) const;
		double Find_X (double angle) const;
		double Find_Y (double angle) const;
	};
}
