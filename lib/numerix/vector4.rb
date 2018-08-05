module Numerix

  ##
  # A structure encapsulating four single precision floating point values.
  class Vector4 < VectorBase

    ##
    # @return [Float] the X component of the vector.
    attr_accessor :x

    ##
    # @return [Float] the Y component of the vector.
    attr_accessor :y

    ##
    # @return [Float] the Z component of the vector.
    attr_accessor :z

    ##
    # @return [Float] the W component of the vector.
    attr_accessor :w

    ##
    # @overload initialize
    #   Creates a Vector with the default values of `0.0`.
    #
    # @overload initialize(xyzw)
    #   Creates a Vector with each component set to a single value.
    #
    #   @param xyzw [Float] The value to set for all components.
    #
    # @overload initialize(x, y, z, w)
    #   Creates a Vector with the specified values.
    #
    #   @param x [Float] The X component of the vector.
    #   @param y [Float] The Y component of the vector.
    #   @param z [Float] The Z component of the vector.
    #   @param w [Float] The W component of the vector.
    #
    # @overload initialize(xyz, w)
    #   Creates a Vector with the specified values.
    #
    #   @param xyz [Vector3] Vector3 to use for the X, Y, and Z components.
    #   @param w [Float] The W component of the vector.
    #
    # @overload initialize(xy, zw)
    #   Creates a Vector with the specified values.
    #
    #   @param xy [Vector2] Vector2 to use for the X and Y components.
    #   @param zw [Vector2] Vector2 to use for the Z and W components.
    #
    # @overload initialize(xy, z, w)
    #   Creates a Vector with the specified values.
    #
    #   @param xy [Vector2] Vector2 to use for the X and Y components.
    #   @param z [Float] The Z component of the vector.
    #   @param w [Float] The W component of the vector.
    #
    def initialize(*args)
    end

    ##
    # @return [Float] the length of the vector.
    def length
    end

    alias_method :magnitude, :length

    ##
    # @return [Float] the length of the vector squared.
    def length_squared
    end

    ##
    # @return [Boolean] flag indicating if all values of the vector are equal
    #   to `1.0`.
    def one?
    end

    ##
    # @return [Boolean] flag indicating if all values of the vector are equal
    #   to `0.0`.
    def zero?
    end

    ##
    # @return [Float] the lowest value of the vector's components.
    def min_value
    end

    ##
    # @return [Float] the greatest value of the vector's components.
    def max_value
    end

    ##
    # Returns the Euclidean distance between this vector and another.
    #
    # @param vector [Vector4] The point to get distance between.
    #
    # @return [Float] the distance.
    def distance(vector)
    end

    # Returns the squared Euclidean distance between this vector and another.
    #
    # @param vector [Vector4] The point to get distance between.
    #
    # @return [Float] the distance squared.
    def distance_squared(vector)
    end

    ##
    # Returns a new vector with the same direction as the given vector, but with
    # a length of `1.0`.
    #
    # @return [Vector4] a normalized vector.
    def normalize
    end

    ##
    # Alters this vector instance to maintain same direction, but adjust values
    # so that vector has a length of `1.0`.
    #
    # @return [self]
    def normalize!
    end

    ##
    # Linearly interpolates between this vector and another based on the given
    # weighting.
    #
    # @param vector [Vector4] The source vector to interpolate between.
    # @param amount [Float] Value between `0.0` and `1.0` indicating the weight
    #   of the given vector.
    #
    # @return [Vector4] the interpolated vector.
    #
    # @see lerp!
    def lerp(vector, amount)
    end

    ##
    # Linearly interpolates between this vector and another based on the given
    # weighting, altering the values of this vector.
    #
    # @param vector [Vector4] The source vector to interpolate between.
    # @param amount [Float] Value between `0.0` and `1.0` indicating the weight
    #   of the given vector.
    #
    # @return [self]
    #
    # @see lerp
    def lerp!(vector, amount)
    end

    ##
    # Returns a new vector by applying a transformation.
    #
    # @overload transform(matrix)
    #   Transforms this vector by the given matrix.
    #
    #   @param matrix [Matrix4x4] the transformation matrix.
    #
    # @overload transform(rotation)
    #   Transforms this vector by the specified rotation value.
    #
    #   @param rotation [Quaternion] The rotation to apply.
    #
    # @return [Vector4] new transformed vector.
    #
    # @see transform!
    def transform(other)
    end

    ##
    # Transforms this vector.
    #
    # @overload transform(matrix)
    #   Transforms this vector by the given matrix.
    #
    #   @param matrix [Matrix4x4] the transformation matrix.
    #
    # @overload transform(rotation)
    #   Transforms this vector by the specified rotation value.
    #
    #   @param rotation [Quaternion] The rotation to apply.
    #
    # @return [self]
    #
    # @see transform
    def transform!(other)
    end

    # @return [Vector4] a vector whose elements are the absolute values of each
    #   of this vector's elements.
    def abs
    end

    # @return [Vector4] a vector whose elements are the square root of each of
    #   this vector's elements.
    def sqrt
    end

    ##
    # Returns the dot product of this vector and another.
    #
    # @param other [Vector4] the source vector to compute dot product of.
    #
    # @return [Float] the dot product.
    def dot(other)
    end

    ##
    # Returns a vector that is result of clamping this vector between the
    # specified minimum and maximum values.
    #
    # @overload clamp(min, max)
    #   Clamps the vector's components between the specified values.
    #
    #   @param min [Float] The minimum value.
    #   @param max [Float] The maximum value.
    #
    # @overload clamp(min, max)
    #   Clamps the vector's on a component-wise basis between the minimum and
    #   maximum values of the specified vectors.
    #
    #   @param min [Vector4] The minimum value.
    #   @param max [Vector4] The maximum value.
    #
    # @return [Vector4] the result of clamping this vector.
    #
    # @see clamp!
    def clamp(min, max)
    end

    ##
    # Clamps this vector between the specified minimum and maximum values.
    #
    # @overload clamp!(min, max)
    #   Clamps the vector's components between the specified values.
    #
    #   @param min [Float] The minimum value.
    #   @param max [Float] The maximum value.
    #
    # @overload clamp!(min, max)
    #   Clamps the vector's on a component-wise basis between the minimum and
    #   maximum values of the specified vectors.
    #
    #   @param min [Vector4] The minimum value.
    #   @param max [Vector4] The maximum value.
    #
    # @return [Vector4]
    #
    # @see clamp
    def clamp!(min, max)
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
    # @return [Quaternion] a {Quaternion} representation of this instance.
    def to_quaternion
    end

    ##
    # @return [Plane] a {Plane} representation of this instance.
    def to_plane
    end

    ##
    # @return [Vector2] a {Vector2} representation of this instance.
    def to_vec2
    end

    ##
    # @return [Vector3] a {Vector3} representation of this instance.
    def to_vec3
    end

    ##
    # Adds this vector with another.
    #
    # @param other [Vector4] The vector to add.
    #
    # @return [Vector4] the sum of the vectors.
    def +(other)
    end

    # Gets the difference of this vector and another.
    #
    # @param other [Vector4] The vector to subtract.
    #
    # @return [Vector4] the difference of the vectors.
    def -(other)
    end

    ##
    # Vector multiplication.
    #
    # @overload *(scalar)
    #   Scalar vector multiplication.
    #
    #   @param scalar [Float] The scalar value.
    #
    # @overload *(other)
    #   Multiplies this vector by another.
    #
    #   @param other [Vector4] The source vector to multiply.
    #
    # @return [Vector4] the product vector.
    def *(other)
    end

    ##
    # Vector division.
    #
    # @overload *(scalar)
    #   Scalar vector division.
    #
    #   @param scalar [Float] The scalar value.
    #
    # @overload *(other)
    #   Divides this vector by another.
    #
    #   @param other [Vector4] The source vector to divide.
    #
    # @return [Vector4] the resulting vector.
    def /(other)
    end

    ##
    # Returns flag if this vector instance is equal to the given object.
    #
    # @param other [Object] The object to compare.
    #
    # @return [Boolean] `true` if objects are equal, otherwise `false`.
    def ==(other)
    end

    ##
    # Performs unary negation on this vector instance.
    #
    # @return [Vector4] the vector with swapped +/- values.
    def -@
    end

    class << self

      ##
      # @return [Vector4] the vector `<0.0, 0.0, 0.0, 0.0>`.
      def zero
      end

      ##
      # @return [Vector4] the vector `<1.0, 1.0, 1.0, 1.0>`.
      def one
      end

      ##
      # @return [Vector4] the vector `<1.0, 0.0, 0.0, 0.0>`.
      def unit_x
      end

      ##
      # @return [Vector4] the vector `<0.0, 1.0, 0.0, 0.0>`.
      def unit_y
      end

      ##
      # @return [Vector4] the vector `<0.0, 0.0, 1.0, 0.0>`.
      def unit_z
      end

      ##
      # @return [Vector4] the vector `<0.0, 0.0, 0.0, 1.0>`.
      def unit_w
      end

      ##
      # Creates and returns a normalized vector from the specified components.
      #
      # This is more efficient than creating and then normalizing.
      #
      # @param x [Float] The X component of the vector.
      # @param y [Float] The Y component of the vector.
      # @param z [Float] The Z component of the vector.
      # @param w [Float] The W component of the vector.
      #
      # @return [Vector4] the newly created normalized vector.
      def create_norm(x, y, z, w)
      end

      ##
      # Returns a vector that is result of clamping a vector between the
      # specified minimum and maximum values.
      #
      # @overload clamp(min, max)
      #   Clamps the vector's components between the specified values.
      #
      #   @param min [Float] The minimum value.
      #   @param max [Float] The maximum value.
      #
      # @overload clamp(min, max)
      #   Clamps the vector's on a component-wise basis between the minimum and
      #   maximum values of the specified vectors.
      #
      #   @param min [Vector4] The minimum value.
      #   @param max [Vector4] The maximum value.
      #
      # @return [Vector4] the result of clamping this vector.
      def clamp(vector, min, max)
      end

      ##
      # Linearly interpolates between two vectors based on the given weighting.
      #
      # @param vector1 [Vector4] The first source vector.
      # @param vector2 [Vector4] The second source vector.
      # @param amount [Float] Value between `0.0` and `1.0` indicating the
      #   weight of the second source vector.
      #
      # @return [Vector4] the interpolated vector.
      def lerp(vector1, vector2, amount)
      end

      ##
      # Creates a Vector4 by transforming the specified vector and 
      # transformation matrix or quaternion rotation.
      #
      # @overload transform(vector, matrix)
      #   Transforms a vector by the given matrix.
      #
      #   @param vector [Vector2, Vector3, Vector4] The source vector.
      #   @param matrix [Matrix4x4] The transformation matrix.
      #
      #   @return [Vector4] A transformed vector.
      #
      # @overload transform(vector, rotation)
      #   Transforms a vector by the given Quaternion rotation value.
      #
      #   @param vector [Vector2, Vector3, Vector4] The source vector to rotate.
      #   @param rotation [Quaternion] The rotation to apply.
      #
      #   @return [Vector4] A rotated vector.
      def transform(vector, other)
      end

      ##
      # Returns a vector with a minimum set of values.
      #
      # @overload min(vector, other)
      #   Returns a vector whose elements are the minimum of each of the pairs
      #   of elements in the two source vectors.
      #
      #   @param vector [Vector4] The first source vector.
      #   @param other [Vector4] The second source vector.
      #
      # @overload min(vector, value)
      #   Returns a vector whose elements are the minimum of each of vector
      #   element and the specified value.
      #
      #   @param vector [Vector4] The source vector.
      #   @param value [Float] The minimum value.
      #
      # @return [Vector4] the minimized vector.
      def min(vector, other)
      end

      ##
      # Returns a vector with a maximum set of values.
      #
      # @overload max(vector, other)
      #   Returns a vector whose elements are the maximum of each of the pairs
      #   of elements in the two source vectors.
      #
      #   @param vector [Vector4] The first source vector.
      #   @param other [Vector4] The second source vector.
      #
      # @overload max(vector, value)
      #   Returns a vector whose elements are the maximum of each of vector
      #   element and the specified value.
      #
      #   @param vector [Vector4] The source vector.
      #   @param value [Float] The maximum value.
      #
      # @return [Vector4] the maximized vector.
      def max(vector, other)
      end
    end
  end
end
