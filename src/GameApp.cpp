/**
 *
 *  @file GameApp.cpp
 *  @author Gaspard Kirira
 *
 *  Copyright 2026, Gaspard Kirira.
 *  All rights reserved.
 *  https://github.com/vixcpp/vix-game
 *
 *  Use of this source code is governed by a MIT license
 *  that can be found in the LICENSE file.
 *
 *  Vix.cpp
 *
 */

#include "GameApp.hpp"
#include "scenes/MainScene.hpp"
#include <vix/print.hpp>

namespace vixgame
{
  GameApp::GameApp()
      : app_{},
        runtime_{app_}
  {
    app_.set_title("vix-game");
    app_.set_target_fps(60);
  }

  int GameApp::run()
  {
    if (!initialize_runtime())
    {
      return 1;
    }

    if (!register_scenes())
    {
      return 1;
    }

    auto result = app_.run();
    if (!result)
    {
      vix::print("game failed:", result.error().message());
      return 1;
    }

    runtime_.shutdown();
    return 0;
  }

  bool GameApp::initialize_runtime()
  {
    auto result = runtime_.init();
    if (!result)
    {
      vix::print("runtime init failed:", result.error().message());
      return false;
    }

    return true;
  }

  bool GameApp::register_scenes()
  {
    auto scene = app_.scenes().create<MainScene>("main");
    if (!scene)
    {
      vix::print("scene creation failed:", scene.error().message());
      return false;
    }

    auto active = app_.scenes().set_active("main");
    if (!active)
    {
      vix::print("scene activation failed:", active.error().message());
      return false;
    }

    return true;
  }

} // namespace vixgame
