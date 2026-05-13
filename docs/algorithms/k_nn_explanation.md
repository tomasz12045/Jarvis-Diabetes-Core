# Algorytm 3 Okienek (k-Nearest Neighbors) w asynchronicznej glikemii

## Koncepcja
Zamiast budować jeden sztywny profil z ustaloną wrażliwością na insulinę, system przechowuje w `data_lake` historię (zbiór minionych dni i reakcji organizmu). Kiedy pacjent podaje bolus lub spożywa posiłek, algorytm przeszukuje te dane, by znaleźć 3 najbardziej podobne sytuacje z przeszłości.

## Matematyka
Podobieństwo (odległość) między obecnym stanem a stanem z przeszłości obliczamy za pomocą ważonego dystansu euklidesowego:

$$d = \sqrt{w_1(C_{cur} - C_{hist})^2 + w_2(S_{cur} - S_{hist})^2 + w_3(H_{cur} - H_{hist})^2}$$

Gdzie:
* $C$ - Węglowodany (Carbs)
* $S$ - Stres (Stress level)
* $H$ - Godzina (Hour of day)
* $w$ - Wagi określające ważność danego czynnika.

## Aktualizacja (Mikrokrok)
Po znalezieniu 3 najbliższych sąsiadów, system uśrednia ich błąd IAE (Całkę Wartości Bezwzględnej Uchybu) i koryguje wagi w `active_profile` o ułamek procenta (np. 0.01%), co zapobiega gwałtownym skokom przy awarii sensora.
