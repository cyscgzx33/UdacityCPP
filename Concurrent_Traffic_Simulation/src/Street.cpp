#include <iostream>
#include "Vehicle.h"
#include "Intersection.h"
#include "Street.h"


Street::Street()
{
    _type = ObjectType::objectStreet;
    _length = 1000.0; // in m
}

void Street::setInIntersection(std::shared_ptr<Intersection> in)
{
    _interIn = in;
    in->addStreet(get_shared_this()); // add this street to list of streets connected to the intersection
}

void Street::setOutIntersection(std::shared_ptr<Intersection> out)
{
    _interOut = out;
    out->addStreet(get_shared_this()); // add this street to list of streets connected to the intersection
}
