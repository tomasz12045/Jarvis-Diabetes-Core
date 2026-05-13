# Architektura Matematyczna i Logika Algorytmu

## 1. Algorytm Doboru Historii (k-Nearest Neighbors)
Aby uniknąć "przeuczenia" systemu na jednym błędnym odczycie (np. wadliwy sensor lub choroba), system nie aktualizuje profilu globalnie. Zamiast tego, dla każdej nowej iteracji szuka historycznych punktów odniesienia.

**Zasada działania:**
1. Algorytm pobiera wektor obecnego stanu: `[godzina, ilość_węglowodanów, poziom_stresu]`.
2. Przeszukuje `data_lake` i oblicza dystans euklidesowy między obecnym stanem a całą historią.
3. Wybiera **3 scenariusze o najmniejszym dystansie** (najbardziej podobne).
4. Oblicza średni błąd przewidywania z tych 3 scenariuszy i na tej podstawie generuje "mikrokrok" korygujący parametry (np. szybkość wchłaniania $k_a$).

## 2. Całka Uchybu (IAE)
Błąd nie jest liczony punktowo, lecz obszarowo.
`IAE = ∫ | G_real(t) - G_predict(t) | dt`
Dzięki temu system optymalizuje całkowite pole powierzchni pod wykresem błędu.
