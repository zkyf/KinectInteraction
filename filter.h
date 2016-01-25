#include "Matrix.h"
#include "public.h"

#ifndef _FILTER_H_
#define _FILTER_H_

using namespace ljxMat;

class Filter
{
	private:
	static const int Median_limit = 9;
	Joint Medians[Median_limit + 1];
	int Median_count = 0;
	int Median_num = 0;

	static const int Average_limit = 9;
	Joint Averages[Average_limit + 1];
	int Average_Coe[Average_limit];
	int Average_count = 0;
	int Average_num = 0;

	static const int Polynal_limit = 4;
	Joint Polynals[Polynal_limit + 1];
	int Polynal_count = 0;
	int Polynal_num = 0;

	static const int Kalman_limit = 5;
	Joint Kalmans[Kalman_limit + 1];
	int Kalman_count = 0;
	int Kalman_num = 0;
	Matrix Kalman_ex;/*(4, 4)*/
	Matrix Kalman_ey;/*(4, 4)*/
	Matrix Kalman_vx;/*(1, 1)*/
	Matrix Kalman_vy;/*(1, 1)*/
	Matrix Kalman_C ;/*(1, 4)*/
	Matrix Kalman_Sx;/*(4, 1)*/
	Matrix Kalman_Sy;/*(4, 1)*/
	Matrix Kalman_Gx;/*(4, 1)*/
	Matrix Kalman_Gy;/*(4, 1)*/

	public:
	Filter();

	void Median(Joint joint, double &dx, double &dy);
	void Median_Clear();
	JOINTS Filter_Median_Gen(JOINTS joints);
	Joint Filter_Median(Joint now);

	void Average(Joint joint, double &dx, double &dy);
	void Average_Clear();
	Joint Filter_Average(Joint now);
	JOINTS Filter_Average_Gen(JOINTS joints);

	void Polynal(Joint joint, double &dx, double &dy);
	void Polynal_Clear();
	Joint Filter_Polynal(Joint now);
	JOINTS Filter_Polynal_Gen(JOINTS joints);

	void Kalman(Joint joint, double &dx, double &dy);
	void Kalman_Clear();
	void Kalman_Set(Matrix C, Matrix vx, Matrix vy, Matrix ex, Matrix ey);
	Joint Filter_Kalman(Joint now);

	Joint JoyStick(Joint joint);

};


#endif