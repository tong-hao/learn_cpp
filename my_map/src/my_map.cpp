#include <array>

template <typename Key, typename Value, std::size_t Size>
class FixedMap {
private:
	std::array<std::optional<std::pair<Key, Value>>, Size> data;

	std::size_t hash(const Key& key) const {
		// 这只是一个简单的哈希函数，你可能需要根据你的键类型进行修改
		return std::hash{}(key) % Size;
	}

public:
	void insert(const Key& key, const Value& value) {
		data[hash(key)] = std::make_pair(key, value);
	}

	std::optional find(const Key& key) const {
		const auto& pair = data[hash(key)];
		if (pair && pair->first == key) {
			return pair->second;
		}
		return {};
	}
};
