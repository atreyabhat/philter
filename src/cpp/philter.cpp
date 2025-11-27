#include <emscripten/bind.h>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <re2/re2.h>
#include <string_view>
#include "patterns.h" 

using namespace emscripten;

struct PhilterResult {
    bool has_phi;
    std::vector<std::string> detected_types;
};

class Philter {

private:
    std::map<std::string, const RE2*> patterns;

public:
Philter() 
{
    // core
    patterns["DATE"] = &Patterns::DATE_PATTERN;
    patterns["SSN"] = &Patterns::SSN_PATTERN;
    patterns["EMAIL"] = &Patterns::EMAIL_PATTERN;
    patterns["NAME"] = &Patterns::NAME_PATTERN;
    patterns["PHONE"] = &Patterns::PHONE_PATTERN; //phone & fax
    
    // network & location
    patterns["IP_ADDRESS"] = &Patterns::IP_ADDRESS_PATTERN;
    patterns["URL"] = &Patterns::URL_PATTERN;
    patterns["ZIP_CODE"] = &Patterns::ZIP_CODE_PATTERN;
    patterns["ADDRESS"] = &Patterns::ADDRESS_PATTERN;

    // medical & account specifics
    patterns["MRN"] = &Patterns::MRN_PATTERN;
    patterns["HEALTH_PLAN"] = &Patterns::HEALTH_PLAN_PATTERN;
    patterns["ACCOUNT"] = &Patterns::ACCOUNT_PATTERN;
    // patterns["LICENSE"] = &Patterns::LICENSE_PATTERN;
    patterns["CREDIT_CARD"] = &Patterns::CREDIT_CARD_PATTERN; 

    // hardware & physical
    patterns["DEVICE_ID"] = &Patterns::DEVICE_ID_PATTERN; // MAC add
    patterns["SERIAL"] = &Patterns::SERIAL_PATTERN;       // serial nums

    // misc
    patterns["BIOMETRIC"] = &Patterns::BIOMETRIC_PATTERN;
    patterns["PHOTO"] = &Patterns::PHOTO_PATTERN;
    }

    PhilterResult filter(const std::string& input) 
    {
        std::string_view text_view(input);
        
        PhilterResult result;
        result.has_phi = false;

        // iterate through the member map
        for (const auto& [type, pattern] : patterns) {
            if (RE2::PartialMatch(text_view, *pattern)) {
                result.has_phi = true;
                result.detected_types.push_back(type);
            }
        }
        return result;
    }
};


// Binding Code, gemini generated.
EMSCRIPTEN_BINDINGS(my_module) {
    register_vector<std::string>("StringList");
    value_object<PhilterResult>("PhilterResult")
        .field("has_phi", &PhilterResult::has_phi)
        .field("detected_types", &PhilterResult::detected_types);

    class_<Philter>("Philter")
        .constructor<>()
        .function("filter", &Philter::filter);
}
