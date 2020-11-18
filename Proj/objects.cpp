#include "objects.hpp"
#include <QDebug>

#include "config.hpp"

const Dot3D &Vertex::getPosition() const { return position; }

void Vertex::setPosition(Dot3D &position_) { position = position_; }

const std::vector<size_t> Vertex::getUsedFacets() { return usedFacets; }

void Vertex::setUsedFacets(std::vector<size_t> usedFacets_) { usedFacets = usedFacets_; }

const std::vector<size_t> Facet::getUsedDots() { return usedDots; }

void Facet::setUsedDots(std::vector<size_t> usedDots_) { usedDots = usedDots_; }

const std::vector<Vertex> PolModel::getVertices() { return vertices; }

void PolModel::setVertices(std::vector<Vertex> &vertices_) { vertices = vertices_; }

const std::vector<Facet> PolModel::getFacets() { return facets; }

void PolModel::setFacets(std::vector<Facet> facets_) { facets = facets_; }

QString PolModel::getName() { return modelName; }

void PolModel::setName(QString modelName_) { modelName = modelName_; }

std::vector<std::vector<double>> &Illuminant::getShadowMap() { return shadowBuffer; }

Illuminant::Illuminant(Eigen::Matrix4f &transMatrix_)
{
    transMatrix = transMatrix_;
    for (size_t i = 0; i < ILLUM_VIS_X; i++)
    { shadowBuffer.push_back(std::vector<double>(ILLUM_VIS_Y, 0)); }
}

void Illuminant::setBuf(std::vector<std::vector<double>> &setBuf)
{
    shadowBuffer = setBuf;
}

void Illuminant::clearShadowMap()
{
    for (size_t i = 0; i < shadowBuffer.size(); i++)
    {
        for (size_t j = 0; j < shadowBuffer.at(0).size(); j++)
            shadowBuffer.at(i).at(j) = 0;
    }
}

void Illuminant::setAngles(int xAngle_, int yAngle_)
{
    xAngle = xAngle_;
    yAngle = yAngle_;
}

int Illuminant::getXAngle() { return xAngle; }

int Illuminant::getYAngle() { return yAngle; }

void PolModel::addUsedCell(int xCell, int yCell)
{
    std::array<int, 2> addArray;
    addArray[0] = xCell;
    addArray[1] = yCell;
    usedCells.push_back(addArray);
}

std::vector<std::array<int, 2>> PolModel::getUsedCells() { return usedCells; }

Eigen::Matrix4f &Illuminant::getTransMat() { return transMatrix; }

void Illuminant::setTransMat(Eigen::Matrix4f &mat) { transMatrix = mat; }

CellScene::CellScene() {}

CellScene::CellScene(size_t width_, size_t height_)
{
    width = width_;
    height = height_;

    for (size_t i = 0; i < height_; i++)
    {
        cells.push_back(std::vector<bool>(width_));
        for (size_t j = 0; j < width_; j++) cells[i][j] = true;
    }

    modelsNum = 0;
    illumNum = 0;

    transMatrix << 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1;
}

void CellScene::addQuad(std::vector<Vertex> &vertices, std::vector<Facet> &facets, int x1,
int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3, int x4, int y4, int z4)
{
    Dot3D dot;
    std::vector<size_t> vec;

    size_t size = facets.size();

    dot = Dot3D(x1, y1, z1);
    vec = {size, size + 1};
    vertices.push_back(Vertex(dot, vec));

    dot = Dot3D(x2, y2, z2);
    vec = {size};
    vertices.push_back(Vertex(dot, vec));

    dot = Dot3D(x3, y3, z3);
    vec = {size, size + 1};
    vertices.push_back(Vertex(dot, vec));

    dot = Dot3D(x4, y4, z4);
    vec = {size + 1};
    vertices.push_back(Vertex(dot, vec));

    size = vertices.size();
    vec = {size - 4, size - 3, size - 2};
    facets.push_back(vec);
    vec = {size - 4, size - 2, size - 1};
    facets.push_back(vec);
}

size_t CellScene::getWidth() { return width; }

size_t CellScene::getHeight() { return height; }

CellScene::operator bool() const { return this->plateModel; }

