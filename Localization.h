#pragma once

#include <string>
#include <unordered_map>

class Localization {
 public:
    // Get the single instance of the Localization class
    static Localization& getInstance() {
        static Localization instance;   // Guaranteed to be destroyed.
        return instance;   // Instantiated on first use.
    }

    // Delete copy constructor and assignment operator
    Localization(Localization const&) = delete;
    void operator=(Localization const&) = delete;

    // Load translations for a given language
    void loadTranslations(const std::string& language,
        const std::unordered_map<std::string, std::string>& translations);

    // Set the current language
    void setLanguage(const std::string& language);

    // Get the localized message for a given key
    std::string getLocalizedMessage(const std::string& key) const;

 private:
    Localization() = default;   // Constructor is private

    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> translations_;
    std::string current_language_;
};
