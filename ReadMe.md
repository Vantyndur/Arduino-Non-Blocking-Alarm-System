# **Bezpieczny System Reakcji na Zagrożenia** <br>
_Nieblokujący działania układu system reakcji na zagrożenie._ 

**Stan alarmu jest w pełni nieblokujący.** <br>
Sygnalizacja świetlna oraz dźwiękowa nie zatrzymują działania programu.
Rytmiczne (co 500ms) zmiany stanów uzyskane są dzięki, odmierzaniu czasu od ostatniej zmiany stanu, co pozwala na pracę potencjalnemu systemowi usunąć zagrożenie.

**Komunikacja szeregowa została zaprojektowana jako nieblokująca.** <br>
Mając na uwadze ograniczenia bufora transmisji danych, został wprowadzony bufor programowy, który 
przesyła dane tylko wtedy jeżeli w buforze jest na nie miejsce, a jeżeli dostępne miejsce 
jest mniejsze niż komunikat, który ma zostać przesłany, to bufor programowy przesyła komunikat 
częściami tak aby zewnętrzne urządzenia jak najszybciej dostały informacje o zaistniałym zagrożeniu.

Projekt został zrealizowany na symulatorze https://wokwi.com/

Przetestuj projekt wchodząc w ten link -> https://wokwi.com/projects/475161499027179521.

## **1. Komponenty na schemacie**

- Dioda LED koloru czerwonego (symulująca sygnalizację świetlną alarmu) + rezystor 1kOhm <br>
  Podłączona pod pin nr 7 oraz GND. <br>
  Alias -> alarmLedPin <br>
  
- Dioda LED koloru zielonego (oznaczająca poprawną pracę systemu) + rezystor 1kOhm <br>
  Podłączona pod pin nr 8 oraz GND. <br>
  Alias -> workLedPin
  
- Przycisk (symulujący czujnik otwarcia drzwi / awarię) <br>
  Podłączony pod pin nr 4 oraz GND. <br>
  Alias -> buttonPin
  
- Potencjometr (symulujący czujnik analogowy - np. czujnik temperatury / ciśnienia)
  Podłączony pod pin A0 oraz GND i 3.3V.
  Alias -> sensorPin
  
- Buzzer (symulujący sygnalizację dźwiękową alarmu)
  Podłączony pod pin nr 12 oraz GND. <br>
  Alias -> buzzerPin

## **2. Logika w kodzie**

- Odczytujemy wartość z potencjometru.
- Jeśli wartość odczytana z potencjometru przekroczy zadaną wartość, system reaguje przechodząc w stan alarmu o którym informuje sygnalizacją świetlną (LED) oraz dźwiękową (buzzer), przez port szeregowy wysyłany jest komunikat o awarii "ERR_CODE_1: HIGH TEMP!" wraz z wartością odczytaną z czujnika przykładowo "Temperature sensor value: 1023".

- Odczytujemy wartość przycisku
- Jeśli przycisk został naciśnięty, system reaguje przechodząc w stan alarmu o którym informuje sygnalizacją świetlną (LED) oraz dźwiękową (buzzer), przez port szeregowy wysyłany jest komunikat o awarii "ERR_CODE_2: EMERGENCY BUTON PUSHED!".

## **3. W skład repozytorium wchodzą:**

- sketch.ino - kod źródłowy programu
- diagram.json - Plik Schematu z Wokwi
- ReadMe.md
