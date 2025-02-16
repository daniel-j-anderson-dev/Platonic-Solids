#pragma once
#include <array>
#include <cmath>
#include <tuple>
#include <utility>

// #include "vector2.hpp"
#include "vector3.hpp"

struct Quaternion {
 public:
  double x;
  double y;
  double z;
  double w;

  /* constructors */

  // default constructor
  constexpr Quaternion() noexcept : x(0.0), y(0.0), z(0.0), w(0.0) {}

  // copy constructor
  constexpr Quaternion(const Quaternion& other) noexcept
      : w(other.w), x(other.x), y(other.y), z(other.z) {}

  // copy assignment constructor
  constexpr Quaternion& operator=(this Quaternion& lhs,
                                  const Quaternion& rhs) noexcept {
    if (&rhs != &lhs) {
      lhs.w = rhs.w;
      lhs.x = rhs.x;
      lhs.y = rhs.y;
      lhs.z = rhs.z;
    }

    return lhs;
  }

  // move constructor
  constexpr Quaternion(Quaternion&& rhs) noexcept
      : w(std::move(rhs.w)),
        x(std::move(rhs.x)),
        y(std::move(rhs.y)),
        z(std::move(rhs.z)) {}

  // move assignment constructor
  constexpr Quaternion& operator=(this Quaternion& lhs,
                                  Quaternion&& rhs) noexcept {
    if (&rhs != &lhs) {
      lhs.x = std::move(rhs.x);
      lhs.y = std::move(rhs.y);
      lhs.z = std::move(rhs.z);
      lhs.w = std::move(rhs.w);
    }

    return lhs;
  }

  explicit constexpr Quaternion(const Vector3& v) noexcept {
    *this = Quaternion::from_vector3(v);
  }

  explicit Quaternion(const Vector3& axis, double angle) noexcept {
    *this = Quaternion::from_axis_angle(axis, angle);
  }

  explicit constexpr Quaternion(double w, double x, double y, double z) noexcept
      : w(w), x(x), y(y), z(z) {}

  /* destructors */

  ~Quaternion() = default;

  /* getters */

  constexpr auto scalar(this const Quaternion& self) noexcept -> double {
    return self.w;
  }

  constexpr auto vector(this const Quaternion& self) noexcept -> Vector3 {
    return Vector3(self.x, self.y, self.z);
  }

  auto rotation_axis(this const Quaternion& self) noexcept -> Vector3 {
    auto half_angle = acos(self.w);
    auto sin_half_angle = sin(half_angle);
    return self.vector() / sin_half_angle;
  }

  auto angle(this const Quaternion& self) noexcept -> double {
    return acos(self.w) * 2.0;
  }

  auto to_axis_angle(this const Quaternion& self) noexcept
      -> std::tuple<Vector3, double> {
    return std::tuple(self.rotation_axis(), self.angle());
  }

  constexpr auto hamiltonian_product(this const Quaternion& lhs,
                                     const Quaternion& rhs) noexcept
      -> Quaternion {
    return Quaternion(
        lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z,
        lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.w * rhs.y - lhs.x * rhs.z + lhs.y * rhs.w + lhs.z * rhs.x,
        lhs.w * rhs.z + lhs.x * rhs.y - lhs.y * rhs.x + lhs.z * rhs.w);
  }

  constexpr auto euclidean_dot_product(this const Quaternion& lhs,
                                       const Quaternion& rhs) noexcept
      -> double {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
  }

  constexpr auto norm_squared(this const Quaternion& self) noexcept -> double {
    return self.euclidean_dot_product(self);
  }

  constexpr auto norm(this const Quaternion& self) noexcept -> double {
    return sqrt(self.norm_squared());
  }

  constexpr auto conjugate(this const Quaternion& self) noexcept -> Quaternion {
    return Quaternion(self.w, -self.x, -self.y, -self.z);
  }

  /// Safety: Ensure norm is non-zero!!!
  constexpr auto inverse(this const Quaternion& self) -> Quaternion {
    return self.conjugate() / self.norm_squared();
  }

  /// Safety: Ensure norm is non-zero!!!
  constexpr auto normalized(this const Quaternion& self) -> Quaternion {
    return self / self.norm();
  }

  constexpr auto normalized_or_zero(this const Quaternion& self) noexcept
      -> Quaternion {
    auto norm = self.norm();
    if (norm < EPSILON) {
      return Quaternion::ZERO();
    }
    return self / norm;
  }

  /* factories */