void CellScene::moveUp(double value)
{
    Eigen::Matrix4f moveMat;
    moveMat << 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, -value, 0, 1;

    transMatrix *= moveMat;
    //    centerDot.move(0, -value, 0);

    //    Dot3D curDot;
    //    std::vector<Vertex> vertices = plateModel->getVertices();
    //    for (std::vector<Vertex>::iterator iter = vertices.begin(); iter !=
    //    vertices.end();
    //         iter++)
    //    {
    //        curDot = iter->getPosition();
    //        curDot.move(0, -value, 0);
    //        iter->setPosition(curDot);
    //    }
    //    plateModel->setVertices(vertices);

    //    for (size_t i = 0; i < modelsNum; i++)
    //    {
    //        vertices = models.at(i).getVertices();
    //        for (std::vector<Vertex>::iterator iter = vertices.begin(); iter !=
    //        vertices.end();
    //             iter++)
    //        {
    //            curDot = iter->getPosition();
    //            curDot.move(0, -value, 0);
    //            iter->setPosition(curDot);
    //        }

    //        models.at(i).setVertices(vertices);
    //    }
}

void CellScene::moveDown(double value)
{
    Eigen::Matrix4f moveMat;
    moveMat << 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, value, 0, 1;

    transMatrix *= moveMat;
    //    centerDot.move(0, value, 0);

    //    Dot3D curDot;
    //    std::vector<Vertex> vertices = plateModel->getVertices();
    //    for (std::vector<Vertex>::iterator iter = vertices.begin(); iter !=
    //    vertices.end();
    //         iter++)
    //    {
    //        curDot = iter->getPosition();
    //        curDot.move(0, value, 0);
    //        iter->setPosition(curDot);
    //    }
    //    plateModel->setVertices(vertices);

    //    for (size_t i = 0; i < modelsNum; i++)
    //    {
    //        vertices = models.at(i).getVertices();
    //        for (std::vector<Vertex>::iterator iter = vertices.begin(); iter !=
    //        vertices.end();
    //             iter++)
    //        {
    //            curDot = iter->getPosition();
    //            curDot.move(0, value, 0);
    //            iter->setPosition(curDot);
    //        }

    //        models.at(i).setVertices(vertices);
    //    }
}

void CellScene::moveLeft(double value)
{
    Eigen::Matrix4f moveMat;
    moveMat << 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -value, 0, 0, 1;

    transMatrix *= moveMat;
    //    centerDot.move(-value, 0, 0);

    //    Dot3D curDot;
    //    std::vector<Vertex> vertices = plateModel->getVertices();
    //    for (std::vector<Vertex>::iterator iter = vertices.begin(); iter !=
    //    vertices.end();
    //         iter++)
    //    {
    //        curDot = iter->getPosition();
    //        curDot.move(-value, 0, 0);
    //        iter->setPosition(curDot);
    //    }
    //    plateModel->setVertices(vertices);

    //    for (size_t i = 0; i < modelsNum; i++)
    //    {
    //        vertices = models.at(i).getVertices();
    //        for (std::vector<Vertex>::iterator iter = vertices.begin(); iter !=
    //        vertices.end();
    //             iter++)
    //        {
    //            curDot = iter->getPosition();
    //            curDot.move(-value, 0, 0);
    //            iter->setPosition(curDot);
    //        }

    //        models.at(i).setVertices(vertices);
    //    }
}

void CellScene::moveRight(double value)
{
    Eigen::Matrix4f moveMat;
    moveMat << 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, value, 0, 0, 1;

    transMatrix *= moveMat;
    //    centerDot.move(value, 0, 0);

    //    Dot3D curDot;
    //    std::vector<Vertex> vertices = plateModel->getVertices();
    //    //    qDebug() << "До";
    //    //    for (int i = 0; i < (int)vertices.size(); i++)
    //    //        qDebug() << vertices.at(i).getPosition();
    //    for (std::vector<Vertex>::iterator iter = vertices.begin(); iter !=
    //    vertices.end();
    //         iter++)
    //    {
    //        curDot = iter->getPosition();
    //        curDot.move(value, 0, 0);
    //        iter->setPosition(curDot);
    //    }
    //    //    qDebug() << "После";
    //    //    for (int i = 0; i < (int)vertices.size(); i++)
    //    //        qDebug() << vertices.at(i).getPosition();
    //    plateModel->setVertices(vertices);

    //    for (size_t i = 0; i < modelsNum; i++)
    //    {
    //        vertices = models.at(i).getVertices();
    //        for (std::vector<Vertex>::iterator iter = vertices.begin(); iter !=
    //        vertices.end();
    //             iter++)
    //        {
    //            curDot = iter->getPosition();
    //            curDot.move(value, 0, 0);
    //            iter->setPosition(curDot);
    //        }

    //        models.at(i).setVertices(vertices);
    //    }
}

void CellScene::scale(double value)
{
    Eigen::Matrix4f scaleMatrix;
    // clang-format off
    scaleMatrix << value,     0,     0, 0,
                    0,    value,     0, 0,
                    0,        0, value, 0,
                    0,        0,     0, 1;
    // clang-format on
    transMatrix *= scaleMatrix;
}

