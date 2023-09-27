#include <cmath>
#include "curve.h"

vec3 Circle::point(double t){
	return {m_radius * std::cos(t), m_radius * std::sin(t), 0};
}
vec3 Circle::derivative(double t){
	return {m_radius * -std::sin(t), m_radius * std::cos(t), 0};
}

vec3 Ellipse::point(double t){
	return {m_radius1 * std::cos(t), m_radius2 * std::sin(t), 0};
}
vec3 Ellipse::derivative(double t){
	return {m_radius1 * -std::sin(t), m_radius2 * std::cos(t), 0};
}

vec3 Helix::point(double t){
	return {m_radius * std::cos(t), m_radius * std::sin(t), m_pitch * t};
}
vec3 Helix::derivative(double t){
	return {m_radius * -std::sin(t), m_radius * std::cos(t), m_pitch};
}
