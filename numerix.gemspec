
lib = File.expand_path("../lib", __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require "numerix/version"

Gem::Specification.new do |spec|
  spec.name          = "numerix"
  spec.version       = Numerix::VERSION
  spec.authors       = ["Eric Freed"]
  spec.email         = ["efreed09@gmail.com"]

  spec.summary       = %q{High performance vector and matrix C extension for fast vector math and simplified interop.}
  spec.description   = %q{Numerix strives to make working with vectors more "Ruby-like", and far exceeds Ruby's built-in implementations many times over in regards to speed and performance. Great care has been take to make the library "interop" friendly, where each class can easily be passed as a "pointer" or binary string for interop with native libraries, using Ruby's Fiddle, FFI, or even Ruby's legacy Win32API. Numerix has been built from the ground-up for Ruby, not playing middle-man between Ruby and an existing library, and is optimized specifically for it, with focus on speed and a robust collection of functionality. }
  spec.homepage      = "https://github.com/ForeverZer0/numerix"
  spec.license       = "MIT"

  spec.files         = Dir.chdir(File.expand_path('..', __FILE__)) do
    `git ls-files -z`.split("\x0").reject { |f| f.match(%r{^(test|spec|features)/}) }
  end

  spec.bindir        = "exe"
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ["lib"]
  spec.extensions    = ["ext/numerix/extconf.rb"]

  spec.add_development_dependency "bundler", "~> 1.16"
  spec.add_development_dependency "rake", "~> 10.0"
  spec.add_development_dependency "rake-compiler", '~> 0'
  spec.add_development_dependency "minitest", "~> 5.0"
end
