// consoleView.cpp
#include "console.h"
#include <iostream>
#include <thread>
#include <chrono>

namespace s21 {

ConsoleView::ConsoleView(SnakeController* ctrl) : controller_(ctrl) {}

void ConsoleView::PrintMenu() {
    std::cout << "\n--- Snake Menu ---\n";
    std::cout << "1. Start Game\n";
    std::cout << "2. Step\n";
    std::cout << "3. Turn Left\n";
    std::cout << "4. Turn Right\n";
    std::cout << "5. Toggle Fast\n";
    std::cout << "6. Show Score\n";
    std::cout << "0. Quit\n";
    std::cout << "Choice: ";
}

int ConsoleView::AskChoice() {
    int choice;
    std::cin >> choice;
    return choice;
}

void ConsoleView::PrintField() {
    auto field = controller_->GetField();
    std::cout << "\n";
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            if (field[i][j] == 1) std::cout << "S";
            else if (field[i][j] == 2) std::cout << "@";
            else std::cout << ".";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void ConsoleView::StartLoop() {
    bool fast = false;
    while (true) {
        PrintMenu();
        switch (AskChoice()) {
            case START:
                controller_->Start();
                break;
            case STEP:
                controller_->Step();
                PrintField();
                break;
            case LEFT:
                controller_->TurnLeft();
                break;
            case RIGHT:
                controller_->TurnRight();
                break;
            case FAST:
                fast = !fast;
                controller_->SetFast(fast);
                std::cout << (fast ? "Fast ON\n" : "Fast OFF\n");
                break;
            case SCORE:
                std::cout << "Score: " << controller_->GetScore() << "\n";
                break;
            case QUIT:
                std::cout << "Bye!\n";
                return;
            default:
                std::cout << "Invalid choice.\n";
                break;
        }

        auto state = controller_->GetState();
        if (state == WIN) {
            std::cout << "YOU WIN!\n";
            return;
        }
        if (state == LOSE) {
            std::cout << "GAME OVER\n";
            return;
        }

        if (fast) std::this_thread::sleep_for(std::chrono::milliseconds(50));
        else std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

}  // namespace s21
