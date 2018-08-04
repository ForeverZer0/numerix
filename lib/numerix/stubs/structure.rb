
module Numerix

  ##
  # @abstract Abstract class providing common functionality to the base classes.
  class Structure

    private_class_method :new

    ##
    # @return [Object] an exact duplicate of the object.
    def dup
    end

    ##
    # @return [Integer] the address of the internal C-struct in memory.
    def address
    end

    ##
    # Enumerates over the components of the structure.
    #
    # @overload each
    #   When called with a block, enumerates through each component of the
    #   structure, yielding each before returning self;
    #
    #   @yield [component] Yields a component to the block.
    #   @yieldparam component [Float] The current component.
    #
    #   @return [self]
    #
    # @overload each
    #
    #   When called without a block, returned an Enumerator for the structure.
    #
    #   @return [Enumerator] the enumerator for the structure.
    def each
    end

    ##
    # Retrieves the component of the structure at the specified position.
    #
    # @param index [Integer] The position of the component to retrieve.
    #
    # @return [Float, nil] the value at the given position, or +nil+ if _index_
    #   is out of range.
    #
    # @see []=
    def [](index)
    end

    ##
    # Sets the component of the structure at the specified position.
    #
    # If _index_ is out of range, the method does nothing.
    #
    # @param index [Integer] The position of the component to set.
    # @param value [Float] The value to set.
    #
    # @return [Float] the value
    #
    # @see []
    def []=(index, value)
    end

    ##
    # Packs the structures memory into a binary string.
    #
    # This is the equivalent of taking its values into an array and calling
    # `array.pack('f*')` on it, though considerably faster as the parser is
    # bypassed and done directly in C by accessing the memory directly.
    #
    # @return [String] the packed binary string.
    #
    # @see pack
    def pack
    end

    alias_method :_dump, :pack

    if RUBY_VERSION >= '2.0'

      require 'fiddle'

      ##
      # @note This method only exists in Ruby 2.0 and higher.
      #
      # @return [Fiddle::Pointer] a sized pointer to the structure in memory.
      def ptr
      end
    end

    class << self

      ##
      # @return [Integer] the size, in bytes, the structure contains in memory.
      def size
      end

      ##
      # Unpacks a binary string of data into a structure.
      #
      # This is the equivalent of calling `binary.unpack('f*')` on the string
      # and using the values to create a new structure, but much faster as it
      # bypasses the parser and is done in C directly with a pointer in memory.
      #
      # @param binary [String] Binary string of data.
      #
      # @return [Object] the unpacked structure.
      #
      # @see pack
      def unpack(binary)
      end

      alias_method :_load, :unpack
    end
  end
end