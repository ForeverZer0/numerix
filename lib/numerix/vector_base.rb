module Numerix

  ##
  # @abstract Abstract base class for Vector objects.
  class VectorBase < Structure

    private_class_method :new

    include Enumerable

    ##
    # The equivalent of `Enumerable#map`, but returns a vector object instead of
    # an Array.
    #
    # @overload map2
    #   Invokes the given block once for each element of `self`.
    #
    #   Creates a new vector containing the values returned by the block.
    #
    #   @yield [component] Yields a component of the vector to the block.
    #   @yieldparam component [Float] The yielded component.
    #
    #   @return [self]
    #
    # @overload map2
    #
    #   If no block is given, an Enumerator is returned instead.
    #
    #   @return [Enumerator]
    #
    # @return [self, Enumerator]
    #
    # @see map2!
    def map2
    end

    ##
    # @overload map2!
    #   Invokes the given block once for each element of self, replacing the
    #   element with the value returned by the block.
    #
    #   The values of the vector are altered without creating a ne object.
    #
    #   @yield [component] Yields a component of the vector to the block.
    #   @yieldparam component [Float] The yielded component.
    #
    #   @return [self]
    #
    # @overload map2!
    #
    #   If no block is given, an Enumerator is returned instead.
    #
    #   @return [Enumerator]
    #
    # @return [self, Enumerator]
    #
    # @see map2
    def map2!
    end

    ##
    # Raises the vector to the given power.
    #
    # @param exponent [Float] The power to raise the vector to.
    #
    # @return [Object] New vector that is result of the operation.
    def **(exponent)
    end

    alias_method :collect2, :map2
    alias_method :collect2!, :map2!

    ##
    # Raises the vector's components to the specified power.
    #
    # @param vector [VectorBase] The vector object to raise.
    # @param exponent [Float] The power to raise the vector to.
    #
    # @return [Object] New vector that is result of the operation.
    def self.pow(vector, exponent)
    end
  end
end