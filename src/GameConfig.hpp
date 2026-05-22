/**
 *
 *  @file GameConfig.hpp
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
#ifndef VIX_GAME_PROJECT_GAME_CONFIG_HPP
#define VIX_GAME_PROJECT_GAME_CONFIG_HPP

#include <cstdint>
#include <string_view>

namespace vixgame
{
  /**
   * @brief Central configuration values for the game.
   */
  struct GameConfig
  {
    /**
     * @brief Game title.
     */
    static constexpr std::string_view title{"vix-game"};

    /**
     * @brief Main scene name.
     */
    static constexpr std::string_view main_scene{"main"};

    /**
     * @brief Asset root directory.
     */
    static constexpr std::string_view asset_root{"assets"};

    /**
     * @brief Player texture file.
     */
    static constexpr std::string_view player_texture{"player.png"};

    /**
     * @brief Coin texture file.
     */
    static constexpr std::string_view coin_texture{"coin.png"};

    /**
     * @brief Whether the game starts without a real window backend.
     */
    static constexpr bool headless{false};

    /**
     * @brief Whether the game window should be visible.
     */
    static constexpr bool window_visible{true};

    /**
     * @brief Whether the game window should be resizable.
     */
    static constexpr bool window_resizable{true};

    /**
     * @brief Whether vertical synchronization is enabled.
     */
    static constexpr bool window_vsync{true};

    /**
     * @brief Whether the window should use an OpenGL context.
     */
    static constexpr bool window_opengl{true};

    /**
     * @brief Target frame rate.
     */
    static constexpr std::uint32_t target_fps{60};

    /**
     * @brief Window width.
     */
    static constexpr std::uint32_t window_width{960};

    /**
     * @brief Window height.
     */
    static constexpr std::uint32_t window_height{540};
  };

} // namespace vixgame

#endif // VIX_GAME_PROJECT_GAME_CONFIG_HPP
