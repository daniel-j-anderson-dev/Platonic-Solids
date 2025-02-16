#pragma once
#include <cmath>
#include <utility>

constexpr auto EPSILON = 1e-6;

struct Vector2 {
 public:
  double x;
  double y;

  /* constructors */

  // default constructor
  constexpr Vector2() noexcept : x(0.0), y(0.0) {}

  // copy constructor
  constexpr Vector2(const Vector2& other) noexcept : x(other.x), y(other.y) {}

  // copy assignment constructor
  constexpr Vector2& operator=(this Vector2& lhs, const Vector2& rhs) noexcept {
    if (&rhs != &lhs) {
      lhs.x = rhs.x;
      lhs.y = rhs.y;
    }
    return lhs;
  }

  // move constructor
  constexpr Vector2(Vector2&& other) noexcept
      : x(std::move(other.x)), y(std::move(other.y)) {}

  // move assignment constructor
  constexpr Vector2& operator=(this Vector2& lhs, Vector2&& rhs) {
    if (&rhs != &lhs) {
      lhs.x = std::move(rhs.x);
      lhs.y = std::move(rhs.y);
    }
    return lhs;
  }

  explicit constexpr Vector2(double x, double y) noexcept : x(x), y(y) {}

  /* destructors */

  ~Vector2() = default;

  /* factories */

  constexpr static auto ZERO() noexcept -> Vector2 { return Vector2(0.0, 0.0); }

  constexpr static auto X() noexcept -> Vector2 { return Vector2(1.0, 0.0); }

  constexpr static auto Y() noexcept -> Vector2 { return Vector2(0.0, 1.0); }

  constexpr static auto from_components(double x, double y) noexcept
      -> Vector2 {
    return Vector2(x, y);
  }

  // operators

  constexpr auto operator==(this const Vector2& lhs,
                            const Vector2& rhs) noexcept -> bool {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }

  constexpr auto operator+(this const Vector2& lhs, const Vector2& rhs) noexcept
      -> Vector2 {
    return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
  }

  constexpr auto operator-(this const Vector2& self) noexcept -> Vector2 {
    return self * -1.0;
  }
  constexpr auto operator-(this const Vector2& lhs, const Vector2& rhs) noexcept
      -> Vector2 {
    return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
  }

  constexpr auto operator*(this const Vector2& lhs, const Vector2& rhs) noexcept
      -> double {
    return lhs.dot_product(rhs);
  }

  constexpr auto operator*(this const Vector2& lhs, double scalar) noexcept
      -> Vector2 {
    return Vector2(lhs.x * scalar, lhs.y * scalar);
  }

  constexpr auto operator/(this const Vector2& lhs, double scalar) -> Vector2 {
    return Vector2(lhs.x / scalar, lhs.y / scalar);
  }

  constexpr auto operator+=(this Vector2& lhs, const Vector2& rhs) noexcept
      -> Vector2& {
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
  }

  constexpr auto operator-=(this Vector2& lhs, const Vector2& rhs) noexcept
      -> Vector2& {
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs;
  }

  constexpr auto operator*=(this Vector2& lhs, double scalar) noexcept
      -> Vector2& {
    lhs.x *= scalar;
    lhs.y *= scalar;
    return lhs;
  }

  constexpr auto operator/=(this Vector2& lhs, double scalar) -> Vector2& {
    lhs.x /= scalar;
    lhs.y /= scalar;
    return lhs;
  }

  /* getters */

  constexpr auto dot_product(this const Vector2& lhs,
                             const Vector2& rhs) noexcept -> double {
    return (lhs.x * rhs.x) + (lhs.y * rhs.y);
  }
  constexpr auto norm_squared(this const Vector2& self) noexcept -> double {
    return self.dot_product(self);
  }
  constexpr auto norm(this const Vector2& self) noexcept -> double {
    return sqrt(self.norm_squared());
  }

  /// Safety: Ensure norm is non-zero!!!
  constexpr auto normalized(this const Vector2& self) -> Vector2 {
    return self / self.norm();
  }
  constexpr auto normalized_or_zero(this const Vector2& self) -> Vector2 {
    auto norm = self.norm();
    if (norm < EPSILON) {
      return Vector2::ZERO();
    }
    return self / norm;
  }
};

constexpr auto distance(const Vector2& start, const Vector2& end) -> double {
  return (end - start).norm();
}
