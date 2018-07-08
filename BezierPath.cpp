#include "BezierPath.h"

BezierPath::BezierPath() {}

BezierPath::~BezierPath() {}

void BezierPath::AddCurve(BezierCurve curve, int samples)
{
	kCurves.push_back(curve); 
	kSamples.push_back(samples); 
}

void BezierPath::Sample(std::vector<Vector2>* sampledPath)
{
	for (int i=0; i<kCurves.size(); i++)
	{
		for ( float t=0.0f; t <= 1.0f; t += (1.0f / kSamples[i]) )
		{
			sampledPath->push_back(kCurves[i].CalculateCurvePoint(t)); 
		}
	}
}