void CellScene::rotateX(double angle)
{
    Eigen::Matrix4f rotateMatrix;
    // clang-format off
    rotateMatrix << 1,           0,          0, 0,
                    0, cos(angle), -sin(angle), 0,
                    0, sin(angle),  cos(angle), 0,
                    0,           0,          0, 1;
    // clang-format on

    transMatrix *= rotateMatrix;
    //    Dot3D curDot;
    //    std::vector<Vertex> vertices = plateModel->getVertices();
    //    for (std::vector<Vertex>::iterator iter = vertices.begin(); iter !=
    //    vertices.end();
    //         iter++)
    //    {
    //        curDot = iter->getPosition();
    //        curDot.rotateX(angle, centerDot.getXCoordinate(),
    //        centerDot.getYCoordinate(), centerDot.getZCoordinate());
    //        iter->setPosition(curDot);
    //    }

    //    plateModel->setVertices(vertices);

    //    for (size_t i = 0; i < modelsNum; i++)
    //    {
    //        vertices = models.at(i).getVertices();
    //        for (std::vector<Vertex>::iterator iter = vertices.begin(); iter !=
    //        vertices.end();
    //             iter++)
    //        {
    //            curDot = iter->getPosition();
    //            curDot.rotateX(angle, centerDot.getXCoordinate(),
    //            centerDot.getYCoordinate(), centerDot.getZCoordinate());
    //            iter->setPosition(curDot);
    //        }

    //        models.at(i).setVertices(vertices);
    //    }
}

void CellScene::rotateY(double angle)
{
    Eigen::Matrix4f rotateMatrix;
    // clang-format off
    rotateMatrix << cos(angle),  0, sin(angle), 0,
                    0,           1,          0, 0,
                    -sin(angle), 0, cos(angle), 0,
                    0,           0,          0, 1;
    // clang-format on

    transMatrix *= rotateMatrix;
    //    Dot3D curDot;
    //    std::vector<Vertex> vertices = plateModel->getVertices();
    //    for (std::vector<Vertex>::iterator iter = vertices.begin(); iter !=
    //    vertices.end();
    //         iter++)
    //    {
    //        curDot = iter->getPosition();
    //        curDot.rotateY(angle, centerDot.getXCoordinate(),
    //        centerDot.getYCoordinate(), centerDot.getZCoordinate());
    //        iter->setPosition(curDot);
    //    }

    //    plateModel->setVertices(vertices);

    //    for (size_t i = 0; i < modelsNum; i++)
    //    {
    //        vertices = models.at(i).getVertices();
    //        for (std::vector<Vertex>::iterator iter = vertices.begin(); iter !=
    //        vertices.end();
    //             iter++)
    //        {
    //            curDot = iter->getPosition();
    //            curDot.rotateY(angle, centerDot.getXCoordinate(),
    //            centerDot.getYCoordinate(), centerDot.getZCoordinate());
    //            iter->setPosition(curDot);
    //        }

    //        models.at(i).setVertices(vertices);
    //    }
}

void CellScene::rotateZ(double angle)
{
    Eigen::Matrix4f rotateMatrix;
    // clang-format off
    rotateMatrix << cos(angle),  -sin(angle), 0, 0,
                    sin(angle),   cos(angle), 0, 0,
                    0,            0,          1, 0,
                    0,            0,          0, 1;
    // clang-format on

    transMatrix *= rotateMatrix;
}

size_t CellScene::getModelsNum() { return modelsNum; }

PolModel &CellScene::getModel(size_t num) { return models.at(num); }

void CellScene::addModel(PolModel &model)
{
    modelsNum++;
    models.push_back(model);
}

size_t CellScene::getIllumNum() { return illumNum; }

Illuminant &CellScene::getIlluminant(size_t num) { return illuminants.at(num); }

void CellScene::setIlluminant(Illuminant &illum, size_t i) { illuminants.at(i) = illum; }

void CellScene::addIlluminant(Illuminant &illum)
{
    illumNum++;
    illuminants.push_back(illum);
}

void CellScene::deleteIlluminant(size_t num)
{
    if (num < illuminants.size())
    {
        illumNum--;
        illuminants.erase(illuminants.begin() + num);
    }
}

void CellScene::deleteModel(size_t num)
{
    if (num < models.size())
    {
        modelsNum--;
        for (int i = 0; i < (int)models.at(num).getUsedCells().size(); i++)
            setCellStatus(models.at(num).getUsedCells()[i][0], models.at(num).getUsedCells()[i][0], true);
        models.erase(models.begin() + num);
    }
}

bool CellScene::isCellFree(size_t x, size_t y) { return cells.at(x).at(y); }

