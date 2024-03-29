/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include <thrift/lib/cpp2/gen/module_metadata_cpp.h>
#include "protocol/gen-cpp2/calc_metadata.h"

namespace apache {
namespace thrift {
namespace detail {
namespace md {
using ThriftMetadata = ::apache::thrift::metadata::ThriftMetadata;
using ThriftPrimitiveType = ::apache::thrift::metadata::ThriftPrimitiveType;
using ThriftType = ::apache::thrift::metadata::ThriftType;
using ThriftService = ::apache::thrift::metadata::ThriftService;
using ThriftServiceContext = ::apache::thrift::metadata::ThriftServiceContext;
using ThriftFunctionGenerator = void (*)(ThriftMetadata&, ThriftService&);


void StructMetadata<::fbthrift::calc::cpp2::AddRequest>::gen(ThriftMetadata& metadata) {
  auto res = metadata.structs.emplace("calc.AddRequest", ::apache::thrift::metadata::ThriftStruct{});
  if (!res.second) {
    return;
  }
  ::apache::thrift::metadata::ThriftStruct& calc_AddRequest = res.first->second;
  calc_AddRequest.name = "calc.AddRequest";
  calc_AddRequest.is_union = false;
  static const std::tuple<int32_t, const char*, bool, std::unique_ptr<MetadataTypeInterface>>
  calc_AddRequest_fields[] = {
    std::make_tuple(1, "num1", false, std::make_unique<Typedef>("calc.MyInteger", std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I32_TYPE))),
    std::make_tuple(2, "num2", false, std::make_unique<Typedef>("calc.MyInteger", std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I32_TYPE))),
  };
  for (const auto& f : calc_AddRequest_fields) {
    ::apache::thrift::metadata::ThriftField field;
    field.id = std::get<0>(f);
    field.name = std::get<1>(f);
    field.is_optional = std::get<2>(f);
    std::get<3>(f)->writeAndGenType(field.type, metadata);
    calc_AddRequest.fields.push_back(std::move(field));
  }
}
void StructMetadata<::fbthrift::calc::cpp2::AddResponse>::gen(ThriftMetadata& metadata) {
  auto res = metadata.structs.emplace("calc.AddResponse", ::apache::thrift::metadata::ThriftStruct{});
  if (!res.second) {
    return;
  }
  ::apache::thrift::metadata::ThriftStruct& calc_AddResponse = res.first->second;
  calc_AddResponse.name = "calc.AddResponse";
  calc_AddResponse.is_union = false;
  static const std::tuple<int32_t, const char*, bool, std::unique_ptr<MetadataTypeInterface>>
  calc_AddResponse_fields[] = {
    std::make_tuple(1, "code", false, std::make_unique<Typedef>("calc.Code", std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I32_TYPE))),
    std::make_tuple(2, "msg", false, std::make_unique<Typedef>("calc.Message", std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_STRING_TYPE))),
    std::make_tuple(3, "ret", false, std::make_unique<Typedef>("calc.MyInteger", std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I32_TYPE))),
  };
  for (const auto& f : calc_AddResponse_fields) {
    ::apache::thrift::metadata::ThriftField field;
    field.id = std::get<0>(f);
    field.name = std::get<1>(f);
    field.is_optional = std::get<2>(f);
    std::get<3>(f)->writeAndGenType(field.type, metadata);
    calc_AddResponse.fields.push_back(std::move(field));
  }
}

void ServiceMetadata<::fbthrift::calc::cpp2::CalculatorServiceSvIf>::gen_add(ThriftMetadata& metadata, ThriftService& service) {
  ::apache::thrift::metadata::ThriftFunction func;
  (void)metadata;
  func.name = "add";
  auto func_ret_type = std::make_unique<Struct< ::fbthrift::calc::cpp2::AddResponse>>("calc.AddResponse");
  func_ret_type->writeAndGenType(func.returnType, metadata);
  ::apache::thrift::metadata::ThriftField calc_CalculatorService_add_req_1;
  calc_CalculatorService_add_req_1.id = 1;
  calc_CalculatorService_add_req_1.name = "req";
  calc_CalculatorService_add_req_1.is_optional = false;
  auto calc_CalculatorService_add_req_1_type = std::make_unique<Struct< ::fbthrift::calc::cpp2::AddRequest>>("calc.AddRequest");
  calc_CalculatorService_add_req_1_type->writeAndGenType(calc_CalculatorService_add_req_1.type, metadata);
  func.arguments.push_back(std::move(calc_CalculatorService_add_req_1));
  service.functions.push_back(std::move(func));
}

void ServiceMetadata<::fbthrift::calc::cpp2::CalculatorServiceSvIf>::gen(ThriftMetadata& metadata, ThriftServiceContext& context) {
  (void) metadata;
  ::apache::thrift::metadata::ThriftService calc_CalculatorService;
  calc_CalculatorService.name = "calc.CalculatorService";
  static const ThriftFunctionGenerator functions[] = {
    ServiceMetadata<::fbthrift::calc::cpp2::CalculatorServiceSvIf>::gen_add,
  };
  for (auto& function_gen : functions) {
    function_gen(metadata, calc_CalculatorService);
  }
  context.set_service_info(std::move(calc_CalculatorService));
  ::apache::thrift::metadata::ThriftModuleContext module;
  module.set_name("calc");
  context.set_module(std::move(module));
}
} // namespace md
} // namespace detail
} // namespace thrift
} // namespace apache
