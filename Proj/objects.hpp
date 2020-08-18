#ifndef OBJS_HPP
#define OBJS_HPP

#include "additivemathelements.hpp"
#include <iostream>
#include <vector>

class Vertex
{
public:
    const Dot3D &getPosition();
    void setPosition(Dot3D &position_);
    const std::vector<size_t> getUsedFacets();
    void setUsedFacets(std::vector<size_t> usedFacets_);

private:
    Dot3D position;
    std::vector<size_t> usedFacets;
};

class Facet
{
public:
    std::vector<size_t> getUsedDots();
    void setUsedDots(std::vector<size_t> usedDots_);

private:
    std::vector<size_t> usedDots;
};

class PolModel
{
public:
    std::vector<Vertex> getVertices();
    void setVertices(std::vector<Vertex> vertices_);
    std::vector<Facet> getFacets();
    void setFacets(std::vector<Facet> facets_);

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
