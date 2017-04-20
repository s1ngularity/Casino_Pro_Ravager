//
//  main.cpp
//  Casino_Pro_Ravager
//
//  Created by Alex&Alex on __.010.10010 (d_ta c_rrupt_d)
//

#include <iostream>
#include "game_model.h"

int main() {
    for (double percent = 0.51; percent < 0.61; percent += 0.01) {
        GameModel modelX(100, percent);
        modelX.GameOn();
        cout << endl;
    }
    
    
    return 0;
}
