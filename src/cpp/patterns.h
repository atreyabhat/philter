#pragma once
#include <re2/re2.h>

//patterns used from microsoft presidio 

namespace Patterns {

    // 1. DATE
    inline const RE2 DATE_PATTERN(
        R"((?i)(?:)"
        R"(\b(\d{4}-[01]\d-[0-3]\dT[0-2]\d:[0-5]\d:[0-5]\d\.\d+([+-][0-2]\d:[0-5]\d|Z))|)" 
        R"((\d{4}-[01]\d-[0-3]\dT[0-2]\d:[0-5]\d:[0-5]\d([+-][0-2]\d:[0-5]\d|Z))|)"
        R"((\d{4}-[01]\d-[0-3]\dT[0-2]\d:[0-5]\d([+-][0-2]\d:[0-5]\d|Z))|)"
        R"(\b(([1-9]|0[1-9]|1[0-2])/([1-9]|0[1-9]|[1-2][0-9]|3[0-1])/(\d{4}|\d{2}))\b|)" 
        R"(\b(([1-9]|0[1-9]|[1-2][0-9]|3[0-1])/([1-9]|0[1-9]|1[0-2])/(\d{4}|\d{2}))\b|)" 
        R"(\b(\d{4}/([1-9]|0[1-9]|1[0-2])/([1-9]|0[1-9]|[1-2][0-9]|3[0-1]))\b|)" 
        R"(\b(([1-9]|0[1-9]|1[0-2])-([1-9]|0[1-9]|[1-2][0-9]|3[0-1])-\d{4})\b|)" 
        R"(\b(([1-9]|0[1-9]|[1-2][0-9]|3[0-1])-([1-9]|0[1-9]|1[0-2])-\d{4})\b|)" 
        R"(\b(\d{4}-([1-9]|0[1-9]|1[0-2])-([1-9]|0[1-9]|[1-2][0-9]|3[0-1]))\b|)" 
        R"(\b(([1-9]|0[1-9]|[1-2][0-9]|3[0-1])\.([1-9]|0[1-9]|1[0-2])\.(\d{4}|\d{2}))\b|)" 
        R"(\b(([1-9]|0[1-9]|[1-2][0-9]|3[0-1])-(JAN|FEB|MAR|APR|MAY|JUN|JUL|AUG|SEP|OCT|NOV|DEC)-(\d{4}|\d{2}))\b|)"
        R"(\b((JAN|FEB|MAR|APR|MAY|JUN|JUL|AUG|SEP|OCT|NOV|DEC)-(\d{4}|\d{2}))\b|)"
        R"(\b(([1-9]|0[1-9]|[1-2][0-9]|3[0-1])-(JAN|FEB|MAR|APR|MAY|JUN|JUL|AUG|SEP|OCT|NOV|DEC))\b|)"
        R"(\b(([1-9]|0[1-9]|1[0-2])/\d{4})\b|)"
        R"(\b(([1-9]|0[1-9]|1[0-2])/\d{2})\b)"
        R"())", 
        RE2::Quiet
    );

    // 2. CREDIT CARD
    inline const RE2 CREDIT_CARD_PATTERN(R"(\b(?:4\d{3}|5[1-5]\d{2}|6\d{3}|3[47]\d{2})[- ]?\d{4}[- ]?\d{4}[- ]?\d{4}\b)");
    
    // 3. NAME
    inline const RE2 NAME_PATTERN(R"(\b(Patient|Mr\.|Mrs\.|Ms\.|Dr\.)\s+([A-Z][a-z]+)\b)");
    
    // 4. SSN
    inline const RE2 SSN_PATTERN(R"(\b\d{3}-\d{2}-\d{4}\b)");
    
    // 5. EMAIL
    inline const RE2 EMAIL_PATTERN(R"(\b((([!#$%&'*+\-/=?^_`{|}~\w])|([!#$%&'*+\-/=?^_`{|}~\w][!#$%&'*+\-/=?^_`{|}~\.\w]{0,}[!#$%&'*+\-/=?^_`{|}~\w]))[@]\w+([-.]\w+)*\.\w+([-.]\w+)*)\b)");

