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
   * @brief Visual direction of the player.
   *
   * This enum stores the last horizontal direction used by the player.
   * It is used only for rendering, so the player can visually face the
   * direction in which it is moving.
   */
  enum class PlayerFacing
  {
    /**
     * @brief Player is facing the right side of the screen.
     */
    Right,

    /**
     * @brief Player is facing the left side of the screen.
     */
    Left
  };

  /**
   * @brief Controllable player entity.
   *
   * The player owns its position, size, movement speed, visual facing
   * direction, and texture asset identifier.
   *
   * It can load its texture, react to keyboard input, stay inside the
   * game window, and draw itself through Renderer2D.
   */
  class Player
  {
  public:
    /**
     * @brief Load the player texture.
     *
     * The texture is loaded from the asset manager using the path defined
     * in GameConfig, then uploaded to the active renderer.
     *
     * @param assets Asset manager used to load the texture.
     * @param renderer Active renderer used to upload the texture.
     * @return true on success, or a structured game error.
     */
    [[nodiscard]] vix::game::GameBoolResult load(
        vix::game::AssetManager &assets,
        vix::game::Renderer &renderer);

    /**
     * @brief Update player movement and visual direction.
     *
     * The player can be moved with WASD or arrow keys.
     * Horizontal movement updates the visual facing direction.
     *
     * @param input Input system used to read keyboard state.
     * @param frame Current frame information.
     */
    void update(
        const vix::game::InputSystem &input,
        const vix::game::Frame &frame);

    /**
     * @brief Draw the player.
     *
     * The sprite is rendered using the current texture, position, size,
     * and visual facing direction.
     *
     * @param renderer Renderer2D facade used to draw the sprite.
     */
    void draw(vix::game::Renderer2D &renderer) const;

    /**
     * @brief Return player position.
     *
     * @return Constant reference to the player position.
     */
    [[nodiscard]] const vix::game::Vec2 &position() const noexcept;

    /**
     * @brief Return player size.
     *
     * @return Constant reference to the player size.
     */
    [[nodiscard]] const vix::game::Vec2 &size() const noexcept;

  private:
    /**
     * @brief Clamp the player inside the game window.
     *
     * This prevents the player from moving outside the visible world.
     */
    void clamp_to_world() noexcept;

  private:
    /**
     * @brief Current player position in world coordinates.
     */
    vix::game::Vec2 position_{420.0F, 260.0F};

    /**
     * @brief Player sprite size.
     */
    vix::game::Vec2 size_{96.0F, 96.0F};

    /**
     * @brief Player movement speed in pixels per second.
     */
    float speed_{260.0F};

    /**
     * @brief Last horizontal visual direction of the player.
     *
     * This is updated when the player moves left or right and is used
     * during rendering to flip the sprite horizontally.
     */
    PlayerFacing facing_{PlayerFacing::Right};

    /**
     * @brief Texture asset identifier used by the player sprite.
     */
    vix::game::AssetId texture_{vix::game::invalid_asset_id};
  };

} // namespace vixgame

#endif // VIX_GAME_PROJECT_ENTITIES_PLAYER_HPP
