#include "VecClassPointers.h"
#include <iostream>

VecClassPointers::VecClassPointers(const float& x) {
	this->m_comp[0] = x;
	this->m_comp[1] = 0.0f;
	this->m_comp[2] = 0.0f;
}
VecClassPointers::VecClassPointers(const float& x, const float& y) {
	this->m_comp[0] = x;
	this->m_comp[1] = y;
	this->m_comp[2] = 0.0f;

}
VecClassPointers::VecClassPointers(const float& x, const float& y, const float& z) {
	this->m_comp[0] = x;
	this->m_comp[1] = y;
	this->m_comp[2] = z;
}
VecClassPointers::VecClassPointers(const VecClassPointers* const v) {
	this->m_comp[0] = v->m_comp[0];
	this->m_comp[1] = v->m_comp[1];
	this->m_comp[2] = v->m_comp[2];
}

float VecClassPointers::getX() {
	return this->m_comp[0];
}
float VecClassPointers::getY() {
	return this->m_comp[1];
}
float VecClassPointers::getZ() {
	return this->m_comp[2];
}

void VecClassPointers::Add(const VecClassPointers* const v) {
	this->m_comp[0] += v->m_comp[0];
	this->m_comp[1] += v->m_comp[1];
	this->m_comp[2] += v->m_comp[2];
}
void VecClassPointers::Subtract(const VecClassPointers* const v) {
	this->m_comp[0] -= v->m_comp[0];
	this->m_comp[1] -= v->m_comp[1];
	this->m_comp[2] -= v->m_comp[2];
}

void VecClassPointers::Negate() {
	this->m_comp[0] = -this->m_comp[0];
	this->m_comp[1] = -this->m_comp[1];
	this->m_comp[2] = -this->m_comp[2];
}

void VecClassPointers::ScalarMulti(float f) {
	this->m_comp[0] *= f;
	this->m_comp[1] *= f;
	this->m_comp[2] *= f;
}

float VecClassPointers::DotProduct(const VecClassPointers* const v) {
	return this->m_comp[0] * v->m_comp[0] + this->m_comp[1] * v->m_comp[1] + this->m_comp[2] * v->m_comp[2];
}

VecClassPointers VecClassPointers::CrossProduct(const VecClassPointers* const v) {
	return VecClassPointers{ this->m_comp[1] * v->m_comp[2] - this->m_comp[2] * v->m_comp[1], this->m_comp[2] * v->m_comp[0] - this->m_comp[0] * v->m_comp[2], this->m_comp[0] * v->m_comp[1] - this->m_comp[1] * v->m_comp[0] };
}

float VecClassPointers::Length() {
	return sqrtf(this->m_comp[0] * this->m_comp[0] + this->m_comp[1] * this->m_comp[1] + this->m_comp[2] * this->m_comp[2]);
}

void VecClassPointers::Normalize() {
	this->ScalarMulti(1.0f / this->Length());
}

void VecClassPointers::Print() {
	std::cout << "x: " << this->m_comp[0] << " y: " << this->m_comp[1] << " z: " << this->m_comp[2] << '\n';
}