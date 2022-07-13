#include <fmt/format.h>
#include <folly/Conv.h>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

struct PrepareMsg {
	int pn_;
	std::string from_node_id_;
	std::string to_node_id_;
};

struct PromiseMsg {
	int pn_;
	std::string from_node_id_;
	std::string to_node_id_;
};

struct ProposeMsg {
	int pn_;
	std::string record_;
	std::string from_node_id_;
	std::string to_node_id_;
};

struct AcceptMsg {
	std::string from_node_id_;
	std::string record_;
};

struct ReplicationMsg {
	std::string record_;
};

class Base {
public:
	Base(const std::string& node_id) : node_id_(node_id) {
	}

	const std::string GetNodeID() const {
		return node_id_;
	}

private:
	const std::string node_id_;
};

class Proposer : public Base {
public:
	Proposer(const std::string& node_id) : Base(node_id){};
	~Proposer() = default;

	// 生成一个id，想所有的acceptor发送prepare msg
	void SendPrepareMsg();

	// 获取到一半的认可后，send propose
	void OnPromise(const PromiseMsg& m);

	//
	void SendProposeMsg(const std::string& record);

private:
	int pn_;
	std::set<std::string> promised_nodes_;
};

class Acceptor : public Base {
public:
	Acceptor(const std::string& node_id) : Base(node_id){};
	~Acceptor() = default;

	void OnPrepare(const PrepareMsg& msg);

	void SendPromiseMsg(const std::string& from_node_id);

	void OnPropose(const ProposeMsg& msg);

private:
	int max_pn_;
};

class Learner : public Base {
public:
	Learner(const std::string& node_id) : Base(node_id){};
	~Learner() = default;

	void OnAccept(const AcceptMsg& msg);
	void SendReplicateMsg(const std::string&);
	void OnReplicate(const ReplicationMsg& msg);

private:
	// <record, <node_id> >
	std::map<std::string, std::set<std::string>> records_;
};

//============================

class MemberMgr {
public:
	static MemberMgr* Instance() {
		static MemberMgr instance;
		return &instance;
	}

	Proposer* GetProposer(const std::string& node_id) {
		auto iter = proposers_.find(node_id);
		if (iter != proposers_.end()) {
			return &(iter->second);
		}
		return nullptr;
	}
	Learner* GetLearner(const std::string& node_id) {
		auto iter = learners_.find(node_id);
		if (iter != learners_.end()) {
			return &(iter->second);
		}
		return nullptr;
	}

	int AcceptorCount() {
		return acceptors_.size();
	}

	void UpdateLeader(Proposer* p) {
		leader_ = p;
	}

	Proposer* GetLeader() {
		return leader_;
	}

	void AddProposer(const Proposer p) {
		proposers_.emplace(p.GetNodeID(), p);
	}

	void AddAcceptor(const Acceptor p) {
		acceptors_.emplace(p.GetNodeID(), p);
	}

	void AddLearner(const Learner p) {
		learners_.emplace(p.GetNodeID(), p);
	}

	void ForEachProposerExce(std::function<void(Proposer&)> doTask) {
		for (auto iter = proposers_.begin(); iter != proposers_.end(); iter++) {
			doTask(iter->second);
		}
	}

	void ForEachAcceptorExce(std::function<void(Acceptor&)> doTask) {
		for (auto iter = acceptors_.begin(); iter != acceptors_.end(); iter++) {
			doTask(iter->second);
		}
	}

	void ForEachLearnerExce(std::function<void(Learner&)> doTask) {
		for (auto iter = learners_.begin(); iter != learners_.end(); iter++) {
			doTask(iter->second);
		}
	}

private:
	std::map<std::string, Proposer> proposers_;
	std::map<std::string, Acceptor> acceptors_;
	std::map<std::string, Learner> learners_;
	Proposer* leader_;
};

//============================

void Proposer::SendPrepareMsg() {
	pn_++;

	PrepareMsg p;
	p.pn_ = pn_;
	p.from_node_id_ = GetNodeID();
	auto task = [&p](Acceptor& a) { a.OnPrepare(p); };

	// send prepare msg to all accepter;
	MemberMgr::Instance()->ForEachAcceptorExce(task);
}

