#ifndef ORTOSEGM_ORTOSEGM_H_112019
#define ORTOSEGM_ORTOSEGM_H_112019

#include <iosfwd>
#include <limits>

class OrtoSegm {
public:
  OrtoSegm() = default;
  OrtoSegm(OrtoSegm& obj) = default;
  OrtoSegm& operator=(OrtoSegm& obj) = default;
  ~OrtoSegm() = default;
  OrtoSegm(float t1x, float t1y, float t2x, float t2y);

  OrtoSegm intersect(OrtoSegm& rhs);
  void move(float dx, float dy);
  bool contain(float tx, float ty);
  float length();

  //std::istream& readFrom(std::istream& istrm);
  //std::ostream& writeTo(std::ostream& ostrm);
private:
  float pt1x{ std::numeric_limits<float>::epsilon() };
  float pt1y{ std::numeric_limits<float>::epsilon() };
  float pt2x{ std::numeric_limits<float>::epsilon() };
  float pt2y{ std::numeric_limits<float>::epsilon() };
};

#endif

