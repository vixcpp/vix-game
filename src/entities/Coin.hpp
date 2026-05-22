/**
 *
 *  @file Coin.hpp
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
#ifndef VIX_GAME_PROJECT_ENTITIES_COIN_HPP
#define VIX_GAME_PROJECT_ENTITIES_COIN_HPP

#include <vix/game/AssetId.hpp>
#include <vix/game/AssetManager.hpp>
#include <vix/game/Frame.hpp>
#include <vix/game/GameResult.hpp>
#include <vix/game/Renderer.hpp>
#include <vix/game/Renderer2D.hpp>
#include <vix/game/Vec2.hpp>

namespace vixgame
{
  /**
   * @brief Collectible coin entity.
   */
  class Coin
  {
  public:
    /**
     * @brief Load the coin texture.
     *
     * @param assets Asset manager.
     * @param renderer Active renderer.
     * @return true on success, or a structured game error.
     */
    [[nodiscard]] vix::game::GameBoolResult load(
        vix::game::AssetManager &assets,
        vix::game::Renderer &renderer);

    /**
     * @brief Draw the coin.
     *
     * @param renderer Renderer2D facade.
     * @param frame Current frame.
     */
    void draw(
        vix::game::Renderer2D &renderer,
        const vix::game::Frame &frame) const;

    /**
     * @brief Return coin position.
     */
    [[nodiscard]] const vix::game::Vec2 &position() const noexcept;

    /**
     * @brief Return coin size.
     */
    [[nodiscard]] const vix::game::Vec2 &size() const noexcept;

    /**
     * @brief Return true if the coin has been collected.
     */
    [[nodiscard]] bool collected() const noexcept;

    /**
     * @brief Mark the coin as collected.
     */
    void collect() noexcept;

    /**
     * @brief Move the coin to a new position and make it collectible again.
     *
     * @param position New coin position.
     */
    void respawn_at(const vix::game::Vec2 &position) noexcept;

  private:
    vix::game::Vec2 position_{680.0F, 260.0F};
    vix::game::Vec2 size_{64.0F, 64.0F};
    bool collected_{false};
    vix::game::AssetId texture_{vix::game::invalid_asset_id};
  };

} // namespace vixgame

#endif // VIX_GAME_PROJECT_ENTITIES_COIN_HPP
