#include <iostream>
#include <map>
#include <memory>

struct IDBlock {
	std::shared_ptr<int64_t> p_current_id_ = std::make_shared<int64_t>(0);
	std::shared_ptr<int64_t> p_end_id_ = std::make_shared<int64_t>(0);
};

std::map<int64_t, IDBlock> id_blocks;

int64_t Next(const int64_t db_id) {
	IDBlock block = id_blocks[db_id];
	if (id_blocks.count(db_id) == 0 ||
	    *block.p_current_id_ == *block.p_end_id_) {
		*(block.p_current_id_) = 1;
		*(block.p_end_id_) = 10;
	}
	auto id = *block.p_current_id_;

	++(*block.p_current_id_);
	std::cout << id << "--" << *(id_blocks[db_id].p_current_id_) << std::endl;

	return id;
}

int main(int argc, char const *argv[]) {
	for (int i = 0; i < 10; i++) {
		std::cout << Next(1) << std::endl;
	}

	return 0;
}