#include "Slav.h"
#include "Knight.h"
#include "Nomad.h"
#include "Viking.h"
#include "Being.h"

#include <vector>

class Tribe {
private:
    std::vector <Slav> slavVector;
    std::vector <Knight> knightVector;
    std::vector <Nomad> nomadVector;
    std::vector <Viking> vikingVector;
public:
    void addSlav(const Slav &);
    void addKnight(const Knight &);
    void addNomad(const Nomad &);
    void addViking(const Viking &);

    void show();
};
