$LOAD_PATH.unshift File.expand_path("../../lib", __FILE__)
require "numerix"

require "minitest/autorun"


def randf
  rand(0.0..100.0)
end

