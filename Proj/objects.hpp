#ifndef OBJS_HPP
#define OBJS_HPP

#include "additivemathelements.hpp"
#include <vector>
#include <iostream>

class Vertex
{
private:
    Dot3D position;
    std::vector<size_t> usedFacets;
};

class Facet
{
private:
    std::vector<size_t> usedDots;
};

class PolModel
{
private:
    std::vector<Vertex> vertices;
    std::vector<Facet> facets;
};

class Illuminant
{
private:
    Dot3D position;
    MathVec vector;
};

class cellScene
{
private:
    size_t width, length;

    size_t modelsNum;
    std::vector<PolModel> models;

    size_t illumNum;
    std::vector<Illuminant> illuminants;

    std::vector<std::vector<bool>> cells;
};

#endif // OBJS_HPP
