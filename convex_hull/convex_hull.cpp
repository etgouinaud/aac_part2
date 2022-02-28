#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <math.h>
#include <SFML/Graphics.hpp>

#include "Point.hpp"

// Constants
const int INF = 1e6;
const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;
const int WINDOW_DELTA = 50;
const int POINT_RADIUS = 4;

/**
 * @brief Return x scaled with WINDOW_WIDTH and bounds
 * 
 * @param x      : value to scale up
 * @param bounds : bounds of window
 * @return int   : scaled value
 */
int get_scaled_x(int x, const std::array<int, 4>& bounds) {
    return WINDOW_WIDTH * ((x - bounds[0]) / (float)(abs(bounds[2]) + abs(bounds[0])));
}

/**
 * @brief Return y scaled with WINDOW_HEIGHT and bounds
 * 
 * @param y      : value to scale up
 * @param bounds : bounds of window
 * @return int   : scaled value
 */
int get_scaled_y(int y, const std::array<int, 4>& bounds) {
    return WINDOW_HEIGHT * (1 - ((y - bounds[1]) / (float)(abs(bounds[3]) + abs(bounds[1]))));
}

/**
 * @brief Draw a line on window using coordinates, bounds and color
 * 
 * @param window : graphic window
 * @param x0     : x-axis of first point
 * @param y0     : y-axis of first point
 * @param x1     : x-axis of second point
 * @param y1     : y-axis of second point
 * @param bounds : bounds of window
 * @param color  : color of the line
 */
void draw_line(sf::RenderWindow& window, int x0, int y0, int x1, int y1, const std::array<int, 4>& bounds, sf::Color color = sf::Color::Black) {
    sf::VertexArray line(sf::LinesStrip, 2);
    line[0].position = sf::Vector2f(get_scaled_x(x0, bounds) + POINT_RADIUS, get_scaled_y(y0, bounds) + POINT_RADIUS);
    line[0].color = color;
    line[1].position = sf::Vector2f(get_scaled_x(x1, bounds) + POINT_RADIUS, get_scaled_y(y1, bounds) + POINT_RADIUS);
    line[1].color = color;

    window.draw(line);
}

/**
 * @brief Draw a point on window using coordinates, bounds and color
 * 
 * @param window : graphic window
 * @param x      : x-axis
 * @param y      : y-axis
 * @param bounds : bounds of window
 * @param color  : color of the point
 */
void draw_point(sf::RenderWindow& window, int x, int y, const std::array<int, 4>& bounds, sf::Color color = sf::Color::Red) {
    auto circleShape = sf::CircleShape(POINT_RADIUS);
    int xd = get_scaled_x(x, bounds);
    int yd = get_scaled_y(y, bounds);

    circleShape.setFillColor(color);
    circleShape.setPosition(xd, yd);
    window.draw(circleShape);
}

/**
 * @brief Clear the window
 * 
 * @param window : graphic window
 */
void draw_plane(sf::RenderWindow& window) {
    window.clear(sf::Color::White);
}

/**
 * @brief Return minimal x between points of S
 * 
 * @param S    : vector of points
 * @return int : value of minimal x
 */
int getMinX(std::vector<Point> S){
    int min = 0;
    for(int i = 1; i < S.size(); i++){
        if(S.at(i).getX() < S.at(min).getX()){
            min = i;
        }
    }
    return min;
}

/**
 * @brief Return orientation of p2 compared to (p1, p3)
 * 
 * @param p1 : first point
 * @param p2 : second point
 * @param p3 : third point
 * @return int <0 if p2 is on the left of (p1, p3)
 *              0 if p1, p2 and p3 are collinear
 *             >0 if p2 is on the right of (p1, p3)
 */
int orientation(Point p1, Point p2, Point p3){
    int x1 = p1.getX() - p2.getX();
    int x2 = p1.getX() - p3.getX();
    int y1 = p1.getY() - p2.getY();
    int y2 = p1.getY() - p3.getY();
    return y2*x1 - y1*x2;
}

/**
 * @brief Realize one iteration of the gift wrapping algorithm
 * 
 * @param p      : current point of the convex hull
 * @param S      : all points
 * @return Point : next point of the convex hull
 */
