# ICP Projekt 2023 - Pacman

## Autoři
- xkralr06
- xjezek19

## Základní informace

### Projekt používá:
- Make
- Qt verze 5.5
- C++17
- Doxygen (pro dokumentaci)

### Vlastnosti
- Maximální počet duchů je 4.
- Pohyb pouze pomocí W-A-S-D tlačítek .
- Herní smyčka se provádí jednou za 750ms.
- Může být více cílových políček.
- Pacman má více životů, které se vykreslují pod mapou a při kolizi s duchem o jeden přichazí.
V případě, že Pacman už žadné životy nemá hra končí neúspěchem.
- Skore se zvyšuje pomocí bodík, které pacman sbírá anebo získání klíče (skore +100)
- Duchové jsou na hráče navádění pomocí algoritmu BFS.
- Hra má všechny módy přehrávání uvedené v zadání a dá se vybrat soubor logu hry,
v případě zmáčknutí tlačítka "Cancel/Zrušit" se vybere poslední log hry.
- Cíl má ikonu zvonečku, jídlo/body pro Pacmana bílou tečkou, tak jako v původní hře.
- Logování probíhá tím způsobem, že se uloží celá mapa a informace o Pacmanovi
  (např. skore, životy) do souboru.
- Velikost mapy je omezena na velikost 30x30.
- Mapy a logy jsou ve složce examples

### Kompilace a možnosti Makefilu
- `make` - Zkompiluje projekt
- `make clean` - Maže složku `obj` a `bin`
- `make run` - Zkompiluje projekt a spustí ho
- `make doxygen` - Vygeneruje dokumentaci
- `make pack` - Vytvoří .zip archiv se zdrojovým kódem