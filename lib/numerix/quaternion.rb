module Numerix

  ##
  # A structure encapsulating a four-dimensional vector (x,y,z,w), which is used
  # to efficiently rotate an object about the (x,y,z) vector by the angle theta,
  # where `w = cos(theta / 2)`.
  class Quaternion < Structure

    ##
    # @return [Float] the X-value of the vector component of the quaternion.
    attr_accessor :x

    ##
    # @return [Float] the Y-value of the vector component of the quaternion.
    attr_accessor :y

    ##
    # @return [Float] the Z-value of the vector component of the quaternion.
    attr_accessor :z

    ##
    # @return [Float] the rotation component of the quaternion.
    attr_accessor :w

    def initialize(*args)
    end

    def identity?
    end

    def length
    end

    def length_squared
    end

    def normalize
    end

    def normalize!
    end

    def conjugate
    end

    def conjugate!
    end

    def inverse
    end

    def dot(other)
    end

    def concatenate(other)
    end

    def concatenate!(other)
    end

    def lerp()
    end

    def lerp!()
    end

    def slerp()
    end

    def slerp!()
    end
  
    def to_s
    end

    def to_a
    end

    def to_h
    end

    def to_vec4
    end

    def -@
    end

    def +(other)
    end

    def -(other)
    end

    def *(other)
    end

    def /(other)
    end

    def ==(other)
    end

    class << self

      def identity
      end

      def from_axis_angle()
      end

      def from_yaw_pitch_roll()
      end

      def from_rotation_matrix()
      end

      def slerp()
      end

      def lerp()
      end
    end
  end
end