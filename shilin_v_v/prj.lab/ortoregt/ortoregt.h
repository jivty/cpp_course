#ifndef ORTOREGT_ORTOREGT_H_112019
#define ORTOREGT_ORTOREGT_H_112019

#include <iosfwd>
#include <limits>

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
  float pt1x{ std::numeric_limits<float>::epsilon() };
  float pt1y{ std::numeric_limits<float>::epsilon() };
  float pt2x{ std::numeric_limits<float>::epsilon() };
  float pt2y{ std::numeric_limits<float>::epsilon() };
  const char leftBrace{ '(' };
  const char rightBrace{ ')' };
  const char separator{ ',' };
};

#endif