void Proposer::OnPromise(const PromiseMsg& m) {
	promised_nodes_.emplace(m.from_node_id_);
	auto count = MemberMgr::Instance()->AcceptorCount();
	if (promised_nodes_.size() > (count / 2) + 1) {
		std::cout << fmt::format("{} is leader.\n", GetNodeID());
		MemberMgr::Instance()->UpdateLeader(this);
	}
}
void Proposer::SendProposeMsg(const std::string& record) {
	ProposeMsg msg;
	msg.pn_ = pn_;
	msg.record_ = record;
	msg.from_node_id_ = GetNodeID();
	auto task = [&msg](Acceptor& a) { a.OnPropose(msg); };

	MemberMgr::Instance()->ForEachAcceptorExce(task);
}

void Acceptor::OnPrepare(const PrepareMsg& p) {
	if (p.pn_ > max_pn_) {
		max_pn_ = p.pn_;
	}
	std::cout << fmt::format(
	    "Acceptor::OnPrepare, current_node_id:{}, pn={},  from_node_id:{}\n",
	    GetNodeID(), p.pn_, p.from_node_id_);

	this->SendPromiseMsg(p.from_node_id_);
}

void Acceptor::SendPromiseMsg(const std::string& from) {
	PromiseMsg msg;
	msg.pn_ = max_pn_;
	msg.from_node_id_ = GetNodeID();
	auto* p = MemberMgr::Instance()->GetProposer(from);
	p->OnPromise(msg);
}

void Acceptor::OnPropose(const ProposeMsg& msg) {
	if (msg.pn_ != max_pn_) {
		// send reject message
		return;
	}
	std::cout << fmt::format(
	    "Acceptor::OnPropose, current_node_id:{}, pn={}, from_node_id:{}, "
	    "record:{}\n",
	    GetNodeID(), msg.pn_, msg.from_node_id_, msg.record_);

	AcceptMsg m;
	m.from_node_id_ = GetNodeID();
	m.record_ = msg.record_;

	auto* l = MemberMgr::Instance()->GetLearner(msg.from_node_id_);
	l->OnAccept(m);
}

void Learner::OnAccept(const AcceptMsg& msg) {
	std::cout << fmt::format(
	    "Learner::OnAccept, current_node_id:{}, from_node_id:{}, record:{}\n",
	    GetNodeID(), msg.from_node_id_, msg.record_);

	// if receive majoyrity acceptors then chosen
	records_[msg.record_].emplace(msg.from_node_id_);

	auto count = MemberMgr::Instance()->AcceptorCount();
	if (records_[msg.record_].size() > (count / 2) + 1) {
		// chosen
		std::cout << fmt::format("chosen: {}\n", msg.record_);

		// copy to other learners
		this->SendReplicateMsg(msg.record_);
	}
}

void Learner::SendReplicateMsg(const std::string& record) {
	ReplicationMsg msg;
	msg.record_ = record;
	auto task = [&msg, this](Learner& l) {
		if (l.GetNodeID() == this->GetNodeID()) {
			return;
		}
		l.OnReplicate(msg);
	};

	MemberMgr::Instance()->ForEachLearnerExce(task);
}

void Learner::OnReplicate(const ReplicationMsg& msg) {
	std::cout << fmt::format(
	    "Learner::OnReplicate, current_node_id:{}, record:{}\n", GetNodeID(),
	    msg.record_);
}

//============================
int main(int argc, char const* argv[]) {
	for (int i = 1; i < 4; i++) {
		auto node_id = "node" + folly::to<std::string>(i);
		Proposer p(node_id);
		MemberMgr::Instance()->AddProposer(p);

		Acceptor a(node_id);
		MemberMgr::Instance()->AddAcceptor(a);

		Learner l(node_id);
		MemberMgr::Instance()->AddLearner(l);
	}
	MemberMgr::Instance()->ForEachProposerExce(
	    [](auto& r) { std::cout << r.GetNodeID() << std::endl; });

	// node1 as master
	auto* proposer = MemberMgr::Instance()->GetProposer("node1");
	proposer->SendPrepareMsg();

	//
	auto* leader = MemberMgr::Instance()->GetLeader();
	leader->SendProposeMsg("hello A");

	return 0;
}