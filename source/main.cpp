#include <SDL3/SDL.h>

#include "SDL_helper.hpp"
#include "polyhedron.hpp"
#include "quaternion.hpp"
#include "rotation_kind.hpp"
#include "vector3.hpp"

constexpr auto FRAME_RATE = 16.6666666666666666;
constexpr auto IDENTITY_ROTATION = Quaternion::W();
constexpr auto IDENTITY_TRANSLATION = Vector3::ZERO();
constexpr auto ROTATION_SPEED = 0.05;
constexpr auto TRANSLATION_SPEED = 5.0;

auto platonic_solids() -> std::array<Polyhedron, 5> {
  return {Polyhedron::cube(50, Vector3(0.0, 0.0, 0.0)),
          Polyhedron::tetrahedron(50, Vector3(200, 0, 0.0)),
          Polyhedron::octahedron(62.5, Vector3(-200, 0, 0)),
          Polyhedron::dodecahedron(37.5, Vector3(0.0, 200, 0.0)),
          Polyhedron::icosahedron(37.5, Vector3(0.0, -200, 0.0))};
}

auto handle_input(bool& quit, std::array<Polyhedron, 5>& entities,
                  Quaternion& world_orientation, RotationKind& rotation_kind,
                  Quaternion& rotation, Vector3& translation) {
  // reset transformations
  rotation_kind = AboutEntityPosition;
  rotation = IDENTITY_ROTATION;
  translation = IDENTITY_TRANSLATION;

  // get data needed to build transformation from input
  const auto [world_x, world_y, world_z] = world_orientation.basis_vectors();
  const auto is_key_down = get_keyboard_state();

  // check for quit, or reset
  if (is_key_down[KEY_ESCAPE]) {
    quit = true;
    return;
  }
  if (is_key_down[KEY_1]) {
    entities = platonic_solids();
    world_orientation = IDENTITY_ROTATION;
    return;
  }

  /* construct transformation from input */

  if (is_key_down[KEY_LEFT_SHIFT])
    rotation_kind = AboutOrigin;
  if (is_key_down[KEY_LEFT_CTRL])
    rotation_kind = Universal;

  if (is_key_down[KEY_S])
    rotation *= Quaternion(world_x, ROTATION_SPEED);
  if (is_key_down[KEY_W])
    rotation *= Quaternion(-world_x, ROTATION_SPEED);
  if (is_key_down[KEY_D])
    rotation *= Quaternion(world_y, ROTATION_SPEED);
  if (is_key_down[KEY_A])
    rotation *= Quaternion(-world_y, ROTATION_SPEED);
  if (is_key_down[KEY_Q])
    rotation *= Quaternion(world_z, ROTATION_SPEED);
  if (is_key_down[KEY_E])
    rotation *= Quaternion(-world_z, ROTATION_SPEED);

  if (is_key_down[KEY_L])
    translation += world_x;
  if (is_key_down[KEY_J])
    translation -= world_x;
  if (is_key_down[KEY_K])
    translation += world_y;
  if (is_key_down[KEY_I])
    translation -= world_y;
  if (is_key_down[KEY_U])
    translation += world_z;
  if (is_key_down[KEY_O])
    translation -= world_z;

  rotation = rotation.normalized_or_unit_w();
  translation = translation.normalized_or_zero() * TRANSLATION_SPEED;
}

auto apply_transformation(std::span<Polyhedron> entities,
                          Quaternion& world_orientation,
                          const RotationKind& rotation_kind,
                          const Quaternion& rotation,
                          const Vector3& translation) {
  if (rotation_kind == Universal) {
    world_orientation = rotation * world_orientation;
  }

  for (auto& polyhedron : entities) {
    if (rotation_kind == AboutEntityPosition) {
      polyhedron.rotate(rotation, polyhedron.position());
    } else {
      polyhedron.rotate(rotation, Vector3::ZERO());
    }

    polyhedron.translate(translation);
  }
}

auto draw(SDL_Window* window, SDL_Renderer* renderer,
          const Quaternion& world_orientation,
          std::span<const Polyhedron> entities) {
  auto screen_origin = get_window_dimensions(window) / 2.0;
  draw_world_axes_orthographic(renderer, screen_origin, world_orientation);
  for (const auto& polyhedron : entities)
    draw_polyhedron_wireframe_orthographic(renderer, screen_origin, WHITE,
                                           polyhedron);
}

auto main() -> int {
  /* initialize SDL */
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  if (auto result = initialize_SDL(); result) {
    std::tie(window, renderer) = *result;
  } else {
    return -1;
  }

  /* program data */

  // frame timing data
  auto frame_start = 0ull;
  auto frame_end = 0ull;

  // world data
  // auto world_origin = Vector3::ZERO(); // currently unused
  auto world_orientation = IDENTITY_ROTATION;

  // entities
  auto entities = platonic_solids();

  // transformation data
  auto rotation_kind = AboutEntityPosition;
  auto rotation = IDENTITY_ROTATION;
  auto translation = IDENTITY_TRANSLATION;

  // program control data
  auto quit = false;

  /* main loop */

  while (!quit) {
    clear_screen(renderer, BLACK);

    // handle events
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_EVENT_QUIT:
          quit = true;
          break;
      }
    }

    handle_input(quit, entities, world_orientation, rotation_kind, rotation,
                 translation);

    draw(window, renderer, world_orientation, entities);

    apply_transformation(entities, world_orientation, rotation_kind, rotation,
                         translation);

    maintain_frame_rate(FRAME_RATE, frame_start, frame_end);
  }

  deinitialize_SDL(window, renderer);
  return 0;
}
