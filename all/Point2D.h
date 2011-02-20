// ==================================================
// - File______: Point2D.h __________________________
// - Author____: Ahmet Ardal ________________________
// - Contact___: ardalahmet@hotmail.com _____________
// __________________________________________________
// - Copyright (c) 2009, Some Rights Reserved _______
// ==================================================

#ifndef POINT2D_H_
#define POINT2D_H_

#include <iostream>

class Point2D
{
private:
    int m_x;
    int m_y;

public:
    Point2D(int x = 0, int y = 0) : m_x(x), m_y(y)
    {
    }

    // copy constructor
    Point2D(const Point2D &pt)
    {
        m_x = pt.m_x;
        m_y = pt.m_y;
    }

    // accessor member functions
    int x() const
    {
        return m_x;
    }

    int y() const
    {
        return m_y;
    }

    void setX(int x)
    {
        m_x = x;
    }

    void setY(int y)
    {
        m_y = y;
    }

    void setXY(int x, int y)
    {
        m_x = x;
        m_y = y;
    }

    // assignment operator
    Point2D &operator =(const Point2D &pt)
    {
        m_x = pt.m_x;
        m_y = pt.m_y;

        return *this;
    }

    // less than operator
    bool operator <(const Point2D &pt) const
    {
        return (m_x < pt.m_x) && (m_y < pt.m_y);
    }

    // greater than operator
    bool operator >(const Point2D &pt) const
    {
        return (m_x > pt.m_x) && (m_y > pt.m_y);
    }

    // equality operator
    bool operator ==(const Point2D &pt) const
    {
        return (m_x == pt.m_x) && (m_y == pt.m_y);
    }

    // to print a Point2D object to stdout with an ostream object such as "cout"
    friend std::ostream &operator <<(std::ostream &out, const Point2D &pt);
};

#endif // POINT2D_H_
