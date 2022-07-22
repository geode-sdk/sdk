#include "Shared.hpp"

namespace { namespace format_strings {
	char const* source_start = R"CAC(
#include <Geode/Bindings.hpp>
#include <Geode/utils/addresser.hpp>
#include <Geode/utils/casts.hpp>
#include <Geode/modify/Addresses.hpp>
#include <Geode/modify/Types.hpp>
using namespace geode;
using namespace geode::cast;
using cocos2d::CCDestructor;
using namespace geode::core::meta; // Default convention
using namespace geode::core::meta::x86; // Windows x86 conventions, Function
using namespace geode::modifier; // types
)CAC";

	char const* declare_member = R"GEN(
types::ret{index} {class_name}::{function_name}({parameters}){const_whitespace}{const} {{
	auto func = Function<types::meta{index}, {convention}>({{addresses::address{index}()}});
	return func(this{argument_comma}{arguments});
}}
)GEN";

	char const* declare_virtual = R"GEN(
types::ret{index} {class_name}::{function_name}({parameters}){const_whitespace}{const} {{
	auto self = addresser::thunkAdjust((types::member{index})(&{class_name}::{function_name}), this);
	auto func = Function<types::meta{index}, {convention}>({{addresses::address{index}()}});
	return func(self{argument_comma}{arguments});
}}
)GEN";

	char const* declare_static = R"GEN(
types::ret{index} {class_name}::{function_name}({parameters}){const_whitespace}{const} {{
	auto func = Function<types::meta{index}, {convention}>({{addresses::address{index}()}});
	return func({arguments});
}}
)GEN";

	char const* declare_destructor = R"GEN(
{class_name}::{function_name}({parameters}) {{
	// basically we destruct it once by calling the gd function, 
	// then lock it, so that other gd destructors dont get called
	if (CCDestructor::lock(this)) return;
	auto func = Function<types::meta{index}, {convention}>({{addresses::address{index}()}});
	func(this{argument_comma}{arguments});
	// we need to construct it back so that it uhhh ummm doesnt crash
	// while going to the child destructors
	auto thing = new (this) {class_name}(std::monostate(), sizeof({class_name}));
	CCDestructor::lock(this) = true;
}}
)GEN";

	char const* declare_constructor = R"GEN(
{class_name}::{function_name}({parameters}) : {class_name}(std::monostate(), sizeof({class_name})) {{
	// here we construct it as normal as we can, then destruct it
	// using the generated functions. this ensures no memory gets leaked
	// no crashes :pray:
	CCDestructor::lock(this) = true;
	{class_name}::~{unqualified_class_name}();
	auto func = Function<types::meta{index}, {convention}>({{addresses::address{index}()}});
	func(this{argument_comma}{arguments});
}}
)GEN";

	// requires: static, return_type, function_name, raw_parameters, const, class_name, definition
	char const* ool_function_definition = R"GEN(
{return} {class_name}::{function_name}({parameters}){const_whitespace}{const} {definition}
)GEN";
}}

std::string generateGDSource(Root const& root) {
	vector<ClassDefinition*> in_order;
	string output(::format_strings::source_start);

	for (auto& [name, c] : root.classes) {
		

		for (auto& f : c.functions) {            
			if (f.is_defined) {
				output += fmt::format(::format_strings::ool_function_definition,
					fmt::arg("function_name", codegen::getFunctionName(f)),
					fmt::arg("const", codegen::getConst(f)),
				    fmt::arg("const_whitespace", codegen::getConstWhitespace(f)),
					fmt::arg("class_name", codegen::getClassName(f)),
                    fmt::arg("parameters", codegen::getParameters(f)),
                    fmt::arg("index", codegen::getIndex(f)),
					fmt::arg("definition", f.definition),
				    fmt::arg("return", f.return_type)
				);
				continue;
			}
			if (!codegen::isFunctionDefinable(f)) continue; // Function not implemented, skip

			char const* used_declare_format;

			switch (f.function_type) {
				case kVirtualFunction:
					used_declare_format = ::format_strings::declare_virtual;
					break;
				case kRegularFunction:
					used_declare_format = ::format_strings::declare_member;
					break;
				case kStaticFunction:
					used_declare_format = ::format_strings::declare_static;
					break;
				case kDestructor:
					used_declare_format = ::format_strings::declare_destructor;
					break;
				case kConstructor:
					used_declare_format = ::format_strings::declare_constructor;
					break;
			}

			// cout << "dsffdssd" << endl;
			output += fmt::format(used_declare_format,
				fmt::arg("class_name", codegen::getClassName(f)),
				fmt::arg("unqualified_class_name", codegen::getUnqualifiedClassName(f)),
				fmt::arg("const", codegen::getConst(f)),
				fmt::arg("const_whitespace", codegen::getConstWhitespace(f)),
				fmt::arg("convention", codegen::getConvention(f)),
				fmt::arg("function_name", codegen::getFunctionName(f)),
				fmt::arg("index", codegen::getIndex(f)),
				fmt::arg("parameters", codegen::getParameters(f)),
				fmt::arg("parameter_types", codegen::getParameterTypes(f)),
				fmt::arg("arguments", codegen::getArguments(f)),
				fmt::arg("parameter_comma", codegen::getParameterComma(f)),
				fmt::arg("parameter_type_comma", codegen::getParameterTypeComma(f)),
				fmt::arg("argument_comma", codegen::getArgumentComma(f))
			);
		}
		if (codegen::platform == kMac || codegen::platform == kIos) {
			for (auto& i : c.inlines) {
				if (c.name.find("cocos2d") == string::npos) continue; // cocos inlines
				output += i.inlined + "\n";
			}
		}
	}

	return output;
}
