#pragma once
#include <stdexcept>
#include <tuple>

// not optimized for case z = 0
struct vec3{
	double x;
	double y;
	double z;
};

class Curve{
public:
        virtual vec3 point(double t) = 0;
        virtual vec3 derivative(double t) = 0;

        virtual ~Curve() = default;
};

class Circle : public Curve{
public:
        Circle(double radius) : m_radius(radius){
                if(m_radius <= 0){
                        throw std::invalid_argument("arguments must be positive");
                }
        };

        vec3 point(double t) override;
        vec3 derivative(double t) override;

	const double radius(){return m_radius;}

	friend bool operator<(const Circle& l, const Circle& r){
		return l.m_radius < r.m_radius;
	}
private:
        double m_radius;
};

class Ellipse : public Curve{
public:
        Ellipse(double radius1, double radius2) : m_radius1(radius1),m_radius2(radius2){
                if(m_radius1 <= 0 && m_radius1 <= 0){
                        throw std::invalid_argument("arguments must be positive");
                }
        };

        vec3 point(double t) override;
        vec3 derivative(double t) override;

	const double radius1(){return m_radius1;}
	const double radius2(){return m_radius2;}

	friend bool operator<(const Ellipse& l, const Ellipse& r){
		return l.m_radius1+l.m_radius2 < r.m_radius1+r.m_radius2;
	}
private:
        double m_radius1, m_radius2;
};

class Helix : public Curve{
public:
        Helix(double radius, double pitch): m_radius(radius),m_pitch(pitch){ // slope = radius/pitch
                if(m_radius <= 0 && m_pitch <= 0){
                        throw std::invalid_argument("arguments must be positive");
                }
        };

        vec3 point(double t) override;
        vec3 derivative(double t) override;

	const double radius(){return m_radius;}
	const double pitch(){return m_pitch;}

	friend bool operator<(const Helix& l, const Helix& r){
		return std::tie(l.m_radius,l.m_pitch) < std::tie(r.m_radius,r.m_pitch);
	}
private:
        double m_radius, m_pitch;
};
