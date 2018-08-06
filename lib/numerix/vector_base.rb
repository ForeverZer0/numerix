module Numerix

  ##
  # @abstract Abstract base class for Vector objects.
  #
  # This class cannot be instantiated, it of only for providing a common base
  # class for vector types.
  class VectorBase < Structure

    private_class_method :new

    include Enumerable
  end
end