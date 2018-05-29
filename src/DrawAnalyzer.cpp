
#include "DrawAnalyzer.hpp"
#include "Application.hpp"
#include <cmath>

DrawAnalyzer::DrawAnalyzer() :
_capture_points(sf::LinesStrip), _capturing(false)
{
    _shape_paths = {
        { Shape::Circle, "shapes/circle.png" },
        { Shape::DiagonalTopLeft, "shapes/diagonal1.png" },
        { Shape::DiagonalTopRight, "shapes/diagonal2.png" },
        { Shape::Horizontal, "shapes/horizontal.png" },
        { Shape::VeeDown, "shapes/vee1.png" },
        { Shape::VeeUp, "shapes/vee2.png" },
        { Shape::Vertical, "shapes/vertical.png" },

    };

    _drawable.setOutlineColor(sf::Color::White);
    _drawable.setOutlineThickness(10);
}

bool DrawAnalyzer::isCapturing() {
    return _capturing;
}

void DrawAnalyzer::capturePoint(const sf::Vector2f& point) {
    _capture_points.append(point);
}

const sf::VertexArray& DrawAnalyzer::getCapture() {
    return _capture_points;
}

void DrawAnalyzer::startCapture() {
    _capture_points.clear();
    _capturing = true;
}

auto DrawAnalyzer::finishCapture() -> Shape {
    _capturing = false;

    if (!_capture_points.getVertexCount()) {
        return Shape::Unknown;
    }

    scaleCapture(64);
    auto& filtered = filterCapture();

    sf::Image model_img;
    Shape result;
    int weight, best = 1000;
    for (auto& p : _shape_paths) {
        model_img = Application::resources.getImage(p.second); // it's a copy..
        weight = 0;
        for (auto& point : filtered) {
            weight += neighborPixelWeight(point.x, point.y, model_img);
        }
        weight /= filtered.size();
        if (weight < best) {
            result = p.first;
            best = weight;
        }
    }
    return result;
}

const std::vector<sf::Vector2u>& DrawAnalyzer::filterCapture() {

    static std::vector<sf::Vector2u> filtered;
    filtered.clear();

    sf::Vector2f pos = _capture_points[0].position;
    filtered.emplace_back(pos.x, pos.y);

    for (size_t i = 1; i < _capture_points.getVertexCount(); ++i) {
        pos = _capture_points[i].position;
        // drop the point if its too close to its predecessor
        if (3.f < std::sqrt(std::pow(pos.x - filtered.back().x, 2) +
                            std::pow(pos.y - filtered.back().y, 2))) {
            filtered.emplace_back((unsigned) pos.x, (unsigned) pos.y);
        }
    }
    return filtered;
}

void DrawAnalyzer::scaleCapture(float size) {
    auto rect = _capture_points.getBounds();
    float side = rect.width > rect.height ? rect.width : rect.height;
    float box_left = (rect.left + rect.width/2) - side/2;
    float box_top = (rect.top + rect.height/2) - side/2;
    float factor = size / side;
    size -= 1; // just for not to index too high after scaling

    for (size_t i = 0; i < _capture_points.getVertexCount(); ++i) {
        auto& v = _capture_points[i].position;
        v.x = factor * (v.x - box_left);
        if (v.x < 0.f) v.x = 0.f;
        if (v.x > size) v.x = size;
        v.y = factor * (v.y - box_top);
        if (v.y < 0.f) v.y = 0.f;
        if (v.y > size) v.y = size;
    }

}

int DrawAnalyzer::neighborPixelWeight(int x, int y, sf::Image& neig) {
    int span = 5;         // should be odd
    int max_weight = 128; // should be larger than image's biggest dimension
    int up = y - span,
        down = y + span,
        left = x - span,
        right = x + span;

    int w = neig.getSize().x, h = neig.getSize().y;
    if (up < 0) up = 0;
    if (down > h-1) down = h-1;
    if (left < 0) left = 0;
    if (right > w-1) right = w-1;

    float dist, best_dist = max_weight;
    int nx = max_weight, ny = max_weight;

    for (int j = left; j <= right; ++j) {
        for (int k = up; k <= down; ++k) {
            if (j == x && k == y) {
                continue;
            }
            if (neig.getPixel(j,k).r == 255) {
                dist = std::sqrt((x-j)*(x-j) + (y-k)*(y-k));
                if (dist < best_dist) {
                    best_dist = dist;
                    nx = j;
                    ny = k;
                }
            }
        }
    }
    // take a copy of the image to do the below, maybe?
    // neig.setPixel(nx, ny, sf::Color::Black);
    // -> ignores once hit pixels -> better results...
    return nx + ny;
}

