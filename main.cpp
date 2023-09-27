#include <vector>
#include <random>
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
	std::vector<Curve*> curves(128); // TODO smart pointer
	for(auto curve : curves){
		curve = generate_random();
	}
	return 0;
}
