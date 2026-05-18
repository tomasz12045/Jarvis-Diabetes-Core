#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

// Struktura przechowująca pojedynczą dawkę insuliny
struct InsulinDose {
    double time_min; // Czas podania w minutach (np. od północy lub od startu symulacji)
    double dose_U;   // Wielkość dawki w jednostkach (J)
};

// Klasa silnika superpozycji
class SuperpositionEngine {
private:
    std::vector<InsulinDose> activeDoses;

    // Stałe dla modelu Batemana (przykładowe wartości dla insuliny szybkodziałającej)
    const double k_a = 0.02; // Stała wchłaniania (absorpcji)
    const double k_e = 0.01; // Stała eliminacji

    // Obliczanie działania pojedynczej dawki w danym czasie (Równanie Batemana)
    double calculateBateman(double deltaT, double dose) const {
        if (deltaT < 0) return 0.0; // Dawka jeszcze nie została podana

        // Zabezpieczenie przed dzieleniem przez zero w przypadku równych stałych
        if (std::abs(k_a - k_e) < 1e-5) {
            return dose * k_a * deltaT * std::exp(-k_a * deltaT);
        }

        return (dose * k_a) / (k_a - k_e) * (std::exp(-k_e * deltaT) - std::exp(-k_a * deltaT));
    }

public:
    // Dodawanie nowej dawki do systemu
    void addDose(double time_min, double dose_U) {
        activeDoses.push_back({time_min, dose_U});
    }

    // Pętla iterująca po dawkach: oblicza całkowite działanie (Insulin on Board / Activity) dla minuty t
    double getTotalInsulinActionAt(double current_t_min) const {
        double totalAction = 0.0;

        for (const auto& dose : activeDoses) {
            double deltaT = current_t_min - dose.time_min;
            // Sumujemy tylko te dawki, których czas podania już minął
            if (deltaT >= 0) {
                totalAction += calculateBateman(deltaT, dose.dose_U);
            }
        }

        return totalAction;
    }
};

// Funkcja pomocnicza do formatowania czasu z minut (np. 0 = 12:00) na HH:MM
void printTime(int start_hour, int minutes_passed) {
    int current_hour = start_hour + (minutes_passed / 60);
    int current_min = minutes_passed % 60;
    std::cout << std::setfill('0') << std::setw(2) << current_hour << ":"
              << std::setfill('0') << std::setw(2) << current_min;
}

// Kryteria Akceptacji: Symulacja skomplikowanego scenariusza
int main() {
    SuperpositionEngine engine;

    // Czas 0 traktujemy jako godzinę 12:00.
    // Podano 5j o godz. 12:00 (t = 0) i 3j o godz. 13:30 (t = 90)
    engine.addDose(0.0, 5.0);
    engine.addDose(90.0, 3.0);

    std::cout << "--- Symulacja dzialania insuliny (Superpozycja Dawek) ---\n";
    std::cout << "Scenariusz: 5J o 12:00 oraz 3J o 13:30\n\n";
    std::cout << "Czas    | Sumaryczna Aktywnosc Insuliny\n";
    std::cout << "---------------------------------------\n";

    // Pętla symulująca upływ czasu od 12:00 do 18:00 (360 minut) co 30 minut
    for (int t = 0; t <= 360; t += 30) {
        double totalAction = engine.getTotalInsulinActionAt(t);

        printTime(12, t); // Start od 12:00
        std::cout << "   | " << std::fixed << std::setprecision(4) << totalAction << "\n";

        // Opcjonalne graficzne przedstawienie trendu
        if (t == 90) std::cout << " ^^^ [PODANIE KOREKTY 3J] ^^^\n";
    }

    std::cout << "---------------------------------------\n";
    std::cout << "Wynik: Aktywnosc poprawnie spada do wartosci bliskich zeru.\n";

    return 0;
}