    // 6. IP ADDRESS
    inline const RE2 IP_ADDRESS_PATTERN(
        R"((?i)\b(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\b|)"
        R"(\b(?:([0-9a-fA-F]{1,4}:){7,7}[0-9a-fA-F]{1,4}|([0-9a-fA-F]{1,4}:){1,7}:|([0-9a-fA-F]{1,4}:){1,6}:[0-9a-fA-F]{1,4}|([0-9a-fA-F]{1,4}:){1,5}(:[0-9a-fA-F]{1,4}){1,2}|([0-9a-fA-F]{1,4}:){1,4}(:[0-9a-fA-F]{1,4}){1,3}|([0-9a-fA-F]{1,4}:){1,3}(:[0-9a-fA-F]{1,4}){1,4}|([0-9a-fA-F]{1,4}:){1,2}(:[0-9a-fA-F]{1,4}){1,5}|[0-9a-fA-F]{1,4}:((:[0-9a-fA-F]{1,4}){1,6})|:((:[0-9a-fA-F]{1,4}){1,7}|:)|fe80:(:[0-9a-fA-F]{0,4}){0,4}%[0-9a-zA-Z]{1,}|::(ffff(:0{1,4}){0,1}:){0,1}((25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])\.){3,3}(25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])|([0-9a-fA-F]{1,4}:){1,4}:((25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])\.){3,3}(25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9]))\b|)"
        R"(::)"
    );
    
    // 7. URL
    inline const RE2 URL_PATTERN(R"((?i)\b((http|https|ftp|ftps):\/\/)?((([a-z0-9\-]+\.)+[a-z]{2,})|localhost)(:[0-9]{1,5})?(\/[^\s]*)?\b)");
    
    // 8. MRN
    inline const RE2 MRN_PATTERN(R"((?i)\b(MRN|Medical Record Number)[\s:]+#?\d+\b)");

    // 9. ZIP CODE
    inline const RE2 ZIP_CODE_PATTERN(R"(\b\d{5}(-\d{4})?\b)");
    
    // 10. ADDRESS
    inline const RE2 ADDRESS_PATTERN(R"(\b\d{1,5}\s+([A-Za-z0-9#]+\s){1,5}(Street|St\.|Avenue|Ave\.|Boulevard|Blvd\.|Road|Rd\.|Lane|Ln\.|Drive|Dr\.|Court|Ct\.|Circle|Cir\.|Way|Terrace|Ter\.)\b)");
    
    // 11. PHONE
    inline const RE2 PHONE_PATTERN(R"((?i)(\+?\d{1,2}[-.\s]?)?(\(?\d{3}\)?[-.\s]?)?\d{3}[-.\s]?\d{4})");

    // 12. DEVICE_ID 
    inline const RE2 DEVICE_ID_PATTERN(R"(\b([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})\b)");

    // 13. HEALTH_PLAN 
    inline const RE2 HEALTH_PLAN_PATTERN(R"((?i)\b(Member ID|Policy ID|Group ID)[\s:]+#?[a-zA-Z0-9]+\b)");

    // 14. ACCOUNT 
    inline const RE2 ACCOUNT_PATTERN(R"((?i)\b(Account|Acct)[\s#:]+\d+\b)");

    // LICENSE PLATE, skipping for now 
    // inline const RE2 LICENSE_PATTERN(R"((?i)\b(License|Cert)[\s#:]+[a-zA-Z0-9]+\b)");

    // 16. SERIAL 
    inline const RE2 SERIAL_PATTERN(R"((?i)\b(Serial No|S/N)[\s.:]+[a-zA-Z0-9-]+\b)");

    // 17. PHOTO
    inline const RE2 PHOTO_PATTERN(R"((?i)\b(photo of face|facial image|mugshot)\b)");

    // 18. BIOMETRIC
    inline const RE2 BIOMETRIC_PATTERN(R"((?i)\b(Biometric Data|Fingerprint|Retina Scan|Facial Recognition|Voice Print|DNA Sample)\b)");
}