#include "ortoregt.h"
#include <iostream>

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
  return pt1x <= tx && tx <= pt2x
    && pt1y <= ty && ty <= pt2y;
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

//std::istream& OrtoRegt::readFrom(std::istream& istrm) {}

std::ostream& OrtoRegt::writeTo(std::ostream& ostrm) const {
  ostrm << leftBrace << pt1x << separator << pt1y << rightBrace <<
    separator << leftBrace << pt2x << separator << pt2y << rightBrace;
  return ostrm;
}
