#pragma once
#include <SDL3/SDL.h>

#include <algorithm>
#include <array>
#include <cstddef>
#include <optional>
#include <print>
#include <tuple>

#include "polyhedron.hpp"
#include "vector2.hpp"
#include "vector3.hpp"

auto initialize_SDL() -> std::optional<std::tuple<SDL_Window*, SDL_Renderer*>> {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    std::print("failed to initialize SDL: {}", SDL_GetError());
    return std::nullopt;
  }

  auto window =
      SDL_CreateWindow("Platonic Solids", 800, 800, SDL_WINDOW_RESIZABLE);
  if (nullptr == window) {
    std::print("failed to create window: {}", SDL_GetError());
    return std::nullopt;
  }

  auto renderer = SDL_CreateRenderer(window, "software");
  if (nullptr == renderer) {
    std::print("failed to create renderer: {}", SDL_GetError());
    return std::nullopt;
  }

  return std::tuple(window, renderer);
}

auto deinitialize_SDL(SDL_Window* window, SDL_Renderer* renderer) -> void {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}

struct ColorRgba8 {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint8_t alpha;
};
constexpr auto BLACK = ColorRgba8{0, 0, 0, 255};
constexpr auto WHITE = ColorRgba8{255, 255, 255, 255};
constexpr auto RED = ColorRgba8{255, 0, 0, 255};
constexpr auto GREEN = ColorRgba8{0, 255, 0, 255};
constexpr auto BLUE = ColorRgba8{0, 0, 255, 255};
constexpr auto YELLOW = ColorRgba8{255, 255, 0, 255};
constexpr auto CYAN = ColorRgba8{0, 255, 255, 255};
constexpr auto MAGENTA = ColorRgba8{255, 0, 255, 255};
constexpr auto GRAY = ColorRgba8{128, 128, 128, 255};
constexpr auto DARK_GRAY = ColorRgba8{64, 64, 64, 255};
constexpr auto LIGHT_GRAY = ColorRgba8{192, 192, 192, 255};
constexpr auto ORANGE = ColorRgba8{255, 165, 0, 255};
constexpr auto PURPLE = ColorRgba8{128, 0, 128, 255};
constexpr auto BROWN = ColorRgba8{165, 42, 42, 255};
constexpr auto PINK = ColorRgba8{255, 192, 203, 255};

constexpr auto KEY_ESCAPE = SDL_SCANCODE_ESCAPE;
constexpr auto KEY_1 = SDL_SCANCODE_1;
constexpr auto KEY_LEFT_SHIFT = SDL_SCANCODE_LSHIFT;
constexpr auto KEY_LEFT_CTRL = SDL_SCANCODE_LCTRL;
constexpr auto KEY_S = SDL_SCANCODE_S;
constexpr auto KEY_W = SDL_SCANCODE_W;
constexpr auto KEY_D = SDL_SCANCODE_D;
constexpr auto KEY_A = SDL_SCANCODE_A;
constexpr auto KEY_Q = SDL_SCANCODE_Q;
constexpr auto KEY_E = SDL_SCANCODE_E;
constexpr auto KEY_L = SDL_SCANCODE_L;
constexpr auto KEY_J = SDL_SCANCODE_J;
constexpr auto KEY_K = SDL_SCANCODE_K;
constexpr auto KEY_I = SDL_SCANCODE_I;
constexpr auto KEY_U = SDL_SCANCODE_U;
constexpr auto KEY_O = SDL_SCANCODE_O;

auto get_keyboard_state() -> const bool* {
  return SDL_GetKeyboardState(nullptr);
}

auto set_color(SDL_Renderer* renderer, ColorRgba8 color) -> void {
  SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue,
                         color.alpha);
}

auto clear_screen(SDL_Renderer* renderer, ColorRgba8 color) -> void {
  SDL_RenderPresent(renderer);
  set_color(renderer, color);
  SDL_RenderClear(renderer);
}

auto get_window_dimensions(SDL_Window* window) -> Vector2 {
  int32_t w;
  int32_t h;
  SDL_GetWindowSize(window, &w, &h);
  return Vector2(w, h);
}

auto get_window_origin(SDL_Window* window) -> Vector2 {
  return get_window_dimensions(window) / 2.0;
}

auto draw_line(SDL_Renderer* renderer, const Vector2& start, const Vector2& end)
    -> void {
  SDL_RenderLine(renderer, start.x, start.y, end.x, end.y);
}

auto draw_polyhedron_wireframe_orthographic(SDL_Renderer* renderer,
                                            const Vector2& screen_origin,
                                            const ColorRgba8& color,
                                            const Polyhedron& polyhedron)
    -> void {
  set_color(renderer, color);

  const auto vertexes = polyhedron.vertexes();
  for (const auto& [start_i, end_i] : polyhedron.edges()) {
    // orthographic means ignore z component
    auto start = vertexes[start_i].xy() + screen_origin;
    auto end = vertexes[end_i].xy() + screen_origin;
    draw_line(renderer, start, end);
  }
}

auto draw_world_axes_orthographic(SDL_Renderer* renderer,
                                  const Vector2& screen_origin,
                                  const Quaternion& world_orientation) {
  const auto scale = std::max(screen_origin.x, screen_origin.y);

  constexpr auto BASIS_COLORS = std::array{RED, GREEN, BLUE};
  const auto bases = world_orientation.basis_vectors();
  for (size_t i = 0; i < bases.size(); i += 1) {
    set_color(renderer, BASIS_COLORS[i]);
    auto start = (bases[i].xy() * -scale) + screen_origin;
    auto end = (bases[i].xy() * scale) + screen_origin;
    draw_line(renderer, start, end);
  }
}

auto maintain_frame_rate(const double& ms_per_frame, uint64_t& frame_start,
                         uint64_t& frame_end) {
  frame_end = SDL_GetPerformanceCounter();

  auto elapsed_time = static_cast<double>(frame_end - frame_start) /
                      static_cast<double>(SDL_GetPerformanceFrequency() * 1000);
  auto time_to_wait = floor(ms_per_frame - elapsed_time);

  SDL_Delay(time_to_wait);

  frame_start = SDL_GetPerformanceCounter();
}
