#include "objects.hpp"

CellScene::CellScene() {}

CellScene::CellScene(size_t width_, size_t length_)
{
    width = width_;
    length = length_;

    for (size_t i = 0; i < length_; i++)
    {
        cells.push_back(std::vector<bool>(width_));
        for (size_t j = 0; j < width_; j++)
            cells[i][j] = true;
    }

    modelsNum = 0;
    illumNum = 0;
}
