#include "objects.hpp"
#include <QDebug>

const Dot3D &Vertex::getPosition() const { return position; }

void Vertex::setPosition(Dot3D &position_) { position = position_; }

const std::vector<size_t> Vertex::getUsedFacets() { return usedFacets; } // Changeable?

void Vertex::setUsedFacets(std::vector<size_t> usedFacets_) { usedFacets = usedFacets_; }

const std::vector<size_t> Facet::getUsedDots() { return usedDots; }

void Facet::setUsedDots(std::vector<size_t> usedDots_) { usedDots = usedDots_; }

const std::vector<Vertex> PolModel::getVertices() { return vertices; }

void PolModel::setVertices(std::vector<Vertex> vertices_) { vertices = vertices_; }

const std::vector<Facet> PolModel::getFacets() { return facets; }

void PolModel::setFacets(std::vector<Facet> facets_) { facets = facets_; }

const Dot3D &Illuminant::getPosition() { return position; }

void Illuminant::setPosition(Dot3D &position_) { position = position_; }

const MathVec &Illuminant::getVector() { return vector; }

void Illuminant::setVector(MathVec &vector_) { vector = vector_; }

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

const PolModel &CellScene::getPlateModel() { return *plateModel; }

const Dot3D CellScene::getStartOfPlate() { return startOfPlate; }

void CellScene::setStartOfPlate(Dot3D dot_) { startOfPlate = dot_; }

const Dot3D CellScene::getEndOfPlate() { return endOfPlate; }

void CellScene::buildPlateModel(Dot3D startOfPlate_, Dot3D endOfPlate_)
{
    setStartOfPlate(startOfPlate_);
    setEndOfPlate(endOfPlate_);

    Dot3D exDot(startOfPlate_.getXCoordinate() + (endOfPlate_.getXCoordinate() -
                                                  startOfPlate_.getXCoordinate()) / 2,
    endOfPlate_.getYCoordinate() - (endOfPlate_.getYCoordinate() -
                                                startOfPlate_.getYCoordinate()) / 2,
    startOfPlate_.getZCoordinate());

    std::vector<Vertex> vertices;
    vertices.push_back(Vertex(startOfPlate_, std::vector<size_t>{0, 1}));
    vertices.push_back(Vertex(exDot, std::vector<size_t>{0, 1, 2, 3}));
    vertices.push_back(Vertex(endOfPlate_, std::vector<size_t>{2, 3}));

    exDot.setXCoordinate(startOfPlate_.getXCoordinate());
    exDot.setYCoordinate(endOfPlate_.getYCoordinate());
    vertices.push_back(Vertex(exDot, std::vector<size_t>{0, 3}));

    exDot.setXCoordinate(endOfPlate_.getXCoordinate());
    exDot.setYCoordinate(startOfPlate_.getYCoordinate());
    vertices.push_back(Vertex(exDot, std::vector<size_t>{1, 2}));

    std::vector<Facet> facets;
    facets.push_back(std::vector<size_t>{0, 1, 3});
//    facets.push_back(std::vector<size_t>{0, 1, 4});
//    facets.push_back(std::vector<size_t>{1, 2, 4});
//    facets.push_back(std::vector<size_t>{1, 2, 3});


    //    Dot3D newDiagDot(startOfPlate_.getXCoordinate(), endOfPlate_.getYCoordinate(),
    //    startOfPlate_.getZCoordinate());

    //    std::vector<Vertex> vertices;
    //    vertices.push_back(Vertex(startOfPlate_, std::vector<size_t>{0}));
    //    vertices.push_back(Vertex(newDiagDot, std::vector<size_t>{0, 1}));
    //    vertices.push_back(Vertex(endOfPlate_, std::vector<size_t>{1}));

    //    newDiagDot.setXCoordinate(endOfPlate_.getXCoordinate());
    //    newDiagDot.setYCoordinate(startOfPlate_.getYCoordinate());
    //    newDiagDot.setZCoordinate(startOfPlate_.getZCoordinate());
    //    vertices.push_back(Vertex(newDiagDot, std::vector<size_t>{0, 1}));

    //    std::vector<Facet> facets;
    //    facets.push_back(std::vector<size_t>{0, 1, 2});
    //    facets.push_back(std::vector<size_t>{0, 2, 3});

    if (plateModel)
        delete plateModel;
    plateModel = new PolModel(vertices, facets);

    // Debug
    for (size_t i = 0; i < plateModel->getVertices().size(); i++)
        qDebug() << plateModel->getVertices().at(i).getPosition();
}

void CellScene::setEndOfPlate(Dot3D dot_) { endOfPlate = dot_; }

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
