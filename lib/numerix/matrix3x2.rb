module Numerix

  ##
  # A structure encapsulating a 3x2 matrix.
  class Matrix3x2 < MatrixBase
    
    ##
    # @return [Float] the first element of the first row.
    attr_accessor :m11

    ##
    # @return [Float] the second element of the first row.
    attr_accessor :m12

    ##
    # @return [Float] the first element of the second row.
    attr_accessor :m21

    ##
    # @return [Float] the second element of the second row.
    attr_accessor :m22

    ##
    # @return [Float] the first element of the third row.
    attr_accessor :m31

    ##
    # @return [Float] the second element of the third row.
    attr_accessor :m32

    ##
    # @return [Vector2] the translation component of this matrix.
    attr_accessor :translation

    ##
    # @overload initialize
    #   Creates a new matrix with all values set to `0.0`.
    #
    # @overload initialize(m11, m12, m21, m22, m31, m32)
    #   Constructs a Matrix3x2 from the given components.
    #
    #   @param m11 [Float] The first element of the first row.
    #   @param m12 [Float] The second element of the first row.
    #   @param m21 [Float] The first element of the second row.
    #   @param m22 [Float] The second element of the second row.
    #   @param m31 [Float] The first element of the third row.
    #   @param m32 [Float] The second element of the third row.
    #
    # @see create_translation
    # @see create_scale
    # @see create_skew
    # @see create_rotation
    # @see identity
    def initialize(*args)
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
    # Attempts to invert the given matrix.
    #
    # @note Some matrices cannot be inverted, in which case the returned matrix
    #   will have all values set to `NaN`.
    #
    # @return [Matrix3x2] A new matrix that is this matrix inverted.
    def invert
    end

    ##
    # Linearly interpolates from this matrix to another, based on the amount.
    #
    # @param matrix [Matrix3x2] The source matrix to interpolate between.
    # @param amount [Float] The relative weighting of the given matrix, clamped
    #   between `0.0` and `1.0`.
    #
    # @return [Matrix3x2] a newly created interpolated matrix.
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
    # @param matrix [Matrix3x2] The source matrix to interpolate between.
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
    # @return [Matrix3x2] the negated matrix.
    def -@
    end

    ##
    # Adds each matrix element in value1 with its corresponding element in the
    # specified matrix.
    #
    # @param other [Matrix3x2] The matrix to add.
    #
    # @return [Matrix3x2] A matrix containing the summed values.
    def +(other)
    end

    ##
    # Subtracts each matrix element in the specified matrix from its
    # corresponding element in this matrix to form a new matrix of the
    # difference.
    #
    # @param other [Matrix3x2] The matrix to subtract.
    #
    # @return [Matrix3x2] The matrix containing the resulting values.
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
    #   @param other [Matrix3x2] The source matrix to multiply.
    #
    # @return [Matrix3x2] the product matrix.
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

    class << self

      ##
      # @return [Matrix3x2] the multiplicative identity matrix.
      def identity
      end

      ##
      # Creates a translation matrix.
      #
      # @overload create_translation(position)
      #   Creates a translation matrix from the given vector.
      #
      #   @param position [Vector] The translation position.
      #
      # @overload create_translation(x, y)
      #   Creates a translation matrix from the given X and Y components.
      #
      #   @param x [Float] The X position.
      #   @param y [Float] The Y position.
      #
      # @return [Matrix3x2] a translation matrix.
      def create_translation(other)
      end

      ##
      # Creates a scale matrix.
      #
      # @overload create_scale(x, y)
      #   Creates a scale matrix from the given X and Y components.
      #
      #   @param x [Float] Value to scale by on the X-axis.
      #   @param y [Float] Value to scale by on the Y-axis.
      #
      # @overload create_scale(x, y, center)
      #   Creates a scale matrix that is offset by a given center point.
      #
      #   @param x [Float] Value to scale by on the X-axis.
      #   @param y [Float] Value to scale by on the Y-axis.
      #   @param center [Vector2] The center point.
      #
      # @overload create_scale(scales)
      #   Creates a scale matrix from the given vector scale.
      #
      #   @param scales [Vector2] The scale to use.
      #
      # @overload create_scale(scales, center)
      #   Creates a scale matrix from the given vector scale with an offset from
      #   the given center point.
      #
      #   @param scales [Vector2] The scale to use.
      #   @param center [Vector2] The center point.
      #
      # @overload create_scale(scale)
      #   Creates a scale matrix that scales uniformly with the given scale.
      #
      #   @param scale [Float] The uniform scale to use.
      #
      # @overload create_scale(scale, center)
      #   Creates a scale matrix that scales uniformly with the given scale with
      #   an offset from the given center.
      #
      #   @param scale [Float] The uniform scale to use.
      #   @param center [Vector2] The center point.
      #
      # @return [Matrix3x2] a scaling matrix.
      def create_scale(*args)
      end

      ##
      # Creates a skew matrix.
      #
      # @overload create_skew(x, y)
      #   Creates a skew matrix from the given angles in radians.
      #
      #   @param x [Float] The X angle, in radians
      #   @param y [Float] The Y angle, in radians
      #
      # @overload create_skew(x, y, center)
      #   Creates a skew matrix from the given angles in radians and a center
      #   point.
      #
      #   @param x [Float] The X angle, in radians
      #   @param y [Float] The Y angle, in radians
      #   @param center [Vector2] The center point.
      #
      # @return [Matrix3x2] a skew matrix.
      def create_skew(*args)
      end

      ##
      # Creates a rotation matrix.
      #
      # @overload create_rotation(radians)
      #   Creates a rotation matrix using the given rotation in radians.
      #
      #   @param radians [Float] The amount of rotation, in radians.
      #
      # @overload create_rotation(radians, center)
      #   Creates a rotation matrix using the given rotation in radians and a
      #   center point.
      #
      #   @param radians [Float] The amount of rotation, in radians.
      #   @param center [Vector2] The center point
      #
      # @return [Matrix3x2] a rotation matrix.
      def create_rotation
      end

      ##
      # Linearly interpolates from _matrix1_ to _matrix2_, based on the third
      # parameter.
      #
      # @param matrix1 [Matrix3x2] The first source matrix.
      # @param matrix2 [Matrix3x2] The second source matrix.
      # @param amount [Float] The relative weighting of _matrix2_, clamped
      #   between `0.0` and `1.0`.
      #
      # @return [Matrix3x2] the interpolated matrix.
      def lerp(matrix1, matrix2, amount)
      end
    end
  end
end