require_relative 'numerix/version'
require_relative 'numerix/numerix'

module Numerix

  ptr = Vector4.one.ptr

  p ptr.inspect

end
