# Raw Sensor Logs (Surowe Dane)

## Przeznaczenie
Ten folder służy jako zrzutowisko na surowe eksporty danych z urządzeń CGM (Continuous Glucose Monitor), takich jak Dexcom czy Nightscout.

## Przepływ danych (Data Pipeline)
1. Pacjent lub aplikacja ładuje tu surowe pliki `.csv` lub `.json`.
2. Skrypty w Pythonie (z folderu `nightly_ai_trainer/data_cleaner`) skanują te pliki.
3. System identyfikuje i odrzuca anomalia, takie jak błędy kompresji sensora, okluzje i szumy.
4. Oczyszczone, podzielone "okienka" wędrują do folderu `historical_scenarios` jako nowa wiedza dla algorytmu.
