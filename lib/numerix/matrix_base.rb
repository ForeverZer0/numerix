module Numerix

  ##
  # @abstract Abstract base class for matrix classes.
  class MatrixBase < Structure

    include Enumerable

    private_class_method :new

  end
end