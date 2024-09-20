#include "Localization.h"

void Localization::loadTranslations(const std::string& language,
    const std::unordered_map<std::string, std::string>& translations) {
    translations_[language] = translations;
}

void Localization::setLanguage(const std::string& language) {
    if (translations_.find(language) != translations_.end()) {
        current_language_ = language;
    }
}

std::string Localization::getLocalizedMessage(const std::string& key) const {
    auto lang_itr = translations_.find(current_language_);
    if (lang_itr != translations_.end()) {
        auto msg_itr = lang_itr->second.find(key);
        if (msg_itr != lang_itr->second.end()) {
            return msg_itr->second;
        }
    }
    // Return the key itself if translation not found
    return key;
}
