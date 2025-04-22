#ifndef SHIP_H
#define SHIP_H

#include <vector>

struct ShipPart {
    const int x, y;
    bool hit;

    ShipPart(int x, int y)
            : x(x), y(y), hit(false) {}
};

class Ship {
    public:
        Ship(const std::vector<ShipPart>& s)
            : ship(s) {}

        bool hit(int x, int y) {
            for (ShipPart& sp : ship) {
                if (sp.x == x && sp.y == y) {
                    sp.hit = true;
                    return true;
                }
            }
            return false;
        }

        int health() const {
            int sum = 0;
            for (const ShipPart& sp : ship) {
                if (sp.hit == false) {
                    sum += 1;
                }
            }
            return sum;
        }

    private:
        std::vector<ShipPart> ship;
};

#endif
