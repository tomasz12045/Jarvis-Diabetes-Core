# Wearable App (Human-in-the-Loop)

## Funkcja
Minimalistyczna aplikacja na smartwatch, która stanowi ostateczny, ludzki bezpiecznik w systemie (Human-in-the-Loop). Algorytm nie może podać niebezpiecznej dawki bez tej autoryzacji.

## Przebieg autoryzacji:
1. Hub mobilny zgłasza potrzebę zmiany bazy lub podania bolusa.
2. Zegarek zwraca uwagę użytkownika dyskretną wibracją (Haptics).
3. Na ekranie pojawia się interfejs typu **TAK / NIE** ("Zatwierdzasz zmianę?").
4. Decyzja logiczna wraca do telefonu. Zegarek nie przetrzymuje żadnych danych glikemicznych lokalnie.
