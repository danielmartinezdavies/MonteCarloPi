#include <SFML/Graphics.hpp>
#include <boost/random/sobol.hpp>
#include <boost/random/uniform_01.hpp>
#include <boost/random/variate_generator.hpp>
#include <random>

int N = 50000;
int main() {
    boost::random::sobol s_rng(2);
    typedef boost::variate_generator<boost::random::sobol&, boost::uniform_01<float> > quasi_random_gen_t;

    // Initialize the engine to draw randomness out of thin air
    boost::random::sobol engine(2);
    // Glue the engine and the distribution together
    quasi_random_gen_t gen(engine, boost::uniform_01<float>());

    std::random_device non_det;
    std::mt19937 generator (123);
    std::uniform_real_distribution<float> dis(0.0, 1.0 * 800);
    //double randomRealBetweenZeroAndOne = ;


    sf::Font font;
    if (!font.loadFromFile("../resources/arial.ttf"))
    {
        exit(-1);
    }

    sf::Text text;
    text.setFont(font);

    text.setCharacterSize(24); // in pixels, not points!
    text.setFillColor(sf::Color::White);

    sf::Text text_number_points;
    text_number_points.setFont(font);

    text_number_points.setCharacterSize(24); // in pixels, not points!
    text_number_points.setFillColor(sf::Color::White);
    text_number_points.setPosition(0,24);

    sf::RenderWindow window(sf::VideoMode(800, 800), "MonteCarlo Pi");
    window.clear(sf::Color::Black);

    float radius = (float)window.getSize().x / 2 * 3/4;
    float side_size = radius * 2;

    sf::RectangleShape square(sf::Vector2f(side_size, side_size));
    float square_start = (float)window.getSize().x / 2 - radius;
    square.setPosition( square_start, square_start);
    square.setFillColor(sf::Color::Transparent);
    square.setOutlineThickness(1);
    square.setOutlineColor(sf::Color::White);


    sf::CircleShape circle(radius);
    circle.setOutlineColor(sf::Color::White);
    circle.setOutlineThickness(1);
    circle.setPosition( square_start, square_start);

    circle.setFillColor(sf::Color::Transparent);


    std::vector<sf::Vertex> point_vector;
    // run the program as long as the window is open
    int count_in_circle = 0;
    int i = 0;
    while (i < N)
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event{};
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                window.close();
                exit(0);
            }

        }


        point_vector.emplace_back(sf::Vector2f(gen.operator()()*side_size+square_start, gen.operator()()*side_size+square_start), sf::Color::White);
        for(auto & point : point_vector) {
            window.draw(&point, 1, sf::Points);
        }


        // end the current frame
        //sf::Time delayTime = sf::milliseconds(3);
        //sf::sleep(delayTime);
        i++;
        float point_x = point_vector.back().position.x - square_start-radius;
        float point_y = point_vector.back().position.y - square_start-radius;
        if(point_x*point_x  + point_y*point_y <= radius*radius) count_in_circle++;

        sf::RectangleShape clearing(sf::Vector2f((float)window.getSize().x, square_start-1 ));
        clearing.setFillColor(sf::Color::Black);
        window.draw(clearing);

        std::string pi_estimate =  std::to_string(4 * float(count_in_circle) / float(i));
        text.setString(          "Pi estimate:            " + pi_estimate);
        window.draw(text);
        std::string num_points = "Number of points:  " + std::to_string(i);
        text_number_points.setString(num_points);
        window.draw(text_number_points);

        window.draw(circle);
        window.draw(square);
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