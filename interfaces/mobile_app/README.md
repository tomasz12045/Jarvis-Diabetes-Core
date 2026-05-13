# Mobile App (Hub Komunikacyjny)

## Opis
Aplikacja na smartfona, pełniąca rolę centralnego układu nerwowego (Hub). Nie wykonuje ona ciężkiej matematyki, lecz zarządza przepływem informacji.

## Główne zadania aplikacji:
1. **Łączność BLE:** Odbieranie danych z sensora CGM w czasie rzeczywistym.
2. **Most FFI (Foreign Function Interface):** Błyskawiczne wysyłanie odczytów do silnika C++ i odbieranie wyliczonych profili insuliny.
3. **Powiadomienia:** Przekazywanie żądań autoryzacji (bolusów) na Smartwatch.
4. **Łączność z Chmurą:** Wysyłanie pakietów danych do Cloud AI w celu optymalizacji wag lub rozpoznawania posiłków.
