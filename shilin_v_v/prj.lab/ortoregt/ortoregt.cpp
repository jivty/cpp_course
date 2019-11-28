#include <iostream>

class OrtoRegt {
public:
  OrtoRegt() = default;
  OrtoRegt(float t1x, float t1y, float t2x, float t2y);
  OrtoRegt(OrtoRegt& obj) = default;
  OrtoRegt& operator=(OrtoRegt& rhs) = default;
  ~OrtoRegt() = default;

  OrtoRegt intersect(OrtoRegt& rhs);
  bool contain(float tx, float ty);
  void move(float dx, float dy);
  float width();
  float high();

  std::istream& readFrom(std::istream& istrm);
  std::ostream& writeTo(std::ostream& ostrm) const;
private:
  float pt1x { 0 };
  float pt1y { 0 };
  float pt2x { 0 };
  float pt2y { 0 };
  const char leftBrace{ '(' };
  const char rightBrace{ ')' };
  const char separator{ ',' };
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

bool OrtoRegt::contain(float tx, float ty) {
  return tx - pt1x >= std::numeric_limits<float>::epsilon()
    && pt2x - tx >= std::numeric_limits<float>::epsilon()
    && ty - pt1y >= std::numeric_limits<float>::epsilon()
    && pt2y - ty >= std::numeric_limits<float>::epsilon();
}

OrtoRegt OrtoRegt::intersect(OrtoRegt& rhs) {
  float inpt1x = pt1x > rhs.pt1x ? pt1x : rhs.pt1x;
  float inpt1y = pt1y > rhs.pt1y ? pt1y : rhs.pt1y;
  float inpt2x = pt2x < rhs.pt2x ? pt2x : rhs.pt2x;
  float inpt2y = pt2y < rhs.pt2y ? pt2y : rhs.pt2y;
  if (!this->contain(inpt1x, inpt1y) || !this->contain(inpt2x, inpt2y)
    || !rhs.contain(inpt1x, inpt1y) || !rhs.contain(inpt2x, inpt2y)) {
    throw std::exception("No intersection");
  }
  return { inpt1x, inpt1y, inpt2x, inpt2y };
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

inline std::istream& operator>>(std::istream& istrm, OrtoRegt& rhs) {
  return rhs.readFrom(istrm);
}

inline std::ostream& operator<<(std::ostream& ostrm, OrtoRegt& rhs) {
  return rhs.writeTo(ostrm);
}

std::istream& OrtoRegt::readFrom(std::istream& istrm) {
}

std::ostream& OrtoRegt::writeTo(std::ostream& ostrm) const {
  ostrm << leftBrace << pt1x << separator << pt1y << rightBrace <<
    separator << leftBrace << pt2x << separator << pt2y << rightBrace;
  return ostrm;
}

int main() {
  OrtoRegt test;

  OrtoRegt test2(12, 0, 1, 2);
  OrtoRegt test3(1, 1, 2, 2);
  OrtoRegt test4(test2);
  std::cout << test.high() << " " << test.width() << std::endl;
  std::cout << test2.high() << " " << test2.width() << std::endl;
  std::cout << test3.high() << " " << test3.width() << std::endl;
  test3.move(1, 1);

  return 0;
}