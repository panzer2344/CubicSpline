#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

class Point {
private:
	double x, y;

public:
	Point(double _x = 0.0, double _y = 0.0) {
		x = _x;
		y = _y;
	}

	double getX() const {
		return x;
	}

	double getY() const{
		return y;
	}

	void setX(double _x) {
		x = _x;
	}

	void setY(double _y) {
		y = -y;
	}
};

class SplineFunc {
private:
	double a, b, c, d, x;

public:
	SplineFunc(double _a = 0.0, double _b = 0.0, double _c = 0.0, double _d = 0.0) {
		a = _a;
		b = _b;
		c = _c;
		d = _d;
	}

	double getA() const{
		return a;
	}

	double getB() const{
		return b;
	}

	double getC() const{
		return c;
	}

	double getD() const{
		return d;
	}

	double getX() const {
		return x;
	}
	
	void setA(double _a) {
		a = _a;
	}

	void setB(double _b) {
		b = _b;
	}

	void setC(double _c) {
		c = _c;
	}

	void setD(double _d) {
		d = _d;
	}

	void setX(double _x) {
		x = _x;
	}
};

class Spline {
private:
	vector<SplineFunc> splineFuncs;
	size_t funcsNumber;
	vector<Point> keyPoints;
	size_t pointsNumber;

public:
	Spline(const vector<Point>& points) {
		keyPoints = points;
		funcsNumber = points.size() - 1;
		pointsNumber = points.size();
		cout << "funcs number = " << funcsNumber << endl;
	}

	void calculateSpline() {
		vector<double> a(pointsNumber), b(funcsNumber), d(funcsNumber), mu(funcsNumber),
			h(funcsNumber), alfa(funcsNumber - 1), c(pointsNumber), l(pointsNumber), z(pointsNumber);

		//Ai = Yi, i = 0 .. k
		for (size_t i = 0; i < pointsNumber; i++) {
			a[i] = keyPoints[i].getY();
		}

		//Hi = Xi+1 - Xi, i = 0 .. k - 1
		for (size_t i = 0; i < funcsNumber; i++) {
			h[i] = keyPoints[i + 1].getX() - keyPoints[i].getX();
		}

		//calc alfai , i = 1 .. k - 1
		for (size_t i = 1; i < funcsNumber; i++) {
			alfa[i] = 3 * (a[i + 1] - a[i]) / h[i] - 3 * (a[i] - a[i - 1]) / h[i - 1];
		}

		//setting start values of l0, mu0, z0
		mu[0] = 0;
		z[0] = 0;
		l[0] = 1;

		//a direct pass of the algorithm
		for (size_t i = 1; i < funcsNumber; i++) {
			l[i] = 2 * (keyPoints[i + 1].getX() - keyPoints[i - 1].getX()) - h[i - 1] * mu[i - 1];
			mu[i] = h[i] / l[i];
			z[i] = (alfa[i] - h[i - 1] * z[i - 1]) / l[i];
		}

		l[funcsNumber] = 1;
		z[funcsNumber] = 0;
		c[funcsNumber] = 0;

		//the reverse pass of the algorithm
		for (int j = funcsNumber - 1; j >= 0; j--) {
			c[j] = z[j] - mu[j] * c[j + 1];
			b[j] = (a[j + 1] - a[j]) / h[j] - h[j] * (c[j + 1] + 2 * c[j]) / 3;
			d[j] = (c[j + 1] - c[j]) / (3 * h[j]);
		}

		//init spline
		for (size_t i = 0; i < funcsNumber; i++) {
			splineFuncs[i].setA(a[i]);
			splineFuncs[i].setB(b[i]);
			splineFuncs[i].setC(c[i]);
			splineFuncs[i].setD(d[i]);
			splineFuncs[i].setX(keyPoints[i].getX());
		}
	}

	Point aproximate(const Point& point) {
		Point result;
		double resultY;
		double currentX = point.getX();

		if (point.getX() < keyPoints[0].getX()
			|| point.getX() > keyPoints[pointsNumber - 1].getX()
			)
		{
			cout << "Point out of bounds" << endl;
		}

		for (size_t i = 1; i < pointsNumber; i++) {
			double splineX = keyPoints[i].getX();
			if (currentX < splineX) {
				int j = i - 1;
				double diff = currentX - splineX;
				
				resultY = splineFuncs[j].getA() + splineFuncs[j].getB() * diff + splineFuncs[j].getC() * (diff * diff) + splineFuncs[j].getC() * (diff * diff * diff);
				result = Point(currentX, resultY);
				
				return result;
			}
		}
	}

	void print() {
		for (auto func : splineFuncs) {
			double x = func.getX();
			cout << func.getA() << ((func.getB() > 0) ? "+" : "")
				<< func.getB() << "(x" << ((x > 0) ? "+" : "") << x << ")"
				<< ((func.getC() > 0) ? "+" : "") << "(x" << ((x > 0) ? "+" : "") << x << ")^2"
				<< ((func.getD() > 0) ? "+" : "") << "(x" << ((x > 0) ? "+" : "") << x << ")^3";
		}
	}

};

int main(int argc, char* argv[]) {

	vector<Point> points(
				{ 
					Point(-3.0, 5.0),
					Point(-1.0, 1.0),
					Point(1.0, 1.0),
					Point(3.0, 5.0)
				}
	);

	Spline mySpline(points);
	mySpline.calculateSpline();
	mySpline.print();

	Sleep(3000);

	return 0;
}