#pragma once
#include"olcPixelGameEngine.h"

struct Splines
{
	std::vector<olc::v2d_generic<float>> vecPoints2d;
	std::vector<float> vecLength;
	float totalLength;
	//methods
	olc::v2d_generic<float> getSplinePoint(float t, bool isLoop = false)
	{
		//indices base upon t values
		int p0, p1, p2, p3;
		//normal calculations for spline
		if (!isLoop)
		{
			p1 = (int)t + 1;
			p2 = p1 + 1;
			p3 = p1 + 2;
			p0 = p1 - 1;
		}
		else
		{
			//loop calculations, join first and last points to spline
			p1 = (int)t;
			p2 = (p1 + 1) % vecPoints2d.size();
			p3 = (p2 + 1) % vecPoints2d.size();
			p0 = (p1 >= 1) ? p1 - 1 : vecPoints2d.size() - 1;
		}

		//down the value back less than 1
		t = t - (int)t;

		//cuadratic & cube values
		float t_square = t * t;
		float t_cube = t_square * t;

		//Ecuations for interpolation (influential fields values)
		float ec1 = -t_cube + 2.0f * t_square - t;
		float ec2 = 3.0f * t_cube - 5.0f * t_square + 2.0f;
		float ec3 = -3.0f * t_cube + 4.0f * t_square + t;
		float ec4 = t_cube - t_square;

		//x,y axis value(multiply by 0.5 to return a value between 1 and 0)
		float x_interpolation = 0.5f * (vecPoints2d[p0].x * ec1 + vecPoints2d[p1].x * ec2 + vecPoints2d[p2].x * ec3 + vecPoints2d[p3].x * ec4);
		float y_interpolation = 0.5f * (vecPoints2d[p0].y * ec1 + vecPoints2d[p1].y * ec2 + vecPoints2d[p2].y * ec3 + vecPoints2d[p3].y * ec4);


		return { x_interpolation, y_interpolation };
	}

	olc::v2d_generic<float> getGradientPoint(float t, bool isLoop = false)
	{
		//indices base upon t values
		int p0, p1, p2, p3;
		//normal calculations for spline
		if (!isLoop)
		{
			p1 = (int)t + 1;
			p2 = p1 + 1;
			p3 = p1 + 2;
			p0 = p1 - 1;
		}
		else
		{
			//loop calculations, join first and last points to spline
			p1 = (int)t;
			p2 = (p1 + 1) % vecPoints2d.size();
			p3 = (p2 + 1) % vecPoints2d.size();
			p0 = (p1 >= 1) ? p1 - 1 : vecPoints2d.size() - 1;
		}

		//down the value back less than 1
		t = t - (int)t;

		//cuadratic &  values
		float t_square = t * t;

		//Ecuations for interpolation (influential fields values)
		float ec1 = -3.0f * t_square + 4.0f * t - 1.0f;
		float ec2 = 9.0f * t_square - 10.0f * t;
		float ec3 = -9.0f * t_square + 8.0f * t + 1.0f;
		float ec4 = 3.0f * t_square - 2.0f * t;

		//x,y axis value(multiply by 0.5 to return a value between 1 and 0)
		float x_interpolation = 0.5f * (vecPoints2d[p0].x * ec1 + vecPoints2d[p1].x * ec2 + vecPoints2d[p2].x * ec3 + vecPoints2d[p3].x * ec4);
		float y_interpolation = 0.5f * (vecPoints2d[p0].y * ec1 + vecPoints2d[p1].y * ec2 + vecPoints2d[p2].y * ec3 + vecPoints2d[p3].y * ec4);


		return { x_interpolation, y_interpolation };
	}

	float CalculateSegmentLength(int node, bool isLoop = false)
	{
		float length = 0.0f;
		float stepSize = 0.01f;

		olc::v2d_generic<float> oldPoint, newPoint;
		oldPoint = getSplinePoint((float)node, isLoop);

		for (float t = 0.0f; t < 1.0f; t += stepSize)
		{
			newPoint = getSplinePoint((float)node + t, isLoop);

			length += sqrtf((newPoint.x - oldPoint.x) * (newPoint.x - oldPoint.x) + (newPoint.y - oldPoint.y) * (newPoint.y - oldPoint.y));
			oldPoint = newPoint;
		}

		return length;
	}

	float getNormalizedOffset(float pos_length)
	{
		//find  node base
		int i = 0;
		while (pos_length > vecLength[i])
		{
			pos_length -= vecLength[i];
			i++;
		}
		//the remainder is the offset
		return (float)i + (pos_length / vecLength[i]);
	}
};
