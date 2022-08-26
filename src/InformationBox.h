#ifndef MONTECARLOPI_INFORMATIONBOX_H
#define MONTECARLOPI_INFORMATIONBOX_H
#include <SFML/Graphics.hpp>

sf::Font loadFont(std::string filename);
sf::Text createText(sf::Font &font, int character_size, const sf::Color &color, float x, float y);

class InformationBox {
public:
    sf::Text pi_estimate_text;
    sf::Text number_points_text;
    sf::Font font;
public:
    explicit InformationBox(const std::string &filename) {
        font = loadFont(filename);
        pi_estimate_text = createText(font, 50, sf::Color::White, 1,  0);
        number_points_text = createText(font, 50, sf::Color::White, 1,  51);
    }

    void drawTopText(sf::RenderWindow &window,  std::string &pi_estimate, int num_points_total) {
        pi_estimate_text.setString(          "Pi estimate:            " + pi_estimate);
        window.draw(pi_estimate_text);
        std::string num_points = "Number of points:  " + std::to_string(num_points_total);
        number_points_text.setString(num_points);
        window.draw(number_points_text);
    }

};


sf::Font loadFont(std::string filename) {
    sf::Font font;
    if (!font.loadFromFile(filename))
    {
        exit(-1);
    }
    return font;
}
sf::Text createText(sf::Font &font, int character_size, const sf::Color &color, float x, float y) {
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(character_size); // in pixels, not points!
    text.setFillColor(color);
    text.setPosition(x,y);
    return text;
}
#endif //MONTECARLOPI_INFORMATIONBOX_H
