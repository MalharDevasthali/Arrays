#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include "../../header/GameLoop/Gameplay/Cell.h"
#include "../../header/Event/EventPollingManager.h"
#include "../../header/Sound/SoundManager.h"

namespace Gameplay
{
    enum class BoardState
    {
        FIRST_CELL,
        PLAYING,
        COMPLETED,
    };

    class Board
    {
    private:
        // Board Constants
        static const int number_of_rows = 9;
        static const int number_of_columns = 9;
        static const int mines_count = 9;

        // State and View Members
        BoardState board_state;
        Cell* board[number_of_rows][number_of_columns];
        int flagged_cells;

        // Rendering
        const float board_width_offset = 115.f;
        const float board_height_offset = 329.f;
        const float board_width = 866.f;
        const float board_height = 1080.f;
        const float background_alpha = 85.f;

        sf::Texture background_texture;
        sf::Sprite background_sprite;
        sf::Texture board_texture;
        sf::Sprite board_sprite;

        // Randomization
        std::default_random_engine random_engine;
        std::random_device random_device;

        // Private helper methods
        void CreateBoard();
        void InitializeBackgroundImage();
        void InitializeBoardImage();
        void InitializeCells();
        void PopulateBoard(sf::Vector2i first_cell_position);
        void PopulateMines(sf::Vector2i first_cell_position);
        void PopulateCells();
        int CountMinesAround(sf::Vector2i cell_position);
        void FlagCell(sf::Vector2i cell_position);
        void OpenCell(sf::Vector2i cell_position);
        bool IsValidCellPosition(sf::Vector2i cell_position);
        void ProcessCellType(sf::Vector2i cell_position);
        void ProcessEmptyCell(sf::Vector2i cell_position);
        void ProcessMineCell(sf::Vector2i cell_position);
        void OpenEmptyCells(sf::Vector2i cell_position);
        void ResetBoard();
        void DeleteBoard();
        void OpenAllCells();
        void RevealAllMines();

    public:
        Board();
        ~Board();

        // Game flow methods
        void Initialize();
        void Update(Event::EventPollingManager& eventManager, sf::RenderWindow& window);
        void Render(sf::RenderWindow& window);
        void ProcessCellInput(Event::EventPollingManager& eventManager, sf::Vector2i cell_position);
        void Reset();

        // Getters
        BoardState GetBoardState() const;
        void SetBoardState(BoardState state);
        int GetMinesCount() const;
        float GetCellWidth() const;
        float GetCellHeight() const;

        float GetSampleCellLeftOffset() const;
        float GetSampleCellTopOffset() const;
        int GetNumberOfColumns() const;
        int GetNumberOfRows() const;


        bool AreAllCellsOpen();
        void FlagAllMines();
        void ShowBoard();
    };
}
