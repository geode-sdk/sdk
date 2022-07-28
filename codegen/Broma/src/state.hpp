#pragma once

#include <tao/pegtl.hpp>
#include <ast.hpp>

template <typename Rule>
struct run_action {};

struct ScratchData {
	Class wip_class;
	Field wip_field;
	PlatformNumber wip_bind;
	Platform wip_bind_platform;
	Type wip_type;
	FunctionBegin wip_fn_begin;

	std::vector<tao::pegtl::parse_error> errors;
};
