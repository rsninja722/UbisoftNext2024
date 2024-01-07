#ifndef _VECCLASSPOINTER_H_
#define _VECCLASSPOINTER_H_

#include <array>

class VecClassPointers {
public:
	VecClassPointers(const float& x);
	VecClassPointers(const float& x, const float& y);
	VecClassPointers(const float& x, const float& y, const float& z);
	VecClassPointers(const VecClassPointers* const v);

	float getX();
	float getY();
	float getZ();

	void Add(const VecClassPointers* const v);
	void Subtract(const VecClassPointers* const v);
	void Negate();
	void ScalarMulti(float f);
	float DotProduct(const VecClassPointers* const v);
	VecClassPointers CrossProduct(const VecClassPointers* const v);
	float Length();
	void Normalize();
	void Print();
private:
	std::array<float, 3> m_comp;
};


#endif