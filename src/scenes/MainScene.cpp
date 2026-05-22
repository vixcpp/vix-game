/**
 *
 *  @file MainScene.cpp
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

#include "MainScene.hpp"
#include <vix/print.hpp>

namespace vixgame
{
  MainScene::MainScene()
      : vix::game::Scene("main")
  {
  }

  vix::game::GameBoolResult MainScene::on_load()
  {
    vix::print("Main scene loaded");
    return vix::game::Scene::on_load();
  }

  void MainScene::on_update(const vix::game::Frame &frame)
  {
    vix::print("frame:", frame.index);

    if (frame.index >= 5)
    {
      app().stop();
    }
  }

} // namespace vixgame
