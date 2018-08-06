module Numerix

  ##
  # @abstract Abstract base class for matrix classes.
  #
  # This class cannot be instantiated, it of only for providing a common base
  # class for matrix types.
  class MatrixBase < Structure

    private_class_method :new

    include Enumerable
  end
end