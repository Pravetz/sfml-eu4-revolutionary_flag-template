![rev_flag](https://user-images.githubusercontent.com/46265909/127778066-1816eb66-0fa1-4546-824b-b500c39f8944.png)

# sfml-eu4-revolutionary_flag-template
Simple C++/SFML program, which generates revolutionary flags based on color IDs from Europa Universalis IV.

# Usability and necessity
This program can be used to see how different color codes will look together without running the game. It's also possible to add one's own color codes by editing the `colors.txt` file in `assets` directory.

# Quick guide to color creation
In `colors.txt`, each line describes separate color, the syntax is fairly simple:
```
R0, G128, B200, A255   # this is comment
```
Values for corresponding colors are prefixed with channel name - `R`, `G`, `B` or `A`
It is possible to set multiple channels with one value by combining their identifiers:
```
GA255, RB128   # will produce Color(128, 255, 128, 255)
RGBA255        # will produce Color(255, 255, 255, 255)
RGB0, A255     # will produce Color(0, 0, 0, 255)
```

# Compiling:
On Linux systems, one can type:
```
chmod +x compile.sh
./compile.sh
```
And get a `eu4rvf` executable, ready to use.

# RUNNING:
Type:
./eu4rvf (ID) (ID) (ID)
 
ID means color code from `colors.txt` file, colors are saved sequentially, so color at `line 5` in `colors.txt` will correspond to 0-based index `4`.
If the utility is unable to fetch color, it will return Color(0, 0, 0, 255) - Black.

# LIST OF THE IDs:
The exact color values can be seen in `assets/colors.txt`.
```
  0   Argent (White )
  1   Sable (Black)
  2   Purple
  3   Murrey (Mulberry) Burgundy
  4   Sanguine (Blood Red)
  5   Gules (Red)
  6   Tenné (Tawny aka orange)
  7	Brown
  8   Or (Gold)
  9   Dark green
  10   Vert (Light Green)
  11   Teal
  12   Turqouise
  13   Azure ( Blue)
  14   Bleu-Celeste (Sky Blue)
  15   Reflex Blue variant (darker than current french)
  16   Red 032 variant (darker than current french)
```

Color codes are taken from the official EU4 wiki: https://eu4.paradoxwikis.com/Template:Revolutionary_flag
