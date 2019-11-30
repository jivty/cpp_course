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

OrtoSegm& OrtoSegm::operator=(const OrtoSegm& rhs) {
  pt1x = rhs.pt1x;
  pt2x = rhs.pt2x;
  pt1y = rhs.pt1y;
  pt2y = rhs.pt2y;
  return *this;
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
  return pt1x - eps < tx && tx < pt2x + eps
    && pt1y - eps < ty && ty < pt2y + eps;
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

std::ostream& OrtoSegm::writeTo(std::ostream& ostrm) const {
  std::string segm(OrtoSegm::segm, sizeof(OrtoSegm::segm));
  ostrm << segm << leftBracket << pt1x << comma << pt1y << rightBracket
    << leftBracket << pt2x << comma << pt2y << rightBracket;
  return ostrm;
}

std::istream& OrtoSegm::readFrom(std::istream& istrm) {
  char segm[6];
  char leftBracket1('0');
  char leftBracket2('0');
  char rightBracket1('0');
  char rightBracket2('0');
  char comma1('0');
  char comma2('0');
  float t1x(0);
  float t1y(0);
  float t2x(0);
  float t2y(0);
  istrm.get(segm, 6);
  if (std::strcmp(segm, OrtoSegm::segm)) {
    istrm >> leftBracket1 >> t1x >> comma1 >> t1y >> rightBracket1
      >> leftBracket2 >> t2x >> comma2 >> t2y >> rightBracket2;
    if (istrm.good()) {
      if (comma1 == comma && comma2 == comma
        && leftBracket1 == leftBracket && leftBracket2 == leftBracket
        && rightBracket1 == rightBracket && rightBracket2 == rightBracket) {
        pt1x = t1x;
        pt1y = t1y;
        pt2x = t2x;
        pt2y = t2y;
      }
      else {
        istrm.setstate(std::ios_base::failbit);
      }
    }
  }
  else {
    istrm.setstate(std::ios_base::failbit);
  }
  return istrm;
}
