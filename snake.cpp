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
        srand(time(0));

        // Set up snake
        snake.push_back(sf::RectangleShape(sf::Vector2f(SIZE, SIZE)));
        snake[0].setFillColor(sf::Color::Green);
        snake[0].setPosition(WIDTH / 2, HEIGHT / 2);

        direction = STOP;
        food.setFillColor(sf::Color::Red);
        food.setSize(sf::Vector2f(SIZE, SIZE));

        spawnFood();
    }

    void run() {
        while (window.isOpen()) {
            handleEvents();
            update();     // Always update (even when snake is not moving)
            draw();       // Always draw (to display snake & food)
            sf::sleep(sf::milliseconds(100)); // Optional delay to slow down game loop
        }
    }
    
private:
    sf::RenderWindow window;
    std::vector<sf::RectangleShape> snake;
    sf::RectangleShape food;
    Direction direction;
    int score = 0;

    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
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
        // Move the body
        for (int i = snake.size() - 1; i > 0; --i) {
            snake[i].setPosition(snake[i - 1].getPosition());
        }

        // Move the head
        sf::Vector2f headPosition = snake[0].getPosition();
        switch (direction) {
            case LEFT:  headPosition.x -= SIZE; break;
            case RIGHT: headPosition.x += SIZE; break;
            case UP:    headPosition.y -= SIZE; break;
            case DOWN:  headPosition.y += SIZE; break;
            default: break;
        }
        snake[0].setPosition(headPosition);
    }

    void checkCollisions() {
        // Check for collision with walls
        if (snake[0].getPosition().x < 0 || snake[0].getPosition().x >= WIDTH || 
            snake[0].getPosition().y < 0 || snake[0].getPosition().y >= HEIGHT) {
            gameOver();
        }

        // Check for collision with itself
        for (int i = 1; i < snake.size(); i++) {
            if (snake[0].getPosition() == snake[i].getPosition()) {
                gameOver();
            }
        }
    }

    void checkFoodCollision() {
        // If snake eats food
        if (snake[0].getGlobalBounds().intersects(food.getGlobalBounds())) {
            score++;
            snake.push_back(sf::RectangleShape(sf::Vector2f(SIZE, SIZE)));
            snake.back().setFillColor(sf::Color::Green);
            spawnFood();
        }
    }

    void spawnFood() {
        // Random position for food
        int x = (rand() % (WIDTH / SIZE)) * SIZE;
        int y = (rand() % (HEIGHT / SIZE)) * SIZE;
        food.setPosition(x, y);
    }

    void draw() {
        window.clear();
        
        // Draw snake
        for (auto &segment : snake) {
            window.draw(segment);
        }

        // Draw food
        window.draw(food);

        // Display score
        displayScore();

        window.display();
    }

    void displayScore() {
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            std::cout << "Error loading font!" << std::endl;
        }

        sf::Text scoreText;
        scoreText.setFont(font);
        scoreText.setString("Score: " + std::to_string(score));
        scoreText.setCharacterSize(20);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(10, 10);

        window.draw(scoreText);
    }

    void gameOver() {
        // Display "Game Over"
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            std::cout << "Error loading font!" << std::endl;
        }

        sf::Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setString("Game Over!\nScore: " + std::to_string(score));
        gameOverText.setCharacterSize(30);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setPosition(WIDTH / 4, HEIGHT / 3);

        window.clear();
        window.draw(gameOverText);
        window.display();

        // Wait for a while and close
        sf::sleep(sf::seconds(2));
        window.close();
    }
};

int main() {
    SnakeGame game;
    game.run();
    return 0;
}
