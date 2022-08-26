#ifndef MONTECARLOPI_FRAMEHANDLER_H
#define MONTECARLOPI_FRAMEHANDLER_H
#include <SFML/Graphics.hpp>
#include <boost/random/sobol.hpp>
#include <boost/random/uniform_01.hpp>
#include <utility>
#include <boost/random/variate_generator.hpp>
#include "InformationBox.h"

void checkEvents(sf::RenderWindow &window, sf::View &view);

template <typename Generator>
class FrameHandler{
public:
    sf::View view;
    sf::View view2;
    sf::CircleShape circle;
    sf::RectangleShape square;
    std::vector<sf::Vertex> point_vector;
    Generator gen;
    InformationBox info_box;


    FrameHandler( const sf::View &view, const sf::View &view2,
                 sf::CircleShape circle, sf::RectangleShape square,
                 const boost::variate_generator<boost::random::sobol &, boost::uniform_01<float>> &gen,
                 InformationBox infoBox) :  view(view), view2(view2), circle(std::move(circle)),
                                                  square(std::move(square)), gen(gen),
                                                  info_box(std::move(infoBox)) {}

    void drawFrame(sf::RenderWindow &window, float square_start, float square_start_y, int &num_points_in_total, int &num_points_in_circle) {
        auto side_size = square.getSize().x;
        auto circle_radius = circle.getRadius();
        checkEvents(window, view);
        window.setView(view);

        window.draw(circle);
        window.draw(square);

        point_vector.emplace_back(sf::Vector2f(gen.operator()()*side_size+square_start, gen.operator()()*side_size+square_start_y), sf::Color::White);
        for(auto & point : point_vector) {
            window.draw(&point, 1, sf::Points);
        }
        num_points_in_total++;

        float point_x = point_vector.back().position.x - square_start-circle_radius;
        float point_y = point_vector.back().position.y - square_start_y-circle_radius;
        if(point_x*point_x  + point_y*point_y <= circle_radius*circle_radius) num_points_in_circle++;

        window.setView(view2);
        std::string pi_estimate =  std::to_string(4 * float(num_points_in_circle) / float(num_points_in_total));
        info_box.drawTopText(window,  pi_estimate, num_points_in_total);

        window.display();
        window.clear();
    }
};



void checkEvents(sf::RenderWindow &window, sf::View &view) {
    sf::Event event{};
    while (window.pollEvent(event))
    {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed) {
            window.close();
            exit(0);
        }

        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {

            if (event.mouseWheelScroll.delta > 0) {
                view.zoom(0.9f);
            }
            else {
                view.zoom(1 / 0.9f);
            }
        }
        if(event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Left) {
                view.move(-view.getSize().x/10, 0);
            }
            if (event.key.code == sf::Keyboard::Right) {
                view.move(view.getSize().x/10, 0);
            }
            if (event.key.code == sf::Keyboard::Up) {
                view.move(0, -view.getSize().y/10);
            }
            if (event.key.code == sf::Keyboard::Down) {
                view.move(0, view.getSize().y/10);
            }
        }
    }
}
#endif //MONTECARLOPI_FRAMEHANDLER_H
