#pragma once
#include <stdexcept>
#include <tuple>

// not optimized for case z = 0
template<typename T,bool isTransposite = false>
struct vec3{
  T x;
  T y;
  T z;
};

template<typename T = double>
class Curve{
public:
  Curve() {
    static_assert(std::is_floating_point_v<T>, "only float types");
  }

  virtual vec3<T> point(T t) = 0;
  virtual vec3<T,true> derivative(T t) = 0;

  virtual ~Curve() = default;
  Curve(const Curve&) = default;
  Curve& operator=(const Curve&) = default;
  Curve(Curve&&) = default;
  Curve& operator=(Curve&&) = default;
};

template<typename T = double>
class Circle : public Curve<T>{
public:
  Circle(T radius) : m_radius(radius){
    if(m_radius <= 0){
      throw std::invalid_argument("arguments must be positive");
    }
  };

  vec3<T> point(T t) override;
  vec3<T,true> derivative(T t) override;

  const T radius(){return m_radius;}

  friend bool operator<(const Circle& l, const Circle& r){
    return l.m_radius < r.m_radius;
  }
private:
  T m_radius;
};

template<typename T = double>
class Ellipse : public Curve<T>{
public:
  Ellipse(T radius1, T radius2) : m_radius1(radius1),m_radius2(radius2){
    if(m_radius1 <= 0 && m_radius2 <= 0){
      throw std::invalid_argument("arguments must be positive");
    }
  };

  vec3<T> point(T t) override;
  vec3<T,true> derivative(T t) override;

  const T radius1(){return m_radius1;}
  const T radius2(){return m_radius2;}

  friend bool operator<(const Ellipse& l, const Ellipse& r){
    return l.m_radius1+l.m_radius2 < r.m_radius1+r.m_radius2;
  }
private:
  T m_radius1, m_radius2;
};

template<typename T = double>
class Helix : public Curve<T>{
public:
  Helix(T radius, T pitch): m_radius(radius),m_pitch(pitch){ // slope = radius/pitch
    if(m_radius <= 0 && m_pitch <= 0){
      throw std::invalid_argument("arguments must be positive");
    }
  };

  vec3<T> point(T t) override;
  vec3<T,true> derivative(T t) override;

  const T radius(){return m_radius;}
  const T pitch(){return m_pitch;}

  friend bool operator<(const Helix& l, const Helix& r){
    return std::tie(l.m_radius,l.m_pitch) < std::tie(r.m_radius,r.m_pitch);
  }
private:
  T m_radius, m_pitch;
};
