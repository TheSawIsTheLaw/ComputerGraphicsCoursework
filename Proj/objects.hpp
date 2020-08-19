#ifndef OBJS_HPP
#define OBJS_HPP

#include "additivemathelements.hpp"
#include <iostream>
#include <vector>

class Vertex
{
public:
    Vertex() {}
    Vertex(Dot3D &position_, std::vector<size_t> usedFacets_)
    : position(position_), usedFacets(usedFacets_)
    {
    }

    const Dot3D &getPosition() const;
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
    Facet() {}
    Facet(std::vector<size_t> usedDots_) : usedDots(usedDots_) {}

    const std::vector<size_t> getUsedDots();
    void setUsedDots(std::vector<size_t> usedDots_);

private:
    std::vector<size_t> usedDots;
};

class PolModel
{
public:
    PolModel() {}
    PolModel(std::vector<Vertex> vertices_, std::vector<Facet> facets_)
    : vertices(vertices_), facets(facets_)
    {
    }

    const std::vector<Vertex> getVertices();
    void setVertices(std::vector<Vertex> vertices_);
    const std::vector<Facet> getFacets();
    void setFacets(std::vector<Facet> facets_);

private:
    std::vector<Vertex> vertices;
    std::vector<Facet> facets;
};

class Illuminant
{
public:
    const Dot3D &getPosition();
    void setPosition(Dot3D &position_);

    const MathVec &getVector();
    void setVector(MathVec &vector_);

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

    const Dot3D getStartOfPlate();
    void setStartOfPlate(Dot3D dot_);

    const Dot3D getEndOfPlate();
    void setEndOfPlate(Dot3D dot_);

    void buildPlateModel(Dot3D startOfPlate_, Dot3D endOfPlate_);

    void changeSize(size_t newWidth, size_t newLength);

private:
    size_t width, length;

    Dot3D startOfPlate, endOfPlate;
    PolModel *plateModel = nullptr;

    size_t modelsNum;
    std::vector<PolModel> models;

    size_t illumNum;
    std::vector<Illuminant> illuminants;

    std::vector<std::vector<bool>> cells;
};

#endif // OBJS_HPP
