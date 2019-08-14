#ifndef STREET_H
#define STREET_H

#include "TrafficObject.h"

// forward declaration to avoid include cycle
class Intersection;

class Street : public TrafficObject, public std::enable_shared_from_this<Street>
{
public:
    // constructor / desctructor
    Street();

    // getters / setters
    double getLength() { return _length; }
    void setInIntersection(std::shared_ptr<Intersection> in);
    void setOutIntersection(std::shared_ptr<Intersection> out);
    std::shared_ptr<Intersection> getOutIntersection() { return _interOut; }
    std::shared_ptr<Intersection> getInIntersection() { return _interIn; }

    // typical behaviour methods

    // miscellaneous
    std::shared_ptr<Street> get_shared_this() { return shared_from_this(); }

private:
    double _length;                                    // length of this street in m
    std::shared_ptr<Intersection> _interIn, _interOut; // intersections from which a vehicle can enter (one-way streets is always from 'in' to 'out')
};

#endif