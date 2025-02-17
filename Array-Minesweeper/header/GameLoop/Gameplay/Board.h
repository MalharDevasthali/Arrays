#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include "../../header/GameLoop/Gameplay/Cell.h"
#include "../../header/Event/EventPollingManager.h"

namespace Gameplay
{
    class Board
    {
    private:


        static const int numberOfRows = 9;
        static const int numberOfColumns = 9;
        const float boardWidth = 866.f;
        const float boardHeight = 1080.f;
        const float boardPosition = 530.f;
        const float horizontalCellPadding = 115.f;
        const float verticalCellPadding = 329.f;

        const std::string boardTexturePath = "assets/textures/board.png";
        sf::Texture boardTexture;
        sf::Sprite boardSprite;
        Cell* cell;

        void initializeBoardImage();
        void initialize();
        void createBoard();
        float getCellWidthInBoard() const;
        float getCellHeightInBoard() const;

    public:

        Board();

        void render(sf::RenderWindow& window);
    };
}