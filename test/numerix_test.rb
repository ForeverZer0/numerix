require "test_helper"

include Numerix

class NumerixTest < Minitest::Test
  def test_that_it_has_a_version_number
    refute_nil ::Numerix::VERSION
  end


end
