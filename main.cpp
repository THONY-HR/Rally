#include <SFML/Graphics.hpp>
#include <iostream>

class TextInput {
private:
    sf::Text label;
    sf::RectangleShape field;
    sf::Font font;
    sf::RenderWindow& window;
    bool isSelected;
    std::string text; // Text entered by user

public:
    TextInput(sf::RenderWindow& window, const std::string& labelText, float x, float y)
        : window(window), isSelected(false), text("") {
        if (!font.loadFromFile("D:/ITU DS PROM 3/S4/Programmation/C++/rallye/fonts/Sansation_Regular.ttf")) {
            std::cerr << "Failed to load font" << std::endl;
            return;
        }

        label.setFont(font);
        label.setString(labelText);
        label.setPosition(x, y);
        label.setCharacterSize(15); // Set font size to 15 pixels

        field.setSize(sf::Vector2f(200, 30));
        field.setPosition(x + 150, y);
        field.setFillColor(sf::Color::White);
        field.setOutlineThickness(1);
        field.setOutlineColor(sf::Color::Black);
    }

    void draw() {
        window.draw(field); // Draw field before label to ensure label is on top
        window.draw(label);

        sf::Text inputText(text, font, 15); // Create text object for input text
        inputText.setPosition(field.getPosition().x + 5, field.getPosition().y + 5); // Set position inside field
        inputText.setFillColor(sf::Color(64, 64, 64)); // Set text color to dark gray
        window.draw(inputText);
    }

    bool contains(sf::Vector2f point) const {
        return field.getGlobalBounds().contains(point);
    }

    void setSelected(bool selected) {
        isSelected = selected;
        if (isSelected) {
            field.setOutlineColor(sf::Color::Red); // Highlight the field when selected
        } else {
            field.setOutlineColor(sf::Color::Black);
        }
    }

    bool getSelected() const {
        return isSelected;
    }

    void addCharacter(char c) {
        text += c; // Add character to input text
    }

    void deleteLastCharacter() {
        if (!text.empty()) {
            text.pop_back(); // Delete last character from input text
        }
    }
};

class Button {
private:
    sf::Text label;
    sf::RectangleShape button;
    sf::Font font;
    sf::RenderWindow& window;

public:
    Button(sf::RenderWindow& window, const std::string& buttonText, float x, float y)
        : window(window) {
        if (!font.loadFromFile("D:/ITU DS PROM 3/S4/Programmation/C++/rallye/fonts/Sansation_Regular.ttf")) {
            std::cerr << "Failed to load font" << std::endl;
            return;
        }

        label.setFont(font);
        label.setString(buttonText);
        label.setCharacterSize(15); // Set font size to 15 pixels

        // Set position of text to the center of the button
        label.setPosition(x + 50 - label.getGlobalBounds().width / 2, y + 25 - label.getGlobalBounds().height / 2);

        button.setSize(sf::Vector2f(100, 50));
        button.setPosition(x, y);
        button.setFillColor(sf::Color(220, 20, 60)); // Set button color to crimson
        button.setOutlineThickness(1);
        button.setOutlineColor(sf::Color(220, 20, 60)); // Set outline color to blue
    }

    void draw() {
        window.draw(button);
        window.draw(label);
    }

    bool contains(sf::Vector2f point) const {
        return button.getGlobalBounds().contains(point);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 700), "SFML Window");
    window.clear(sf::Color::Black); // Set background color to black

    // Create text inputs and button
    TextInput textInput1(window, "Special", 100, 100);
    TextInput textInput2(window, "Concurrent", 100, 200);
    Button button(window, "Valider", 100, 300);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                if (textInput1.contains(mousePos)) {
                    textInput1.setSelected(true);
                    textInput2.setSelected(false);
                } else if (textInput2.contains(mousePos)) {
                    textInput1.setSelected(false);
                    textInput2.setSelected(true);
                } else if (button.contains(mousePos)) {
                    std::cout << "Valider clicked" << std::endl;

                    sf::RenderWindow newWindow(sf::VideoMode(1200, 700), "New Window");
                    while (newWindow.isOpen()) {
                        sf::Event newEvent;
                        while (newWindow.pollEvent(newEvent)) {
                            if (newEvent.type == sf::Event::Closed)
                                newWindow.close();
                        }
                        newWindow.clear(sf::Color::Black);
                        newWindow.display();
                    }

                } else {
                    textInput1.setSelected(false);
                    textInput2.setSelected(false);
                }
            } else if (event.type == sf::Event::TextEntered) {
                if (textInput1.getSelected()) {
                    if (event.text.unicode < 128) {
                        if (event.text.unicode == '\b') { // Backspace character
                            textInput1.deleteLastCharacter();
                        } else {
                            textInput1.addCharacter(static_cast<char>(event.text.unicode));
                        }
                    }
                } else if (textInput2.getSelected()) {
                    if (event.text.unicode < 128) {
                        if (event.text.unicode == '\b') { // Backspace character
                            textInput2.deleteLastCharacter();
                        } else {
                            textInput2.addCharacter(static_cast<char>(event.text.unicode));
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::Black); // Clear window with black background

        // Draw text inputs and button
        textInput1.draw();
        textInput2.draw();
        button.draw();

        window.display();
    }

    return 0;
}

// g++ main.cpp -o rallye.exe -I C:/SFML-2.5.1/include -L C:/SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system
// g++ -E OracleDatabase.cpp > bdConnect.h -I C:\ocilib-4.7.6-windows\include -L C:\ocilib-4.7.6-windows\lib64