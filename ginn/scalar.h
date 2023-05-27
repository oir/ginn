#ifndef GINN_SCALAR_H
#define GINN_SCALAR_H

enum DeviceKind { CPU, GPU, NULL_DEV };

template <enum DeviceKind Kind>
struct Float {
  static const DeviceKind device_kind = Kind;
  using Raw = float;

  template <enum DeviceKind OtherKind>
  using To = Float<OtherKind>;
};

#endif
