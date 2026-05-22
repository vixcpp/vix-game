name = "vix-game"
type = "executable"
standard = "c++20"

sources = [
  "src/main.cpp",
]

include_dirs = [
  "src",
]

compile_features = [
  "cxx_std_20",
]

packages = [
  "vix",
]

links = [
  "vix::game",
  "vix::io",
]

resources = [
  "assets=assets",
  "game.package.json=game.package.json",
]

output_dir = "bin"
