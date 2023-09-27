#include <cmath>
#include "curve.h"

vec3 Circle::point(double t){
	return {radius * std::cos(t), radius * std::sin(t), 0};
}
vec3 Circle::derivative(double t){
	return {radius * -std::sin(t), radius * std::cos(t), 0};
}

vec3 Ellipse::point(double t){
	return {radius1 * std::cos(t), radius2 * std::sin(t), 0};
}
vec3 Ellipse::derivative(double t){
	return {radius1 * -std::sin(t), radius2 * std::cos(t), 0};
}

vec3 Helix::point(double t){
	return {radius * std::cos(t), radius * std::sin(t), pitch * t};
}
vec3 Helix::derivative(double t){
	return {radius * -std::sin(t), radius * std::cos(t), pitch};
}
