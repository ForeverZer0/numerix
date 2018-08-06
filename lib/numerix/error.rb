
module Numerix

  ##
  # Size of the internal {Vector2} struct, in bytes.
  SIZEOF_VECTOR2 = SIZEOF_FLOAT * 2

  ##
  # Size of the internal {Vector3} struct, in bytes.
  SIZEOF_VECTOR3 = SIZEOF_FLOAT * 3

  ##
  # Size of the internal {Vector4} struct, in bytes.
  SIZEOF_VECTOR4 = SIZEOF_FLOAT * 4

  ##
  # Size of the internal {Matrix3x2} struct, in bytes.
  SIZEOF_MATRIX3X2 = SIZEOF_FLOAT * 6

  ##
  # Size of the internal {Matrix4x4} struct, in bytes.
  SIZEOF_MATRIX4X4 = SIZEOF_FLOAT * 16

  ##
  # Size of the internal {Plane} struct, in bytes.
  SIZEOF_PLANE = SIZEOF_FLOAT * 4

  ##
  # Size of the internal {Quaternion} struct, in bytes.
  SIZEOF_QUATERNION = SIZEOF_FLOAT * 4

  ##
  # Exception class for Numerix specific errors.
  class NumerixError < StandardError
  end
end