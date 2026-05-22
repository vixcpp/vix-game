/**
 *
 *  @file Coin.cpp
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

#include "Coin.hpp"
#include "../GameConfig.hpp"

#include <cmath>
#include <string>

#include <vix/game/Color.hpp>
#include <vix/game/GameError.hpp>
#include <vix/game/Sprite.hpp>
#include <vix/game/Transform2D.hpp>

namespace vixgame
{
  vix::game::GameBoolResult Coin::load(
      vix::game::AssetManager &assets,
      vix::game::Renderer &renderer)
  {
    auto loaded = assets.load_or_get(std::string{GameConfig::coin_texture});
    if (!loaded)
    {
      return loaded.error();
    }

    texture_ = loaded.value();

    auto *asset = assets.get(texture_);
    if (asset == nullptr)
    {
      return vix::game::make_game_error(
          vix::game::GameErrorCode::AssetNotFound,
          "coin texture was loaded but cannot be found");
    }

    auto uploaded = renderer.upload_texture(*asset);
    if (!uploaded)
    {
      return uploaded.error();
    }

    return true;
  }

  void Coin::draw(
      vix::game::Renderer2D &renderer,
      const vix::game::Frame &frame) const
  {
    if (collected_)
    {
      return;
    }

    const float pulse =
        0.5F + 0.5F * std::sin(static_cast<float>(frame.index) * 0.04F);

    vix::game::Transform2D transform =
        vix::game::Transform2D::at(position_);

    const float scale = 1.0F + pulse * 0.15F;
    transform.scale = vix::game::Vec2{scale, scale};

    vix::game::Sprite sprite = vix::game::Sprite::from_asset(texture_);
    sprite.set_size(size_);
    sprite.tint = vix::game::Color{1.0F, 0.9F, 0.35F, 1.0F};

    renderer.draw_sprite(transform, sprite);
  }

  const vix::game::Vec2 &Coin::position() const noexcept
  {
    return position_;
  }

  const vix::game::Vec2 &Coin::size() const noexcept
  {
    return size_;
  }

  bool Coin::collected() const noexcept
  {
    return collected_;
  }

  void Coin::collect() noexcept
  {
    collected_ = true;
  }

  void Coin::respawn_at(const vix::game::Vec2 &position) noexcept
  {
    position_ = position;
    collected_ = false;
  }

} // namespace vixgame
