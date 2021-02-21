/*
 * @File: point.cpp
 * @Author: Galen
 * @File Created: 2021-02-20 1:11:48 pm
 * @Last Modified: 2021-02-20 1:19:52 pm
 * @Description: 
 */

#include <iostream>
#include <cmath>
#include <stdexcept>

#include "point.h"

Point Point::operator+(const Point &other){
    return Point(this->x_ + other.x_,
                 this->y_ + other.y_,
                 this->z_ + other.z_);
}

Point Point::operator+=(const Point &other){
    x_ += other.x_;
    y_ += other.y_;
    z_ += other.z_;

    return *this;
}

Point Point::operator-() const{
    return Point(-this->x_, -this->y_, -this->z_);
}

Point Point::operator-(const Point &other){
    return Point(this->x_-other.x_, this->y_-other.y_, this->z_-other.z_);
}

Point Point::operator*(double m){
    return Point(this->x_*m, this->y_*m, this->z_*m);
}

// Point Point::operator/(double d){
//     return Point(this->x_/d, this->y_/d, this->z_/d);
// }

double Point::operator[](int i) const{
    if (i == 0)
        return this->x_;
    else if (i == 1)
        return this->y_;
    else if (i == 2)
        return this->z_;
    else{
        throw std::out_of_range("Pointer out of range");
        return -1;
    }
}

double& Point::operator[](int i){
    if (i == 0)
        return this->x_;
    else if (i == 1)
        return this->y_;
    else if (i == 2)
        return this->z_;
    else{
        throw std::out_of_range("Pointer out of range");
        return this->x_;
    }
}

std::ostream& operator<<(std::ostream &out, const Point &p) {
    return out << "Point(" << p[0] << ", " << p[1] << ", " << p[2] << ")";
}

double Point::length() const{
    return std::sqrt(x_*x_ + y_*y_ + z_*z_);
}