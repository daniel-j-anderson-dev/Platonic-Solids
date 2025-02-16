#pragma once
#include <array>
#include <span>
#include <tuple>
#include <utility>
#include <vector>

#include "quaternion.hpp"
#include "vector3.hpp"

constexpr double PHI = 1.61803398874989484820;

constexpr std::array<Vector3, 8> UNIT_CUBE_VERTEXES = {
    Vector3(1.0, 1.0, 1.0),   Vector3(1.0, 1.0, -1.0),
    Vector3(1.0, -1.0, 1.0),  Vector3(1.0, -1.0, -1.0),
    Vector3(-1.0, 1.0, 1.0),  Vector3(-1.0, 1.0, -1.0),
    Vector3(-1.0, -1.0, 1.0), Vector3(-1.0, -1.0, -1.0),
};
constexpr std::array<std::tuple<uint64_t, uint64_t>, 12> CUBE_EDGES = {
    std::tuple(0, 1), std::tuple(0, 2), std::tuple(0, 4), std::tuple(1, 3),
    std::tuple(1, 5), std::tuple(2, 3), std::tuple(2, 6), std::tuple(3, 7),
    std::tuple(4, 5), std::tuple(4, 6), std::tuple(5, 7), std::tuple(6, 7),
};

constexpr std::array<Vector3, 4> UNIT_TETRAHEDRON_VERTEXES = {
    Vector3(1.0, 1.0, 1.0), Vector3(-1.0, -1.0, 1.0), Vector3(-1.0, 1.0, -1.0),
    Vector3(1.0, -1.0, -1.0)};
constexpr std::array<std::tuple<uint64_t, uint64_t>, 6> TETRAHEDRON_EDGES = {
    std::tuple(0, 1), std::tuple(0, 2), std::tuple(0, 3),
    std::tuple(1, 2), std::tuple(1, 3), std::tuple(2, 3),
};

constexpr std::array<Vector3, 6> UNIT_OCTAHEDRON_VERTEXES = {
    Vector3(1.0, 0.0, 0.0),  Vector3(-1.0, 0.0, 0.0), Vector3(0.0, 1.0, 0.0),
    Vector3(0.0, -1.0, 0.0), Vector3(0.0, 0.0, 1.0),  Vector3(0.0, 0.0, -1.0)};
constexpr std::array<std::tuple<uint64_t, uint64_t>, 12> OCTAHEDRON_EDGES = {
    std::tuple(0, 2), std::tuple(0, 3), std::tuple(0, 4), std::tuple(0, 5),
    std::tuple(1, 2), std::tuple(1, 3), std::tuple(1, 4), std::tuple(1, 5),
    std::tuple(2, 4), std::tuple(2, 5), std::tuple(3, 4), std::tuple(3, 5),
};

constexpr std::array<Vector3, 20> UNIT_DODECAHEDRON_VERTEXES = {
    Vector3(1.0, 1.0, 1.0),        Vector3(1.0, 1.0, -1.0),
    Vector3(1.0, -1.0, 1.0),       Vector3(1.0, -1.0, -1.0),
    Vector3(-1.0, 1.0, 1.0),       Vector3(-1.0, 1.0, -1.0),
    Vector3(-1.0, -1.0, 1.0),      Vector3(-1.0, -1.0, -1.0),
    Vector3(0.0, 1.0 / PHI, PHI),  Vector3(0.0, 1.0 / PHI, -PHI),
    Vector3(0.0, -1.0 / PHI, PHI), Vector3(0.0, -1.0 / PHI, -PHI),
    Vector3(1.0 / PHI, PHI, 0.0),  Vector3(1.0 / PHI, -PHI, 0.0),
    Vector3(-1.0 / PHI, PHI, 0.0), Vector3(-1.0 / PHI, -PHI, 0.0),
    Vector3(PHI, 0.0, 1.0 / PHI),  Vector3(PHI, 0.0, -1.0 / PHI),
    Vector3(-PHI, 0.0, 1.0 / PHI), Vector3(-PHI, 0.0, -1.0 / PHI)};
