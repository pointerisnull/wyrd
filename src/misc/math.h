#ifndef MISC_MATH_H
#define MISC_MATH_H

#define PI 3.14159265359

typedef struct Vec3 Vec3;
typedef struct Vec4 Vec4;
typedef struct Mat3 Mat3;
typedef struct Mat4 Mat4;

struct Vec3 {
	float x, y, z;
};

struct Vec4 {
	float x, y, z, w;
};

struct Mat3 {
	Vec3 a1, a2, a3;
};

struct Mat4 {
	Vec4 a1, a2, a3, a4;
};

float abs_v3(Vec3 v);
float dot_v3(Vec3 v, Vec3 w);
Vec3 scale_v3(Vec3 v, float s);
Vec3 cross_v3(Vec3 v, Vec3 w);
Vec3 norm_v3(Vec3 v);


Mat3 new_m3();
Mat3 identity_m3();
Vec3 mult_vm3(Mat3 m, Vec3 v);

Vec4 extend_v3(Vec3 v);

Mat4 new_m4();
Mat4 identity_m4();



#endif
