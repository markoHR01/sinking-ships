#include "ship.h"

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
