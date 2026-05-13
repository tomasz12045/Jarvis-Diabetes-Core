#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

// Struktura reprezentująca pliki JSON z folderu data_lake
struct Scenario {
    double carbs;
    double stressLevel;
    double hour;
    double errorIAE;

    // Funkcja obliczająca matematyczne podobieństwo
    double calculateDistance(double curCarbs, double curStress, double curHour) const {
        return std::sqrt(
            std::pow(carbs - curCarbs, 2) + 
            std::pow(stressLevel - curStress, 2) +
            std::pow(hour - curHour, 2)
        );
    }
};

// Funkcja realizująca Twój pomysł szukania 3 najbardziej podobnych okienek
void findBestMatches(const std::vector<Scenario>& history, double curCarbs, double curStress, double curHour) {
    std::vector<std::pair<double, Scenario>> distances;

    for (const auto& s : history) {
        distances.push_back({s.calculateDistance(curCarbs, curStress, curHour), s});
    }

    // Sortowanie wyników od najbardziej podobnego
    std::sort(distances.begin(), distances.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
    });

    std::cout << "--- Algorytm k-NN (3 Okienka) ---" << std::endl;
    for (int i = 0; i < std::min(3, (int)distances.size()); ++i) {
        std::cout << "Dystans: " << distances[i].first 
                  << " | Blad IAE w tamtym dniu: " << distances[i].second.errorIAE << std::endl;
    }
}

int main() {
    // Przykładowe dane wczytane do pamięci RAM
    std::vector<Scenario> history = {
        {60, 2.0, 14.0, -15.2}, 
        {55, 3.0, 13.5, -10.5}, 
        {100, 8.0, 19.0, 45.0}  
    };

    findBestMatches(history, 58.0, 2.5, 14.2);

    return 0;
}
