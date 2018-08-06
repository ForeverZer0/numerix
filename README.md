
# ![logo](./extra/numerix32.png)  Numerix

Numerix is a powerful and feature-rich Ruby C-extension for working with vectors and matrices. 

The vector and matrix classes that are part of Ruby's standard library are implemented purely as Ruby code, and lack anything beyond the most basic function. Numerix strives to make working with vectors more "Ruby-like", and far exceeds Ruby's built-in implementations many times over in regards to speed and performance.

Great care has been take to make the library "interop" friendly, where each class can easily be passed as a "pointer" or binary string for interop with native libraries, using Ruby's `Fiddle`, FFI, or even Ruby's legacy `Win32API`. Numerix has been built from the ground-up for Ruby, not playing middle-man between Ruby and an existing library, and is optimized specifically for it, with focus on speed and a robust collection of functionality.

This is my first publicly released C extension for Ruby, and I welcome bug reports of any kind, in addition to feature requests, and ALL constructive feedback. Please don't hesitate to report any issues [on GitHub](https://github.com/ForeverZer0/numerix/issues)!

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

Numerix was based strongly off the `System.Numerics` library of Microsoft's .NET Framework (the inspiration behind the name), and contains the minimum set of functions and classes that are within it, in addition to many more. 

The following base classes are implemented completeley, and all work together to form a unified experience.

* **Vector2** - A structure encapsulating two single precision floating point values (_x, y_)
* **Vector3** - A structure encapsulating three single precision floating point values (_x, y, z_)
* **Vector4** - A structure encapsulating four single precision floating point values (_x, y, z, w_)
* **Matrix3x2** - A structure encapsulating a 3x2 matrix
* **Matrix4x4** - A structure encapsulating a 4x4 matrix
* **Plane** - A structure encapsulating a 3D plane (Vector3 denoting _normal_ and a float for _distance_)
* **Quaternion** - A structure encapsulating four single precision floating point values (_x, y, z, w_)

In addition to the "core" classes, there is a basic `Vector` class that is an analog to the standard library's `Vector` class, but implemented in `C`. This class allows for arbitrary sized vectors same as its Ruby analog, but is not as optmized or feature-rich as is possible with the fixed-size vector classes.  

For each method (where applicable), there is typically a standard "pure" method, and "impure" variation that alters the object's state. All of the impure methods follow the standard Ruby convention of being suffixed with a `!`.

```ruby
# Create a vector with 3 elements
vec3 = Vector3.new(5.0, 4.0, 9.0)

norm = vec3.normalize
vec3.normalize!
```

There is a host of methods available for each class, which are outlined in detail within the documentation, and excompass all that would be expected of any vector/matrix library, and additionally many "helper" functions to efficiently perform many common and less-common operations. All of these functions are implemented the "Ruby-way", following standard Ruby style and syntax.

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/ForeverZer0/numerix. This project is intended to be a safe, welcoming space for collaboration, and contributors are expected to adhere to the [Contributor Covenant](http://contributor-covenant.org) code of conduct.

## License

The gem is available as open source under the terms of the [MIT License](https://opensource.org/licenses/MIT).

## Code of Conduct

Everyone interacting in the Numerix project’s codebases, issue trackers, chat rooms and mailing lists is expected to follow the [code of conduct](https://github.com/ForeverZer0/numerix/blob/master/CODE_OF_CONDUCT.md).