#ifndef ORTO_ORTO_H_122019
#define ORTO_ORTO_H_122019

#include <iosfwd>
#include <limits>

class OrtoFigure {
public:
  virtual std::istream& readFrom(std::istream& istrm);
  virtual std::ostream& writeTo(std::ostream& ostrm) const;
  virtual bool contain(float tx, float ty);
  virtual ~OrtoFigure() {}

protected:
  const float eps{ std::numeric_limits<float>::epsilon() };
  static const char leftBracket{ '(' };
  static const char rightBracket{ ')' };
  static const char comma{ ',' };
};

inline std::istream& operator>>(std::istream& istrm, OrtoFigure& rhs) {
  return rhs.readFrom(istrm);
}

inline std::ostream& operator<<(std::ostream& ostrm, OrtoFigure& rhs) {
  return rhs.writeTo(ostrm);
}

class OrtoRegt : public OrtoFigure {
public:
  OrtoRegt() = default;
  OrtoRegt(float t1x, float t1y, float t2x, float t2y);
  OrtoRegt(OrtoRegt& obj) = default;
  OrtoRegt& operator=(const OrtoRegt& rhs) = default;
  ~OrtoRegt() = default;

  OrtoRegt& move(float fx, float dy);
  bool contain(float tx, float ty) override;
  float width();
  float high();
  float getLowLeftX();
  float getLowLeftY();
  float getTopRightX();
  float getTopRightY();

  std::istream& readFrom(std::istream& istrm) override;
  std::ostream& writeTo(std::ostream& ostrm) const override;

private:
  float pt1x{ eps };
  float pt1y{ eps };
  float pt2x{ eps };
  float pt2y{ eps };
  const char box[4]{ 'b','o','x',':' };
};

OrtoRegt& intersect(OrtoRegt& lhs, OrtoRegt& rhs);

class OrtoSegm : public OrtoFigure {
public:
  OrtoSegm() = default;
  OrtoSegm(OrtoSegm& obj) = default;
  OrtoSegm& operator=(const OrtoSegm& obj) = default;
  ~OrtoSegm() = default;
  OrtoSegm(float t1x, float t1y, float t2x, float t2y);

  OrtoSegm& move(float fx, float dy);
  bool contain(float tx, float ty) override;
  float length();
  float getLowLeftX();
  float getLowLeftY();
  float getTopRightX();
  float getTopRightY();

  std::istream& readFrom(std::istream& istrm) override;
  std::ostream& writeTo(std::ostream& ostrm) const override;

private:
  float pt1x{ eps };
  float pt1y{ eps };
  float pt2x{ eps };
  float pt2y{ eps };
  const char segm[5]{ 's','e','g','m',':' };
};

OrtoSegm& intersect(OrtoSegm& lhs, OrtoSegm& rhs);

class Reader;

class ReaderDestroyer {
public:
  ~ReaderDestroyer();
  void initialize(Reader* p);
private:
  Reader* p_instance;
};

class Reader {
public:
  static Reader& getInstance();

protected:
  Reader() {}
  ~Reader() {}
  friend class ReaderDestroyer;
private:
  static Reader* p_instance;
  static ReaderDestroyer destroyer;

};

#endif
