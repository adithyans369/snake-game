#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

const int WIDTH = 800;
const int HEIGHT = 600;
const int SIZE = 20;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

class SnakeGame {
public:
    SnakeGame() {
        window.create(sf::VideoMode(WIDTH, HEIGHT), "SFML Snake Game");
        srand(static_cast<unsigned>(time(nullptr)));

        // Load DejaVu Sans (default on Ubuntu)
        if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
            std::cerr << "Failed to load DejaVuSans.ttf\n";
        }
    }

    void run() {
        showMenu();
        resetGame();

        while (window.isOpen()) {
            handleEvents();
            update();
            draw();
            sf::sleep(sf::milliseconds(100));
        }
    }

private:
    sf::RenderWindow window;
    std::vector<sf::RectangleShape> snake;
    sf::RectangleShape food;
    Direction direction = STOP;
    int score = 0;
    sf::Font font;

    void resetGame() {
        snake.clear();
        snake.push_back(sf::RectangleShape(sf::Vector2f(SIZE, SIZE)));
        snake[0].setFillColor(sf::Color::Green);
        snake[0].setPosition(WIDTH / 2, HEIGHT / 2);
        direction = RIGHT;
        score = 0;
        spawnFood();
    }

    void showMenu() {
        while (window.isOpen()) {
            window.clear();

            sf::Text title("Snake Game", font, 50);
            title.setFillColor(sf::Color::Green);
            title.setPosition(WIDTH / 2 - 150, HEIGHT / 4);

            sf::Text start("Press ENTER to Start", font, 30);
            start.setFillColor(sf::Color::White);
            start.setPosition(WIDTH / 2 - 160, HEIGHT / 2);

            sf::Text exit("Press ESC to Exit", font, 30);
            exit.setFillColor(sf::Color::White);
            exit.setPosition(WIDTH / 2 - 130, HEIGHT / 2 + 50);

            window.draw(title);
            window.draw(start);
            window.draw(exit);
            window.display();

            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Enter)
                        return;
                    else if (event.key.code == sf::Keyboard::Escape)
                        window.close();
                }
            }
        }
    }

    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left && direction != RIGHT) direction = LEFT;
                if (event.key.code == sf::Keyboard::Right && direction != LEFT) direction = RIGHT;
                if (event.key.code == sf::Keyboard::Up && direction != DOWN) direction = UP;
                if (event.key.code == sf::Keyboard::Down && direction != UP) direction = DOWN;
            }
        }
    }

    void update() {
        moveSnake();
        checkCollisions();
        checkFoodCollision();
    }

    void moveSnake() {
        for (int i = static_cast<int>(snake.size()) - 1; i > 0; --i) {
            snake[i].setPosition(snake[i - 1].getPosition());
        }

        sf::Vector2f headPos = snake[0].getPosition();
        switch (direction) {
            case LEFT:  headPos.x -= SIZE; break;
            case RIGHT: headPos.x += SIZE; break;
            case UP:    headPos.y -= SIZE; break;
            case DOWN:  headPos.y += SIZE; break;
            default: break;
        }
        snake[0].setPosition(headPos);
    }

    void checkCollisions() {
        sf::Vector2f headPos = snake[0].getPosition();
        if (headPos.x < 0 || headPos.x >= WIDTH || headPos.y < 0 || headPos.y >= HEIGHT) {
            gameOver();
        }
        for (size_t i = 1; i < snake.size(); ++i) {
            if (snake[0].getPosition() == snake[i].getPosition()) {
                gameOver();
            }
        }
    }

    void checkFoodCollision() {
        if (snake[0].getGlobalBounds().intersects(food.getGlobalBounds())) {
            score++;
            sf::RectangleShape newSeg(sf::Vector2f(SIZE, SIZE));
            newSeg.setFillColor(sf::Color::Green);
            newSeg.setPosition(-SIZE, -SIZE);
            snake.push_back(newSeg);
            spawnFood();
        }
    }

    void spawnFood() {
        int x = (rand() % (WIDTH / SIZE)) * SIZE;
        int y = (rand() % (HEIGHT / SIZE)) * SIZE;
        food.setSize(sf::Vector2f(SIZE, SIZE));
        food.setFillColor(sf::Color::Red);
        food.setPosition(x, y);
    }

    void draw() {
        window.clear();
        for (auto &seg : snake) window.draw(seg);
        window.draw(food);
        displayScore();
        window.display();
    }

    void displayScore() {
        sf::Text scoreText;
        scoreText.setFont(font);
        scoreText.setString("Score: " + std::to_string(score));
        scoreText.setCharacterSize(20);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(10, 10);
        window.draw(scoreText);
    }

    void gameOver() {
        window.clear();
        sf::Text over("Game Over!", font, 50);
        over.setFillColor(sf::Color::Red);
        over.setPosition(WIDTH / 2 - 150, HEIGHT / 3);

        sf::Text final("Final Score: " + std::to_string(score), font, 30);
        final.setFillColor(sf::Color::White);
        final.setPosition(WIDTH / 2 - 130, HEIGHT / 2);

        window.draw(over);
        window.draw(final);
        window.display();

        sf::sleep(sf::seconds(3));
        window.close();
    }
};

int main() {
    SnakeGame game;
    game.run();
    return 0;
}

cd your_project_folder

git init
git add .
git commit -m "Initial commit"
git remote add origin https://github.com/yourusername/tic-tac-toe-rl.git
git branch -M main
git push -u origin main
