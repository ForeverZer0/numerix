module Numerix

  ##
  # @abstract Abstract base class for Vector objects.
  class VectorBase < Structure

    private_class_method :new

    include Enumerable
  end
end