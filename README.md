# sfml-eu4-revolutionary_flag-template
Simple C++/SFML program, which generates revolutionary flags based on color IDs from Europa Universalis IV.
There shouldn't be problems with running on any Linux distribution, compatibility with other operating systems is not tested.

# Usability and necessity
This program can be used to see how different color codes will look together without running the game. It's also possible to add one's own color codes by editing the code.

# Compiling(LINUX ONLY):
0. Be sure, that you have installed SFML library.
1. Open terminal in directory of the project
2. Paste the following commands:
```
   g++ -c main.cpp
   g++ main.o -o main -lsfml-window -lsfml-graphics -lsfml-system
```
3. In order to run compiled program type this in terminal:
```
   chmod u+x main
```

# RUNNING:
Type:
./main (ID) (ID) (ID) (SAVE_INT)
 
ID means color code from 0 to 16, which is used by 3 stripes on the flag.
SAVE_INT is a value from 0 to 1. 0 means that generated flag will not be saved to a file, 1 means that it will be saved as (id) (id) (id).png

# LIST OF THE IDs:
```
  0   	Argent (White )
  1   	Sable (Black)
  2   	Purple
  3  	  Murrey (Mulberry) Burgundy
  4   	Sanguine (Blood Red)
  5   	Gules (Red)
  6   	Tenné (Tawny aka orange)
  7  	  Brown
  8  	  Or (Gold)
  9  	  Dark green
  10   	Vert (Light Green)
  11  	Teal
  12  	Turqouise
  13   	Azure ( Blue)
  14		Bleu-Celeste (Sky Blue)
  15		Reflex Blue variant (darker than current french)
  16		Red 032 variant (darker than current french)
```

Color codes are taken from the official EU4 wiki: https://eu4.paradoxwikis.com/Template:Revolutionary_flag