constexpr std::array<std::tuple<uint64_t, uint64_t>, 30> DODECAHEDRON_EDGES = {
    std::tuple(0, 8),   std::tuple(0, 12),  std::tuple(0, 16),
    std::tuple(1, 9),   std::tuple(1, 12),  std::tuple(1, 17),
    std::tuple(2, 10),  std::tuple(2, 13),  std::tuple(2, 16),
    std::tuple(3, 11),  std::tuple(3, 13),  std::tuple(3, 17),
    std::tuple(4, 8),   std::tuple(4, 14),  std::tuple(4, 18),
    std::tuple(5, 9),   std::tuple(5, 14),  std::tuple(5, 19),
    std::tuple(6, 10),  std::tuple(6, 15),  std::tuple(6, 18),
    std::tuple(7, 11),  std::tuple(7, 15),  std::tuple(7, 19),
    std::tuple(8, 10),  std::tuple(9, 11),  std::tuple(12, 14),
    std::tuple(13, 15), std::tuple(16, 17), std::tuple(18, 19),
};

constexpr std::array<Vector3, 12> UNIT_ICOSAHEDRON_VERTEXES = {
    Vector3(0.0, 1.0, PHI),  Vector3(0.0, 1.0, -PHI),
    Vector3(0.0, -1.0, PHI), Vector3(0.0, -1.0, -PHI),
    Vector3(1.0, PHI, 0.0),  Vector3(1.0, -PHI, 0.0),
    Vector3(-1.0, PHI, 0.0), Vector3(-1.0, -PHI, 0.0),
    Vector3(PHI, 0.0, 1.0),  Vector3(PHI, 0.0, -1.0),
    Vector3(-PHI, 0.0, 1.0), Vector3(-PHI, 0.0, -1.0)};
constexpr std::array<std::tuple<uint64_t, uint64_t>, 30> ICOSAHEDRON_EDGES = {
    std::tuple(0, 2),  std::tuple(0, 4),  std::tuple(0, 6),  std::tuple(0, 8),
    std::tuple(0, 10), std::tuple(1, 3),  std::tuple(1, 4),  std::tuple(1, 6),
    std::tuple(1, 9),  std::tuple(1, 11), std::tuple(2, 5),  std::tuple(2, 7),
    std::tuple(2, 8),  std::tuple(2, 10), std::tuple(3, 5),  std::tuple(3, 7),
    std::tuple(3, 9),  std::tuple(3, 11), std::tuple(4, 6),  std::tuple(4, 8),
    std::tuple(4, 9),  std::tuple(5, 7),  std::tuple(5, 8),  std::tuple(5, 9),
    std::tuple(6, 10), std::tuple(6, 11), std::tuple(7, 10), std::tuple(7, 11),
    std::tuple(8, 9),  std::tuple(10, 1),
};

struct Polyhedron {
 private:
  std::vector<Vector3> _vertexes;
  std::vector<std::tuple<uint64_t, uint64_t>> _edges;
  Vector3 _position;

 public:
  /* constructors */

  // default constructor
  constexpr Polyhedron() noexcept = default;

  // copy constructor
  constexpr Polyhedron(const Polyhedron& other) noexcept
      : _vertexes(other._vertexes),
        _edges(other._edges),
        _position(other._position) {}

  // copy assignment constructor
  constexpr Polyhedron& operator=(this Polyhedron& lhs,
                                  const Polyhedron& rhs) noexcept {
    if (&rhs != &lhs) {
      lhs._vertexes = rhs._vertexes;
      lhs._edges = rhs._edges;
      lhs._position = rhs._position;
    }
    return lhs;
  }

  // move constructor
  constexpr Polyhedron(Polyhedron&& other) noexcept
      : _vertexes(std::move(other._vertexes)),
        _edges(std::move(other._edges)),
        _position(std::move(other._position)) {}

  // move assignment constructor
  constexpr Polyhedron& operator=(this Polyhedron& lhs,
                                  Polyhedron&& rhs) noexcept {
    if (&rhs != &lhs) {
      lhs._vertexes = std::move(rhs._vertexes);
      lhs._edges = std::move(rhs._edges);
      lhs._position = std::move(rhs._position);
    }
    return lhs;
  }

