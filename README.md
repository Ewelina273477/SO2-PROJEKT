# Projekt 1 Systemy Operacyjne 2 - Problem jedzących filozofów 

## Spis treści 
1. Wprowadzenie
2. Opis problemu  
3. Jak działa program?
4. Opis implementacji
5. Podsumowanie i wnioski
6. Instrukcja uruchamiania 
7. Bibliografia 



## 1.Wprowadzenie

Kod implementuje rozwiązanie klasycznego problemu ucztujących filozofów przy użyciu wielowątkowości w C++. Program symuluje filozofów, którzy na przemian myślą i jedzą, używając współdzielonych widelców. W rozwiązaniu wykorzystane zostały mechanizmy synchronizacji, aby uniknąć problemów zakleszczenia (deadlock) i zagłodzenia (starvation). Zastosowano mechanizmy synchronizacji takie jak muteksy (mutex) i kolejkę FIFO do zarządzania dostępem do zasobów.  

## 2. Opis problemu

Problem ucztujących filozofów to klasyczny problem synchronizacji w programowaniu równoległym. Opisuje pięciu filozofów siedzących przy okrągłym stole, gdzie pomiędzy nimi znajdują się widelce. Każdy filozof może albo myśleć, albo jeść, ale do jedzenia potrzebuje dwóch widelców (tego po lewej i prawej). 

Problemem jest taki przydział zasobów, aby:

* Filozofowie mogli myśleć lub jeść.

* Nie doszło do zakleszczenia (deadlock), w którym wszyscy filozofowie podniosą jeden widelec i czekają na drugi.

* Żaden filozof nie był głodzony (starvation) - czyli nie czekał nieskończenie długo na swoją kolej do jedzenia.

### Zastosowanie problemu w informatyce

* Zarządzanie zasobami – w systemach operacyjnych problem filozofów modeluje np. alokację procesów do drukarek czy baz danych.

* Synchronizacja wątków – używane w wielowątkowych aplikacjach, takich jak systemy operacyjne, serwery, bazy danych.

* Algorytmy planowania procesów – zapobieganie zakleszczeniom (deadlock) i zagłodzeniu (starvation).


## 3. Jak działa program?

1. Użytkownik podaje liczbę filozofów.

2. Tworzone są wątki symulujące filozofów.

3. Filozofowie losowo myślą i próbują jeść.

4. Dostęp do widelców jest kontrolowany przez kolejkę FIFO i mechanizm kelnera.

5. Program działa w nieskończoność, aż użytkownik naciśnie Enter.

6. Wszystkie wątki są bezpiecznie zamykane, a program kończy działanie.

## 4. Opis implementacji

Program został zaimplementowany w języku C++ przy użyciu biblioteki `<thread>` do obsługi wielowątkowości oraz `<mutex>` do synchronizacji dostępu do zasobów, `<queue>` – implementacja FIFO dla sprawiedliwego dostępu `requestQueue` znajdująca się poza klasą `DiningPhilosophers`.

### Klasa DiningPhilosophers

* `eatingCount` śledzi liczbę filozofów jedzących jednocześnie (maksymalnie n-1).

* `stopFlag` pozwala na zakończenie działania programu.

* Każdy filozof działa w osobnym wątku i przechodzi przez cykle myślenia i jedzenia.

### Metody klasy DiningPhilosophers

* `think(int id)`: Filozof symuluje myślenie, czekając 1 sekundę.

* `eat(int id)`: Filozof dodaje się do kolejki FIFO i czeka na zgodę kelnera. Gdy dostanie dostęp, podnosi dwa widelce i je przez 1 sekundę, a następnie odkłada widelce. 

* `stop()`: Ustawia flagę stopFlag na true, kończąc działanie filozofów.

### Funkcja main()

* Pobiera od użytkownika liczbę filozofów.

* Tworzy instancję `DiningPhilosophers` oraz uruchamia odpowiednią liczbę wątków.

* Wystąpienie filozofów (`philosopher(int id)`): Każdy filozof działa w osobnym wątku, w pętli wykonując myślenie i jedzenie, dopóki nie zostanie zatrzymany. 

* Program kończy działanie po naciśnięciu klawisza `Enter` przez użytkownika, a następnie zatrzymuje wszystkie wątki.

### Mechanizmy synchronizacji


* Muteksy (`mutex`) – używane do blokowania dostępu do widelców, aby jednocześnie tylko jeden filozof mógł je trzymać.

* Kolejka FIFO (`queue<int>`) – reguluje sprawiedliwy dostęp do jedzenia.

* Kelner (`waiterMutex`) – pozwala maksymalnie n-1 filozofom jeść jednocześnie, eliminując ryzyko zakleszczenia.


## 5. Podsumowanie i wnioski


* Program działa poprawnie i nie dochodzi do zakleszczeń – filozofowie cyklicznie myślą i jedzą. Dzięki kolejce FIFO żaden filozof nie jest głodzony, co oznacza, że każdy dostaje swoją kolej do jedzenia. Muteksy i kelner zapewniają, że nie dochodzi do sytuacji, w której wszyscy filozofowie próbują podnieść widelce jednocześnie, dbając o sprawiedliwy podział zasobów i efektywnie zapobiegają zakleszczeniu i zagłodzeniu filozofów.

* Dzięki zastosowaniu synchronizacji program działa wydajnie i skalowalnie, umożliwiając symulację dla dowolnej liczby filozofów.

* Implementacja wykorzystuje muteksy, co zapewnia bezpieczeństwo danych.

* Rozwiązanie można skalować do dowolnej liczby filozofów.

Dzięki temu projektowi można lepiej zrozumieć, jak działa programowanie współbieżne, jakie problemy mogą się w nim pojawić oraz jak skutecznie je rozwiązywać. 

## 6. Instrukcja uruchamiania

* Windows
  
  Visual Studio 2022: Projekt -> wybierz tryb w jakim chcesz odpalić program -> kliknij jednocześnie Fn+F5 -> wpisz liczbę filozofów -> enter -> aby zakończyć działanie programu -> enter
  zamknięcie okna -> emter lub krzyżyk w prawym górym rogu

* Linux
  
  skompiluj program: g++ -o Filozof_nowy Filozof_nowy.cpp
  instrukcja uruchomienia: ./Filozof_nowy 5

## 7. Bibliografia
* https://pl.wikipedia.org/wiki/Problem_ucztuj%C4%85cych_filozof%C3%B3w
* https://home.agh.edu.pl/~balis/dydakt/tw/lab8/tw-5fil.pdf
* https://ssamolej.kia.prz.edu.pl/dydaktyka/pwir/pwir_wyk3_Czyt_Pis_Fil_Bar.pdf
