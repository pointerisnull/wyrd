#include "math.h"

#include <math.h>


/* 3D Vectors */

float abs_v3(Vec3 v) {
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

float dot_v3(Vec3 v, Vec3 w) {
	return v.x*w.x + v.y*w.y + v.z*w.z;
}

Vec3 scale_v3(Vec3 v, float s) {
	Vec3 a = {v.x*s, v.y*s, v.z*s};
	return a;
}

Vec3 cross_v3(Vec3 v, Vec3 w) {
	Vec3 a = {(v.y*w.z)-(v.z*w.y), (v.z*w.x)-(v.x*w.z), (v.x*w.y-v.y*w.x)};
	return a;
}

Vec3 zero_v3() {
	Vec3 z = {0.0, 0.0, 0.0};
	return z;
}

Vec3 norm_v3(Vec3 v) {
	float vabs = abs_v3(v);
	if (vabs == 0.0)
		return zero_v3();
	Vec3 vn = {v.x/vabs, v.y/vabs, v.z/vabs};
	return vn;
}

/* 3x3 Matrices */

Mat3 new_m3() {
	Mat3 m = {{0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}};
	return m; 
}

Mat3 identity_m3() {
	Mat3 i = {{1.0,0.0,0.0}, {0.0,1.0,0.0}, {0.0,0.0,1.0}};
	return i;
}

Mat3 mult_m3(Mat3 m1, Mat3 m2) {
	Mat3 m;

	// Row 1
	m.a1.x = m1.a1.x * m2.a1.x + m1.a1.y * m2.a2.x + m1.a1.z * m2.a3.x;
	m.a1.y = m1.a1.x * m2.a1.y + m1.a1.y * m2.a2.y + m1.a1.z * m2.a3.y;
	m.a1.z = m1.a1.x * m2.a1.z + m1.a1.y * m2.a2.z + m1.a1.z * m2.a3.z;
	
	// Row 2
	m.a2.x = m1.a2.x * m2.a1.x + m1.a2.y * m2.a2.x + m1.a2.z * m2.a3.x;
	m.a2.y = m1.a2.x * m2.a1.y + m1.a2.y * m2.a2.y + m1.a2.z * m2.a3.y;
	m.a2.z = m1.a2.x * m2.a1.z + m1.a2.y * m2.a2.z + m1.a2.z * m2.a3.z;
	
	// Row 3
	m.a3.x = m1.a3.x * m2.a1.x + m1.a3.y * m2.a2.x + m1.a3.z * m2.a3.x;
	m.a3.y = m1.a3.x * m2.a1.y + m1.a3.y * m2.a2.y + m1.a3.z * m2.a3.y;
	m.a3.z = m1.a3.x * m2.a1.z + m1.a3.y * m2.a2.z + m1.a3.z * m2.a3.z;
	
	return m;
}

Vec3 mult_vm3(Mat3 m, Vec3 v) {
	Vec3 a = {dot_v3(m.a1, v), dot_v3(m.a2, v), dot_v3(m.a2, v)};
	return a;
}

/* 4D Vectors */
Vec4 extend_v3(Vec3 v) {
	Vec4 a = {v.x, v.y, v.z, 1};
	return a;
}

/* 4x4 Matrices */

Mat4 new_m4() {
	Mat4 m = {{0.0,0.0,0.0,0.0}, {0.0,0.0,0.0,0.0}, {0.0,0.0,0.0,0.0}, {0.0,0.0,0.0,0.0}};
	return m; 
}

Mat4 identity_m4() {
	Mat4 i = {{1.0,0.0,0.0,0.0}, {0.0,1.0,0.0,0.0}, {0.0,0.0,1.0,0.0}, {0.0,0.0,0.0,1.0}};
	return i; 
}
