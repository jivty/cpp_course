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

}

Rational& Rational::operator-=(const Rational& rhs) {

}

Rational& Rational::operator*=(const Rational& rhs) {
  num *= rhs.num;
  den *= rhs.den;
  return *this;
}

Rational& Rational::operator/=(const Rational& rhs) {
  if (rhs.num == 0) {
    throw std::invalid_argument("Division by zero");
  } else {

  }
}