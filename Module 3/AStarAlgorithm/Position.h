#pragma once

class Position {
	int x_, y_;

public:
	Position();

	int x() const { return x_; }
	int y() const { return y_; }

	void SetPosition(int _x, int _y);
	
	int GetPosition() { return x_, y_; }

	/// <summary>
	/// Returns the maganitude of x^2 + y^2
	/// </summary>
	/// <returns></returns>
	int GetMagnitude() { return (x_ * x_) + (y_ * y_); }

	/// <summary>
	/// Returns the distance between this point and the next.
	/// </summary>
	/// <param name="pos2"></param>
	/// <returns></returns>
	int GetDistance(Position pos2) {
		return sqrt(pos2.GetMagnitude() - GetMagnitude());
	}

};