# vix-game

A small 2D game built with Vix.cpp and the `vix/game` runtime.

## Overview

`vix-game` is a simple game project used to demonstrate how to build a real interactive application with Vix.cpp.

It uses:

- `vix.app`
- `vix/game`
- `GameRuntime`
- `Scene`
- SDL window backend
- OpenGL renderer backend
- asset loading
- sprite rendering
- keyboard movement
- collision
- score update

## Controls

```text
W / Arrow Up       Move up
S / Arrow Down     Move down
A / Arrow Left     Move left
D / Arrow Right    Move right
Escape             Quit
```

## Project structure

```text
vix-game/
  assets/
    player.jpg
    coin.jpeg

  src/
    main.cpp
    GameConfig.hpp
    GameApp.hpp
    GameApp.cpp

    entities/
      Player.hpp
      Player.cpp
      Coin.hpp
      Coin.cpp

    gameplay/
      Collision.hpp

    scenes/
      MainScene.hpp
      MainScene.cpp

  game.package.json
  vix.app
  vix.json
```

## Build

```bash
vix build
```

## Run

```bash
vix run
```

## Export

```bash
vix game export
```

## Requirements

The installed Vix.cpp game module must be built with SDL support enabled.

On Ubuntu:

```bash
sudo apt update
sudo apt install libsdl2-dev libsdl2-image-dev
```

## Goal

This project is intentionally small.

It exists to show the clean path from:

- Vix project
- game app
- window
- renderer
- sprite
- input
- gameplay

## Create folders

```bash
mkdir -p src/entities src/gameplay src/scenes assets
```

## Expected assets

Place these files:

```text
assets/player.jpg
assets/coin.jpeg
```

## Test

```bash
vix build
vix run
```
