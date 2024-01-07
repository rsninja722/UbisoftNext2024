#ifndef _VECSTRUCT_H_
#define _VECSTRUCT_H_

#include <vector>
#include <utility>

struct Vec3 {
	float x, y, z;

	Vec3();
	Vec3(const float &x, const  float &y, const  float &z);

	void Add(const Vec3 &v);
	void Subtract(const Vec3 &v);
	void Negate();
	void ScalarMulti(const float &f);
	float DotProduct(const Vec3 &v);
	Vec3 CrossProduct(const Vec3 &v);
	float Length();
	void Normalize();
	void Print();

};

#endif 