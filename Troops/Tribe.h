#include "Slav.h"
#include "Knight.h"
#include "Nomad.h"
#include "Viking.h"
#include "Being.h"

#include <vector>

class Tribe {
private:
    int slavQuantity = 0;
    int knightQuantity = 0;
    int nomadQuantity = 0;
    int vikingQuantity = 0;

    std::vector <Slav> slavVector;
    std::vector <Knight> knightVector;
    std::vector <Nomad> nomadVector;
    std::vector <Viking> vikingVector;
public:
    void addSlav(Slav);
    void addKnight(Knight);
    void addNomad(Nomad);
    void addViking(Viking);

    void show();
};
