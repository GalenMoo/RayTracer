#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point
{
    public:
        Point() : x_(0), y_(0), z_(0) {};
        Point(double x, double y, double z) : x_(x), y_(y), z_(z) {};

        double x() const { return x_; }
        double y() const { return y_; }
        double z() const { return z_; }

        Point operator+(const Point &other);
        Point operator+=(const Point &other);
        Point operator-() const;
        Point operator-(const Point &other);
        Point operator*(double m);
        // Point operator/(double d);

        double operator[](int i) const;
        double& operator[](int i);
        
        friend std::ostream& operator<<(std::ostream &out, const Point &p);

        double length() const;
        double length_squared() const;
        
        static Point random();
        static Point random(double min, double max);
    private:
        double x_;
        double y_;
        double z_;   
};

inline Point operator+(const Point &p1, const Point &p2) {
    return Point(p1[0] + p2[0], p1[1] + p2[1], p1[2] + p2[2]);
}

inline Point operator*(const Point &p1, const Point &p2) {
    return Point(p1[0] * p2[0], p1[1] * p2[1], p1[2] * p2[2]);
}

inline Point operator*(double t, const Point &p) {
    return Point(t*p[0], t*p[1], t*p[2]);
}

inline Point operator*(const Point &p, double t) {
    return t * p;
}

inline Point operator-(const Point &p1, const Point &p2) {
    return Point(p1[0] - p2[0], p1[1] - p2[1], p1[2] - p2[2]);
}

inline Point operator/(Point p, double t) {
    return (1/t) * p;
}


using Color = Point;
#endif