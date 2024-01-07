#include "vecClass.h"
#include <iostream>

VecClass::VecClass(const float& x) {
	this->m_comp[0] = x;
	this->m_comp[1] = 0.0f;
	this->m_comp[2] = 0.0f;
}
VecClass::VecClass(const float& x, const float& y) {
	this->m_comp[0] = x;
	this->m_comp[1] = y;
	this->m_comp[2] = 0.0f;

}
VecClass::VecClass(const float& x, const float& y, const float& z) {
	this->m_comp[0] = x;
	this->m_comp[1] = y;
	this->m_comp[2] = z;
}
VecClass::VecClass(const VecClass& v) {
	this->m_comp[0] = v.m_comp[0];
	this->m_comp[1] = v.m_comp[1];
	this->m_comp[2] = v.m_comp[2];
}

float VecClass::getX() {
	return this->m_comp[0];
}
float VecClass::getY() {
	return this->m_comp[1];
}
float VecClass::getZ() {
	return this->m_comp[2];
}

void VecClass::Add(const VecClass& v) {
	this->m_comp[0] += v.m_comp[0];
	this->m_comp[1] += v.m_comp[1];
	this->m_comp[2] += v.m_comp[2];
}
void VecClass::Subtract(const VecClass& v) {
	this->m_comp[0] -= v.m_comp[0];
	this->m_comp[1] -= v.m_comp[1];
	this->m_comp[2] -= v.m_comp[2];
}

void VecClass::Negate() {
	this->m_comp[0] = -this->m_comp[0];
	this->m_comp[1] = -this->m_comp[1];
	this->m_comp[2] = -this->m_comp[2];
}

void VecClass::ScalarMulti(const float& f) {
	this->m_comp[0] *= f;
	this->m_comp[1] *= f;
	this->m_comp[2] *= f;
}

float VecClass::DotProduct(const VecClass& v) {
	return this->m_comp[0] * v.m_comp[0] + this->m_comp[1] * v.m_comp[1] + this->m_comp[2] * v.m_comp[2];
}

VecClass VecClass::CrossProduct(const VecClass& v) {
	return VecClass{ this->m_comp[1] * v.m_comp[2] - this->m_comp[2] * v.m_comp[1], this->m_comp[2] * v.m_comp[0] - this->m_comp[0] * v.m_comp[2], this->m_comp[0] * v.m_comp[1] - this->m_comp[1] * v.m_comp[0] };
}

float VecClass::Length() {
	return sqrtf(this->m_comp[0] * this->m_comp[0] + this->m_comp[1] * this->m_comp[1] + this->m_comp[2] * this->m_comp[2]);
}

void VecClass::Normalize() {
	this->ScalarMulti(1.0f / this->Length());
}

void VecClass::Print() {
	std::cout << "x: " << this->m_comp[0] << " y: " << this->m_comp[1] << " z: " << this->m_comp[2] << '\n';
}