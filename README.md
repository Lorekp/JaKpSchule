# JaKpSchule — Labyrinth

A C++ school-project prototype for building and playing grid-based labyrinths. It combines a graphical maze editor, a ball controlled through queued directions, and a custom binary level format. SFML supplies rendering, window management, and input.

## Features

- Place and rotate diagonal slopes and straight barriers on a grid.
- Expand or shrink the grid and reposition its start and finish markers.
- Pan and zoom the editor, with placement previews and resize controls.
- Save a maze to `saves/level.labdat` and load it in play mode.
- Navigate an interactive maze menu to select the editor or the saved level.
- Queue directional turns, move between obstacles, and follow the player with the camera.

This is a prototype: level completion and navigation between modes are unfinished, and there is no campaign or level browser.

## Build and run

The most complete checked-in build configuration is **Win32** in `JaKpSchule.sln`. It requires Windows, Visual Studio 2022 C++ build tools (MSVC v143), and a Windows 10 SDK. Keep the bundled `SFML-2.6.0`, `thor-2.0`, and `TGUI-1.x-nightly` directories beside the solution; the project references their headers and static libraries by relative path.

From a Visual Studio Developer Command Prompt in the repository root:

```bat
msbuild JaKpSchule.sln /p:Configuration=Debug /p:Platform=Win32
.\Debug\JaKpSchule.exe
```

Run with the repository root as the working directory so `resources/`, `levels/`, and `saves/` can be found. Visual Studio can also open the solution and run the Win32 Debug target. If bundled library binaries are incompatible with the installed compiler, rebuild matching dependency libraries before linking.

The x64 configurations lack the dependency include and link settings present in Win32. The VS Code GCC task uses outdated flat source paths, so it is not a ready-to-use Linux build recipe. No project-level CMake build or automated test command is provided.

## Controls and workflow

The main menu is itself a maze. Use the arrow keys to queue turns; leaving on the left selects the editor, while leaving on the right opens the saved level.

| Editor control | Action |
| --- | --- |
| W / A / S / D | Pan the camera |
| Mouse wheel | Zoom |
| F | Select or toggle slope placement |
| G | Select or toggle straight-barrier placement |
| R or right click | Rotate the selected piece |
| Left click | Place a piece or operate a visible control |
| Plus / minus icons | Resize the grid |
| Start / finish arrows | Select boundary marker positions |
| Ctrl+S | Overwrite `saves/level.labdat` |
| Backspace | Leave the editor; the current application then exits |
| F11 | Toggle fullscreen |

Save before leaving the editor. Restart the application and take the menu's right exit to play the saved maze. Play mode uses arrow keys for queued directions, the mouse wheel for zoom, and F11 for fullscreen.

For a manual smoke check, open the editor, place and rotate a piece, resize the grid, save, restart, and load the saved level. This is a suggested check, not a recorded passing test.

## Source layout

| Path | Responsibility |
| --- | --- |
| `Main.cpp` | Create the window and dispatch menu, editor, and level modes |
| `src/gameModes/` | Menu, editor interactions, and gameplay loops |
| `src/Player.cpp` | Direction queue, obstacle scanning, turn rules, and movement |
| `src/grid/` | Grid cells, barriers, geometry, and rendering |
| `src/utils/AssetManager.cpp` | Cache textures and grids; read and write levels |
| `resources/` | Runtime images |
| `levels/mainGrid.labdat` | Interactive menu layout |
| `saves/level.labdat` | Saved playable layout |

The `.labdat` format stores native binary integers: grid dimensions, each cell's element count and element type/rotation or side, then start and finish coordinates and directions. It has no version header or portability guarantee. Loading assumes well-formed files; missing or damaged files are not handled robustly.

## Status and credits

The application contains bespoke editor and movement code, alongside substantial bundled third-party libraries. SFML, Thor, and TGUI are dependencies, not original implementations by this project. Preserve their included copyright and license notices. A project-wide license is not specified, and artwork provenance is not documented comprehensively.

Known limitations include a single hardcoded save slot, incomplete end-of-level handling, no return-to-menu loop, and no first-party automated tests. Treat it as a learning project rather than a finished game release.
