/**
 *
 *  @file GameApp.cpp
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

#include "GameApp.hpp"
#include "GameConfig.hpp"
#include "scenes/MainScene.hpp"
#include <vix/game.hpp>
#include <vix/game/RendererBackend.hpp>
#include <vix/game/WindowBackend.hpp>
#include <vix/game/backends/sdl/SDLOpenGLRenderer.hpp>
#include <vix/game/backends/sdl/SDLWindow.hpp>
#include <vix/print.hpp>

namespace vixgame
{
  GameApp::GameApp()
      : app_{make_app_config()},
        runtime_{app_}
  {
    app_.set_target_fps(GameConfig::target_fps);
  }

  vix::game::AppConfig GameApp::make_app_config()
  {
    auto config = vix::game::AppConfig::defaults();

    config.title = std::string{GameConfig::title};
    config.asset_root = std::string{GameConfig::asset_root};
    config.headless = GameConfig::headless;

    config.window = vix::game::WindowConfig::defaults();
    config.window.title = std::string{GameConfig::title};
    config.window.width = GameConfig::window_width;
    config.window.height = GameConfig::window_height;
    config.window.resizable = GameConfig::window_resizable;
    config.window.visible = GameConfig::window_visible;
    config.window.vsync = GameConfig::window_vsync;
    config.window.headless = GameConfig::headless;
    config.window.opengl = GameConfig::window_opengl;

    return config;
  }

  int GameApp::run()
  {
    if (!initialize_runtime())
    {
      return 1;
    }

    if (!initialize_backends())
    {
      return 1;
    }

    if (!register_scenes())
    {
      return 1;
    }

    auto result = app_.run();
    if (!result)
    {
      vix::print("game failed:", result.error().message());
      return 1;
    }

    runtime_.shutdown();
    return 0;
  }

  bool GameApp::initialize_runtime()
  {
    auto result = runtime_.init();
    if (!result)
    {
      vix::print("runtime init failed:", result.error().message());
      return false;
    }

    return true;
  }

  bool GameApp::initialize_backends()
  {
    auto config = make_app_config();
    auto &context = app_.runtime().context();

    auto window_backend =
        std::unique_ptr<vix::game::WindowBackend>(
            new vix::game::sdl::SDLWindow());

    auto renderer_backend =
        std::unique_ptr<vix::game::RendererBackend>(
            new vix::game::sdl::SDLOpenGLRenderer());

    context
        .set_window_backend(std::move(window_backend))
        .set_renderer_backend(std::move(renderer_backend));

    auto opened = context.window().open(config.window);
    if (!opened)
    {
      vix::print("window open failed:", opened.error().message());
      return false;
    }

    auto renderer_init = context.renderer().init(context.window());
    if (!renderer_init)
    {
      vix::print("renderer init failed:", renderer_init.error().message());
      return false;
    }

    context.renderer2d().set_camera(
        vix::game::Camera2D::from_size(
            context.window().width(),
            context.window().height()));

    return true;
  }

  bool GameApp::register_scenes()
  {
    auto scene = app_.scenes().create<MainScene>(
        std::string{GameConfig::main_scene});

    if (!scene)
    {
      vix::print("scene creation failed:", scene.error().message());
      return false;
    }

    auto active = app_.scenes().set_active(
        std::string{GameConfig::main_scene});

    if (!active)
    {
      vix::print("scene activation failed:", active.error().message());
      return false;
    }

    return true;
  }

} // namespace vixgame
