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
        Circle(double radius) : radius(radius){
                if(radius <= 0){
                        throw std::invalid_argument("arguments must be positive");
                }
        };

        vec3 point(double t) override;
        vec3 derivative(double t) override;

	friend bool operator<(const Circle& l, const Circle& r){
		return l.radius < r.radius;
	}
private:
        double radius;
};

class Ellipse : public Curve{
public:
        Ellipse(double radius1, double radius2) : radius1(radius1),radius2(radius2){
                if(radius1 <= 0 && radius1 <= 0){
                        throw std::invalid_argument("arguments must be positive");
                }
        };

        vec3 point(double t) override;
        vec3 derivative(double t) override;

	friend bool operator<(const Ellipse& l, const Ellipse& r){
		return l.radius1+l.radius2 < r.radius1+r.radius2;
	}
private:
        double radius1, radius2;
};

class Helix : public Curve{
public:
        Helix(double radius, double pitch): radius(radius),pitch(pitch){ // slope = radius/pitch 
                if(radius <= 0 && pitch <= 0){
                        throw std::invalid_argument("arguments must be positive");
                }
        };

        vec3 point(double t) override;
        vec3 derivative(double t) override;

	friend bool operator<(const Helix& l, const Helix& r){
		return std::tie(l.radius,l.pitch) < std::tie(r.radius,r.pitch);
	}
private:
        double radius, pitch;
};
