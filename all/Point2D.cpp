// ==================================================
// - File______: Point2D.cpp ________________________
// - Author____: Ahmet Ardal ________________________
// - Contact___: ardalahmet@hotmail.com _____________
// __________________________________________________
// - Copyright (c) 2009, Some Rights Reserved _______
// ==================================================

#include "Point2D.h"

std::ostream &operator <<(std::ostream &out, const Point2D &pt)
{
    return (out << "(x:" << pt.m_x << "|y:" << pt.m_y << ")");
}
