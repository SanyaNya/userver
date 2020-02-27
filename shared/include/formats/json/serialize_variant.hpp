#pragma once

#include <variant>

#include <formats/json/value_builder.hpp>
#include <formats/serialize/to.hpp>

namespace formats::serialize {

template <typename... Types>
formats::json::Value Serialize(const std::variant<Types...>& value,
                               To<::formats::json::Value>) {
  return std::visit(
      [](const auto& item) {
        return formats::json::ValueBuilder(item).ExtractValue();
      },
      value);
}

}  // namespace formats::serialize