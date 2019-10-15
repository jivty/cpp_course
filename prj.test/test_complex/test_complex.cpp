#include "complex.h"
#include <iostream>
#include <sstream>
using namespace std;

bool testParse(const std::string& str) {
	istringstream istrm(str);
	Complex z;
	istrm >> z;
	if (istrm.good())
	{
		cout << "Read success: " << str << " -> " << z << endl;
	}
	else
	{
		cout << "Read error: " << str << " -> " << z << endl;
	}
	return istrm.good();
}

int main() {
	Complex z;
	cout << "z = " << z << endl;
	z = 3.14;
	cout << "z = 3.14 : z -> " << z << endl;
	z = Complex(-43.2, -8);
	cout << "z = Complex(-43.2, -8) : z -> " << z << endl;
	cout << endl;
	cout << "z == Complex(-43.2, -8) ? -> " << (z == Complex(-43.2, -8) ? "yes" : "no") << endl;
	cout << "z != Complex(1, 2) ? -> " << (z != Complex(1, 2) ? "yes" : "no") << endl;
	cout << endl;
	z += Complex(8.1);
	cout << "z += Complex(8.1) : z -> " << z << endl;
	z += 2.71;
	cout << "z += 2.71 : z -> " << z << endl;
	z -= Complex(5.0, 3.2);
	cout << "z -= Complex(5.0, 3.2) : z -> " << z << endl;
	z -= 2.71;
	cout << "z -= 2.71 : z -> " << z << endl;
	z *= Complex(3.2, 4.5);
	cout << "z *= Complex(3.2, 4.5) : z -> " << z << endl;
	z *= 7.9;
	cout << "z *= 7.9 : z -> " << z << endl;
	z /= Complex(1.2, 2.3);
	cout << "z /= Complex(1.2, 2.3) : z -> " << z << endl;
	z /= 1.5;
	cout << "z /= 1.5 : z -> " << z << endl;
	z = conj(z);
	cout << "z = conj(z) : z -> " << z << endl;
	cout << endl;
	Complex b(27.32,-8.9);
	cout << "b = " << b << endl;
	cout << "z + b = " << z + b << endl;
	cout << "z - b = " << z - b << endl;
	cout << "z * b = " << z * b << endl;
	cout << "z / b = " << z / b << endl;
	cout << endl;
	cout << "z = " << z << endl;
	cout << "z + 3.2 = " << z + 3.2 << endl;
	cout << "4.2 + z = " << 4.2 + z << endl;
	cout << "z - 4.7 = " << z - 4.7 << endl;
	cout << "7.8 - z = " << 7.8 - z << endl;
	cout << "z * 0.9 = " << z * 0.9 << endl;
	cout << "1.2 * z = " << 1.2 * z << endl;
	cout << "z / 0.9 = " << z / 0.9 << endl;
	cout << "0.9 / z = " << 0.9 / z << endl;
	cout << endl;
	cout << "z / 0 = ";
	try {
		cout << z / 0;
	}
	catch (invalid_argument) {
		cout << "Division by zero is cathed" << endl;
	}
	cout << "z / Complex(0, 0) = ";
	try {
		cout << z / Complex(0, 0);
	}
	catch (invalid_argument) {
		cout << "Division by zero is cathed" << endl;
	}
	cout << endl;
	testParse("(8.9,9)");
	testParse("{8.9,9}");
	testParse("(8.9, 9)");
	testParse("(8.9,9");
	return 0;
}