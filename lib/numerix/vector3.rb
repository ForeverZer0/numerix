module Numerix

  ##
  # A structure encapsulating three single precision floating point values.
  class Vector3 < VectorBase

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
    # @overload initialize
    #   Creates a Vector with the default values of `0.0`.
    #
    # @overload initialize(xyz)
    #   Creates a Vector with each component set to a single value.
    #
    #   @param xyz [Float] The value to set for all components.
    #
    # @overload initialize(x, y, z)
    #   Creates a Vector with the specified values.
    #
    #   @param x [Float] The X component of the vector.
    #   @param y [Float] The Y component of the vector.
    #   @param z [Float] The Z component of the vector.
    #
    # @overload initialize(xy, z)
    #   Creates a Vector with the specified values.
    #
    #   @param xy [Vector3] Vector2 to use for the X and Y components.
    #   @param z [Float] The Z component of the vector.
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
    # The equivalent of `Enumerable#map`, but returns a vector object instead of
    # an Array.
    #
    # Invokes the given block once for each element of `self`.
    #
    # Creates a new vector containing the values returned by the block.
    #
    # @yield [component] Yields a component of the vector to the block.
    # @yieldparam component [Float] The yielded component.
    #
    # @return [Vector3]

    # @see map!
    def map
    end

    ##
    # Invokes the given block once for each element of self, replacing the
    # element with the value returned by the block.
    #
    # The values of the vector are altered without creating a ne object.
    #
    # @yield [component] Yields a component of the vector to the block.
    # @yieldparam component [Float] The yielded component.
    #
    # @return [self]
    #
    # @see map
    def map!
    end

    alias_method :collect, :map
    alias_method :collect!, :map!

    ##
    # Raises the vector to the given power.
    #
    # @param exponent [Float] The power to raise the vector to.
    #
    # @return [Vector3] New vector that is result of the operation.
    def **(exponent)
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
    # @param vector [Vector3] The point to get distance between.
    #
    # @return [Float] the distance.
    def distance(vector)
    end

    # Returns the squared Euclidean distance between this vector and another.
    #
    # @param vector [Vector3] The point to get distance between.
    #
    # @return [Float] the distance squared.
    def distance_squared(vector)
    end

    ##
    # Returns a new vector with the same direction as the given vector, but with
    # a length of `1.0`.
    #
    # @return [Vector3] a normalized vector.
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
    # @param vector [Vector3] The source vector to interpolate between.
    # @param amount [Float] Value between `0.0` and `1.0` indicating the weight
    #   of the given vector.
    #
    # @return [Vector3] the interpolated vector.
    #
    # @see lerp!
    def lerp(vector, amount)
    end

    ##
    # Linearly interpolates between this vector and another based on the given
    # weighting, altering the values of this vector.
    #
    # @param vector [Vector3] The source vector to interpolate between.
    # @param amount [Float] Value between `0.0` and `1.0` indicating the weight
    #   of the given vector.
    #
    # @return [self]
    #
    # @see lerp
    def lerp!(vector, amount)
    end

    ##
    # @return [Vector3] a vector whose elements are the absolute values of each
    #   of this vector's elements.
    def abs
    end

    ##
    # @return [Vector3] a vector whose elements are the square root of each of
    #   this vector's elements.
    def sqrt
    end

    ##
    # Returns the dot product of this vector and another.
    #
    # @param other [Vector3] the source vector to compute dot product of.
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
    #   @param min [Vector3] The minimum value.
    #   @param max [Vector3] The maximum value.
    #
    # @return [Vector3] the result of clamping this vector.
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
    #   @param min [Vector3] The minimum value.
    #   @param max [Vector3] The maximum value.
    #
    # @return [Vector3]
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
    # @return [Vector4] a {Vector4} representation of this instance.
    def to_vec4
    end

    ##
    # Adds this vector with another.
    #
    # @param other [Vector3] The vector to add.
    #
    # @return [Vector3] the sum of the vectors.
    def +(other)
    end

    ##
    # Gets the difference of this vector and another.
    #
    # @param other [Vector3] The vector to subtract.
    #
    # @return [Vector3] the difference of the vectors.
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
    #   @param other [Vector3] The source vector to multiply.
    #
    # @return [Vector3] the product vector.
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
    #   @param other [Vector3] The source vector to divide.
    #
    # @return [Vector3] the resulting vector.
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
    # @return [Vector3] the vector with swapped +/- values.
    def -@
    end

    ##
    # Returns a new vector by applying a transformation.
    #
    # @overload transform(matrix)
    #   Transforms this vector by the given matrix.
    #
    #   @param matrix [Matrix4x4] The transformation matrix.
    #
    # @overload transform(rotation)
    #   Transforms this vector by the specified rotation value.
    #
    #   @param rotation [Quaternion] The rotation to apply.
    #
    # @return [Vector3] new transformed vector.
    #
    # @see transform!
    def transform(other)
    end

    ##
    # Transforms this vector by the given matrix.
    #
    # @overload transform(matrix)
    #   Transforms this vector by the given matrix.
    #
    #   @param matrix [Matrix4x4] The transformation matrix.
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

    ##
    # Transforms a vector normal by the given matrix.
    #
    # @param matrix [Matrix4x4] The transformation matrix.
    #
    # @return [Vector3] new transformed vector.
    def transform_normal(matrix)
    end

    ##
    # Transforms a vector normal by the given matrix.
    #
    # @param matrix [Matrix4x4] The transformation matrix.
    #
    # @return [self]
    def transform_normal!(matrix)
    end

    ##
    # Computes the cross product of two vectors.
    #
    # @param other [Vector3] The source vector.
    #
    # @return [Vector3] the cross product.
    def cross(other)
    end

    # Computes the cross product of two vectors, altering the values of this
    # vector.
    #
    # @param other [Vector3] The source vector.
    #
    # @return [self]
    def cross!(other)
    end

    ##
    # Alters this vector to be the reflection of the specified normal.
    #
    # @param other [Vector3] The normal of the surface being reflected off.
    #
    # @return [Vector3] a newly created reflected vector.
    def reflect(other)
    end

    ##
    # Returns the reflection of a vector off a surface that has the specified
    # normal.
    #
    # @param other [Vector3] The normal of the surface being reflected off.
    #
    # @return [self]
    def reflect!(other)
    end

    ##
    # Computes the angle between this vector and another.
    #
    # @param other [Vector3] The vector to calculate angle from.
    #
    # @return [Float] the angle, in degrees, between the two vectors.
    def angle(other)
    end

    class << self

      ##
      # @return [Vector3] the vector `<0.0, 0.0, 0.0>`.
      def zero
      end

      ##
      # @return [Vector3] the vector `<1.0, 1.0, 1.0>`.
      def one
      end

      ##
      # @return [Vector3] the vector `<1.0, 0.0, 0.0>`.
      def unit_x
      end

      ##
      # @return [Vector3] the vector `<0.0, 1.0, 0.0>`.
      def unit_y
      end

      ##
      # @return [Vector3] the vector `<0.0, 0.0, 1.0>`.
      def unit_z
      end

      ##
      # Creates and returns a normalized vector from the specified components.
      #
      # This is more efficient than creating and then normalizing.
      #
      # @param x [Float] The X component of the vector.
      # @param y [Float] The Y component of the vector.
      # @param z [Float] The Z component of the vector.
      #
      # @return [Vector3] the newly created normalized vector.
      def create_norm(x, y, z)
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
      #   @param min [Vector3] The minimum value.
      #   @param max [Vector3] The maximum value.
      #
      # @return [Vector3] the result of clamping this vector.
      def clamp(vector, min, max)
      end

      ##
      # Linearly interpolates between two vectors based on the given weighting.
      #
      # @param vector1 [Vector3] The first source vector.
      # @param vector2 [Vector3] The second source vector.
      # @param amount [Float] Value between `0.0` and `1.0` indicating the
      #   weight of the second source vector.
      #
      # @return [Vector3] the interpolated vector.
      def lerp(vector1, vector2, amount)
      end

      ##
      # Returns a vector with a minimum set of values.
      #
      # @overload min(vector, other)
      #   Returns a vector whose elements are the minimum of each of the pairs
      #   of elements in the two source vectors.
      #
      #   @param vector [Vector3] The first source vector.
      #   @param other [Vector3] The second source vector.
      #
      # @overload min(vector, value)
      #   Returns a vector whose elements are the minimum of each of vector
      #   element and the specified value.
      #
      #   @param vector [Vector3] The source vector.
      #   @param value [Float] The minimum value.
      #
      # @return [Vector3] the minimized vector.
      def min(vector, other)
      end

      ##
      # Returns a vector with a maximum set of values.
      #
      # @overload max(vector, other)
      #   Returns a vector whose elements are the maximum of each of the pairs
      #   of elements in the two source vectors.
      #
      #   @param vector [Vector3] The first source vector.
      #   @param other [Vector3] The second source vector.
      #
      # @overload max(vector, value)
      #   Returns a vector whose elements are the maximum of each of vector
      #   element and the specified value.
      #
      #   @param vector [Vector3] The source vector.
      #   @param value [Float] The maximum value.
      #
      # @return [Vector3] the maximized vector.
      def max(vector, other)
      end
    end
  end
end
