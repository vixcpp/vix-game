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
#include "../GameConfig.hpp"
#include "../gameplay/Collision.hpp"

#include <vix/game.hpp>
#include <vix/log.hpp>

namespace vixgame
{
  MainScene::MainScene()
      : vix::game::Scene("main")
  {
  }

  vix::game::GameBoolResult MainScene::on_load()
  {
    vix::log::info("Main scene loaded");
    vix::log::info("Move with WASD or arrow keys. Press Escape to quit.");

    auto player_loaded = player_.load(assets(), renderer());
    if (!player_loaded)
    {
      vix::log::error("player load failed: {}", player_loaded.error().message());
      return player_loaded.error();
    }

    auto coin_loaded = coin_.load(assets(), renderer());
    if (!coin_loaded)
    {
      vix::log::error("coin load failed: {}", coin_loaded.error().message());
      return coin_loaded.error();
    }

    return vix::game::Scene::on_load();
  }

  void MainScene::on_update(const vix::game::Frame &frame)
  {
    if (input().key_pressed(vix::game::InputKey::Escape))
    {
      vix::log::info("escape pressed, stopping game");
      app().stop();
      return;
    }

    update_gameplay(frame);
    render(frame);
  }

  void MainScene::update_gameplay(const vix::game::Frame &frame)
  {
    player_.update(input(), frame);

    if (!coin_.collected() && player_can_collect_coin())
    {
      coin_.collect();
      ++score_;
      ++coin_spawn_index_;

      vix::log::logf(
          vix::log::LogLevel::Info,
          "coin collected",
          "score", score_);

      coin_.respawn_at(next_safe_coin_position());

      vix::log::logf(
          vix::log::LogLevel::Debug,
          "coin respawned",
          "x", coin_.position().x,
          "y", coin_.position().y);
    }
  }

  void MainScene::render(const vix::game::Frame &frame)
  {
    renderer2d().clear(vix::game::Color{0.008F, 0.051F, 0.039F, 1.0F});

    coin_.draw(renderer2d(), frame);
    player_.draw(renderer2d());
  }

  bool MainScene::player_can_collect_coin() const noexcept
  {
    constexpr float collect_radius = 72.0F;

    const vix::game::Vec2 player_center{
        player_.position().x + player_.size().x * 0.5F,
        player_.position().y + player_.size().y * 0.5F};

    const vix::game::Vec2 coin_center{
        coin_.position().x + coin_.size().x * 0.5F,
        coin_.position().y + coin_.size().y * 0.5F};

    const float dx = coin_center.x - player_center.x;
    const float dy = coin_center.y - player_center.y;

    return (dx * dx + dy * dy) <= (collect_radius * collect_radius);
  }

  vix::game::Vec2 MainScene::next_safe_coin_position() const noexcept
  {
    constexpr float margin = 72.0F;
    constexpr float min_distance_from_player = 220.0F;

    const float max_x =
        static_cast<float>(GameConfig::window_width) -
        coin_.size().x -
        margin;

    const float max_y =
        static_cast<float>(GameConfig::window_height) -
        coin_.size().y -
        margin;

    const vix::game::Vec2 positions[] = {
        vix::game::Vec2{margin, margin},
        vix::game::Vec2{max_x, margin},
        vix::game::Vec2{margin, max_y},
        vix::game::Vec2{max_x, max_y},
        vix::game::Vec2{
            static_cast<float>(GameConfig::window_width) * 0.5F,
            margin},
        vix::game::Vec2{
            static_cast<float>(GameConfig::window_width) * 0.5F,
            max_y},
        vix::game::Vec2{
            static_cast<float>(GameConfig::window_width) * 0.25F,
            static_cast<float>(GameConfig::window_height) * 0.5F},
        vix::game::Vec2{
            static_cast<float>(GameConfig::window_width) * 0.75F,
            static_cast<float>(GameConfig::window_height) * 0.5F}};

    constexpr int position_count =
        static_cast<int>(sizeof(positions) / sizeof(positions[0]));

    const vix::game::Vec2 player_center{
        player_.position().x + player_.size().x * 0.5F,
        player_.position().y + player_.size().y * 0.5F};

    for (int offset = 0; offset < position_count; ++offset)
    {
      const int index = (coin_spawn_index_ + offset) % position_count;
      const vix::game::Vec2 candidate = positions[index];

      const vix::game::Vec2 coin_center{
          candidate.x + coin_.size().x * 0.5F,
          candidate.y + coin_.size().y * 0.5F};

      const float dx = coin_center.x - player_center.x;
      const float dy = coin_center.y - player_center.y;
      const float distance_squared = dx * dx + dy * dy;

      if (distance_squared >=
              min_distance_from_player * min_distance_from_player &&
          !intersects(
              player_.position(),
              player_.size(),
              candidate,
              coin_.size()))
      {
        return candidate;
      }
    }

    return vix::game::Vec2{max_x, margin};
  }
} // namespace vixgame
