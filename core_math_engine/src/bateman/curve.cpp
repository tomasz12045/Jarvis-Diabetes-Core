#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>                         // NOWOŚĆ: Potrzebne do otwierania plików z dysku
#include "../../include/nlohmann/json.hpp" // NOWOŚĆ: Ścieżka do pobranej biblioteki JSON

// Definicja struktury (zostaje bez zmian)
struct UserProfile {
    double insulinSensitivity;
    double absorptionRate;
    double eliminationRate;
};

// Funkcja matematyczna Batemana (zostaje bez zmian)
double batemanFunction(double t, const UserProfile& profile) {
    if (t <= 0) return 0.0;

    double ka = profile.absorptionRate;
    double kel = profile.eliminationRate;

    if (ka == kel) return 0.0;

    return (ka / (ka - kel)) * (std::exp(-kel * t) - std::exp(-ka * t));
}

// NOWOŚĆ: Funkcja wymagana w Tasku 1.4 do dynamicznego ładowania danych
UserProfile loadProfile(const std::string& path) {
    std::ifstream configFile(path);

    // Zabezpieczenie: jeśli plik nie istnieje lub ścieżka jest zła
    if (!configFile.is_open()) {
        std::cerr << "BLAD: Nie mozna otworzyc pliku JSON pod sciezka: " << path << std::endl;
        std::cerr << "Zwracam profil domyslny awaryjny." << std::endl;
        return {40.0, 0.02, 0.01};
    }

    nlohmann::json jsonData;
    configFile >> jsonData; // Wczytujemy strumień tekstu bezpośrednio do obiektu JSON
    configFile.close();

    UserProfile loadedProfile;
    // Mapujemy klucze z pliku tekstowego na naszą strukturę w C++
    loadedProfile.insulinSensitivity = jsonData["insulinSensitivity"];
    loadedProfile.absorptionRate = jsonData["absorptionRate"];
    loadedProfile.eliminationRate = jsonData["eliminationRate"];

    return loadedProfile;
}

int main() {
    // Ścieżka relatywna prowadząca z folderu budowania (cmake-build-debug) do data_lake
    std::string configPath = "../../data_lake/active_profile/current_weights.json";

    // Zamiast sztywnych wartości, ładujemy je dynamicznie z dysku
    UserProfile myProfile = loadProfile(configPath);

    std::cout << "Modelowanie krzywej Batemana (Zmienne zaladowane z pliku JSON)" << std::endl;
    std::cout << "Parametry -> Sensitivity: " << myProfile.insulinSensitivity
              << " | ka: " << myProfile.absorptionRate
              << " | kel: " << myProfile.eliminationRate << std::endl;
    std::cout << "---------------------------------------------------------" << std::endl;
    std::cout << "Czas (min) | Aktywnosc" << std::endl;
    std::cout << "-----------------------" << std::endl;

    // Symulacja przez 360 minut (6 godzin) w krokach co 5 minut
    for (int t = 0; t <= 360; t += 5) {
        double activity = batemanFunction(t, myProfile);

        std::cout << std::setw(6) << t << " min | " \
                  << std::fixed << std::setprecision(6) << activity << std::endl;
    }

    return 0;
}
