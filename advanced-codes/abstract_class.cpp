#include<iostream>
#include<string>
#include<sstream>
#include<vector>

using namespace std;

//base class
class Shape {
	virtual void setX(int xcor) = 0;
	virtual void setY(int ycor) = 0;
	virtual int getX() const = 0; //http://stackoverflow.com/questions/751681/meaning-of-const-last-in-a-c-method-declaration
	virtual int getY() const = 0;
	virtual void draw() const = 0;
};

class Circle : public Shape {
private:
	int x, y, radius;
public:
	Circle(int xcorr, int ycorr, int r) {
		x = xcorr;
		y = ycorr;
		radius = r;
	}

	virtual void setX(int xcorr) {
		x = xcorr;
	}

	virtual void setY(int ycorr) {
		y = ycorr;
	}

	virtual int getX() const{
		return x;
	}

	virtual int getY() const{
		return y;
	}

	virtual int getRadius() const {
		return radius;
	}

	virtual void draw() const {
		cout << "drawing circle at: " << getX() << "," << getY() << ", With a radius of: " << getRadius() <<endl;
	}

};

int main() {

	Circle cl(2, 3, 5);
	cl.draw();

	return 0;
}