void CellScene::setCellStatus(size_t x, size_t y, bool newStatus)
{
    cells.at(x).at(y) = newStatus;
}

PolModel &CellScene::getPlateModel() { return *plateModel; }

const Dot3D CellScene::getStartOfPlate() { return startOfPlate; }

void CellScene::setStartOfPlate(Dot3D dot_) { startOfPlate = dot_; }

const Dot3D CellScene::getEndOfPlate() { return endOfPlate; }

void CellScene::buildPlateModel(Dot3D startOfPlate_, Dot3D endOfPlate_)
{
    if (plateModel)
        return;
    setStartOfPlate(startOfPlate_);
    setEndOfPlate(endOfPlate_);

    std::vector<Vertex> vertices;
    std::vector<Facet> facets;

    for (size_t y = startOfPlate_.getYCoordinate(); y < endOfPlate_.getYCoordinate();
         y += SCALE_FACTOR)
        for (size_t x = startOfPlate_.getXCoordinate(); x < endOfPlate_.getXCoordinate();
             x += SCALE_FACTOR)
            addQuad(vertices, facets, x, y, PLATE_Z, x + SCALE_FACTOR, y, PLATE_Z,
            x + SCALE_FACTOR, y + SCALE_FACTOR, PLATE_Z, x, y + SCALE_FACTOR, PLATE_Z);

    addQuad(vertices, facets, startOfPlate_.getXCoordinate(), startOfPlate_.getYCoordinate(), PLATE_Z - 10,
                              startOfPlate_.getXCoordinate(), endOfPlate_.getYCoordinate() + 10, PLATE_Z - 10,
                              endOfPlate_.getXCoordinate() + 10, endOfPlate_.getYCoordinate() + 10, PLATE_Z - 10,
                              endOfPlate_.getXCoordinate() + 10, startOfPlate_.getYCoordinate(), PLATE_Z - 10);

    addQuad(vertices, facets, startOfPlate_.getXCoordinate(), startOfPlate_.getYCoordinate(), PLATE_Z - 10,
                              startOfPlate_.getXCoordinate(), endOfPlate_.getYCoordinate() + 10, PLATE_Z - 10,
                              startOfPlate_.getXCoordinate(), endOfPlate_.getYCoordinate() + 10, PLATE_Z,
                              startOfPlate_.getXCoordinate(), startOfPlate_.getYCoordinate(), PLATE_Z);

    addQuad(vertices, facets, startOfPlate_.getXCoordinate(), endOfPlate_.getYCoordinate() + 10, PLATE_Z - 10,
                              endOfPlate_.getXCoordinate() + 10, endOfPlate_.getYCoordinate() + 10, PLATE_Z - 10,
                              endOfPlate_.getXCoordinate() + 10, endOfPlate_.getYCoordinate() + 10, PLATE_Z,
                              startOfPlate_.getXCoordinate(), endOfPlate_.getYCoordinate() + 10, PLATE_Z);

    addQuad(vertices, facets, endOfPlate_.getXCoordinate() + 10, endOfPlate_.getYCoordinate() + 10, PLATE_Z - 10,
                              endOfPlate_.getXCoordinate() + 10, startOfPlate_.getYCoordinate(), PLATE_Z - 10,
                              endOfPlate_.getXCoordinate() + 10, startOfPlate_.getYCoordinate(), PLATE_Z,
                              endOfPlate_.getXCoordinate() + 10, endOfPlate_.getYCoordinate() + 10, PLATE_Z);

    addQuad(vertices, facets, endOfPlate_.getXCoordinate() + 10, startOfPlate_.getYCoordinate(), PLATE_Z - 10,
                              startOfPlate_.getXCoordinate(), startOfPlate_.getYCoordinate(), PLATE_Z - 10,
                              startOfPlate_.getXCoordinate(), startOfPlate_.getYCoordinate(), PLATE_Z,
                              endOfPlate_.getXCoordinate() + 10, startOfPlate_.getYCoordinate(), PLATE_Z);
    if (plateModel)
        delete plateModel;
    plateModel = new PolModel(vertices, facets);
}

void CellScene::setEndOfPlate(Dot3D dot_) { endOfPlate = dot_; }

void CellScene::changeSize(size_t newWidth, size_t newheight)
{
    if (newWidth >= width)
        width = newWidth;
    //    else Вот тут потребуется анализ ситуации...
    //    qDebug("%zu is new width\n", width);

    if (newheight >= height)
        height = newheight;
    //    else Тоже самое

    //    qDebug("%zu is new height\n", height);
}

Eigen::Matrix4f &CellScene::getTransMatrix() { return transMatrix; }
