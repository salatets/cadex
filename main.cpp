
#include <vector>
#include <random>
#include <iostream>
#include <memory>
#include <algorithm>
#include <execution>
#include <charconv>
#include <cstring>
#define _USE_MATH_DEFINES 
#include <math.h> // since we use cpp<20
#include <omp.h> 
#include "curve.ipp"

template<bool isShared, typename T, typename... Args>
auto make_smart(Args&&... args)
-> std::conditional_t<
			       isShared,
			       std::shared_ptr<T>,
			       std::unique_ptr<T>>
{
    if constexpr (isShared)
      return std::make_shared<T>(std::forward<Args>(args)...);
    else
      return std::make_unique<T>(std::forward<Args>(args)...);
}

template<bool isShared>
auto generate_random()
-> std::conditional_t<
		      isShared,
		      std::shared_ptr<Curve<>>,
		      std::unique_ptr<Curve<>>>
{
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_real_distribution<> dis(1.0,16.0);

  int i = static_cast<int>(dis(gen)) % 3;
  switch(i){
  case 0:;
    return make_smart<isShared,Circle<>>(dis(gen));
  case 1:
    return make_smart<isShared,Ellipse<>>(dis(gen),dis(gen));
  case 2:
    return make_smart<isShared,Helix<>>(dis(gen),dis(gen));
  }
  // never go here
  return std::unique_ptr<Curve<>>(nullptr);
}

void print_curve(Curve<>* const curve, double t){
  std::cout << "coord: " << curve->point(t).x
	    << "," << curve->point(t).y
	    << "," << curve->point(t).z
	    << " derive: " << curve->derivative(t).x
	    << "," << curve->derivative(t).y
	    << "," << curve->derivative(t).z
	    << "\n";
}

template<typename> struct is_vector : std::false_type {};

template<typename T,typename A>
struct is_vector<std::vector<T,A>> : std::true_type {};

template<typename T>
inline constexpr bool is_vector_v = is_vector<T>::value;

// TODO make dereferences consistant(without if constexpr)
template<bool isShared, typename Curves, typename Circles,
	 typename = std::enable_if_t<
				     is_vector_v<std::remove_reference_t<Curves>> &&
				     is_vector_v<std::remove_reference_t<Circles>>>>
void test2(Curves&& curves, Circles&& circles){
  auto t = M_PI / 4;
  for(auto& curve : curves){
    curve = generate_random<isShared>();
    print_curve(curve.get(),t);
    if constexpr (isShared){
      if(auto ptr = std::dynamic_pointer_cast<Circle<>>(curve);ptr){
	circles.push_back(ptr);
      }
    }else{
      if(dynamic_cast<Circle<>*>(curve.get())){
	circles.push_back(reinterpret_cast<std::unique_ptr<Circle<>>*>(&curve));
      }
    }
  }
  std::sort(circles.begin(), circles.end(),
	    [](const auto& r,const auto& l)
	    {if constexpr (isShared){
		return (*r) < (*l);
	      }else{
		return (**r) < (**l);
	      }});

  double sum = std::transform_reduce( // parallel computation using Standart Library
				      std::execution::par,
				      circles.cbegin(),
				      circles.cend(),
				      0.0,
				      std::plus{},
				      [](const auto& circle) {
					if constexpr (isShared){
					  return circle->radius();
					}else{
					  return (*circle)->radius();
					}}); // is require additional allocations?

  double sumMP = 0.0;
  auto c_size = circles.size();

  // more overhead compare to manual critical section
#pragma omp parallel for reduction (+:sumMP)
  for(auto i = 0; i < c_size; i++){
    if constexpr (isShared){
      sumMP += circles[i]->radius();
    }else{
      sumMP += (*circles[i])->radius();
    }
  }

  std::cout << "sum of all circles: " << sum << " or with openMP: " << sumMP << "\n";
}

template<bool isShared>
void test(size_t size){
  if constexpr (isShared){
    std::vector<std::shared_ptr<Curve<>>> curves(size);
    std::vector<std::shared_ptr<Circle<>>> circles;
    test2<isShared>(curves, circles);
  }else{
    test2<isShared>
      (std::vector<std::unique_ptr<Curve<>>>(size),
       std::vector<std::unique_ptr<Circle<>>*>() // If we not need autonomous collection
       );
  }
}


int main(int argc, char **argv){
  size_t size = 128;
  if(argc >= 2) {
    auto [ptr, ec] = std::from_chars(argv[1],argv[1] + std::strlen(argv[1]),size);
    if (ec != std::errc()){
      std::cerr << "this is not a number, using default value\n";
    }
  }

  test<true>(size); // use much more memory
  test<false>(size);
  return 0;
}
