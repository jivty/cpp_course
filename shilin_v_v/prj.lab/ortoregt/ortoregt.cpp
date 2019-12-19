#include <ortoregt/ortoregt.h>
#include <iostream>

OrtoRegt::OrtoRegt(float t1x, float t1y, float t2x, float t2y)
  : pt1x(t1x)
  , pt1y(t1y)
  , pt2x(t2x)
  , pt2y(t2y) {
  if (pt1x > pt2x) {
    std::swap(pt1x, pt2x);
  }
  if (pt1y > pt2y) {
    std::swap(pt1y, pt2y);
  }
}

OrtoRegt& OrtoRegt::operator=(const OrtoRegt& rhs) {
  pt1x = rhs.pt1x;
  pt2x = rhs.pt2x;
  pt1y = rhs.pt1y;
  pt2y = rhs.pt2y;
  return *this;
}

bool OrtoRegt::contain(float tx, float ty) {
  return pt1x - eps <= tx && tx <= pt2x + eps
    && pt1y - eps <= ty && ty <= pt2y + eps;
}

float OrtoRegt::getLowLeftX() {
  return pt1x;
}

float OrtoRegt::getLowLeftY() {
  return pt1y;
}

float OrtoRegt::getTopRightX() {
  return pt2x;
}

float OrtoRegt::getTopRightY() {
  return pt2y;
}

OrtoRegt& intersect(OrtoRegt& lhs, OrtoRegt& rhs) {
  constexpr float eps(std::numeric_limits<float>::epsilon());
  float inpt1x = lhs.getLowLeftX() > rhs.getLowLeftX() ? 
    lhs.getLowLeftX() : rhs.getLowLeftX();
  float inpt1y = lhs.getLowLeftY() > rhs.getLowLeftY() ? 
    lhs.getLowLeftY() : rhs.getLowLeftY();
  float inpt2x = lhs.getTopRightX() < rhs.getTopRightX() ?
    lhs.getTopRightX() : rhs.getTopRightX();
  float inpt2y = lhs.getTopRightY() < rhs.getTopRightY() ? 
    lhs.getTopRightY() : rhs.getTopRightY();
  if (lhs.contain(inpt1x, inpt1y) && lhs.contain(inpt2x, inpt2y)
    && rhs.contain(inpt1x, inpt1y) && rhs.contain(inpt2x, inpt2y)) {
    OrtoRegt ans(inpt1x, inpt1y, inpt2x, inpt2y);
    return ans;
  } else {
    OrtoRegt ans(eps * eps, eps * eps, eps * eps, eps * eps);
    return ans;
  }
}

float OrtoRegt::high() {
  return pt2y - pt1y;
}

float OrtoRegt::width() {
  return pt2x - pt1x;
}

OrtoRegt& OrtoRegt::move(float dx, float dy) {
  pt1x += dx;
  pt1y += dy;
  pt2x += dx;
  pt2y += dy;
  return *this;
}

std::istream& OrtoRegt::readFrom(std::istream& istrm) {
  char box[5];
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
  istrm.get(box, 5);
  if (std::strcmp(box, OrtoRegt::box)) {
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
  } else {
    istrm.setstate(std::ios_base::failbit);
  }
  return istrm;
}

std::ostream& OrtoRegt::writeTo(std::ostream& ostrm) const {
  std::string box(OrtoRegt::box, sizeof(OrtoRegt::box));
  ostrm << box << leftBracket << pt1x << comma << pt1y << rightBracket 
    << leftBracket << pt2x << comma << pt2y << rightBracket;
  return ostrm;
}
