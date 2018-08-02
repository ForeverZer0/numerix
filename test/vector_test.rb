
require "test_helper"
include Numerix

class NumerixTest < Minitest::Test

  # def initialize(*args)
  #   super
  #   @v2_1 = Vector2.new(randf, randf)
  #   @v2_2 = Vector2.new(randf, randf)
  #   @v3_1 = Vector3.new(randf, randf, randf)
  #   @v3_2 = Vector4.new(randf, randf, randf)
  #   @v4_1 = Vector4.new(randf, randf, randf, randf)
  #   @v4_2 = Vector4.new(randf, randf, randf, randf)
  # end

  def test_vector2_creation
    assert Vector2.new(1).one?
    assert Vector2.new(1, 1).one?
    assert Vector2.one.one?
    assert Vector2.zero.zero?
    refute Vector2.zero.one?
    refute Vector2.one.zero?
    assert Vector2.unit_x.x == 1.0 && Vector2.unit_x.y == 0.0
    assert Vector2.unit_y.x == 0.0 && Vector2.unit_y.y == 1.0
  end

  def test_vector3_creation
    assert Vector3.new(1).one?
    assert Vector3.new(1, 1, 1).one?
    assert Vector3.new(0, 0, 0).zero?
    refute Vector3.new(1, 0, 1).one?
    assert Vector3.zero == Vector3.new(0,0,0)
    assert Vector3.one == Vector3.new(1,1,1)
    refute Vector3.zero == Vector3.new(0,1,0)
    assert Vector3.one.one?
    assert Vector3.zero.zero?
    refute Vector3.zero.one?
    refute Vector3.one.zero?
  end







end
