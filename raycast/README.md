*This project has been created as part of the 42 curriculum by vlchinen, ikiriush.*

# cub3D — My first RayCaster with miniLibX

## Description

cub3D is a 3D maze viewer built from scratch in C, inspired by Wolfenstein 3D — the game widely considered the first true First-Person Shooter (1992). The project implements the **ray-casting** technique to render a first-person perspective view of a 2D map in real time.

The engine supports:
- Directional wall textures (North / South / East / West)
- Configurable floor and ceiling colors
- Smooth window management via miniLibX

**Bonus features implemented:**
- Wall collision detection
- Minimap overlay
- Doors that open and close
- Mouse-controlled point-of-view rotation

## Instructions

### Requirements

- Linux (X11)
- miniLibX (bundled in `minilibx-linux/`)

### Compilation

```bash
make        # build the project
make re     # rebuild from scratch
make clean  # remove object files
make fclean # remove objects and binary
```

### Running

```bash
./cub3D <map.cub>
```

The map file must use the `.cub` extension. Example:

```bash
./cub3D map.cub
```

### Map file format

```
NO ./wall_textures/N_wall.xpm
SO ./wall_textures/S_wall.xpm
WE ./wall_textures/W_wall.xpm
EA ./wall_textures/E_wall.xpm

F 220,100,0
C 225,30,0

111111
100N01
100001
111111
```

- `1` — wall
- `0` — empty space
- `N` / `S` / `E` / `W` — player start position and facing direction
- The map must be fully enclosed by walls
- Map must be the last element in the file

### Controls

| Key | Action |
|-----|--------|
| `W` `A` `S` `D` | Move |
| `←` `→` | Rotate view |
| Mouse | Rotate view (bonus) |
| Space | Open door (bonus) |
| `ESC` | Quit |
| Red cross | Quit |

## Resources

### Ray-casting references

- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) — the primary reference for the ray-casting algorithm
- [miniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx) — windowing and image API
- [Wolfenstein 3D original game](http://users.atw.hu/wolf3d/) — the historical inspiration for this project
