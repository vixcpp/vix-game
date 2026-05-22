/**
 *
 *  @file GameApp.hpp
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
#ifndef VIX_GAME_PROJECT_GAME_APP_HPP
#define VIX_GAME_PROJECT_GAME_APP_HPP

#include <vix/game/game.hpp>

namespace vixgame
{
  /**
   * @brief Main application wrapper for the vix-game project.
   *
   * GameApp owns the Vix game application object and its runtime.
   * It is responsible for:
   * - configuring the game application
   * - initializing the game runtime
   * - registering scenes
   * - starting the main game loop
   */
  class GameApp
  {
  public:
    /**
     * @brief Construct the game application.
     */
    GameApp();

    /**
     * @brief Run the game application.
     *
     * @return 0 on success, 1 on failure.
     */
    [[nodiscard]] int run();

  private:
    /**
     * @brief Initialize the Vix game runtime.
     *
     * @return true on success, false on failure.
     */
    [[nodiscard]] bool initialize_runtime();

    /**
     * @brief Register and activate all game scenes.
     *
     * @return true on success, false on failure.
     */
    [[nodiscard]] bool register_scenes();

  private:
    /**
     * @brief Root Vix game application.
     */
    vix::game::App app_{};

    /**
     * @brief Runtime coordinator for the game application.
     */
    vix::game::GameRuntime runtime_;
  };

} // namespace vixgame

#endif // VIX_GAME_PROJECT_GAME_APP_HPP
