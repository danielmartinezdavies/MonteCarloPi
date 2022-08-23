#include <SFML/Graphics.hpp>
#include <boost/random/sobol.hpp>
#include <boost/random/uniform_01.hpp>
#include <boost/random/variate_generator.hpp>
#include <random>

int N = 50000;

void checkEvents(sf::RenderWindow &window) {
    sf::Event event{};
    while (window.pollEvent(event))
    {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed) {
            window.close();
            exit(0);
        }
    }
}

void drawTopText(sf::RenderWindow &window, sf::Text &text, sf::Text &text_number_points, std::string &pi_estimate, int num_points_total) {
    text.setString(          "Pi estimate:            " + pi_estimate);
    window.draw(text);
    std::string num_points = "Number of points:  " + std::to_string(num_points_total);
    text_number_points.setString(num_points);
    window.draw(text_number_points);
}

sf::Font loadFont() {
    sf::Font font;
    if (!font.loadFromFile("../resources/arial.ttf"))
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

int main() {

    boost::random::sobol s_rng(2);
    typedef boost::variate_generator<boost::random::sobol&, boost::uniform_01<float> > quasi_random_gen_t;

    // Initialize the engine to draw randomness out of thin air
    boost::random::sobol engine(2);
    // Glue the engine and the distribution together
    quasi_random_gen_t gen(engine, boost::uniform_01<float>());

    std::random_device non_det;
    std::mt19937 generator (123);
    std::uniform_real_distribution<float> dis(0.0, 1.0);
    //double randomRealBetweenZeroAndOne = ;

    sf::Font font = loadFont();

    sf::Text pi_estimate_text = createText(font, 24, sf::Color::White, 1,  0);
    sf::Text number_points_text = createText(font, 24, sf::Color::White, 1,  24);

    sf::RenderWindow window(sf::VideoMode(800, 800), "MonteCarlo Pi");
    window.clear(sf::Color::Black);

    float circle_radius = (float)window.getSize().x / 2 * 3/4;
    float side_size = circle_radius * 2;

    sf::RectangleShape square(sf::Vector2f(side_size, side_size));
    float square_start = (float)window.getSize().x / 2 - circle_radius;
    square.setPosition( square_start, square_start);
    square.setFillColor(sf::Color::Transparent);
    square.setOutlineThickness(1);
    square.setOutlineColor(sf::Color::White);


    sf::CircleShape circle(circle_radius);
    circle.setPosition( square_start, square_start);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineThickness(1);
    circle.setOutlineColor(sf::Color::White);

    int num_points_in_circle = 0;
    int num_points_in_total = 0;
    std::vector<sf::Vertex> point_vector;
    while (num_points_in_total < N)
    {
        checkEvents(window);

        window.draw(circle);
        window.draw(square);

        point_vector.emplace_back(sf::Vector2f(gen.operator()()*side_size+square_start, gen.operator()()*side_size+square_start), sf::Color::White);

        for(auto & point : point_vector) {
            window.draw(&point, 1, sf::Points);
        }
        num_points_in_total++;

        float point_x = point_vector.back().position.x - square_start-circle_radius;
        float point_y = point_vector.back().position.y - square_start-circle_radius;
        if(point_x*point_x  + point_y*point_y <= circle_radius*circle_radius) num_points_in_circle++;

        std::string pi_estimate =  std::to_string(4 * float(num_points_in_circle) / float(num_points_in_total));
        drawTopText(window, pi_estimate_text, number_points_text, pi_estimate, num_points_in_total);

        window.display();
        window.clear();
    }

    std::string filename = "rng.jpeg";
    sf::Texture texture;
    texture.create(window.getSize().x, window.getSize().y);
    texture.update(window);
    if (texture.copyToImage().saveToFile(filename))
    {
        std::cout << "screenshot saved to " << filename << std::endl;
    }

}