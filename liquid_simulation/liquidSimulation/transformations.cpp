// 
// Michael Shafae
// mshafae at fullerton.edu
// 
// Procedural module that implements transformations used in
// the homework assignment.
//
// $Id: transformations.cpp 5672 2015-04-09 01:55:03Z mshafae $
//
// STUDENTS _MUST_ ADD THEIR CODE INTO THIS FILE
//

#include "transformations.h"

#ifndef __SOLUTION__

void rotateCameraLeft(float degrees, Vec3& eyePosition, Vec3& centerPosition, Vec3& upVector){
	// Please implement this function.
	Vec3 upNorm = normalize(upVector);
	Mat4 rotation = rotate(degrees, upNorm);
	Mat3 rotMat;

	rotMat[0][0] = rotation[0][0];
	rotMat[0][1] = rotation[0][1];
	rotMat[0][2] = rotation[0][2];
	rotMat[1][0] = rotation[1][0];
	rotMat[1][1] = rotation[1][1];
	rotMat[1][2] = rotation[1][2];
	rotMat[2][0] = rotation[2][0];
	rotMat[2][1] = rotation[2][1];
	rotMat[2][2] = rotation[2][2];

	eyePosition = (rotMat * (eyePosition - centerPosition)) + centerPosition;
}

void rotateCameraUp(float degrees, Vec3& eyePosition, Vec3& centerPosition, Vec3& upVector){
	// Please implement this function.
	Vec3 axis = normalize(cross(eyePosition, upVector));
	Mat4 rotation = rotate(degrees, axis);
	Mat3 rotMat;

	rotMat[0][0] = rotation[0][0];
	rotMat[0][1] = rotation[0][1];
	rotMat[0][2] = rotation[0][2];
	rotMat[1][0] = rotation[1][0];
	rotMat[1][1] = rotation[1][1];
	rotMat[1][2] = rotation[1][2];
	rotMat[2][0] = rotation[2][0];
	rotMat[2][1] = rotation[2][1];
	rotMat[2][2] = rotation[2][2];

	eyePosition = (rotMat * (eyePosition - centerPosition)) + centerPosition;

	upVector = normalize(rotMat*upVector);
}


#else
#include "transformations_solution.cpp"
#endif
