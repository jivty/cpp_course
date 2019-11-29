#include "ortosegm.h"
#include <iostream>

OrtoSegm::OrtoSegm(float t1x, float t1y, float t2x, float t2y)
  : pt1x(t1x)
  , pt1y(t1y)
  , pt2x(t2x)
  , pt2y(t1x) {
  if (fabs(t1x - t2x) > eps &&
    fabs(t1y - t2y) > eps) {
    throw std::invalid_argument("Not orto");
  }
  if (pt1x > pt2x || pt1y > pt2y) {
    pt1x = t2x;
    pt2x = t1x;
    pt1y = t2y;
    pt2y = t1y;
  }
}

float OrtoSegm::length() {
  return pt2x - pt1x + pt2y - pt1y;
}

void OrtoSegm::move(float dx, float dy) {
  pt1x += dx;
  pt1y += dy;
  pt2x += dx;
  pt2y += dy;
}

bool OrtoSegm::contain(float tx, float ty) {
  return pt1x <= tx && tx <= pt2x
    && pt1y <= ty && ty <= pt2y;
}

OrtoSegm OrtoSegm::intersect(OrtoSegm& rhs) {
  float inpt1x = pt1x > rhs.pt1x ? pt1x : rhs.pt1x;
  float inpt1y = pt1y > rhs.pt1y ? pt1y : rhs.pt1y;
  float inpt2x = pt2x < rhs.pt2x ? pt2x : rhs.pt2x;
  float inpt2y = pt2y < rhs.pt2y ? pt2y : rhs.pt2y;
  if (!this->contain(inpt1x, inpt1y) || !this->contain(inpt2x, inpt2y)
    || !rhs.contain(inpt1x, inpt1y) || !rhs.contain(inpt2x, inpt2y)) {
    return { eps * eps, eps * eps, eps * eps, eps * eps };
  }
  return { inpt1x, inpt1y, inpt2x, inpt2y };
}
