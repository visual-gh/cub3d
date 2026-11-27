*This project has been created as part of the 42 curriculum by Visual, flvejux.*

# cub3D

## Description

cub3D is a small first-person 3D maze explorer, inspired by early raycasting games. It is written in C with the MiniLibX graphics library.

The program reads a scene description file (`.cub`) containing:
- four wall textures (one per orientation: north, south, west, east),
- the floor and ceiling colors,
- a map made of walls, empty spaces and the player's starting position.

It then renders the maze in real time using **raycasting**: one ray is cast per screen column with a DDA (Digital Differential Analysis) algorithm. The distance to the first wall hit gives the height of that column on screen.

### Features
- Textured walls, with a different texture depending on which way the wall faces (N / S / E / W)
- Floor and ceiling colors read from the `.cub` file
- Smooth, time-based movement (same speed on every machine), sliding along walls, normalized diagonal movement
- Distance fog, slightly darker east/west walls for readability, and a procedurally drawn paneled ceiling with lights
- Strict validation of the scene file: any misconfiguration prints `Error` followed by an explicit message, then the program exits cleanly with no leaks

## Instructions

### Requirements
- Linux (X11) or macOS
- `cc`, `make`
- On Linux: the X11 development headers (`libx11-dev`, `libxext-dev`)

The MiniLibX and libft sources are included in the repository and built automatically.

### Build
```bash
make        # builds libft, the MiniLibX and ./cub3D
make clean  # removes object files
make fclean # removes object files and the binary
make re     # full rebuild
```

### Run
```bash
./cub3D maps/backrooms.cub
```

### Controls
| Key | Action |
|---|---|
| `W` / `S` | Move forward / backward |
| `A` / `D` | Strafe left / right |
| `←` / `→` | Look left / right |
| `ESC` or the window's close button | Quit |

### Scene file format (`.cub`)
```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 185,180,109
C 161,150,76

        1111111111
        1000000001
111111111000N00001
100000000000000001
111111111111111111
```
- The 6 elements (`NO`, `SO`, `WE`, `EA`, `F`, `C`) can appear in any order, separated by empty lines and/or spaces. Each one must appear exactly once.
- Textures must be `.xpm` files. Colors are `R,G,B` with each value in `[0,255]`.
- The map always comes last. It may only contain `0` (empty), `1` (wall), spaces, and exactly one player start: `N`, `S`, `E` or `W` (the starting orientation).
- The map must be closed: every walkable cell must be surrounded by walls. Empty lines inside the map are not allowed.

### Tests
```bash
bash tests/make_maps.sh   # generates valid maps in maps/ok/ and invalid ones in maps/bad/
bash tests/test_bad.sh    # checks that every invalid map is rejected with "Error"
```

## Project structure

| Path | Content |
|---|---|
| `src/parsing/` | Reading and validating the `.cub` file (elements, colors, map, player) |
| `src/render/` | MiniLibX setup, raycasting (DDA), walls, ceiling, floor, fog, colors |
| `src/game/` | Key handling, main loop, movement, rotation, collisions |
| `src/utils/` | Error handling, cleanup, timer |
| `includes/cub3d.h` | Shared structures, constants and prototypes |

## Resources

- Lode Vandevenne, *Raycasting* tutorial: https://lodev.org/cgtutor/raycasting.html
- MiniLibX documentation (42 Docs): https://harm-smits.github.io/42docs/libs/minilibx
- Wikipedia, *Ray casting*: https://en.wikipedia.org/wiki/Ray_casting
- Wikipedia, *Digital differential analyzer (graphics algorithm)*: https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm)

### Use of AI

- **Parsing (flvejux)**: AI was used to adapt the parsing code from a previous 42 project (so_long) to the cub3D requirements, and to suggest ideas and approaches to think about (for example how to check that the map is closed, or which edge cases to handle in color parsing).
- **Rendering and game logic (Visual)**: AI was used as a tutor and reviewer: explaining the raycasting maths (DDA, camera plane, rotation, texture mapping), as well as to figure out how to best implement the fog and procedural ceiling texture in an efficient way.
