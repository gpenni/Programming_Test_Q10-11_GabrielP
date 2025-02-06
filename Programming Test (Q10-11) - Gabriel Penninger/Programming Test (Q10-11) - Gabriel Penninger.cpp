// Programming Test (Q10-11) - Gabriel Penninger.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <queue>
#include "CoinRandomizer.h"

class Coin {
public:
    Coin(int id) : id(id), isActive(false), frameCount(0), type(CoinType::Bronze) {}

    // Activates a coin with a specific type and resets its lifetime counter
    void Activate(CoinType newType) {
        isActive = true;
        frameCount = 0;
        type = newType;
        std::cout << "Coin " << id << " (" << GetTypeString() << ") activated!" << std::endl;
    }

    // Deactivates a coin and resets its state
    void Deactivate() {
        isActive = false;
        std::cout << "Coin " << id << " (" << GetTypeString() << ") deactivated!" << std::endl;
    }

    // Updates the coin's lifespan and returns false if it should be deactivated
    bool Update(int frameIncrement) {
        if (isActive) {
            frameCount += frameIncrement;
            if (frameCount > 300) {
                return false;
            }
        }
        return true;
    }

    bool IsActive() const { return isActive; }
    CoinType GetType() const { return type; }

private:
    std::string GetTypeString() const {
        switch (type) {
        case CoinType::Bronze: return "Bronze";
        case CoinType::Silver: return "Silver";
        case CoinType::Gold: return "Gold";
        default: return "Unknown";
        }
    }

    int id;
    bool isActive;
    int frameCount;
    CoinType type;
};

class CoinObjectPool {
public:
    CoinObjectPool(int poolSize) : score(0), randomizer() {
        for (int i = 0; i < poolSize; ++i) {
            pool.push(new Coin(i));
        }
        std::cout << "Pool initialized with " << poolSize << " coins" << std::endl;
    }

    // Destructor to free allocated memory
    ~CoinObjectPool() {
        while (!pool.empty()) {
            delete pool.front();
            pool.pop();
        }
        for (Coin* coin : activeCoins) {
            delete coin;
        }
    }

    // Spawns a coin from the pool if available and assigns it a random type
    void SpawnCoin() {
        Coin* coin = GetCoin();
        if (coin) {
            // Get random coin type for unpredictable rewards
            CoinType type = randomizer.GetRandomCoinType();
            coin->Activate(type);
            score += randomizer.GetCoinValue(type);
            activeCoins.push_back(coin);

            // Print current score after spawning
            std::cout << "Score increased by " << randomizer.GetCoinValue(type)
                << " points. Total score: " << score << std::endl;
        }
    }

    // Updates active coins and deactivates expired ones
    void UpdateActiveCoins(int frameIncrement) {
        for (auto it = activeCoins.begin(); it != activeCoins.end(); ) {
            Coin* coin = *it;
            if (!coin->Update(frameIncrement)) {
                ReturnCoin(coin);
                it = activeCoins.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    size_t GetActiveCoinsCount() const { return activeCoins.size(); }
    size_t GetAvailableCoinsCount() const { return pool.size(); }
    int GetScore() const { return score; }

private:
    Coin* GetCoin() {
        if (pool.empty()) {
            std::cout << "No coins available in the pool!" << std::endl;
            return nullptr;
        }
        Coin* coin = pool.front();
        pool.pop();
        return coin;
    }

    void ReturnCoin(Coin* coin) {
        coin->Deactivate();
        pool.push(coin);
    }

    std::queue<Coin*> pool;
    std::vector<Coin*> activeCoins;
    CoinRandomizer randomizer;
    int score;
};

int main() {
    CoinObjectPool coinPool(10000);
    const int frameIncrement = 10;

    for (int frame = 0; frame < 350; frame += frameIncrement) {
        std::cout << "\nFrame: " << frame << std::endl;
        std::cout << "Active coins: " << coinPool.GetActiveCoinsCount()
            << " Available coins: " << coinPool.GetAvailableCoinsCount()
            << " Current Score: " << coinPool.GetScore() << std::endl;

        if (frame % 10 == 0) {
            coinPool.SpawnCoin();
        }

        coinPool.UpdateActiveCoins(frameIncrement);
    }

    std::cout << "\nPress Enter to exit...";
    std::cin.ignore();
    std::cin.get();

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
