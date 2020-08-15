#ifndef OBJS_HPP
#define OBJS_HPP

#include "additivemathelements.hpp"
#include <iostream>
#include <vector>

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

class CellScene
{
public:
    CellScene();
    CellScene(size_t width_, size_t length_);

    size_t getWidth();
    size_t getLength();

    void changeSize(size_t newWidth, size_t newLength);

private:
    size_t width, length;

    size_t modelsNum;
    std::vector<PolModel> models;

    size_t illumNum;
    std::vector<Illuminant> illuminants;

    std::vector<std::vector<bool>> cells;
};

#endif // OBJS_HPP