  explicit constexpr Polyhedron(
      std::vector<Vector3> vertexes,
      std::vector<std::tuple<uint64_t, uint64_t>> edges,
      Vector3 position) noexcept
      : _vertexes(std::move(vertexes)),
        _edges(std::move(edges)),
        _position(std::move(position)) {}

  template <size_t VertexCount, size_t EdgeCount>
  explicit constexpr Polyhedron(
      std::array<Vector3, VertexCount> vertexes,
      std::array<std::tuple<uint64_t, uint64_t>, EdgeCount> edges,
      Vector3 position) noexcept
      : _vertexes(std::vector(vertexes.begin(), vertexes.end())),
        _edges(std::vector(edges.begin(), edges.end())),
        _position(position) {}

  /* destructors */

  ~Polyhedron() = default;

  /* getters */

  constexpr auto vertexes(this const Polyhedron& self) noexcept
      -> std::span<const Vector3> {
    return self._vertexes;
  }

  constexpr auto edges(this const Polyhedron& self) noexcept
      -> std::span<const std::tuple<uint64_t, uint64_t>> {
    return self._edges;
  }

  constexpr auto position(this const Polyhedron& self) noexcept
      -> const Vector3& {
    return self._position;
  }

  /* mutators */

  constexpr auto scale(this Polyhedron& self, const double& scale) noexcept {
    for (auto& vertex : self._vertexes)
      vertex *= scale;
  }

  constexpr auto translate(this Polyhedron& self,
                           const Vector3& translation) noexcept {
    self._position += translation;
    for (auto& vertex : self._vertexes)
      vertex += translation;
  }

  constexpr auto rotate(this Polyhedron& self, const Quaternion& rotation,
                        const Vector3& center_of_rotation) {
    self._position = rotate_point_about_another(rotation, self._position,
                                                center_of_rotation);

    for (auto& vertex : self._vertexes)
      vertex = rotate_point_about_another(rotation, vertex, center_of_rotation);
  }

  /* factories */

  // unit

  static auto cube() noexcept -> Polyhedron {
    return Polyhedron(UNIT_CUBE_VERTEXES, CUBE_EDGES, Vector3::ZERO());
  }
  static auto tetrahedron() noexcept -> Polyhedron {
    return Polyhedron(UNIT_TETRAHEDRON_VERTEXES, TETRAHEDRON_EDGES,
                      Vector3::ZERO());
  }
  static auto octahedron() noexcept -> Polyhedron {
    return Polyhedron(UNIT_OCTAHEDRON_VERTEXES, OCTAHEDRON_EDGES,
                      Vector3::ZERO());
  }
  static auto dodecahedron() noexcept -> Polyhedron {
    return Polyhedron(UNIT_DODECAHEDRON_VERTEXES, DODECAHEDRON_EDGES,
                      Vector3::ZERO());
  }
  static auto icosahedron() noexcept -> Polyhedron {
    return Polyhedron(UNIT_ICOSAHEDRON_VERTEXES, ICOSAHEDRON_EDGES,
                      Vector3::ZERO());
  }

  // scale and translate
  static auto cube(const double& scale, const Vector3& position) noexcept
      -> Polyhedron {
    auto cube = Polyhedron::cube();
    cube.scale(scale);
    cube.translate(position);
    return cube;
  }
  static auto tetrahedron(const double& scale, const Vector3& position) noexcept
      -> Polyhedron {
    auto tetrahedron = Polyhedron::tetrahedron();
    tetrahedron.scale(scale);
    tetrahedron.translate(position);
    return tetrahedron;
  }
  static auto octahedron(const double& scale, const Vector3& position) noexcept
      -> Polyhedron {
    auto octahedron = Polyhedron::octahedron();
    octahedron.scale(scale);
    octahedron.translate(position);
    return octahedron;
  }
  static auto dodecahedron(const double& scale,
                           const Vector3& position) noexcept -> Polyhedron {
    auto dodecahedron = Polyhedron::dodecahedron();
    dodecahedron.scale(scale);
    dodecahedron.translate(position);
    return dodecahedron;
  }
  static auto icosahedron(const double& scale, const Vector3& position) noexcept
      -> Polyhedron {
    auto icosahedron = Polyhedron::icosahedron();
    icosahedron.scale(scale);
    icosahedron.translate(position);
    return icosahedron;
  }
};
