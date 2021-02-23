/*
 * @File: ray.cpp
 * @Author: Galen
 * @File Created: 2021-02-20 3:16:53 pm
 * @Last Modified: 2021-02-20 5:27:58 pm
 * @Description: 
 */
#include <iostream>

#include "ray.h"

Point Ray::at(double t) const{
    return origin_ + t*dir_;
}
