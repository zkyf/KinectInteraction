#include <Kinect.h>
#include <Windows.h>
#include <vector>
#include <algorithm>

using namespace std;

#ifndef _PUBLIC_H_
#define _PUBLIC_H_

typedef vector<POINT> DRAWLIST;
typedef vector<Joint> JOINTS;
typedef vector<JOINTS> JOINTSLIST;
typedef vector<POINT>::iterator DRAWITE;
typedef vector<Joint>::iterator JOINTP;

#endif