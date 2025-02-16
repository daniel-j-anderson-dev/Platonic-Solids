#pragma once

enum RotationKind {
  /// rotates entties relative to their position
  AboutEntityPosition,

  /// rotates entties relative to world origin but doesn't rotate world axes
  AboutOrigin,

  /// rotates the world axes and the entties
  Universal,
};
