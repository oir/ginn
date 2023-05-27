#ifndef GINN_SCALAR_H
#define GINN_SCALAR_H

namespace ginn {

enum DeviceKind { CPU, GPU, NULL_DEV };

template <enum DeviceKind Kind>
struct Float {
  static const DeviceKind device_kind = Kind;
  using Raw = float;

  template <enum DeviceKind OtherKind>
  using To = Float<OtherKind>;
};

} // namespace ginn

#endif
