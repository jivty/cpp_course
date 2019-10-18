#include "rational.h"
#include <iostream>

Rational& Rational::reduction() {
  int tmpNum = num;
  int tmpDen = den;
  while ((tmpNum != 0) && (tmpDen != 0))
    tmpNum > tmpDen ? tmpNum %= tmpDen : tmpDen %= tmpNum;
  num /= (tmpNum + tmpDen);
  den /= (tmpNum + tmpDen);
  return *this;
}

Rational::Rational(const int numerator, const int denuminator)
  : num(numerator)
  , den(denuminator) {
  reduction();
}

Rational::Rational(const int numerator)
  : Rational(numerator, 1) {
}

Rational& Rational::operator=(const int rhs) {
  num = rhs;
  den = 1; 
  return *this;
}

bool Rational::operator==(const Rational& rhs) const {
  return ((num == rhs.num) && (den == rhs.den));
}

bool Rational::operator!=(const Rational& rhs) const {
  return !operator==(rhs);
}

Rational& Rational::operator+=(const Rational& rhs) {
  num = num * rhs.den + den * rhs.num;
  den *= rhs.den;
  reduction();
  return *this;
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
  Rational sum(lhs);
  sum += rhs;
  return sum;
}

Rational operator+(const Rational& lhs, const int rhs) {
  return lhs + Rational(rhs);
}

Rational operator+(const int lhs, const Rational& rhs) {
  return Rational(lhs) + rhs;
}

Rational& Rational::operator-=(const Rational& rhs) {
  num = num * rhs.den - den * rhs.num;
  den *= rhs.den;
  reduction();
  return *this;
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
  Rational res(lhs);
  res -= rhs;
  return res;
}

Rational operator-(const Rational& lhs, const int rhs) {
  return lhs - Rational(rhs);
}

Rational operator-(const int lhs, const Rational& rhs) {
  return Rational(lhs) - rhs;
}

Rational& Rational::operator*=(const Rational& rhs) {
  num *= rhs.num;
  den *= rhs.den;
  reduction();
  return *this;
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
  Rational res(lhs);
  res *= rhs;
  return res;
}

Rational operator*(const Rational& lhs, const int rhs) {
  return lhs * Rational(rhs);
}

Rational operator*(const int lhs, const Rational& rhs) {
  return Rational(lhs) * rhs;
}

Rational& Rational::operator/=(const Rational& rhs) {
  if (rhs.num == 0) {
    throw std::invalid_argument("Division by zero");
  } else {
    num *= rhs.den;
    den *= rhs.num;
    reduction();
  }
  return *this;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
  Rational res(lhs);
  res /= rhs;
  return res;
}

Rational operator/(const Rational& lhs, const int rhs) {
  return lhs / Rational(rhs);
}

Rational operator/(const int lhs, const Rational rhs) {
  return Rational(lhs) / rhs;
}

std::ostream& Rational::writeTo(std::ostream& ostrm) const {
  ostrm << num << vinculum << den;
  return ostrm;
}
std::istream& Rational::readFrom(std::istream& istrm) {
  int numerator = 0;
  char viniculum = '0';
  int denuminator = 0;
  istrm >> numerator >> viniculum >> denuminator;
  if (istrm.good()) {
    if (Rational::vinculum == viniculum) {
      num = numerator;
      den = denuminator;
    } else {
      istrm.setstate(std::ios_base::failbit);
    }
  }
  return istrm;
}
