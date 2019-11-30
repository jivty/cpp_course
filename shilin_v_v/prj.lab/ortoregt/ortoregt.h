#ifndef ORTOREGT_ORTOREGT_H_112019
#define ORTOREGT_ORTOREGT_H_112019

#include <iosfwd>
#include <limits>

class OrtoRegt {
public:
  OrtoRegt() = default;
  OrtoRegt(float t1x, float t1y, float t2x, float t2y);
  OrtoRegt(OrtoRegt& obj) = default;
  OrtoRegt& operator=(const OrtoRegt& rhs);
  ~OrtoRegt() = default;

  bool contain(float tx, float ty);
  OrtoRegt& move(float dx, float dy);
  float width();
  float high();
  float getLowLeftX();
  float getLowLeftY();
  float getTopRightX();
  float getTopRightY();

  std::istream& readFrom(std::istream& istrm);
  std::ostream& writeTo(std::ostream& ostrm) const;

private:
  const float eps{ std::numeric_limits<float>::epsilon() };
  float pt1x{ eps };
  float pt1y{ eps };
  float pt2x{ eps };
  float pt2y{ eps };
  static const char leftBracket{ '(' };
  static const char rightBracket{ ')' };
  static const char comma{ ',' };
  const char box[4]{ 'b','o','x',':' };
};

OrtoRegt& intersect(OrtoRegt& lhs, OrtoRegt& rhs);

inline std::istream& operator>>(std::istream& istrm, OrtoRegt& rhs) {
  return rhs.readFrom(istrm);
}

inline std::ostream& operator<<(std::ostream& ostrm, OrtoRegt& rhs) {
  return rhs.writeTo(ostrm);
}

#endif
