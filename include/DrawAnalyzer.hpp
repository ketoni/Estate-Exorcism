#ifndef EXO_DRAW_ANALYZER_HPP
#define EXO_DRAW_ANALYZER_HPP

#include <SFML/Graphics.hpp>

class DrawAnalyzer {

    public:
        DrawAnalyzer();

        enum Shape {
            Unknown,
            Circle,
            DiagonalTopLeft,
            DiagonalTopRight,
            Diamond,
            Square,
            VeeDown,
            VeeUp,
            Vertical,
            Horizontal,
            None,
        };

        bool isCapturing();
        void capturePoint(const sf::Vector2f& point);
        const sf::VertexArray& getCapture();
        void startCapture();
        Shape finishCapture();

    private:

        sf::VertexArray _capture_points;
        bool _capturing;

        std::vector<std::pair<Shape, std::string>> _shape_paths;
        sf::ConvexShape _drawable;

        const std::vector<sf::Vector2u>& filterCapture();
        void scaleCapture(float size);
        int neighborPixelWeight(int x, int y, sf::Image& neig);
};

#endif // EXO_DRAW_ANALYZER_HPP
