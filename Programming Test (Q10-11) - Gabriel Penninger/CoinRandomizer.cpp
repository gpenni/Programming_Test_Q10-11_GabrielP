#include "CoinRandomizer.h"

// Question 11: I decided to add a Score System whenever a coin is activated. 
// Each coin will receive a random value, which will add to your total Score. 
// Irregularity within Game Design is an important aspect of creating continuous interest and replayability in my opinion.
// It can make collecting items or reaching certain events more exciting and fun for the player.

// Initialize with a truly random seed for different results each time
CoinRandomizer::CoinRandomizer() : rng(std::random_device{}()), dist(0.0f, 1.0f) {}

CoinType CoinRandomizer::GetRandomCoinType() {
    float random = dist(rng);

    // 60% Bronze, 30% Silver, 10% Gold
    if (random < 0.6f) return CoinType::Bronze;
    if (random < 0.9f) return CoinType::Silver;
    return CoinType::Gold;
}

int CoinRandomizer::GetCoinValue(CoinType type) const {
    switch (type) {
    case CoinType::Bronze: return 100;
    case CoinType::Silver: return 500;
    case CoinType::Gold: return 1000;
    default: return 0;
    }
}