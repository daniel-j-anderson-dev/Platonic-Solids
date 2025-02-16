#pragma once
#include <cmath>
#include <utility>

#include "vector2.hpp"

struct Vector3 {
 public:
  double x;
  double y;
  double z;

  /* constructors */

  // default constructor
  constexpr Vector3() noexcept : x(0.0), y(0.0), z(0.0) {}

  // copy constructor
  constexpr Vector3(const Vector3& other) noexcept
      : x(other.x), y(other.y), z(other.z) {}

  // copy assignment constructor
  constexpr Vector3& operator=(this Vector3& lhs, const Vector3& rhs) noexcept {
    if (&rhs != &lhs) {
      lhs.x = rhs.x;
      lhs.y = rhs.y;
      lhs.z = rhs.z;
    }
    return lhs;
  }

  // move constructor
  constexpr Vector3(Vector3&& other) noexcept
      : x(std::move(other.x)), y(std::move(other.y)), z(std::move(other.z)) {}

  // move assignment constructor
  constexpr Vector3& operator=(this Vector3& lhs, Vector3&& rhs) {
    if (&rhs != &lhs) {
      lhs.x = std::move(rhs.x);
      lhs.y = std::move(rhs.y);
      lhs.z = std::move(rhs.z);
    }
    return lhs;
  }

  explicit constexpr Vector3(double x, double y, double z) noexcept
      : x(x), y(y), z(z) {}

  explicit constexpr Vector3(Vector2 v) noexcept : x(v.x), y(v.y), z(0.0) {}

  /* destructors */

  ~Vector3() = default;

  /* factories */

  constexpr static auto ZERO() noexcept -> Vector3 {
    return Vector3(0.0, 0.0, 0.0);
  }

  constexpr static auto X() noexcept -> Vector3 {
    return Vector3(1.0, 0.0, 0.0);
  }

  constexpr static auto Y() noexcept -> Vector3 {
    return Vector3(0.0, 1.0, 0.0);
  }

  constexpr static auto Z() noexcept -> Vector3 {
    return Vector3(0.0, 0.0, 1.0);
  }

  constexpr static auto from_components(double x, double y, double z) noexcept
      -> Vector3 {
    return Vector3(x, y, z);
  }

  // operators

  constexpr auto operator==(this const Vector3& lhs,
                            const Vector3& other) noexcept -> bool {
    return lhs.x == other.x && lhs.y == other.y && lhs.z == other.z;
  }

  constexpr auto operator+(this const Vector3& lhs, const Vector3& rhs) noexcept
      -> Vector3 {
    return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
  }

  constexpr auto operator-(this const Vector3& self) noexcept -> Vector3 {
    return self * -1.0;
  }

  constexpr auto operator-(this const Vector3& lhs, const Vector3& rhs) noexcept
      -> Vector3 {
    return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
  }

  constexpr auto operator*(this const Vector3& lhs, const Vector3& rhs) noexcept
      -> double {
    return lhs.dot_product(rhs);
  }

  constexpr auto operator*(this const Vector3& lhs, double scalar) noexcept
      -> Vector3 {
    return Vector3(lhs.x * scalar, lhs.y * scalar, lhs.z * scalar);
  }

  constexpr auto operator/(this const Vector3& lhs, double rhs) -> Vector3 {
    return Vector3(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
  }

  constexpr auto operator+=(this Vector3& lhs, const Vector3& rhs) noexcept
      -> Vector3& {
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    lhs.z += rhs.z;
    return lhs;
  }

  constexpr auto operator-=(this Vector3& lhs, const Vector3& rhs) noexcept
      -> Vector3& {
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    lhs.z -= rhs.z;
    return lhs;
  }

  constexpr auto operator*=(this Vector3& lhs, double rhs) noexcept
      -> Vector3& {
    lhs.x *= rhs;
    lhs.y *= rhs;
    lhs.z *= rhs;
    return lhs;
  }

  constexpr auto operator/=(this Vector3& lhs, double rhs) -> Vector3& {
    lhs.x /= rhs;
    lhs.y /= rhs;
    lhs.z /= rhs;
    return lhs;
  }

  /* getters */

  constexpr auto xy(this const Vector3& self) noexcept -> Vector2 {
    return Vector2(self.x, self.y);
  }

  constexpr auto dot_product(this const Vector3& lhs,
                             const Vector3& rhs) noexcept -> double {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
  }
  constexpr auto norm_squared(this const Vector3& self) noexcept -> double {
    return self.dot_product(self);
  }
  constexpr auto norm(this const Vector3& self) noexcept -> double {
    return sqrt(self.norm_squared());
  }

  /// Safety: Ensure norm is non-zero!!!
  constexpr auto normalized(this const Vector3& self) -> Vector3 {
    return self / self.norm();
  }
  constexpr auto normalized_or_zero(this const Vector3& self) -> Vector3 {
    auto norm = self.norm();
    if (norm < EPSILON) {
      return Vector3::ZERO();
    }
    return self / norm;
  }
};

constexpr auto distance(const Vector3& u, const Vector3& v) -> double {
  return (v - u).norm();
}
