/*
* 
* Коэффициенты уравнения кривой второго порядка 
* a * x ^ 2 + b * y ^ 2 + c * x + d * y + e = 0
* - целые числа от - 10 до 10. 
* Дано 30 таких уравнений.
* Расссортировать их по типу кривых
* ( окружности, эллипсы, гиперболы, параболы и т.д. )
* 
*/


#include <vector>
#include <string>

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>

#include <windows.h>
#include <math.h>
#include "conio.h"



// количество уравнений кривых
#define CURVE_COUNT 3

// струтура с коэффициентами кривой
class Curve2 {

public:
	short a, b, c, d, e;

public:
	Curve2() = default;
	Curve2(short A, short B, short C, short D, short E) : a(A), b(B), c(C), d(D), e(E) {}
	~Curve2() = default;
	Curve2(const Curve2&) = default;

	std::string getStrStrm() {
		std::stringstream output;

		if (a != 0) {
			output << std::setw(4) << fabs(a) << " * x^2";
		} else {
			output << std::setw(10) << ' ';
		}
		if (b != 0) {
			output << std::setw(3) << ((b < 0) ? "-" : "+");
			output << std::setw(4) << fabs(b) << " * y^2";
		} else {
			output << std::setw(13) << ' ';
		}
		if (c != 0) {
			output << std::setw(3) << ((c < 0) ? "-" : "+");
			output << std::setw(4) << fabs(c) << " * x  ";
		} else {
			output << std::setw(13) << ' ';
		}
		if (d != 0) {   
			output << std::setw(3) << ((d < 0) ? "-" : "+");
			output << std::setw(4) << fabs(d) << " * y  ";
		} else {
			output << std::setw(13) << ' ';
		}
		if (e != 0) {
			output << std::setw(3) << ((e < 0) ? "-" : "+");
			output << std::setw(4) << fabs(e) << "   = 0";
		} else {
			output << std::setw(13) << ' ';
		}

		return output.str();
	}

};

// тип кривой
enum Curve2Type {
	incorrect_curve2 = 0u,
	circle,
	ellips,
	hyperbole,
	parabola,
};

// тип кривой текстом
LPCSTR Curve2TypeStr(unsigned int type) {
	switch (type) {

		case 0u: {
			return "unknown";
		} break;

		case 1u: {
			return "circle";
		} break;

		case 2u: {
			return "ellips";
		} break;

		case 3u: {
			return "hyperbole";
		} break;

		case 4u: {
			return "parabola";
		} break;

		default: {
			return "lol error";
		}

	}
}

// кривая и ее тип
struct Curve2Add {
	Curve2 curve;
	byte type;
};


// получиение типа кривой
byte GetCurveType(Curve2 curve){

	// проверка на эллипс ( ab > 0 )
	if (curve.a * curve.b > 0) {
		// окружность ( )
		/*if (a == c) {
			return circle;
		}*/
		return ellips;
	}
	// проверка на гиперболу ( ab < 0 )
	if (curve.a * curve.b < 0) {
		return hyperbole;
	}
	// проверка на параболу ( только один из a, b равен 0 )
	if (curve.a * curve.a + curve.b * curve.b != 0 && curve.a * curve.b == 0) {
		return parabola;
	}

	return incorrect_curve2;
}


// получение вектора с кривыми и типами и вектора с кривыми
std::vector<Curve2Add>* Curve2AddVecConstr( std::vector<Curve2>* vec ) {

	auto newVec = new std::vector<Curve2Add>;

	for (const auto& i : *vec) {
		
		newVec->push_back({
			i,					// Curve
			GetCurveType(i),	// Type
		});

	}

	return newVec;

}


// сортировка вектора с кривыми
void Curve2Sort(std::vector<Curve2Add>* vec) {

	// конец вектора
	auto vec_end = vec->end();

	for (auto i = vec->begin(); i < vec_end; i++) {
		for (auto k = i; k < vec_end; k++)

			if (i->type < k->type) {
				auto tmp = *i;
				*i = *k;
				*k = tmp;
			}

	}

}


// сортировка вектора с кривыми
std::vector<Curve2Add>* Curve2Sort( std::vector<Curve2>* vec ) {
	
	// получение типов кривых
	auto v = Curve2AddVecConstr( (std::vector<Curve2>*)(vec) );

	// сортировка
	Curve2Sort(v);

	return v;

}


std::vector<Curve2>* GetDataRandom(unsigned int n) {

	auto curveVec = new std::vector<Curve2>;

	std::cout << "generating " << n << " random equations\n";

	srand(GetTickCount64());

	for (auto i = 0u; i < n; i++) {
		curveVec->push_back(Curve2(
			rand() % 20 - 10,
			rand() % 20 - 10,
			rand() % 20 - 10,
			rand() % 20 - 10,
			rand() % 20 - 10
		));
	}

	return curveVec;

}

std::vector<Curve2>* GetDataFile(unsigned int n) {

	auto curveVec = new std::vector<Curve2>;

	std::cout << "input filename: ";
	std::string filename;
	std::cin >> filename;
	std::ifstream fin(filename);

	short a, b, c, d, e;
	for (auto i = 0u; i < n; i++) {
		fin >> a >> b >> c >> d >> e;
		curveVec->push_back(Curve2(a, b, c, d, e));
	}

	fin.close();
	return curveVec;

}

std::vector<Curve2>* GetDataCmd(unsigned int n) {

	auto curveVec = new std::vector<Curve2>;

	std::cout << "input " << n << " sets of a,b,c,d,e coefficients\n";

	short a, b, c, d, e;
	for (auto i = 0u; i < n; i++) {
		std::cin >> a >> b >> c >> d >> e;
		curveVec->push_back(Curve2(a, b, c, d, e));
	}

	return curveVec;

}



int main() {

	


	// вектор с исходными данными
	std::vector<Curve2>* curveVec = 0;

	bool flag = true;

	while (flag) {

		std::cout << "\
choose where to get data from\n\
1 - random\n\
2 - file\n\
3 - cmd\n\n";

		byte cmd = _getch();

		switch (cmd) {

		case '1': {
			curveVec = GetDataRandom(CURVE_COUNT);
			flag = false;
		} break;

		case '2': {
			curveVec = GetDataFile(CURVE_COUNT);
			flag = false;
		} break;

		case '3': {
			curveVec = GetDataCmd(CURVE_COUNT);
			flag = false;
		} break;

		}

	}
	

	std::cout << "sort by curve type\n";

	auto curveVecSorted = Curve2Sort(curveVec);
	delete curveVec;


	std::cout << "\nresult:\n\n";

	for (auto& i : *curveVecSorted) {
		std::cout << i.curve.getStrStrm() << "      " << Curve2TypeStr(i.type) << "\n\n";
	}

	
	std::cout << "\n\npress any button for exit...";
	_getch();



	delete curveVecSorted;

	return 0;

}
