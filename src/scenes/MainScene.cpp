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
#include "../gameplay/Collision.hpp"
#include <vix/game.hpp>
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
    vix::print("Move with WASD or arrow keys. Press Escape to quit.");

    auto player_loaded = player_.load(assets(), renderer());
    if (!player_loaded)
    {
      vix::print("player load failed:", player_loaded.error().message());
      return player_loaded.error();
    }

    auto coin_loaded = coin_.load(assets(), renderer());
    if (!coin_loaded)
    {
      vix::print("coin load failed:", coin_loaded.error().message());
      return coin_loaded.error();
    }

    return vix::game::Scene::on_load();
  }

  void MainScene::on_update(const vix::game::Frame &frame)
  {
    if (input().key_pressed(vix::game::InputKey::Escape))
    {
      app().stop();
      return;
    }

    update_gameplay(frame);
    render(frame);
  }

  void MainScene::update_gameplay(const vix::game::Frame &frame)
  {
    player_.update(input(), frame);

    if (!coin_.collected() &&
        intersects(
            player_.position(),
            player_.size(),
            coin_.position(),
            coin_.size()))
    {
      coin_.collect();
      ++score_;

      vix::print("coin collected. score:", score_);
    }
  }

  void MainScene::render(const vix::game::Frame &frame)
  {
    renderer2d().clear(vix::game::Color{0.05F, 0.06F, 0.09F, 1.0F});

    player_.draw(renderer2d());
    coin_.draw(renderer2d(), frame);
  }

} // namespace vixgame
