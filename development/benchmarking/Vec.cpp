#include "Vec.h"
#include <iostream>

Vec::Vec(const Vec& v) {
	for (const float a : v.comp) {
		this->comp.emplace_back(a);
	}
}
Vec::Vec(const float &x) {
	this->comp.emplace_back(x);
}
Vec::Vec(const float &x, const float &y) {
	this->comp.emplace_back(x);
	this->comp.emplace_back(y);
}
Vec::Vec(const float &x, const float &y, const float &z) {
	this->comp.emplace_back(x);
	this->comp.emplace_back(y);
	this->comp.emplace_back(z);
}

float Vec::getX() {
	return this->comp[0];
}
float Vec::getY() {
	return this->comp[1];
}
float Vec::getZ() {
	return this->comp[2];
}

void Vec::Add(const Vec &v) {
	std::pair<Vec, Vec> p = Vec::prep(*this, v);
	for (int i = 0; i < this->comp.size(); i++) {
		this->comp[i] += p.second.comp[i];
	}
}

void Vec::Subtract(const Vec &v) {
	std::pair<Vec, Vec> p = Vec::prep(*this, v);
	for (int i = 0; i < this->comp.size(); i++) {
		this->comp[i] -= p.second.comp[i];
	}
}

void Vec::Negate() {
	for (float& i : this->comp) {
		i = -i;
	}
}

void Vec::ScalarMulti(const float &f) {
	for (float& i : this->comp) {
		i *= f;
	}
}

// if one vec is longer than the other, any components of extra length don't affect the outcome because it will just be * 0
float Vec::DotProduct(const Vec &v) {
	std::pair<Vec, Vec> p = Vec::prep(*this, v);
	float total = 0;
	for (int i = 0; i < this->comp.size(); i++) {
		total += this->comp[i] * p.second.comp[i];
	}
	return total;
}

Vec Vec::CrossProduct(const Vec &v) {
	std::pair<Vec, Vec> p = Vec::prep(*this, v, 3);
	std::vector<float> &a = p.first.comp;
	std::vector<float> &b = p.second.comp;
	return Vec(a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0]);
}

float Vec::Length() {
	float tot = 0;
	for (float& i : this->comp) {
		tot += i * i;
	}
	return sqrtf(tot);
}

void Vec::Normalize() {
	this->ScalarMulti(1.0f / this->Length());
}


void Vec::Print() {
	if (this->comp.size() > 0) std::cout << "x: " << this->comp[0];
	if (this->comp.size() > 1) std::cout << " y: " << this->comp[1];
	if (this->comp.size() > 2) std::cout << " z: " << this->comp[2];
	std::cout << '\n';
}



std::pair<Vec, Vec> Vec::prep(const Vec &a, const Vec &b) {
	std::pair<Vec, Vec> ret { a,b };
	int as = a.comp.size();
	int bs = b.comp.size();
	if (as > bs) {
		ret.second = Vec(b);
		for (int i = bs; i < as; i++) {
			ret.second.comp.emplace_back(0);
		}
		return ret;
	} else {
		ret.first = Vec(a);
		for (int i = as; i < bs; i++) {
			ret.first.comp.emplace_back(0);
		}
		return ret;
	}
}

std::pair<Vec, Vec> Vec::prep(const Vec& a, const Vec& b, int size) {
	std::pair<Vec, Vec> ret { Vec(a),Vec(b) };
	for (int i = a.comp.size(); i < size; i++) {
		ret.first.comp.emplace_back(0);
	}
	for (int i = b.comp.size(); i < size; i++) {
		ret.second.comp.emplace_back(0);
	}
	return ret;
}
