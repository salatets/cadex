#include <cmath>
#include "curve.h"

template<typename T>
vec3<T> Circle<T>::point(T t){
	return {m_radius * std::cos(t), m_radius * std::sin(t), 0};
}
template<typename T>
vec3<T,true> Circle<T>::derivative(T t){
	return {m_radius * -std::sin(t), m_radius * std::cos(t), 0};
}


template<typename T>
vec3<T> Ellipse<T>::point(T t){
	return {m_radius1 * std::cos(t), m_radius2 * std::sin(t), 0};
}
template<typename T>
vec3<T,true> Ellipse<T>::derivative(T t){
	return {m_radius1 * -std::sin(t), m_radius2 * std::cos(t), 0};
}


template<typename T>
vec3<T> Helix<T>::point(T t){
	return {m_radius * std::cos(t), m_radius * std::sin(t), m_pitch * t};
}
template<typename T>
vec3<T,true> Helix<T>::derivative(T t){
	return {m_radius * -std::sin(t), m_radius * std::cos(t), m_pitch};
}
