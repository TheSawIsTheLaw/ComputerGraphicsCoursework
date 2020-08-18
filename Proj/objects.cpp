#include "objects.hpp"
#include <QDebug>

const Dot3D &Vertex::getPosition() { return position; }

void Vertex::setPosition(Dot3D &position_) { position = position_; }

const std::vector<size_t> Vertex::getUsedFacets() { return usedFacets; } // Changeable?

void Vertex::setUsedFacets(std::vector<size_t> usedFacets_) { usedFacets = usedFacets_; }

const std::vector<size_t> Facet::getUsedDots() { return usedDots; }

void Facet::setUsedDots(std::vector<size_t> usedDots_) { usedDots = usedDots_; }

const std::vector<Vertex> PolModel::getVertices() { return vertices; }

void PolModel::setVertices(std::vector<Vertex> vertices_) { vertices = vertices_; }

const std::vector<Facet> PolModel::getFacets() { return facets; }

void PolModel::setFacets(std::vector<Facet> facets_) { facets = facets_; }

CellScene::CellScene() {}

CellScene::CellScene(size_t width_, size_t length_)
{
    width = width_;
    length = length_;

    for (size_t i = 0; i < length_; i++)
    {
        cells.push_back(std::vector<bool>(width_));
        for (size_t j = 0; j < width_; j++) cells[i][j] = true;
    }

    modelsNum = 0;
    illumNum = 0;
}

size_t CellScene::getWidth() { return width; }

size_t CellScene::getLength() { return length; }

void CellScene::changeSize(size_t newWidth, size_t newLength)
{
    if (newWidth >= width)
        width = newWidth;
    //    else Вот тут потребуется анализ ситуации...
    qDebug("%zu is new width\n", width);

    if (newLength >= length)
        length = newLength;
    //    else Тоже самое

    qDebug("%zu is new length\n", length);
}
