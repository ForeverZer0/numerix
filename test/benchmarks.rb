
################################################################################
# Options 
###############################################################################

# Number of tests to run
COUNT = 1000000

# Run Vector3 benchmarks
VECTOR3 = true

################################################################################



require 'benchmark'
require 'matrix'
require_relative '../lib/numerix'

include Numerix
include Benchmark

def header(str, count, info = nil)
  puts
  puts '/' * 80
  puts "//  #{str} (performed #{count} times)"
  unless info.nil?
    puts "//  #{info}"
  end
  puts '/' * 80
end

def result(ruby, numerix)
  if ruby > numerix
    diff = (ruby.real / numerix.real).round(2)
    puts "\nNumerix is #{diff} timers faster than Ruby."
  else
    diff = (numerix.real / ruby.real).round(2)
    # Will never see this...
    puts "\nRuby is #{diff} timers faster than Numerix."
  end
  puts
end

if VECTOR3

  x, y, z = rand(0.0..100.0), rand(0.0..100.0), rand(0.0..100.0)
  rv = Vector[x, y, z]          # Ruby Standard Library
  nv = Vector3.new(x, y, z)     # Numerix
  
  header('Vector 3 Normalize', COUNT, nv)

  Benchmark.bm(10) do |x|
    r = x.report('Ruby') { COUNT.times { rv.normalize }}
    n = x.report('Numerix') { COUNT.times { Vector3.normalize(nv) }}
    result(r.real, n.real)
  end

  header('Vector 3 Element Access', COUNT)

  Benchmark.bm(10) do |x|
    r = x.report('Ruby') { COUNT.times { rv.to_a; }}
    n = x.report('Numerix') { COUNT.times { nv.to_a; }}
    result(r.real, n.real)
  end


end


