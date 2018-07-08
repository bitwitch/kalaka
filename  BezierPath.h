#ifndef _BEZIERPATH_H
#define _BEZIERPATH_H

#include "MathHelper.h"
#include <vector>

// using namespace "Ather";

class BezierPath 
{
private:
	std::vector<BezierCurve> kCurves;
	std::vector<int> kSamples; 	

public:
	BezierPath();
	~BezierPath();

	void AddCurve(BezierCurve curve, int samples); 
	void Sample(std::vector<Vector2>* sampledPath); 
};

#endif