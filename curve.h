#pragma once
#include <stdexcept>

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
private:
        double radius;
};

class Ellipse : public Curve{
public:
        Ellipse(double focus1, double focus2) : focus1(focus1),focus2(focus2){
                if(focus1 <= 0 && focus1 <= 0){
                        throw std::invalid_argument("arguments must be positive");
                }
        };

        vec3 point(double t) override;
        vec3 derivative(double t) override;
private:
        double focus1, focus2;
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
private:
        double radius, pitch;
};
