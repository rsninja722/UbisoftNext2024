#ifndef _VEC_H_
#define _VEC_H_

#include <vector>
#include <utility>
#include <iostream>


class Vec {
public:
	
	Vec(const float &x);
	Vec(const float &x, const float &y);
	Vec(const float &x, const float &y, const float &z);
	Vec(const Vec& v);

	float getX();
	float getY();
	float getZ();

	void Add(const Vec &v);
	void Subtract(const Vec &v);
	void Negate();
	void ScalarMulti(const float &f);
	float DotProduct(const Vec &v);
	Vec CrossProduct(const Vec &v);
	float Length();
	void Normalize();
	void Print();
	static std::pair<Vec, Vec> prep(const Vec &a, const Vec &b);
	static std::pair<Vec, Vec> prep(const Vec &a, const Vec &b, int size);

private:
	std::vector<float> comp;
};

#endif 