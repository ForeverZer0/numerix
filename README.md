# ![icon](https://github.com/ForeverZer0/numerix/blob/master/extra/numerix128.png)Numerix

Numerix is a powerful and feature-rich C-extension for working with vectors and matrices. 

The vector and matrix classes that are part of Ruby's standard library are implemented purely as Ruby code, and lack anything beyond the most basic functions. Numerix strives to make working with vectors more "Ruby-like", and far exceeding Ruby's built-in functions many times over in regards to speed and performance.

Great care has been take to make the library "interop" friendly, where each class can easily be passed as "pointer" or binary block of code for interop with languages using that also accept "pointer" types, whether it be Ruby's `Fiddle` library, or binary strings. Numerix has been built from the ground up specifically for Ruby, and is optimized specifically for it, with focus on speed and function.


## Installation

Add this line to your application's Gemfile:

```ruby
gem 'numerix'
```

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install numerix

## Usage

Numerix was based strongly off the `System.Numerics` library of Microsoft's .NET Framework, and contains the minimum set of functions and classes that are within it, in addition to many more. 

The following base classes are implemented completeley, and all work together to form a unified experience.

* **Vector2** - A structure encapsulating two single precision floating point values (_x, y_)
* **Vector3** - A structure encapsulating three single precision floating point values (_x, y, z_)
* **Vector4** - A structure encapsulating four single precision floating point values (_x, y, z, w_)
* **Matrix3x2** - A structure encapsulating a 3x2 matrix
* **Matrix4x4** - A structure encapsulating a 4x4 matrix
* **Plane** - A structure encapsulating a 3D plane (Vector3 denoting _normal_ and a float for _distance_)
* **Quaternion** - A structure encapsulating four single precision floating point values (_x, y, z, w_)

For each function (where applicable), there typically a static singleton version of the method, an instance version, and a "impure" variation that alters the object's state. All of the impure methods follow the standard Ruby convention of being suffixed with a `!`.

```ruby
# Create a vector with 3 elements
vec3 = Numerix::Vector3.new(5.0, 4.0, 9.0)

# Create a normalized vector from it with a static method
norm = Numerix::Vector3.normalize(vec3)

# Create a normalized vector from it with an instance method
norm = vec3.normalize

# Alter the state of the existing vector without creating new instance
vec3.normalize!
```

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/ForeverZer0/numerix. This project is intended to be a safe, welcoming space for collaboration, and contributors are expected to adhere to the [Contributor Covenant](http://contributor-covenant.org) code of conduct.

## License

The gem is available as open source under the terms of the [MIT License](https://opensource.org/licenses/MIT).

## Code of Conduct

Everyone interacting in the Numerix project’s codebases, issue trackers, chat rooms and mailing lists is expected to follow the [code of conduct](https://github.com/ForeverZer0/numerix/blob/master/CODE_OF_CONDUCT.md).