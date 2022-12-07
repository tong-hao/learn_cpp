#include <iostream>
#include <vector>

struct Index {
	std::vector<std::string> fields;
};
struct IndexResult {
	bool result;
	Index idx;
	int score;
};

enum class ExprType { RELEATION, LOGICAL };
enum class ExprKind { TAG_PROP, EDGE_PROP, CONSTANT };
struct Expresstion {
	ExprType type;
	ExprKind kind;
	Expresstion *left;
	Expresstion *right;
	std::string name;
	std::string value;
};

enum RelExpresstionOpt { EQ, GE, GT, LE, LT, NE };
struct RelExpresstion : public Expresstion {
	RelExpresstionOpt opt;
};

IndexResult selectIndex(const Expresstion &expr, Index &idx) {
	if (expr.left == nullptr || expr.right == nullptr) {
		return IndexResult{false};
	}
	if (expr.left->kind != ExprKind::TAG_PROP ||  // todo
	    expr.left->kind != ExprKind::EDGE_PROP) {
		return IndexResult{false};
	}
	if (expr.right->kind != ExprKind::CONSTANT) {
		return IndexResult{false};
	}

	if (expr.type == ExprType::RELEATION) {
		const RelExpresstion *realExpr =
		    reinterpret_cast<const RelExpresstion *>(&expr);
		switch (realExpr->opt) {
			case RelExpresstionOpt::EQ:
				return IndexResult{true, idx, 2};
			case RelExpresstionOpt::GE:
			case RelExpresstionOpt::GT:
			case RelExpresstionOpt::LE:
			case RelExpresstionOpt::LT:
				return IndexResult{true, idx, 1};

			case RelExpresstionOpt::NE:
				return IndexResult{true, idx, 0};
			default:
				return IndexResult{false};
				break;
		}
	} else {
	}
}

int main(int argc, char const *argv[]) {
	return 0;
}
