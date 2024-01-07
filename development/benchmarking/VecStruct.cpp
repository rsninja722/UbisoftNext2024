#include "VecStruct.h"
#include <iostream>

Vec3::Vec3() : x{0.0f}, y{ 0.0f }, z{ 0.0f } {}
Vec3::Vec3(const float& x, const  float& y, const  float& z) : x{x}, y{y}, z{z} {}


void Vec3::Add(const Vec3& v) {
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
}

void Vec3::Subtract(const Vec3& v) {
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
}

void Vec3::Negate() {
	this->x = -this->x;
	this->y = -this->y;
	this->z = -this->z;
}

void Vec3::ScalarMulti(const float& f) {
	this->x *= f;
	this->y *= f;
	this->z *= f;
}

float Vec3::DotProduct(const Vec3& v) {
	return this->x * v.x + this->y * v.y + this->z * v.z;
}

Vec3 Vec3::CrossProduct(const Vec3& v) {
	return Vec3(this->y * v.z - this->z * v.y, this->z * v.x - this->x * v.z, this->x * v.y - this->y * v.x);
}

float Vec3::Length() {
	return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
}

void Vec3::Normalize() {
	this->ScalarMulti(1.0f / this->Length());
}

void Vec3::Print() {
	std::cout << "x: " << this->x << " y: " << this->y << " z: " << this->z << '\n';
}
