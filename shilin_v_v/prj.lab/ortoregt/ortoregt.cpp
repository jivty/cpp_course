#include <iostream>

class OrtoRegt {
public:
  OrtoRegt() = default;
  OrtoRegt(float t1x, float t1y, float t2x, float t2y);
  OrtoRegt(OrtoRegt& obj) = default;
  OrtoRegt& operator=(OrtoRegt& rhs) = default;
  ~OrtoRegt() = default;

  OrtoRegt& intersect(OrtoRegt lhs, OrtoRegt rhs);
  void move(float dx, float dy);
  float width();
  float high();

  std::istream& readFrom(std::istream istrm);
  std::ostream& writeTo(std::ostream ostrm) const;
private:
  float pt1x { 0 };
  float pt1y { 0 };
  float pt2x { 0 };
  float pt2y { 0 };
};

OrtoRegt::OrtoRegt(float t1x, float t1y, float t2x, float t2y)
  : pt1x(t1x)
  , pt1y(t1y)
  , pt2x(t2x)
  , pt2y(t1x) {
  if (pt1x > pt2x) {
    std::swap(pt1x, pt2x);
  }
  if (pt1y > pt2y) {
    std::swap(pt1y, pt2y);
  }
}

float OrtoRegt::high() {
  return pt2y - pt1y;
}

float OrtoRegt::width() {
  return pt2x - pt1x;
}

void OrtoRegt::move(float dx, float dy) {
  pt1x += dx;
  pt1y += dy;
  pt2x += dx;
  pt2y += dy;
}

inline std::istream& OrtoRegt::readFrom(std::istream istrm) {
  
}

inline std::ostream& OrtoRegt::writeTo(std::ostream ostrm) const {
  ostrm << 
}

int main() {
  OrtoRegt test;
  Point t1(12, 9);
  Point t2(0, 0);
  Point t3(12, 0);

  OrtoRegt test2(t1, t2);
  OrtoRegt test3(t3, t1);
  OrtoRegt test4(test2);
  std::cout << test.high() << " " << test.width() << std::endl;
  std::cout << test2.high() << " " << test2.width() << std::endl;
  std::cout << test3.high() << " " << test3.width() << std::endl;
  test3.move(1, 1);

  return 0;
}