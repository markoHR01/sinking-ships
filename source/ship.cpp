#include "ship.h"

#include <vector>
#include <algorithm>

ShipPart::ShipPart(int x, int y)
          : x(x), y(y), hit(false) {}

Ship::Ship(const std::vector<ShipPart>& s)
      : ship(s) {}

bool Ship::hit(int x, int y) {
    for (ShipPart& sp : ship) {
        if (sp.x == x && sp.y == y) {
            sp.hit = true;
            return true;
        }
    }
    return false;
}

int Ship::health() const {
    int sum = 0;
    for (const ShipPart& sp : ship) {
        if (!sp.hit) {
            sum += 1;
        }
    }
    return sum;
}

bool shipIsValid(const std::vector<ShipPart>& ship) {
    if (ship.empty()) return false;

    std::vector<int> xs, ys;
    for (const auto& shipPart : ship) {
        xs.push_back(shipPart.x);
        ys.push_back(shipPart.y);
    }

    bool xInLine = std::all_of(xs.begin(), xs.end(),
                               [&](int x){ return x == xs[0]; });
    bool yInLine = std::all_of(ys.begin(), ys.end(),
                               [&](int y){ return y == ys[0]; });

    if (!(xInLine || yInLine)) return false;

    std::vector<int>& line = xInLine ? ys : xs;
    std::sort(line.begin(), line.end());

    for (size_t i = 1; i < line.size(); ++i) {
        if (line[i] != line[i - 1] + 1) {
            return false;
        }
    }

    return true;
}
