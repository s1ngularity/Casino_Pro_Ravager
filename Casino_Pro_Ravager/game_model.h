//
//  game_model.h
//  Casino_Pro_Ravager
//
//  Created by Alex&Alex on __.010.10010 (d_ta c_rrupt_d)
//

#ifndef game_model_h
#define game_model_h

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

#define BaulaLovesAssembler !gameOver
#define EndOf2ndTerm break
const char player_ch = '=';
const char bank_ch = ' ';
const int term_str_size = 78;
const int maxRounds = 1000;
const int maxGames = 10000;

const double ravage_point = 1; // the point of no return for OUR teacher.

class GameModel
{
private:
    // Gambler:
    class Gambler
    {
    public:
        double Cash;
        
        Gambler(double Cash){
            //Gambler::Cash = Cash;
            // or:
            this->Cash = Cash;
        }
        
        Gambler() = default;
        
        bool Loss() {
            if (Cash/2 > ravage_point) {
                Cash /= 2;
                return true;
            }
            return false;
        }
        
        void Add(double Stakes) {
            Cash *= 3/2;
        }
        
        double Stakes() {
            return Cash/2;
        }
    };

    
    bool gameOver = false;
    const double player_percent;
    const double initial_cash;
    int round;
    Gambler Player, Bank;
    
    void BaulasChart() {
        static ofstream fout("baulas_log.txt");
        static double scale = term_str_size / initial_cash;
        if (round == 0) { // to prevent f_ckd_up output
            fout << "\n\nNew game+\n";
        }
        
        int player_ch_num = Player.Cash * scale;
        int bank_ch_num = term_str_size - player_ch_num;
        
        fout << '[';
        for (int i = 0; i < player_ch_num; i++) {
            fout << player_ch;
        }
        for (int i = 0; i < bank_ch_num; i++) {
            fout << bank_ch;
        }
        fout << "]\n";
        
    }
    
    struct Stat {
        int rounds;
        bool playerWon;
    };
    
    void Init() {
        Bank.Cash = Player.Cash = initial_cash / 2;
        round = 0;
        gameOver = false;
    }
    
public:
    
    GameModel (double cash, double percent) : player_percent(percent), initial_cash(cash * 2) {}
    
    void GameOn() {
        srand(time(NULL));
        double player_times_won = 0;
        long totalRounds = 0;
        for (int i = 1; i <= maxGames; i++) {
            Init();
            Stat stat = Start();
            if (stat.playerWon) player_times_won++;
            totalRounds += stat.rounds;
        }
        cout << "Probability of Player's win: " << player_percent << endl;
        cout << "player won in " << (player_times_won / maxGames) * 100 << " percent(s) of games\n";
        cout << "the game's average duration is " << totalRounds / maxGames << " rounds\n";
        cout << "player's credits at the end: " << Player.Cash << "$. \n";
    }
    
    Stat Start() {
        //BaulasChart();
        
        while (BaulaLovesAssembler && round++ < maxRounds) {
            double FullStake = Player.Stakes() * 2;
            int dice = rand() % 1000;
            if (dice <= player_percent * 1000) {
                Player.Add(FullStake);
                gameOver = !Bank.Loss();
            }
            else {
                Bank.Add(FullStake);
                gameOver = !Player.Loss();
            }
            
            //BaulasChart();
        }
        //cout << "Total rounds: " << round << endl;
        //cout << "Winner: " << ((Player.Cash < Bank.Cash) ? "Bank" : "Player") << endl;
        Stat gameStats = { round, ((Player.Cash < Bank.Cash) ? false : true) };
        return gameStats;
    }
    
    
    //
    
    
};



// 2 players of class Gambler
// 1st is a bank, literally
// 2nd is a student that wants to win
// Game_Model:
// Game_Model(

#endif /* game_model_h */
