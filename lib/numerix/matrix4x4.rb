module Numerix

  ##
  # A structure encapsulating a 4x4 matrix.
  class Matrix4x4 < MatrixBase

    ##
    # @return [Float] Value at row 1, column 1 of the matrix.
    attr_accessor :m11

    ##
    # @return [Float] Value at row 1, column 2 of the matrix.
    attr_accessor :m12

    ##
    # @return [Float] Value at row 1, column 3 of the matrix.
    attr_accessor :m13

    ##
    # @return [Float] Value at row 1, column 4 of the matrix.
    attr_accessor :m14

        ##
    # @return [Float] Value at row 2, column 1 of the matrix.
    attr_accessor :m21

    ##
    # @return [Float] Value at row 2, column 2 of the matrix.
    attr_accessor :m22

    ##
    # @return [Float] Value at row 2, column 3 of the matrix.
    attr_accessor :m23

    ##
    # @return [Float] Value at row 2, column 4 of the matrix.
    attr_accessor :m24

        ##
    # @return [Float] Value at row 3, column 1 of the matrix.
    attr_accessor :m31

    ##
    # @return [Float] Value at row 3, column 2 of the matrix.
    attr_accessor :m32

    ##
    # @return [Float] Value at row 3, column 3 of the matrix.
    attr_accessor :m33

    ##
    # @return [Float] Value at row 3, column 4 of the matrix.
    attr_accessor :m34

        ##
    # @return [Float] Value at row 4, column 1 of the matrix.
    attr_accessor :m41

    ##
    # @return [Float] Value at row 4, column 2 of the matrix.
    attr_accessor :m42

    ##
    # @return [Float] Value at row 4, column 3 of the matrix.
    attr_accessor :m43

    ##
    # @return [Float] Value at row 4, column 4 of the matrix.
    attr_accessor :m44

    ##
    # @return [Vector3] the translation component of this matrix.
    attr_accessor :translation

    ##
    # @overload initialize
    #   Constructs a default matrix with all values set to `0.0`.
    #
    # @overload initialize(matrix)
    #   Constructs a Matrix4x4 from the given {Matrix3x2}.
    #
    #   @param matrix [Matrix3x3] The source matrix.
    #
    # @overload initialize(value)
    #   Constructs a matrix from a single component value.
    #
    #   @param value [Float] Value to applied to all components.
    # 
    # @overload initialize(m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44)
    #   Constructs a matrix from the given components.
    #
    #   @param m11 [Float] Value at row 1, column 1 of the matrix.
    #   @param m12 [Float] Value at row 1, column 2 of the matrix.
    #   @param m13 [Float] Value at row 1, column 3 of the matrix.
    #   @param m14 [Float] Value at row 1, column 4 of the matrix.
    #   @param m21 [Float] Value at row 2, column 1 of the matrix.
    #   @param m22 [Float] Value at row 2, column 2 of the matrix.
    #   @param m23 [Float] Value at row 2, column 3 of the matrix.
    #   @param m24 [Float] Value at row 2, column 4 of the matrix.
    #   @param m31 [Float] Value at row 3, column 1 of the matrix.
    #   @param m32 [Float] Value at row 3, column 2 of the matrix.
    #   @param m33 [Float] Value at row 3, column 3 of the matrix.
    #   @param m34 [Float] Value at row 3, column 4 of the matrix.
    #   @param m41 [Float] Value at row 4, column 1 of the matrix.
    #   @param m42 [Float] Value at row 4, column 2 of the matrix.
    #   @param m43 [Float] Value at row 4, column 3 of the matrix.
    #   @param m44 [Float] Value at row 4, column 4 of the matrix.
    #
    def initialize(*args)
    end

    ##
    # The equivalent of `Enumerable#map`, but returns a matrix object instead of
    # an Array.
    #
    # Invokes the given block once for each element of `self`.
    #
    # Creates a new matrix containing the values returned by the block.
    #
    # @yield [component] Yields a component of the matrix to the block.
    # @yieldparam component [Float] The yielded component.
    #
    # @return [Matrix4x4]
    #
    # @see map!
    def map
    end

    ##
    # Invokes the given block once for each element of self, replacing the
    # element with the value returned by the block.
    #
    # The values of the matrix are altered without creating a ne object.
    #
    # @yield [component] Yields a component of the matrix to the block.
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
    # Raises the matrix to the given power.
    #
    # @param exponent [Float] The power to raise the matrix to.
    #
    # @return [Matrix4x4] New matrix that is result of the operation.
    def **(exponent)
    end

    ##
    # @return [Boolean] `true` if the matrix is the identity matrix, otherwise
    #   `false`.
    def identity?
    end

    ##
    # Calculates the determinant for this matrix.
    #
    # The determinant is calculated by expanding the matrix with a third column
    # whose values are (0,0,1).
    #
    # @return [Float] the determinant.
    def determinant
    end

    ##
    # Returns the specified matrix row as an array.
    #
    # @param index [Integer] The row index to retrieve.
    #
    # @return [Array<Float>, nil] the requested row, or `nil` if index is out of
    #   range.
    #
    # @see column
    def row(index)
    end

    ##
    # Returns the specified matrix column as an array.
    #
    # @param index [Integer] The column index to retrieve.
    #
    # @return [Array<Float>, nil] the requested column, or `nil` if index is out
    #   of range.
    #
    # @see row
    def column(index)
    end

    ##
    # Enumerates the rows of the matrix.
    #
    # @yield [row] Yields a row to the block.
    # @yieldparam row [Array<Float>] The current row as an array.
    #
    # @return [self]
    #
    # see each_column
    def each_row
    end

    ##
    # Enumerates the columns of the matrix.
    #
    # @yield [column] Yields a column to the block.
    # @yieldparam column [Array<Float>] The current column as an array.
    #
    # @return [self]
    #
    # @see each_row
    def each_column
    end

    ##
    # Linearly interpolates from this matrix to another, based on the amount.
    #
    # @param matrix [Matrix4x4] The source matrix to interpolate between.
    # @param amount [Float] The relative weighting of the given matrix, clamped
    #   between `0.0` and `1.0`.
    #
    # @return [Matrix4x4] a newly created interpolated matrix.
    #
    # @see lerp!
    def lerp(matrix, amount)
    end

    ##
    # @note This method is the same as {#lerp}, but alters the values of this
    #   matrix instead of creating a new instance.
    #
    # Linearly interpolates from this matrix to another, based on the amount.
    #
    # @param matrix [Matrix4x4] The source matrix to interpolate between.
    # @param amount [Float] The relative weighting of the given matrix, clamped
    #   between `0.0` and `1.0`.
    #
    # @return [self]
    #
    # @see lerp
    def lerp!(matrix, amount)
    end

    ##
    # @return [String] a String representation of this instance.
    def to_s
    end

    ##
    # @return [Array<Array<Float>>] an Array representation of this instance.
    def to_a
    end

    alias_method :elements, :to_a

    ##
    # @return [Hash{Symbol => Float}] a Hash representation of this instance.
    def to_h
    end

    ##
    # Negates the given matrix by multiplying all values by `-1.0`.
    #
    # @return [Matrix4x4] the negated matrix.
    def -@
    end

    ##
    # Adds each matrix element in value1 with its corresponding element in the
    # specified matrix.
    #
    # @param other [Matrix4x4] The matrix to add.
    #
    # @return [Matrix4x4] A matrix containing the summed values.
    def +(other)
    end

    ##
    # Subtracts each matrix element in the specified matrix from its
    # corresponding element in this matrix to form a new matrix of the
    # difference.
    #
    # @param other [Matrix4x4] The matrix to subtract.
    #
    # @return [Matrix4x4] The matrix containing the resulting values.
    def -(other)
    end

    ##
    # Multiplies this matrix by the specified value.
    #
    # @overload *(scalar)
    #   Scales all elements in a matrix by the given scalar factor.
    #
    #   @param scalar [Float] The scaling value to use.
    #
    # @overload *(other)
    #   Multiplies two matrices together and returns the resulting matrix.
    #
    #   @param other [Matrix4x4] The source matrix to multiply.
    #
    # @return [Matrix4x4] the product matrix.
    def *(other)
    end

    ##
    # Returns flag if this matrix instance is equal to the given object.
    #
    # @param other [Object] The object to compare.
    #
    # @return [Boolean] `true` if objects are equal, otherwise `false`.
    def ==(other)
    end

    ##
    # Accesses the matrix component using the zero-based row/column indices.
    #
    # @param row [Integer] The zero-based row index.
    # @param column [Integer] The zero-based column index.
    #
    # @return [Float, nil] the value at the specified location, or `nil` if an
    #   index is out of range.
    def [](row, column)
    end

    ##
    # Sets the matrix component using the zero-based row/column indices.
    #
    # @param row [Integer] The zero-based row index.
    # @param column [Integer] The zero-based column index.
    # @param value [Float] The value to set.
    #
    # @return [Float] the value.
    def []=(row, column, value)
    end

    ##
    # Attempts to invert the given matrix.
    #
    # @note Some matrices cannot be inverted, in which case the returned matrix
    #   will have all values set to `NaN`.
    #
    # @return [Matrix4x4] A new matrix that is this matrix inverted.
    def invert
    end

    ##
    # Creates a matrix by transforming this instance by applying the given 
    # quaternion rotation.
    #
    # @param rotation [Quaternion] The rotation to apply.
    #
    # @return [Matrix4x4] a transformed matrix.
    def transform(rotation)
    end

    ##
    # Transforms this matrix by applying the given quaternion rotation.
    #
    # @param rotation [Quaternion] The rotation to apply.
    #
    # @return [self]
    def transform!(rotation)
    end

    ##
    # Transposes the rows and columns of a matrix.
    #
    # @return [Matrix4x4] a transposed matrix.
    def transpose
    end

    class << self

      ##
      # @return [Matrix4x4] the multiplicative identity matrix.
      def identity
      end

      ##
      # Creates a spherical billboard that rotates around a specified object
      # position.
      #
      # @param position [Vector3] Position of the object the billboard will
      #   rotate around.
      # @param camera [Vector3] Position of the camera.
      # @param up [Vector3] The up vector of the camera.
      # @param forward [Vector3] The forward vector of the camera.
      #
      # @return [Matrix4x4] the created billboard matrix.
      def create_billboard(position, camera, up, forward)
      end

      ##
      # Creates a cylindrical billboard that rotates around a specified axis.
      #
      # @param position [Vector3] Position of the object the billboard will
      #   rotate around.
      # @param camera [Vector3] Position of the camera.
      # @param axis [Vector3] Axis to rotate the billboard around.
      # @param cam_forward [Vector3] Forward vector of the camera.
      # @param obj_forward [Vector3] Forward vector of the object.
      #
      # @return [Matrix4x4] the created billboard matrix.
      def create_constrained_billboard(position, camera, axis, cam_forward, obj_forward)
      end

      ##
      # Creates a translation matrix.
      #
      # @overload create_translation(position)
      #   @param position [Vector3] The amount to translate in each axis.
      #
      # @overload create_translation(x, y, z)
      #   @param x [Float] The amount to translate on the X-axis.
      #   @param y [Float] The amount to translate on the Y-axis.
      #   @param z [Float] The amount to translate on the Z-axis.
      #
      # @return [Matrix4x4] the translation matrix.
      def create_translation
      end

      ##
      # Creates a scaling matrix.
      #
      # @overload create_scale(x, y, z)
      #   @param x [Float] Value to scale by on the X-axis.
      #   @param y [Float] Value to scale by on the Y-axis.
      #   @param z [Float] Value to scale by on the Z-axis.
      #
      # @overload create_scale(x, y, z, center)
      #   @param x [Float] Value to scale by on the X-axis.
      #   @param y [Float] Value to scale by on the Y-axis.
      #   @param z [Float] Value to scale by on the Z-axis.
      #   @param center [Vector3] The center point.
      #
      # @overload create_scale(scales)
      #   @param scales [Vector3] The vector containing the amount to scale by
      #     on each axis.
      #
      # @overload create_scale(scales, center)
      #   @param scales [Vector3] The vector containing the amount to scale by
      #     on each axis.
      #   @param center [Vector3] The center point.
      #
      # @overload create_scale(scale)
      #   @param scale [Float] The uniform scaling factor.
      #
      # @overload create_scale(scale, center)
      #   @param scale [Float] The uniform scaling factor.
      #   @param center [Vector3] The center point.
      #
      # @return [Matrix4x4] the scaling matrix.
      def create_scale
      end

      ##
      # Creates a matrix for rotating points around the X-axis.
      #
      # @overload create_rotation_x(radians)
      #   @param radians [Float] The amount, in radians, by which to rotate
      #     around the X-axis.
      #
      # @overload create_rotation_x(radians, center)
      #   @param radians [Float] The amount, in radians, by which to rotate
      #     around the X-axis.
      #   @param center [Vector3] The center point.
      #
      # @return [Matrix4x4] the rotation matrix.
      def create_rotation_x
      end

      ##
      # Creates a matrix for rotating points around the Y-axis.
      #
      # @overload create_rotation_y(radians)
      #   @param radians [Float] The amount, in radians, by which to rotate
      #     around the Y-axis.
      #
      # @overload create_rotation_y(radians, center)
      #   @param radians [Float] The amount, in radians, by which to rotate
      #     around the Y-axis.
      #   @param center [Vector3] The center point.
      #
      # @return [Matrix4x4] the rotation matrix.
      def create_rotation_y
      end

      ##
      # Creates a matrix for rotating points around the Z-axis.
      #
      # @overload create_rotation_z(radians)
      #   @param radians [Float] The amount, in radians, by which to rotate
      #     around the Z-axis.
      #
      # @overload create_rotation_z(radians, center)
      #   @param radians [Float] The amount, in radians, by which to rotate
      #     around the Z-axis.
      #   @param center [Vector3] The center point.
      #
      # @return [Matrix4x4] the rotation matrix.
      def create_rotation_z
      end

      ##
      # Creates a perspective projection matrix based on a field of view, aspect
      # ratio, and near and far view plane distances.
      #
      # @param fov [Float] Field of view in the y direction, in radians.
      # @param ratio [Float] Aspect ratio, defined as view space width divided
      #   by height.
      # @param near [Float] Distance to the near view plane.
      # @param far [Float] Distance to the far view plane.
      #
      # @return [Vector3] the perspective projection matrix.
      def create_perspective_fov(fov, ratio, near, far)
      end

      ##
      # Creates a perspective projection matrix from the given view volume
      # dimensions.
      #
      # @param width [Float] Width of the view volume at the near view plane.
      # @param height [Float] Height of the view volume at the near view plane.
      # @param near [Float] Distance to the near view plane.
      # @param far [Float] Distance to the far view plane.
      #
      # @return [Vector3] the perspective projection matrix.
      def create_perspective(width, height, near, far)
      end

      ##
      # Creates a customized, perspective projection matrix.
      #
      # @param left [Float] Minimum x-value of the view volume at the near view
      #   plane.
      # @param right [Float] Maximum x-value of the view volume at the near view
      #   plane.
      # @param bottom [Float] Minimum y-value of the view volume at the near
      #   view plane.
      # @param top [Float] Maximum y-value of the view volume at the near view
      #   plane.
      # @param near [Float] Distance to the near view plane.
      # @param far [Float] Distance to the far view plane.
      #
      # @return [Vector3] the perspective projection matrix.
      def create_perspective_off_center(left, right, bottom, top, near, far)
      end

      ##
      # Creates an orthographic perspective matrix from the given view volume
      # dimensions.
      #
      # @param width [Float] Width of the view volume.
      # @param height [Float] Height of the view volume.
      # @param near [Float] Minimum Z-value of the view volume.
      # @param far [Float] Maximum Z-value of the view volume.
      #
      # @return [Matrix4x4] the orthographic projection matrix.
      def create_orthographic(width, height, near, far)
      end

      ##
      # Builds a customized, orthographic projection matrix.
      #
      # @param left [Float] Minimum X-value of the view volume.
      # @param right [Float] Maximum X-value of the view volume.
      # @param bottom [Float] Minimum Y-value of the view volume.
      # @param top [Float] Maximum Y-value of the view volume.
      # @param near [Float] Minimum Z-value of the view volume.
      # @param far [Float] Maximum Z-value of the view volume.
      #
      # @return [Matrix4x4] the orthographic projection matrix.
      def create_orthographic_off_center(left, right, bottom, top, near, far)
      end

      ##
      # Creates a view matrix.
      #
      # @param camera [Vector3] The position of the camera.
      # @param target [Vector3] The target towards which the camera is pointing.
      # @param up [Vector3] The direction that is "up" from the camera's point
      #   of view.
      #
      # @return [Matrix4x4] The view matrix.
      def create_look_at(camera, target, up)
      end

      ##
      # Creates a world matrix with the specified parameters.
      #
      # @param position [Vector3] The position of the object; used in
      #   translation operations.
      # @param forward [Vector3] Forward direction of the object.
      # @param up [Vector3] Upward direction of the object; usually
      #   `<0.0, 1.0, 0.0>`.
      #
      # @return [Matrix4x4] the world matrix.
      def create_world(position, forward, up)
      end

      ##
      # Creates a Matrix that flattens geometry into a specified Plane as if
      # casting a shadow from a specified light source.
      #
      # @param direction [Vector3] The direction from which the light that will
      #   cast the shadow is coming.
      # @param plane [Plane] he Plane onto which the new matrix should flatten
      #   geometry so as to cast a shadow.
      #
      # @return [Matrix4x4] A new Matrix that can be used to flatten geometry
      #   onto the specified plane from the specified direction.
      def create_shadow(direction, plane)
      end

      ##
      # Creates a Matrix that reflects the coordinate system about a specified
      # plane.
      #
      # @param plane [Plane] The plane about which to create a reflection.
      #
      # @return [Matrix4x4] a new matrix expressing the reflection.
      def create_reflection(plane)
      end

      ##
      # Creates a matrix that rotates around an arbitrary vector.
      #
      # @param axis [Vector3] The axis to rotate around.
      # @param angle [Float] The angle to rotate around the given axis, in
      #   radians.
      #
      # @return [Matrix4x4] the rotation matrix.
      def from_axis_angle(axis, angle)
      end

      ##
      # Creates a rotation matrix from the given quaternion rotation value.
      #
      # @param quaternion [Quaternion] The source quaternion.
      #
      # @return [Matrix4x4] the rotation matrix.
      def from_quaternion(quaternion)
      end

      ##
      # Creates a rotation matrix from the specified yaw, pitch, and roll.
      #
      # @param yaw [Float] Angle of rotation, in radians, around the Y-axis.
      # @param pitch [Float] Angle of rotation, in radians, around the X-axis.
      # @param roll [Float] Angle of rotation, in radians, around the Z-axis.
      #
      # @return [Matrix4x4] the rotation matrix.
      def from_yaw_pitch_roll(yaw, pitch, roll)
      end

      ##
      # Linearly interpolates from _matrix1_ to _matrix2_, based on the third
      # parameter.
      #
      # @param matrix1 [Matrix4x4] The first source matrix.
      # @param matrix2 [Matrix4x4] The second source matrix.
      # @param amount [Float] The relative weighting of _matrix2_, clamped
      #   between `0.0` and `1.0`.
      #
      # @return [Matrix4x4] the interpolated matrix.
      def lerp(matrix1, matrix2, amount)
      end
    end
  end
end