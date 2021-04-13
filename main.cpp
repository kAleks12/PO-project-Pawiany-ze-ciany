//
//  Created by 
// Kacper Aleks
//     and
// Michał Malewicz
//

#include <iostream>
#include "Being.h"
#include <windows.h>

int main() {
    
    Being beka("Thomas",10,10);
    Being baka("Sheep",5,5);
    beka.Show();
    baka.Show();
    baka.ChangeHp(-6);
    baka.Show();
    baka.ChangeHp(10);
    baka.Show();

    system("Pause");
}
