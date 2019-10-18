#ifndef RATIONAL_RATIONAL_H_102019
#define RATIONAL_RATIONAL_H_102019

#include <iosfwd>

class Rational {
public:
  Rational() {}
  Rational(const Rational&) = default;
  explicit Rational(const int numerator);
  Rational(const int numerator, const int denuminator);
  ~Rational() = default;
  Rational& operator=(const Rational&) = default;
  Rational& operator=(const int rhs);
  bool operator==(const Rational& rhs) const;
  bool operator!=(const Rational& rhs) const;
  Rational& operator+=(const Rational& rhs);
  Rational& operator+=(const int rhs) { return operator+=(Rational(rhs)); }
  Rational& operator-=(const Rational& rhs);
  Rational& operator-=(const int rhs) { return operator-=(Rational(rhs)); }
  Rational& operator*=(const Rational& rhs);
  Rational& operator*=(const int rhs) { return operator*=(Rational(rhs)); }
  Rational& operator/=(const Rational& rhs);
  Rational& operator/=(const int rhs) { return operator/=(Rational(rhs)); }
  std::ostream& writeTo(std::ostream& ostrm) const;
  std::istream& readFrom(std::istream& istrm);
  static const char Vinculum{ '/' };
private:
  int num { 0 };
  int den { 1 };
  Rational& reduction();
};

  Rational operator+(const Rational& lhs, const Rational& rhs);
  Rational operator+(const Rational& lhs, const int rhs);
  Rational operator+(const int lhs, const Rational& rhs);

  Rational operator-(const Rational& lhs, const Rational& rhs);
  Rational operator-(const Rational& lhs, const int rhs);
  Rational operator-(const int lhs, const Rational& rhs);

  Rational operator*(const Rational& lhs, const Rational& rhs);
  Rational operator*(const Rational& lhs, const int rhs);
  Rational operator*(const int lhs, const Rational& rhs);

  Rational operator/(const Rational& lhs, const Rational& rhs);
  Rational operator/(const Rational& lhs, const int rhs);
  Rational operator/(const int lhs, const Rational& rhs);

  inline std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs) {
    return rhs.writeTo(ostrm);
  }

  inline std::istream& operator>>(std::istream istrm, Rational& rhs) {
    return rhs.readFrom(istrm);
  }

#endif
