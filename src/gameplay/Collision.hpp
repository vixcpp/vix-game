/**
 *
 *  @file Collision.hpp
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
#ifndef VIX_GAME_PROJECT_GAMEPLAY_COLLISION_HPP
#define VIX_GAME_PROJECT_GAMEPLAY_COLLISION_HPP

#include <vix/game/Vec2.hpp>

namespace vixgame
{
  /**
   * @brief Test whether two axis-aligned rectangles intersect.
   *
   * @param a_position First rectangle position.
   * @param a_size First rectangle size.
   * @param b_position Second rectangle position.
   * @param b_size Second rectangle size.
   * @return true if the rectangles intersect.
   */
  [[nodiscard]] inline bool intersects(
      const vix::game::Vec2 &a_position,
      const vix::game::Vec2 &a_size,
      const vix::game::Vec2 &b_position,
      const vix::game::Vec2 &b_size) noexcept
  {
    const float a_left = a_position.x;
    const float a_right = a_position.x + a_size.x;
    const float a_top = a_position.y;
    const float a_bottom = a_position.y + a_size.y;

    const float b_left = b_position.x;
    const float b_right = b_position.x + b_size.x;
    const float b_top = b_position.y;
    const float b_bottom = b_position.y + b_size.y;

    return a_left < b_right &&
           a_right > b_left &&
           a_top < b_bottom &&
           a_bottom > b_top;
  }

} // namespace vixgame

#endif // VIX_GAME_PROJECT_GAMEPLAY_COLLISION_HPP
