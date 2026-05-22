/**
 *
 *  @file Player.hpp
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
#ifndef VIX_GAME_PROJECT_ENTITIES_PLAYER_HPP
#define VIX_GAME_PROJECT_ENTITIES_PLAYER_HPP

#include <vix/game/AssetId.hpp>
#include <vix/game/AssetManager.hpp>
#include <vix/game/Frame.hpp>
#include <vix/game/GameResult.hpp>
#include <vix/game/InputSystem.hpp>
#include <vix/game/Renderer.hpp>
#include <vix/game/Renderer2D.hpp>
#include <vix/game/Vec2.hpp>

namespace vixgame
{
  /**
   * @brief Controllable player entity.
   */
  class Player
  {
  public:
    /**
     * @brief Load the player texture.
     *
     * @param assets Asset manager.
     * @param renderer Active renderer.
     * @return true on success, or a structured game error.
     */
    [[nodiscard]] vix::game::GameBoolResult load(
        vix::game::AssetManager &assets,
        vix::game::Renderer &renderer);

    /**
     * @brief Update player movement.
     *
     * @param input Input system.
     * @param frame Current frame.
     */
    void update(
        const vix::game::InputSystem &input,
        const vix::game::Frame &frame);

    /**
     * @brief Draw the player.
     *
     * @param renderer Renderer2D facade.
     */
    void draw(vix::game::Renderer2D &renderer) const;

    /**
     * @brief Return player position.
     */
    [[nodiscard]] const vix::game::Vec2 &position() const noexcept;

    /**
     * @brief Return player size.
     */
    [[nodiscard]] const vix::game::Vec2 &size() const noexcept;

  private:
    /**
     * @brief Clamp the player inside the game window.
     */
    void clamp_to_world() noexcept;

  private:
    vix::game::Vec2 position_{420.0F, 260.0F};
    vix::game::Vec2 size_{96.0F, 96.0F};
    float speed_{260.0F};
    vix::game::AssetId texture_{vix::game::invalid_asset_id};
  };

} // namespace vixgame

#endif // VIX_GAME_PROJECT_ENTITIES_PLAYER_HPP
