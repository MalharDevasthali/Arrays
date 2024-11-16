#include "../../header/GameLoop/GameLoop.h"
#include <iostream>

GameLoop::GameLoop() {
    windowManager = new GameWindow::GameWindowManager();
    windowManager->initialize();
    eventManager = new Event::EventPollingManager(windowManager->getGameWindow());
    splashScreenManager = new SplashScreenManager(windowManager->getGameWindow());
    mainMenuManager = new MainMenuManager(windowManager->getGameWindow());
    gameplayManager = new GameplayManager();
    currentState = GameState::SPLASH_SCREEN;
    Sound::SoundManager::Initialize();
    Sound::SoundManager::PlayBackgroundMusic();
}

GameLoop::~GameLoop() {
    delete windowManager;
    delete eventManager;
    delete splashScreenManager;
    delete mainMenuManager;
    delete gameplayManager;
}

void GameLoop::handleState() {
    switch (currentState) {
    case GameState::SPLASH_SCREEN:
        splashScreenManager->show();
        currentState = GameState::MAIN_MENU;
        break;

    case GameState::MAIN_MENU:
        mainMenuManager->Update(*eventManager);
        mainMenuManager->Render();
        eventManager->update();

        if (mainMenuManager->IsPlayButtonPressed()) {
            mainMenuManager->ResetButtonStates();
            gameplayManager->Initialize();
            std::cout << "Switching to Gameplay state\n";
            currentState = GameState::GAMEPLAY;
        }
        else if (mainMenuManager->IsQuitButtonPressed()) {
            mainMenuManager->ResetButtonStates();
            currentState = GameState::EXIT;
        }
        break;

    case GameState::GAMEPLAY:
        gameplayManager->Update(*eventManager, *windowManager->getGameWindow());
        eventManager->update();
        gameplayManager->Render(*windowManager->getGameWindow());
        break;

    case GameState::EXIT:
        windowManager->getGameWindow()->close();
        break;
    }
}

void GameLoop::run() {
    while (windowManager->isGameWindowOpen()) {
        eventManager->processEvents();
        windowManager->getGameWindow()->clear();
        handleState();
        windowManager->getGameWindow()->display();
    }
}
