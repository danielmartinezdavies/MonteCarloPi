
#include "InformationBox.h"
#include "FrameHandler.h"
#include "RandomNumberGenerator.h"
#include "SobolGenerator.h"
#include "Parameters.h"
#include <boost/random/sobol.hpp>
#include <boost/random/uniform_01.hpp>
#include <boost/random/variate_generator.hpp>
#include <random>

int N = 50000;

void createShape(sf::Shape &s, float square_start, float square_start_y) {
    s.setPosition( square_start, square_start_y);
    s.setFillColor(sf::Color::Transparent);
    s.setOutlineThickness(1);
    s.setOutlineColor(sf::Color::White);
}


int main(int argc, char *argv[]) {
    std::vector<std::string> allArgs(argv, argv + argc);

    std::string csv = "";
    const Parameters param = parseInputParameters(allArgs);

    std::random_device non_det;
    std::mt19937 generator (123);
    std::uniform_real_distribution<float> dis(0.0, 1.0);
    //double randomRealBetweenZeroAndOne = ;

    InformationBox info_box("../resources/arial.ttf");

    sf::RenderWindow window(sf::VideoMode(800, 800), "MonteCarlo Pi");
    window.clear(sf::Color::Black);

    float circle_radius = (float)window.getSize().x / 2 * 3/4;
    float side_size = circle_radius * 2;

    float square_start = (float)window.getSize().x / 2 - circle_radius;
    float square_start_y = square_start - (float(window.getSize().y) * 0.065f);

    sf::RectangleShape square(sf::Vector2f(side_size, side_size));
    createShape( square, square_start, square_start_y);

    sf::CircleShape circle(circle_radius);
    createShape( circle, square_start, square_start_y);

    std::vector<sf::Vertex> point_vector;

    sf::View view(sf::FloatRect(0.f, 0.f, float(window.getSize().x), float(window.getSize().y)));
    view.setViewport(sf::FloatRect(0, 0.15, 1, 1));

    sf::View view2;
    FrameHandler f_m(view, view2, circle, square, info_box);

    int num_points_in_circle = 0;
    int num_points_in_total = 0;
    while (true) {
        f_m.drawFrame(window, square_start, square_start_y, num_points_in_total, num_points_in_circle, param.rng);
    }

}