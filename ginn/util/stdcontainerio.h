#ifndef GINN_UTIL_STDCONTAINERIO_H
#define GINN_UTIL_STDCONTAINERIO_H

#include <ostream>
#include <string>
#include <vector>

#include <ginn/util/fmt.h>

namespace ginn {

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
  os << fmt::format("{{{}}}", fmt::join(v, ", "));
  return os;
}

} // namespace ginn

#endif