  constexpr static auto ZERO() noexcept -> Quaternion {
    return Quaternion(0.0, 0.0, 0.0, 0.0);
  }
  constexpr static auto W() noexcept -> Quaternion {
    return Quaternion(1.0, 0.0, 0.0, 0.0);
  }
  constexpr static auto X() noexcept -> Quaternion {
    return Quaternion(0.0, 1.0, 0.0, 0.0);
  }
  constexpr static auto Y() noexcept -> Quaternion {
    return Quaternion(0.0, 0.0, 1.0, 0.0);
  }
  constexpr static auto Z() noexcept -> Quaternion {
    return Quaternion(0.0, 0.0, 0.0, 1.0);
  }

  constexpr auto x_basis(this const Quaternion& self) noexcept -> Vector3 {
    return Vector3(1 - 2 * self.y * self.y - 2 * self.z * self.z,
                   2 * self.x * self.y + 2 * self.z * self.w,
                   2 * self.x * self.z - 2 * self.y * self.w);
  }
  constexpr auto y_basis(this const Quaternion& self) noexcept -> Vector3 {
    return Vector3(2 * self.x * self.y - 2 * self.z * self.w,
                   1 - 2 * self.x * self.x - 2 * self.z * self.z,
                   2 * self.y * self.z + 2 * self.x * self.w);
  };
  constexpr auto z_basis(this const Quaternion& self) noexcept -> Vector3 {
    return Vector3(2 * self.x * self.z + 2 * self.y * self.w,
                   2 * self.y * self.z - 2 * self.x * self.w,
                   1 - 2 * self.x * self.x - 2 * self.y * self.y);
  };
  constexpr auto basis_vectors(this const Quaternion& self) noexcept
      -> std::array<Vector3, 3> {
    return {self.x_basis(), self.y_basis(), self.z_basis()};
  }

  constexpr auto normalized_or_unit_w(this const Quaternion& self) noexcept
      -> Quaternion {
    auto norm = self.norm();
    if (norm < EPSILON) {
      return Quaternion::W();
    }
    return self / norm;
  }

  static auto from_axis_angle(const Vector3& axis, const double& angle) noexcept
      -> Quaternion {
    if (axis.norm_squared() == 0.0) {
      return Quaternion::W();
    }

    auto half_angle = angle / 2.0;

    auto scalar = cos(half_angle);
    auto vector = axis.normalized() * sin(half_angle);

    return Quaternion(scalar, vector.x, vector.y, vector.z);
  }

  constexpr static auto from_components(double w, double x, double y,
                                        double z) noexcept -> Quaternion {
    return Quaternion(w, x, y, z);
  }

  constexpr static auto from_vector3(Vector3 v) noexcept -> Quaternion {
    return Quaternion::from_components(0.0, v.x, v.y, v.z);
  }

  /* operators */

  constexpr auto operator==(this const Quaternion& lhs,
                            const Quaternion& rhs) noexcept {
    return lhs.w == rhs.w && lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
  }

  constexpr auto operator+(this const Quaternion& lhs,
                           const Quaternion& rhs) noexcept -> Quaternion {
    return Quaternion(lhs.w + rhs.w, lhs.x + rhs.x, lhs.y + rhs.y,
                      lhs.z + rhs.z);
  }

  constexpr auto operator-(this const Quaternion& self) noexcept -> Quaternion {
    return self * -1.0;
  }

  constexpr auto operator-(this const Quaternion& lhs,
                           const Quaternion& rhs) noexcept -> Quaternion {
    return Quaternion(lhs.w - rhs.w, lhs.x - rhs.x, lhs.y - rhs.y,
                      lhs.z - rhs.z);
  }

  constexpr auto operator*(this const Quaternion& lhs,
                           const double& rhs) noexcept -> Quaternion {
    return Quaternion(lhs.w * rhs, lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
  }

  constexpr auto operator/(this const Quaternion& lhs,
                           const double& rhs) noexcept -> Quaternion {
    return Quaternion(lhs.w / rhs, lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
  }

  constexpr auto operator*(this const Quaternion& lhs,
                           const Quaternion& rhs) noexcept -> Quaternion {
    return lhs.hamiltonian_product(rhs);
  }

  constexpr auto operator*=(this Quaternion& lhs,
                            const Quaternion& rhs) noexcept {
    lhs = lhs * rhs;
  }

  constexpr Quaternion& operator/=(this Quaternion& lhs, const double& scalar) {
    lhs.w /= scalar;
    lhs.x /= scalar;
    lhs.y /= scalar;
    lhs.z /= scalar;
    return lhs;
  }
};

constexpr auto rotate_point_about_another(
    const Quaternion& rotation, const Vector3& point,
    const Vector3& center_of_rotation) noexcept -> Vector3 {
  // change reference frame to the center_of_rotation
  auto point_local = Quaternion(point - center_of_rotation);

  // rotate the point
  auto rotated_point_local = rotation * point_local * rotation.inverse();

  // return the reference frame to global
  auto rotated_point_global = rotated_point_local.vector() + center_of_rotation;

  return rotated_point_global;
}
