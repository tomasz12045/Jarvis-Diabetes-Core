#include <iostream>
#include <cmath>
#include <iomanip>

// 1. Zaimplementowana struktura UserProfile
struct UserProfile {
    double insulinSensitivity; // Wrażliwość na insulinę
    double absorptionRate;     // Szybkość wchłaniania (k_a)
    double eliminationRate;    // Szybkość eliminacji (k_el)
};

// 2. Zaimplementowana funkcja batemanFunction
double batemanFunction(double t, const UserProfile& profile) {
    // Jeśli czas jest zerowy lub ujemny, insulina jeszcze nie działa
    if (t <= 0) return 0.0;
    
    double ka = profile.absorptionRate;
    double kel = profile.eliminationRate;
    
    // Zabezpieczenie przed dzieleniem przez zero (gdy k_a == k_el)
    if (ka == kel) return 0.0; 

    // Wzór na krzywą Batemana
    return (ka / (ka - kel)) * (std::exp(-kel * t) - std::exp(-ka * t));
}

// 3. Prosta pętla w main() co 5 minut
int main() {
    // Przykładowy profil pacjenta
    UserProfile myProfile = {40.0, 0.02, 0.01};
    
    std::cout << "Modelowanie krzywej Batemana (aktywnosc insuliny)" << std::endl;
    std::cout << "Czas (min) | Aktywnosc" << std::endl;
    std::cout << "-----------------------" << std::endl;

    // Symulacja przez 360 minut (6 godzin) w krokach co 5 minut
    for (int t = 0; t <= 360; t += 5) {
        double activity = batemanFunction(t, myProfile);
        
        // Formatowanie wyjścia dla lepszej czytelności w terminalu
        std::cout << std::setw(6) << t << " min | " 
                  << std::fixed << std::setprecision(6) << activity << std::endl;
    }

    return 0;
}
