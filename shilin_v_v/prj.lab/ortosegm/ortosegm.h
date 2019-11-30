#ifndef ORTOSEGM_ORTOSEGM_H_112019
#define ORTOSEGM_ORTOSEGM_H_112019

#include <iosfwd>
#include <limits>

class OrtoSegm {
public:
  OrtoSegm() = default;
  OrtoSegm(OrtoSegm& obj) = default;
  OrtoSegm& operator=(const OrtoSegm& obj);
  ~OrtoSegm() = default;
  OrtoSegm(float t1x, float t1y, float t2x, float t2y);

  OrtoSegm& move(float dx, float dy);
  bool contain(float tx, float ty);
  float length();
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
  const char segm[5]{ 's','e','g','m',':' };
};

OrtoSegm& intersect(OrtoSegm& lhs, OrtoSegm& rhs);

inline std::istream& operator>>(std::istream& istrm, OrtoSegm& rhs) {
  return rhs.readFrom(istrm);
}

inline std::ostream& operator<<(std::ostream& ostrm, const OrtoSegm& rhs) {
  return rhs.writeTo(ostrm);
}

#endif
