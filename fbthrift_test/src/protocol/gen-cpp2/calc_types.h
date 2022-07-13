/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#pragma once

#include <thrift/lib/cpp2/gen/module_types_h.h>

namespace apache {
namespace thrift {
namespace tag {
struct num1;
struct num2;
struct code;
struct msg;
struct ret;
}  // namespace tag
namespace detail {
#ifndef APACHE_THRIFT_ACCESSOR_num1
#define APACHE_THRIFT_ACCESSOR_num1
APACHE_THRIFT_DEFINE_ACCESSOR(num1);
#endif
#ifndef APACHE_THRIFT_ACCESSOR_num2
#define APACHE_THRIFT_ACCESSOR_num2
APACHE_THRIFT_DEFINE_ACCESSOR(num2);
#endif
#ifndef APACHE_THRIFT_ACCESSOR_code
#define APACHE_THRIFT_ACCESSOR_code
APACHE_THRIFT_DEFINE_ACCESSOR(code);
#endif
#ifndef APACHE_THRIFT_ACCESSOR_msg
#define APACHE_THRIFT_ACCESSOR_msg
APACHE_THRIFT_DEFINE_ACCESSOR(msg);
#endif
#ifndef APACHE_THRIFT_ACCESSOR_ret
#define APACHE_THRIFT_ACCESSOR_ret
APACHE_THRIFT_DEFINE_ACCESSOR(ret);
#endif
}  // namespace detail
}  // namespace thrift
}  // namespace apache

// BEGIN declare_enums

// END declare_enums
// BEGIN struct_indirection

