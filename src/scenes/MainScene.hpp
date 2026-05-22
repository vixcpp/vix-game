/**
 *
 *  @file MainScene.hpp
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
#ifndef VIX_GAME_PROJECT_SCENES_MAIN_SCENE_HPP
#define VIX_GAME_PROJECT_SCENES_MAIN_SCENE_HPP

#include "../entities/Coin.hpp"
#include "../entities/Player.hpp"
#include <vix/game.hpp>

namespace vixgame
{
  /**
   * @brief Main gameplay scene.
   */
  class MainScene final : public vix::game::Scene
  {
  public:
    /**
     * @brief Construct the main scene.
     */
    MainScene();

    /**
     * @brief Load the main scene.
     *
     * @return true on success, or a structured game error.
     */
    [[nodiscard]] vix::game::GameBoolResult on_load() override;

    /**
     * @brief Update the main scene each frame.
     *
     * @param frame Current frame information.
     */
    void on_update(const vix::game::Frame &frame) override;

  private:
    /**
     * @brief Update gameplay state.
     *
     * @param frame Current frame.
     */
    void update_gameplay(const vix::game::Frame &frame);

    /**
     * @brief Render the scene.
     *
     * @param frame Current frame.
     */
    void render(const vix::game::Frame &frame);

    /**
     * @brief Return true if the player is close enough to collect the coin.
     *
     * @return true when the coin should be collected.
     */
    [[nodiscard]] bool player_can_collect_coin() const noexcept;

    /**
     * @brief Compute the next coin position that does not overlap the player.
     *
     * @return New safe coin position.
     */
    [[nodiscard]] vix::game::Vec2 next_safe_coin_position() const noexcept;

  private:
    Player player_{};
    Coin coin_{};
    int score_{0};
    int coin_spawn_index_{0};
  };

} // namespace vixgame

#endif // VIX_GAME_PROJECT_SCENES_MAIN_SCENE_HPP
