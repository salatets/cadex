#include <vector>
#include <random>
#include <iostream>
#define _USE_MATH_DEFINES 
#include <math.h> // since we use cpp<20
#include "curve.h"

Curve* generate_random(){
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<> dis(1.0,16.0);
        int i = static_cast<int>(dis(gen)) % 3;
        switch(i){
                case 0:
                        return new Circle(dis(gen));
                case 1:
                        return new Ellipse(dis(gen),dis(gen));
                case 2:
                        return new Helix(dis(gen),dis(gen));
        }
        return nullptr;
}

int main(void){
	auto t = M_PI / 4;
	std::vector<Curve*> curves(128); // TODO smart pointer
	for(auto curve : curves){
		curve = generate_random();
		// TODO better format
 		std::cout << "coord: " << curve->point(t).x
                        << "," << curve->point(t).y
                        << "," << curve->point(t).z
                        << " derive: " << curve->derivative(t).x
                        << "," << curve->derivative(t).y
                        << "," << curve->derivative(t).z
                        << "\n";
	}
	return 0;
}
