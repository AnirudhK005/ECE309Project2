#include "core/sentinel_scanner.h"

SentinelScanner::SentinelScanner(std::string sentinel) {
    sentinel_ = sentinel;
    pending_ = "";
}

SentinelScanner::Out SentinelScanner::feed(std::string_view chunk){
    std::string newString = pending_ + std::string(chunk);

    std::size_t position = 0;
    bool sentinelFound = false;
    for(std::size_t i = 0; i + sentinel_.size() <= newString.size(); i++) {
        for(std::size_t x = 0; x < sentinel_.size(); x++){
            if(newString[i + x] == sentinel_[x]){
                sentinelFound = true;
            } else {
                sentinelFound = false;
                break;
            }
        }
        if(sentinelFound == true){
            position = i;
            std::string safeText = newString.substr(0, position);
            Out output;
            output.safe_text = safeText;
            output.sentinel_found = true;
            return output;
        }
    }

    Out output;
    std::size_t oldString = sentinel_.size() - 1;
    if(newString.size() > oldString){
        pending_ = newString.substr(newString.size() - oldString, oldString);
        output.sentinel_found = false;
        output.safe_text = newString.substr(0, newString.size() - oldString);
    } else {
        pending_ = newString;
        output.sentinel_found = false;
        output.safe_text = "";
    }
    return output;
}