module Numerix

  ##
  # A structure encapsulating a four-dimensional vector (x,y,z,w), which is used
  # to efficiently rotate an object about the (x,y,z) vector by the angle theta,
  # where `w = cos(theta / 2)`.
  class Quaternion < Structure

    ##
    # @return [Float] the X-value of the quaternion component of the quaternion.
    attr_accessor :x

    ##
    # @return [Float] the Y-value of the quaternion component of the quaternion.
    attr_accessor :y

    ##
    # @return [Float] the Z-value of the quaternion component of the quaternion.
    attr_accessor :z

    ##
    # @return [Float] the rotation component of the quaternion.
    attr_accessor :w

    ##
    # @overload initialize
    #   Constructs a default quaternion with all components set to `0.0`.
    #
    # @overload initialize(x, y, z, w)
    #   Constructs a Quaternion from the given components.
    #
    #   @param x [Float] The X component of the quaternion.
    #   @param y [Float] The Y component of the quaternion.
    #   @param z [Float] The Z component of the quaternion.
    #   @param w [Float] The W component of the quaternion.
    #
    # @overload initialize(vector, scalar)
    #   Constructs a Quaternion from the given vector and rotation parts.
    #
    #   @param vector [Vector3] The vector part of the quaternion.
    #   @param scalar [Float] The rotation part of the quaternion.
    #
    def initialize(*args) # TODO
    end

    ##
    # @return [Boolean] `true` if the quaternion is the identity quaternion,
    #   otherwise `false`.
    def identity?
    end

    ##
    # @return [Float] the length of the quaternion.
    def length
    end

    alias_method :magnitude, :length

    ##
    # @return [Float] the length of the quaternion squared.
    def length_squared
    end

    ##
    # Returns a new quaternion with the same direction as the given quaternion,
    # but with a length of `1.0`.
    #
    # @return [Quaternion] a normalized quaternion.
    def normalize
    end

    ##
    # Alters this quaternion instance to maintain same direction, but adjust
    # values so that quaternion has a length of `1.0`.
    #
    # @return [self]
    def normalize!
    end

    ##
    # Creates the conjugate of this quaternion.
    #
    # @return [Quaternion] the conjugate of the os instance.
    #
    # @see conjugate!
    def conjugate
    end

    ##
    # Alters this instance to be its conjugate.
    #
    # @return [self]
    #
    # @see conjugate
    def conjugate!
    end

    ##
    # @return [Quaternion] the inverse of this quaternion.
    def inverse
    end

    ##
    # Calculates the dot product of two quaternions.
    #
    # @param other [Quaternion] The source quaternion to compute product from.
    #
    # @return [Float] the dot product of the quaternions.
    def dot(other)
    end

    ##
    # Concatenates this quaternion and another, the result represents the this
    # rotation followed by the given quaternion's rotation.
    #
    # @param other [Quaternion] The rotation to add in the series.
    #
    # @return [Quaternion] a new quaternion representing the concatenation this
    #   rotation followed by the other rotation.
    #
    # @see concatenate!
    def concatenate(other)
    end

    ##
    # @note This function is identical to {#concatenate}, but alters the values
    #   of this instance without creating a new object.
    #
    # Concatenates this quaternion and another, the result represents the this
    # rotation followed by the given quaternion's rotation.
    #
    # @param other [Quaternion] The rotation to add in the series.
    #
    # @return [self]
    #
    # @see concatenate
    def concatenate!(other)
    end

    ##
    # Linearly interpolates between this quaternion and another based on the
    # given weighting.
    #
    # @param quaternion [Quaternion] The source quaternion to interpolate
    #   between.
    # @param amount [Float] Value between `0.0` and `1.0` indicating the weight
    #   of the given quaternion.
    #
    # @return [Quaternion] the interpolated quaternion.
    #
    # @see lerp!
    def lerp(quaternion, amount)
    end

    ##
    # Linearly interpolates between this quaternion and another based on the given
    # weighting, altering the values of this quaternion.
    #
    # @param quaternion [Quaternion] The source quaternion to interpolate between.
    # @param amount [Float] Value between `0.0` and `1.0` indicating the weight
    #   of the given quaternion.
    #
    # @return [self]
    #
    # @see lerp
    def lerp!(quaternion, amount)
    end

    ##
    # Interpolates between this quaternion and another using spherical linear
    # interpolation.
    #
    # @param quaternion [Quaternion] The source quaternion to interpolate between.
    # @param amount [Float] Value between `0.0` and `1.0` indicating the weight
    #   of the given quaternion.
    #
    # @return [Quaternion] the interpolated quaternion.
    #
    # @see slerp!
    def slerp(quaternion, amount)
    end

    ##
    # @note This function is identical to {#slerp}, but alters the values of
    #   this instance without creating a new object.
    #
    # Interpolates between this quaternion and another using spherical linear
    # interpolation.
    #
    # @param quaternion [Quaternion] The source quaternion to interpolate between.
    # @param amount [Float] Value between `0.0` and `1.0` indicating the weight
    #   of the given quaternion.
    #
    # @return [self]
    #
    # @see slerp
    def slerp!(quaternion, amount)
    end

    ##
    # @return [String] a String representation of this instance.
    def to_s
    end

    ##
    # @return [Array<Float>] an Array representation of this instance.
    def to_a
    end

    alias_method :elements, :to_a

    ##
    # @return [Hash{Symbol => Float}] a Hash representation of this instance.
    def to_h
    end

    ##
    # @return [Vector4] a {Vector4} representation of this instance.
    def to_vec4
    end

    ##
    # Performs unary negation on this quaternion instance.
    #
    # @return [Quaternion] the vector with swapped +/- values.
    def -@
    end

    ##
    # Adds this quaternion with another.
    #
    # @param other [Quaternion] The quaternion to add.
    #
    # @return [Quaternion] the sum of the quaternions.
    def +(other)
    end

    # Gets the difference of this quaternion and another.
    #
    # @param other [Quaternion] The quaternion to subtract.
    #
    # @return [Quaternion] the difference of the quaternions.
    def -(other)
    end

    ##
    # Quaternion multiplication.
    #
    # @overload *(scalar)
    #   Scalar quaternion multiplication.
    #
    #   @param scalar [Float] The scalar value.
    #
    # @overload *(other)
    #   Multiplies this quaternion by another.
    #
    #   @param other [Quaternion] The source quaternion to multiply.
    #
    # @return [Quaternion] the product quaternion.
    def *(other)
    end

    ##
    # Quaternion division.
    #
    # @overload *(scalar)
    #   Scalar quaternion division.
    #
    #   @param scalar [Float] The scalar value.
    #
    # @overload *(other)
    #   Divides this quaternion by another.
    #
    #   @param other [Quaternion] The source quaternion to divide.
    #
    # @return [Quaternion] the resulting quaternion.
    def /(other)
    end

    ##
    # Returns flag if this quaternion instance is equal to the given object.
    #
    # @param other [Object] The object to compare.
    #
    # @return [Boolean] `true` if objects are equal, otherwise `false`.
    def ==(other)
    end

    class << self

      ##
      # @return [Quaternion] a quaternion representing no rotation.
      def identity
      end

      ##
      # Creates a quaternion from a vector and an angle to rotate about the
      # vector.
      #
      # @param axis [Vector3] The vector to rotate around.
      # @param angle [Float] The angle, in radians, to rotate around the vector.
      #
      # @return [Quaternion] the created quaternion.
      def from_axis_angle(axis, angle)
      end

      ##
      # Creates a new quaternion from the given yaw, pitch, and roll, in
      # radians.
      #
      # @param yaw [Float] The yaw angle, in radians, around the Y-axis.
      # @param pitch [Float] The pitch angle, in radians, around the X-axis.
      # @param roll [Float] The roll angle, in radians, around the Z-axis.
      #
      # @return [Quaternion] the created quaternion.
      def from_yaw_pitch_roll(yaw, pitch, roll)
      end

      ##
      # Creates a quaternion from the given rotation matrix.
      #
      # @param matrix [Matrix4x4] The rotation matrix
      #
      # @return [Quaternion] the created quaternion.
      def from_rotation_matrix(matrix)
      end

      ##
      # Interpolates between two quaternions, using spherical linear
      # interpolation.
      #
      # @param quaternion1 [Quaternion] The first source quaternion.
      # @param quaternion2 [Quaternion] The second source quaternion.
      # @param amount [Float] Value between `0.0` and `1.0` indicating the
      #   weight of the second source quaternion.
      #
      # @return [Quaternion] the interpolated quaternion.
      def slerp(quaternion1, quaternion2, amount)
      end

      ##
      # Linearly interpolates between two quaternions based on the given
      # weighting.
      #
      # @param quaternion1 [Quaternion] The first source quaternion.
      # @param quaternion2 [Quaternion] The second source quaternion.
      # @param amount [Float] Value between `0.0` and `1.0` indicating the
      #   weight of the second source quaternion.
      #
      # @return [Quaternion] the interpolated quaternion.
      def lerp(quaternion1, quaternion2, amount)
      end
    end
  end
end