# Asynchronous Glycemia Digital Twin 🩸⚙️

W pełni asynchroniczny, spersonalizowany system modelowania glikemii i optymalizacji dawek insuliny w pętli zamkniętej (Closed-Loop), oparty na architekturze Human-in-the-Loop.

## 🎯 Główne założenia projektu

Dzisiejsze komercyjne pompy insulinowe opierają się na sztywnych krzywych działania insuliny i izolowanych "wydarzeniach" (np. posiłek). Ten projekt odrzuca ten paradygmat na rzecz podejścia ciągłego:

1. **Brak sztywnych schematów (Moving Window Estimation):** System nie wycina z dnia posiłków. Analizuje ciągły strumień danych z sensora CGM w przesuwnym oknie czasu, co pozwala pacjentowi na naturalne, asynchroniczne funkcjonowanie.
2. **Superpozycja fal (Zasada ciągłości):** Dawki insuliny (oraz węglowodany) są traktowane jako dynamiczne fale (bazujące na funkcji Batemana), które nakładają się na siebie, tworząc jeden płynny wykres wypadkowy.
3. **Uczenie "Mikrokrokami" (k-NN / Case-Based Reasoning):** Zamiast jednej uśrednionej reguły, system uczy się na błędach (całka IAE) poprzez przeszukiwanie bazy historycznych scenariuszy. Dobiera **3 najbardziej zbliżone sytuacje z przeszłości** (pod względem czynników takich jak godzina, stres, makroskładniki) i na ich podstawie minimalnie koryguje wagi profilu.

## 🏗️ Architektura Monorepo

*   `core_math_engine/` - Ultralekki silnik matematyczny w C++ (liczenie superpozycji, k-NN).
*   `data_lake/` - Baza historycznych profili i scenariuszy w formacie JSON.
*   `nightly_ai_trainer/` - Skrypty Pythonowe do wyliczania całek błędu uchybu i optymalizacji wag w tle.
*   `interfaces/` - Puste szuflady na przyszłą aplikację mobilną oraz interfejs na smartwatch.

## 🚀 Status
Projekt jest w fazie początkowego projektowania architektury matematycznej i budowy topologii danych.
