/**
 *
 *  @file Player.cpp
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

#include "Player.hpp"
#include "../GameConfig.hpp"

#include <cmath>
#include <string>

#include <vix/game/GameError.hpp>
#include <vix/game/InputKey.hpp>
#include <vix/game/Sprite.hpp>
#include <vix/game/Transform2D.hpp>

namespace
{
  [[nodiscard]] float clamp_float(
      float value,
      float minimum,
      float maximum) noexcept
  {
    if (value < minimum)
    {
      return minimum;
    }

    if (value > maximum)
    {
      return maximum;
    }

    return value;
  }
}

namespace vixgame
{
  vix::game::GameBoolResult Player::load(
      vix::game::AssetManager &assets,
      vix::game::Renderer &renderer)
  {
    auto loaded = assets.load_or_get(std::string{GameConfig::player_texture});
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
          "player texture was loaded but cannot be found");
    }

    auto uploaded = renderer.upload_texture(*asset);
    if (!uploaded)
    {
      return uploaded.error();
    }

    return true;
  }

  void Player::update(
      const vix::game::InputSystem &input,
      const vix::game::Frame &frame)
  {
    vix::game::Vec2 direction{0.0F, 0.0F};

    if (input.key_down(vix::game::InputKey::A) ||
        input.key_down(vix::game::InputKey::ArrowLeft))
    {
      direction.x -= 1.0F;
      facing_ = PlayerFacing::Left;
    }

    if (input.key_down(vix::game::InputKey::D) ||
        input.key_down(vix::game::InputKey::ArrowRight))
    {
      direction.x += 1.0F;
      facing_ = PlayerFacing::Right;
    }

    if (input.key_down(vix::game::InputKey::W) ||
        input.key_down(vix::game::InputKey::ArrowUp))
    {
      direction.y -= 1.0F;
    }

    if (input.key_down(vix::game::InputKey::S) ||
        input.key_down(vix::game::InputKey::ArrowDown))
    {
      direction.y += 1.0F;
    }

    const float length =
        std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length > 0.0F)
    {
      direction.x /= length;
      direction.y /= length;
    }

    const float delta_seconds =
        static_cast<float>(frame.delta_ms()) / 1000.0F;

    position_.x += direction.x * speed_ * delta_seconds;
    position_.y += direction.y * speed_ * delta_seconds;

    clamp_to_world();
  }

  void Player::draw(vix::game::Renderer2D &renderer) const
  {
    vix::game::Transform2D transform =
        vix::game::Transform2D::at(position_);

    if (facing_ == PlayerFacing::Left)
    {
      transform.scale = vix::game::Vec2{-1.0F, 1.0F};
    }
    else
    {
      transform.scale = vix::game::Vec2{1.0F, 1.0F};
    }

    vix::game::Sprite sprite = vix::game::Sprite::from_asset(texture_);
    sprite.set_size(size_);

    renderer.draw_sprite(transform, sprite);
  }

  const vix::game::Vec2 &Player::position() const noexcept
  {
    return position_;
  }

  const vix::game::Vec2 &Player::size() const noexcept
  {
    return size_;
  }

  void Player::clamp_to_world() noexcept
  {
    position_.x = clamp_float(
        position_.x,
        0.0F,
        static_cast<float>(GameConfig::window_width) - size_.x);

    position_.y = clamp_float(
        position_.y,
        0.0F,
        static_cast<float>(GameConfig::window_height) - size_.y);
  }

} // namespace vixgame
