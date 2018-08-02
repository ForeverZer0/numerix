require_relative 'numerix/version'
require_relative 'numerix/numerix'

module Numerix

  if RUBY_VERSION >= '2.0'

    require 'fiddle'

    class Structure

      def ptr
       Fiddle::Pointer.new(address, self.class.size)
      end
    end

  end
end



