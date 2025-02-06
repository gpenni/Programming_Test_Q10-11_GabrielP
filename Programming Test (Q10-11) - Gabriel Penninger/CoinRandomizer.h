#pragma once
#include <random>

enum class CoinType {
    Bronze,  // Worth 100 points
    Silver,  // Worth 500 points
    Gold     // Worth 1000 points
};

class CoinRandomizer {
public:
    CoinRandomizer();
    CoinType GetRandomCoinType();
    int GetCoinValue(CoinType type) const;

private:
    std::mt19937 rng;
    std::uniform_real_distribution<float> dist;
};