Point giftWrapping(Point p, std::vector<Point> S){
    double min_angle = INF;
    double angle;
    Point p_next;

    if(S.at(0) != p){
        p_next = S.at(0);
    }
    else{
        p_next = S.at(1);
    }
    
    for(auto& w : S){
        // If candidate point is not current point
        if(w != p){
            // If candidate is oriented counterclockwise of (p, p_next) line
            if(orientation(p, w, p_next) < 0){
                // Candidate becomes p_next
                p_next = w;
            }
        }
    }
    return p_next;
}

/**
 * @brief Build convex hull of vector of points
 * 
 * @param S       : points
 * @param bounds  : window bounds
 * @return std::vector<Point>  : convex hull
 */
std::vector<Point> getConvexHull(std::vector<Point> S, std::array<int, 4> bounds){
    if(S.size() < 2){
        return S;
    }

    // Create graphic window
    sf::RenderWindow window(
        sf::VideoMode(WINDOW_WIDTH + WINDOW_DELTA, WINDOW_HEIGHT + WINDOW_DELTA),
        "Gift wrapping algorithm",
        sf::Style::Default
    );
    sf::Event event;

    std::vector<Point> L;
    int     min = INF;
    Point   p0 = S[getMinX(S)];
    Point   p_draw;
    Point   p = p0;
    // Write user indication
    std::cout << "Click on the graphic window to build convex hull" << std::endl;

    // Show window
    while (window.isOpen()) {
        // Clear window and draw axis
        draw_plane(window);
        draw_line(window, bounds[0], 0, bounds[2], 0, bounds);
        draw_line(window, 0, bounds[1], 0, bounds[3], bounds);

        // Draw points of S
        for (const auto& point : S) {
            auto color = sf::Color::Black;
            draw_point(window, point.getX(), point.getY(), bounds, color);
        }

        // Draw convex hull
        if(L.size() > 0){
            auto color = sf::Color::Red;
            p_draw = L.at(0);
            draw_line(window, p_draw.getX(), p_draw.getY(), L.at(L.size()-1).getX(), L.at(L.size()-1).getY(), bounds, color);
            for(int i = 1; i < L.size(); i++){
                draw_line(window, p_draw.getX(), p_draw.getY(), L.at(i).getX(), L.at(i).getY(), bounds, color);
                p_draw = L.at(i);
            }
        }
        
        while (window.pollEvent(event)){
            // If window is closed
            if (event.type == sf::Event::Closed){
                window.close();
            }
            // If a mouse button is released
            else if (event.type == sf::Event::MouseButtonReleased){
                // If the convex hull is built
                if(L.size() > 1 && p == p0){
                    std::cout << "End reached. Quit the graphic window to print convex hull" << std::endl;
                }
                else{
                    // Find next point
                    std::cout << p.getX() << "," << p.getY() << std::endl;
                    L.push_back(p);
                    p = giftWrapping(p, S);
                }
            }
        }
        window.display();
    }
    return L;
}



int main(){
    // Create points
    const int N = 1; // Number of points
    std::vector<Point> S;
    int tab[N*2] = {1,1};

   //int tab[N*2] = {-6,3, 3,1, 2,0, -3,-4, -3,3, -1,-2, 0,6, -1,3, 4,5, 4,4, 1,-2, 0,-2, -1,-6, 9,8, 7,-4, 2,2};
    for(int i = 0; i < N*2; i+=2){
        Point p(tab[i], tab[i+1]);
        S.push_back(p);
    }

    // Definition of screen bounds.
    // (!) points outside of the bounds wiil not appear on the window
    std::array<int, 4> bounds;
    bounds[0] = -10; // x min
    bounds[1] = -10; // y min
    bounds[2] = 10;  // x max
    bounds[3] = 10;  // y max

    // Build convex hull
    auto L = getConvexHull(S, bounds);

    // Print convex hull
    for(auto& point : L){
        std::cout << point.getX() << "," << point.getY() << " ";
    }
    std::cout << std::endl;
    return EXIT_SUCCESS;
}