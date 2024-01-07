#ifndef _VECCLASS_H_
#define _VECCLASS_H_

#include <array>

class VecClass {
public:
	VecClass(const float& x);
	VecClass(const float& x, const float& y);
	VecClass(const float& x, const float& y, const float& z);
	VecClass(const VecClass& v);

	float getX();
	float getY();
	float getZ();

	void Add(const VecClass& v);
	void Subtract(const VecClass& v);
	void Negate();
	void ScalarMulti(const float& f);
	float DotProduct(const VecClass& v);
	VecClass CrossProduct(const VecClass& v);
	float Length();
	void Normalize();
	void Print();
private:
	std::array<float, 3> m_comp;
};


#endif