// END struct_indirection
// BEGIN forward_declare
namespace fbthrift {
namespace calc {
namespace cpp2 {
class AddRequest;
class AddResponse;
}  // namespace cpp2
}  // namespace calc
}  // namespace fbthrift
// END forward_declare
// BEGIN typedefs
namespace fbthrift {
namespace calc {
namespace cpp2 {
typedef int32_t MyInteger;
typedef int32_t Code;
typedef ::std::string Message;

}  // namespace cpp2
}  // namespace calc
}  // namespace fbthrift
// END typedefs
// BEGIN hash_and_equal_to
// END hash_and_equal_to
namespace fbthrift {
namespace calc {
namespace cpp2 {
class AddRequest final
    : private apache::thrift::detail::st::ComparisonOperators<AddRequest> {
public:
	AddRequest() : num1(0), num2(0) {
	}
	// FragileConstructor for use in initialization lists only.
	[[deprecated("This constructor is deprecated")]] AddRequest(
	    apache::thrift::FragileConstructor,
	    ::fbthrift::calc::cpp2::MyInteger num1__arg,
	    ::fbthrift::calc::cpp2::MyInteger num2__arg);

	AddRequest(AddRequest&&) = default;

	AddRequest(const AddRequest&) = default;

	AddRequest& operator=(AddRequest&&) = default;

	AddRequest& operator=(const AddRequest&) = default;
	void __clear();

public:
	::fbthrift::calc::cpp2::MyInteger num1;

public:
	::fbthrift::calc::cpp2::MyInteger num2;

public:
	struct __isset {
		bool num1;
		bool num2;
	} __isset = {};
	bool operator==(const AddRequest& rhs) const;
	bool operator<(const AddRequest& rhs) const;

	template <typename..., typename T = ::fbthrift::calc::cpp2::MyInteger>
	FOLLY_ERASE ::apache::thrift::field_ref<const T&> num1_ref() const& {
		return {this->num1, __isset.num1};
	}

	template <typename..., typename T = ::fbthrift::calc::cpp2::MyInteger>
	FOLLY_ERASE ::apache::thrift::field_ref<const T&&> num1_ref() const&& {
		return {std::move(this->num1), __isset.num1};
	}

	template <typename..., typename T = ::fbthrift::calc::cpp2::MyInteger>
	FOLLY_ERASE ::apache::thrift::field_ref<T&> num1_ref() & {
		return {this->num1, __isset.num1};
	}

	template <typename..., typename T = ::fbthrift::calc::cpp2::MyInteger>
	FOLLY_ERASE ::apache::thrift::field_ref<T&&> num1_ref() && {
		return {std::move(this->num1), __isset.num1};
	}

	template <typename..., typename T = ::fbthrift::calc::cpp2::MyInteger>
	FOLLY_ERASE ::apache::thrift::field_ref<const T&> num2_ref() const& {
		return {this->num2, __isset.num2};
	}

	template <typename..., typename T = ::fbthrift::calc::cpp2::MyInteger>
	FOLLY_ERASE ::apache::thrift::field_ref<const T&&> num2_ref() const&& {
		return {std::move(this->num2), __isset.num2};
	}

	template <typename..., typename T = ::fbthrift::calc::cpp2::MyInteger>
	FOLLY_ERASE ::apache::thrift::field_ref<T&> num2_ref() & {
		return {this->num2, __isset.num2};
	}

	template <typename..., typename T = ::fbthrift::calc::cpp2::MyInteger>
	FOLLY_ERASE ::apache::thrift::field_ref<T&&> num2_ref() && {
		return {std::move(this->num2), __isset.num2};
	}

	::fbthrift::calc::cpp2::MyInteger get_num1() const {
		return num1;
	}

	::fbthrift::calc::cpp2::MyInteger& set_num1(
	    ::fbthrift::calc::cpp2::MyInteger num1_) {
		num1 = num1_;
		__isset.num1 = true;
		return num1;
	}

	::fbthrift::calc::cpp2::MyInteger get_num2() const {
		return num2;
	}

	::fbthrift::calc::cpp2::MyInteger& set_num2(
	    ::fbthrift::calc::cpp2::MyInteger num2_) {
		num2 = num2_;
		__isset.num2 = true;
		return num2;
	}

	template <class Protocol_>
	uint32_t read(Protocol_* iprot);
	template <class Protocol_>
	uint32_t serializedSize(Protocol_ const* prot_) const;
	template <class Protocol_>
	uint32_t serializedSizeZC(Protocol_ const* prot_) const;
	template <class Protocol_>
	uint32_t write(Protocol_* prot_) const;

private:
	template <class Protocol_>
	void readNoXfer(Protocol_* iprot);

	friend class ::apache::thrift::Cpp2Ops<AddRequest>;
};

void swap(AddRequest& a, AddRequest& b);

template <class Protocol_>
uint32_t AddRequest::read(Protocol_* iprot) {
	auto _xferStart = iprot->getCursorPosition();
	readNoXfer(iprot);
	return iprot->getCursorPosition() - _xferStart;
}

}  // namespace cpp2
}  // namespace calc
}  // namespace fbthrift
namespace fbthrift {
namespace calc {
namespace cpp2 {
class AddResponse final
    : private apache::thrift::detail::st::ComparisonOperators<AddResponse> {
public:
	AddResponse() : code(0), ret(0) {
	}
	// FragileConstructor for use in initialization lists only.
	[[deprecated("This constructor is deprecated")]] AddResponse(
	    apache::thrift::FragileConstructor,
	    ::fbthrift::calc::cpp2::Code code__arg,
	    ::fbthrift::calc::cpp2::Message msg__arg,
	    ::fbthrift::calc::cpp2::MyInteger ret__arg);

	AddResponse(AddResponse&&) = default;

	AddResponse(const AddResponse&) = default;

	AddResponse& operator=(AddResponse&&) = default;

	AddResponse& operator=(const AddResponse&) = default;
	void __clear();

public:
	::fbthrift::calc::cpp2::Code code;

public:
	::fbthrift::calc::cpp2::Message msg;

public:
	::fbthrift::calc::cpp2::MyInteger ret;

public:
	struct __isset {
		bool code;
		bool msg;
		bool ret;
	} __isset = {};
	bool operator==(const AddResponse& rhs) const;
	bool operator<(const AddResponse& rhs) const;

	template <typename..., typename T = ::fbthrift::calc::cpp2::Code>
	FOLLY_ERASE ::apache::thrift::field_ref<const T&> code_ref() const& {
		return {this->code, __isset.code};
	}

	template <typename..., typename T = ::fbthrift::calc::cpp2::Code>
	FOLLY_ERASE ::apache::thrift::field_ref<const T&&> code_ref() const&& {
		return {std::move(this->code), __isset.code};
	}

	template <typename..., typename T = ::fbthrift::calc::cpp2::Code>
	FOLLY_ERASE ::apache::thrift::field_ref<T&> code_ref() & {
		return {this->code, __isset.code};
	}

	template <typename..., typename T = ::fbthrift::calc::cpp2::Code>
	FOLLY_ERASE ::apache::thrift::field_ref<T&&> code_ref() && {
		return {std::move(this->code), __isset.code};
	}

	template <typename..., typename T = ::fbthrift::calc::cpp2::Message>
	FOLLY_ERASE ::apache::thrift::field_ref<const T&> msg_ref() const& {
		return {this->msg, __isset.msg};
	}

	template <typename..., typename T = ::fbthrift::calc::cpp2::Message>
	FOLLY_ERASE ::apache::thrift::field_ref<const T&&> msg_ref() const&& {
		return {std::move(this->msg), __isset.msg};
	}

	template <typename..., typename T = ::fbthrift::calc::cpp2::Message>
	FOLLY_ERASE ::apache::thrift::field_ref<T&> msg_ref() & {
		return {this->msg, __isset.msg};
	}

	template <typename..., typename T = ::fbthrift::calc::cpp2::Message>
	FOLLY_ERASE ::apache::thrift::field_ref<T&&> msg_ref() && {
		return {std::move(this->msg), __isset.msg};
	}

	template <typename..., typename T = ::fbthrift::calc::cpp2::MyInteger>
	FOLLY_ERASE ::apache::thrift::field_ref<const T&> ret_ref() const& {
		return {this->ret, __isset.ret};
	}

	template <typename..., typename T = ::fbthrift::calc::cpp2::MyInteger>
	FOLLY_ERASE ::apache::thrift::field_ref<const T&&> ret_ref() const&& {
		return {std::move(this->ret), __isset.ret};
	}

	template <typename..., typename T = ::fbthrift::calc::cpp2::MyInteger>
	FOLLY_ERASE ::apache::thrift::field_ref<T&> ret_ref() & {
		return {this->ret, __isset.ret};
	}

	template <typename..., typename T = ::fbthrift::calc::cpp2::MyInteger>
	FOLLY_ERASE ::apache::thrift::field_ref<T&&> ret_ref() && {
		return {std::move(this->ret), __isset.ret};
	}

	::fbthrift::calc::cpp2::Code get_code() const {
		return code;
	}

	::fbthrift::calc::cpp2::Code& set_code(::fbthrift::calc::cpp2::Code code_) {
		code = code_;
		__isset.code = true;
		return code;
	}

	const ::fbthrift::calc::cpp2::Message& get_msg() const& {
		return msg;
	}

	::fbthrift::calc::cpp2::Message get_msg() && {
		return std::move(msg);
	}

	template <typename T_AddResponse_msg_struct_setter =
	              ::fbthrift::calc::cpp2::Message>
	::fbthrift::calc::cpp2::Message& set_msg(
	    T_AddResponse_msg_struct_setter&& msg_) {
		msg = std::forward<T_AddResponse_msg_struct_setter>(msg_);
		__isset.msg = true;
		return msg;
	}

	::fbthrift::calc::cpp2::MyInteger get_ret() const {
		return ret;
	}

	::fbthrift::calc::cpp2::MyInteger& set_ret(
	    ::fbthrift::calc::cpp2::MyInteger ret_) {
		ret = ret_;
		__isset.ret = true;
		return ret;
	}

	template <class Protocol_>
	uint32_t read(Protocol_* iprot);
	template <class Protocol_>
	uint32_t serializedSize(Protocol_ const* prot_) const;
	template <class Protocol_>
	uint32_t serializedSizeZC(Protocol_ const* prot_) const;
	template <class Protocol_>
	uint32_t write(Protocol_* prot_) const;

private:
	template <class Protocol_>
	void readNoXfer(Protocol_* iprot);

	friend class ::apache::thrift::Cpp2Ops<AddResponse>;
};

void swap(AddResponse& a, AddResponse& b);

template <class Protocol_>
uint32_t AddResponse::read(Protocol_* iprot) {
	auto _xferStart = iprot->getCursorPosition();
	readNoXfer(iprot);
	return iprot->getCursorPosition() - _xferStart;
}

}  // namespace cpp2
}  // namespace calc
}  // namespace fbthrift