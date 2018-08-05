module Numerix

  ##
  # A structure encapsulating a 3D Plane.
  class Plane < Structure

    ##
    # @return [Vector3] the normal vector of the plane.
    attr_accessor :normal

    ##
    # @return [Float] the distance of the plane along its normal from the
    #   origin.
    attr_accessor :distance

    ##
    # @overload initialize
    #   Creates a new plane will all values default to `0.0`.
    #
    # @overload initialize(vector)
    #   Constructs a Plane from the given Vector4.
    #
    #   @param vector [Vector4] A vector whose first 3 elements describe the
    #     normal vector, and whose W component defines the distance along that
    #     normal from the origin.
    # 
    # @overload initialize(normal, distance)
    #   Constructs a Plane from the given normal and distance along the normal
    #   from the origin.
    #
    #   @param normal [Vector3] The normal vector of the plane.
    #   @param distance [Float] The distance of the plane along its normal from
    #     the origin.
    #
    # @overload initialize(x, y, z, distance)
    #   Constructs a plane from the X, Y, and Z components of its normal, and
    #   its distance from the origin on that normal.
    #
    #   @param x [Float] The normal X component.
    #   @param y [Float] The normal Y component.
    #   @param z [Float] The normal Z component.
    #   @param distance [Float] The distance of the Plane along its normal from
    #     the origin.
    def initialize(*args)
    end

    ##
    # @note This plane must already be normalized, so that its normal vector is
    #   of unit length, before this method is called.
    #
    # Applies a transformation to the plane.
    #
    # @overload transform(matrix)
    #
    #   Transforms a normalized plane by a matrix.
    #
    #   @param matrix [Matrix4x4] The transformation matrix.
    #
    #   @return [Plane] the transformed plane.
    #
    # @overload transform(rotation)
    #   Transforms a normalized plane by a quaternion rotation.
    #
    #   @param rotation [Quaternion] The rotation to apply.
    #
    # @return [Plane] A new plane that results from applying the rotation.
    def transform(other)
    end

    ##
    # @note This plane must already be normalized, so that its normal vector is
    #   of unit length, before this method is called.
    #
    # Applies a transformation to the plane.
    #
    # @overload transform!(matrix)
    #
    #   Transforms a normalized plane by a matrix.
    #
    #   @param matrix [Matrix4x4] The transformation matrix.
    #
    # @overload transform!(rotation)
    #   Transforms a normalized plane by a quaternion rotation.
    #
    #   @param rotation [Quaternion] The rotation to apply.
    #
    # @return [self] 
    def transform!(other)
    end

    ##
    # Calculates the dot product of a plane and {Vector4}.
    #
    # @param other [Vector4] The vector to compute.
    #
    # @return [Float] the dot product.
    def dot(other)
    end

    ##
    # Returns the dot product of a specified {Vector3} and the normal vector of
    # this Plane plus the distance value of the plane.
    #
    # @param other [Vector3] The vector to compute.
    #
    # @return [Float] the dot product.
    def dot_coord(other)
    end

    ##
    # Returns the dot product of a specified Vector3 and the normal vector of
    # this plane.
    #
    # @param other [Vector3] The vector to compute.
    #
    # @return [Float]
    def dot_norm(other)
    end

    ##
    # Creates a new plane whose normal vector is the source plane's normal
    # vector normalized.
    #
    # @return [Plane] newly created normalized plane.
    def normalize
    end

    ##
    # Normalizes this plane's normal vector.
    #
    # @return [self]
    def normalize!
    end

    ##
    # @return [String] a String representation of this instance.
    def to_s
    end

    class << self

      ##
      # Creates a Plane that contains the three given points.
      #
      # @param pnt1 [Vector3] The first point defining the plane.
      # @param pnt2 [Vector3] The second point defining the plane.
      # @param pnt3 [Vector3] The third point defining the plane.
      #
      # @return [Plane] the plane containing the three points.
      def from_vertices(pnt1, pnt2, pnt3)
      end
    end
  end
end