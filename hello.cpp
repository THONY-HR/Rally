#include <SFML/Graphics.hpp>

int main()
{
    // Création de la fenêtre SFML
    sf::RenderWindow window(sf::VideoMode(200, 200), "Hello World");

    // Création d'un texte SFML
    // Chargement de la police par défaut
    sf::Font font;
    if (!font.loadFromFile("E:/DP3_S4/Mr Tahina/rallye/fonts/Sansation_Regular.ttf")) {
        return EXIT_FAILURE;
    }

    sf::Text text("Hello World", font, 30);
    text.setFillColor(sf::Color::White);
    
    // Centrer le texte dans la fenêtre
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));

    // Boucle principale du programme
    while (window.isOpen())
    {
        // Gestion des événements
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Effacer la fenêtre
        window.clear();

        // Dessiner le texte
        window.draw(text);

        // Afficher la fenêtre
        window.display();
    }

    return 0;
}
// g++ hello.cpp -o rallye.exe -I C:/SFML-2.5.1/include -L C:/SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system
