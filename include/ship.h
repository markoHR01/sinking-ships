#ifndef SHIP_H
#define SHIP_H

#include <vector>

struct ShipPart {
    const int x, y;
    bool hit;

    ShipPart(int x, int y);
};

class Ship {
    public:
        Ship(const std::vector<ShipPart>& s);

        bool hit(int x, int y);
        int health() const;

        const std::vector<ShipPart>& shipParts() const;

    private:
        std::vector<ShipPart> ship;
};

bool shipIsValid(const std::vector<ShipPart>& ship);

#endif
