#pragma once
#include <cmath>
class player
{
public:
	player();

	~player();

	struct PositionandRotation
	{
		double x;
		double y;

		double xDir;
		double yDir;
	};
	
	inline PositionandRotation getPositionAndDirection() {
		return { m_xPos, m_yPos, m_xDir, m_yDir };
	}


	inline void MoveForward() {
		m_xPos += m_xDir;
		m_yPos += m_yDir;
	}
	inline void MoveBackwards() {
		m_xPos -= m_xDir;
		m_yPos -= m_yDir;
	}

	inline void RotateClockWise() {
		double oldDirX = m_xDir;
		m_xDir = m_xDir * cos(-m_rotatespeed) - m_yDir * sin(-m_rotatespeed);
		m_yDir = oldDirX * sin(-m_movespeed) + m_yDir * cos(-m_rotatespeed);
	}
	inline void RotateAntiClockWise() {
		double oldDirX = m_xDir;
		m_xDir = m_xDir * cos(m_rotatespeed) - m_yDir * sin(m_rotatespeed);
		m_yDir = oldDirX * sin(m_movespeed) + m_yDir * cos(m_rotatespeed);
	}

 


private:
	double m_xDir = 1, m_yDir = 0;
	double m_xPos = 1, m_yPos = 1;

	static const float m_movespeed;
	static const float m_rotatespeed;
	


};

