#include <string>
#include <variant>

#include "json.h"

namespace detail {
template <std::size_t N>
struct variant_switch {
	template <typename Variant>
	void operator()(int index, nlohmann::json const& value, Variant& v) const {
		if (index == N)
			v = value.get<std::variant_alternative_t<N, Variant>>();
		else
			variant_switch<N - 1>{}(index, value, v);
	}
};

template <>
struct variant_switch<0> {
	template <typename Variant>
	void operator()(int index, nlohmann::json const& value, Variant& v) const {
		if (index == 0)
			v = value.get<std::variant_alternative_t<0, Variant>>();
		else {
			throw std::runtime_error(
			    "while converting json to variant: invalid index");
		}
	}
};
}  // namespace detail

namespace nlohmann {
template <typename... Args>
struct adl_serializer<std::variant<Args...>> {
	static void to_json(nlohmann::json& j, std::variant<Args...> const& v) {
		std::visit(
		    [&](auto&& value) {
			    j["i"] = v.index();
			    j["v"] = std::forward<decltype(value)>(value);
		    },
		    v);
	}

	static void from_json(nlohmann::json const& j, std::variant<Args...>& v) {
		auto const index = j.at("i").get<int>();
		::detail::variant_switch<sizeof...(Args) - 1>{}(index, j.at("v"), v);
	}
};
}  // namespace nlohmann
