#ifndef OBJS_HPP
#define OBJS_HPP

#include "additivemathelements.hpp"
#include <iostream>
#include <vector>

class Vertex
{
public:
    Vertex() {}
    Vertex(Dot3D &position_, std::vector<size_t> &usedFacets_)
    : position(position_), usedFacets(usedFacets_)
    {
    }

    Vertex(Dot3D &position_) : position(position_) {}

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
    void setVertices(std::vector<Vertex> &vertices_);
    const std::vector<Facet> getFacets();
    void setFacets(std::vector<Facet> facets_);

private:
    std::vector<Vertex> vertices;
    std::vector<Facet> facets;
};

class Illuminant
{
public:
    Illuminant(Eigen::Matrix4f &transMat);

    void setBuf(std::vector<std::vector<double>> &setBuf);
    std::vector<std::vector<double>> &getBuf();

    void setTransMat(Eigen::Matrix4f &mat);
    Eigen::Matrix4f &getTransMat();
private:
    std::vector<std::vector<double>> shadowBuffer;
    Eigen::Matrix4f transMatrix;
};

class CellScene
{
public:
    CellScene();
    CellScene(size_t width_, size_t height_);

    operator bool() const;

    size_t getWidth();
    size_t getHeight();

    const Dot3D getStartOfPlate();
    void setStartOfPlate(Dot3D dot_);

    const Dot3D getEndOfPlate();
    void setEndOfPlate(Dot3D dot_);

    void buildPlateModel(Dot3D startOfPlate_, Dot3D endOfPlate_);
    PolModel &getPlateModel();

    void changeSize(size_t newWidth, size_t newheight);

    void moveUp(double value);
    void moveDown(double value);
    void moveLeft(double value);
    void moveRight(double value);

    void rotateX(double angle);
    void rotateY(double angle);
    void rotateZ(double angle);

    size_t getModelsNum();
    PolModel &getModel(size_t num);
    void addModel(PolModel &model);

    size_t getIllumNum();
    Illuminant &getIlluminant(size_t num);
    void addIlluminant(Illuminant &illum);

    Eigen::Matrix4f &getTransMatrix();
    void multToTrans(Eigen::Matrix4f &newTrans);

private:
    size_t width, height;

    Dot3D startOfPlate, endOfPlate;
    PolModel *plateModel = nullptr;

    Eigen::Matrix4f transMatrix;

    size_t modelsNum = 0;
    std::vector<PolModel> models;

    size_t illumNum;
    std::vector<Illuminant> illuminants;

    Dot3D centerDot;

    std::vector<std::vector<bool>> cells;
};

#endif // OBJS_HPP
