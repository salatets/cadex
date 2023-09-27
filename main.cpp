#include <vector>
#include <random>
#include <iostream>
#include <memory>
#include <algorithm>
#define _USE_MATH_DEFINES 
#include <math.h> // since we use cpp<20
#include "curve.h"

std::unique_ptr<Curve> generate_random(){
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<> dis(1.0,16.0);
        int i = static_cast<int>(dis(gen)) % 3;
        switch(i){
                case 0:
                        return std::make_unique<Circle>(dis(gen));
			// TODO or better: std::unique_ptr<Curve>(new Circle(dis(gen))); ?
                case 1:
                        return std::make_unique<Ellipse>(dis(gen),dis(gen));
                case 2:
                        return std::make_unique<Helix>(dis(gen),dis(gen));
        }
        return std::unique_ptr<Curve>(nullptr); // never go here
}

int main(void){ // TODO add variant implementation with shared_ptr
	auto t = M_PI / 4;
	std::vector<std::unique_ptr<Curve>> curves(128);
	std::vector<std::unique_ptr<Circle>*> circles; // If we not need autonomous collection

	for(auto& curve : curves){
		curve = generate_random();
		// TODO better format
 		std::cout << "coord: " << curve->point(t).x
                        << "," << curve->point(t).y
                        << "," << curve->point(t).z
                        << " derive: " << curve->derivative(t).x
                        << "," << curve->derivative(t).y
                        << "," << curve->derivative(t).z
                        << "\n";
		if(dynamic_cast<Circle*>(curve.get())){
                        circles.push_back(reinterpret_cast<std::unique_ptr<Circle>*>(&curve));
                }

	std::sort(circles.begin(), circles.end(),
                        [](auto const r, auto const l)
                        {return (**r) < (**l);});
	}
	return 0;
}
