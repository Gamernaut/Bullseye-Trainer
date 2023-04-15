

// Include 3rd party code
#include <plog/Log.h>

// Include my code
#include "settings_manager.h"

using namespace cpv;

SettingsManager::SettingsManager() {

	// Setup access to the windows registry so logger and difficulty settings can be stored between runs.
	bulls_trainer_result = bulls_trainer_key.TryOpen(HKEY_CURRENT_USER, kRegEntry);
	if (!bulls_trainer_result) {
		// Open failed so log this but just recreate the key anyway with default settings
		PLOG_ERROR << "SettingsManager::Constructor failed to open registry key ";

		bulls_trainer_key.Create(HKEY_CURRENT_USER, kRegEntry);
		bulls_trainer_key.SetStringValue(kRegDifficulty, kDifficultyDefault);
		// TODO - convert string to enum type and set difficultly level
		// SetGameDifficulty(kDifficultyDefault);
		bulls_trainer_key.SetStringValue(kRegLogging, kLoggingDefault);
		// TODO - convert string to enum type and set logging level
		// SetLoggingLevel(kLoggingDefault);
	}
	else {
		PLOG_INFO << "SettingsManager::Constructor opened registry key";
	}
}

SettingsManager::~SettingsManager() {
	bulls_trainer_key.Close();
}


// TODO add return value to check if it worked.
void SettingsManager::WriteSettingsToRegistry() {
	PLOG_VERBOSE << "SettingsManager::WriteSettingsToRegistry() called";

	switch (GetGameDifficulty()) {
		case Difficulty::kRecruit:
			bulls_trainer_key.SetStringValue(kRegDifficulty, L"Recruit");
			break;
		case Difficulty::kRookie:
			bulls_trainer_key.SetStringValue(kRegDifficulty, L"Rookie");
			break;
		case Difficulty::kCadet:
			bulls_trainer_key.SetStringValue(kRegDifficulty, L"Cadet");
			break;
		case Difficulty::kVeteran:
			bulls_trainer_key.SetStringValue(kRegDifficulty, L"Veteran");
			break;
		case Difficulty::kAce:
			bulls_trainer_key.SetStringValue(kRegDifficulty, L"Ace");
			break;
	}

	switch (GetLoggingLevel()) {
		case 1:
			bulls_trainer_key.SetStringValue(kRegLogging, L"verbose");
			break;
		case 2:
			bulls_trainer_key.SetStringValue(kRegLogging, L"info");
			break;
		case 3:
			bulls_trainer_key.SetStringValue(kRegLogging, L"warning");
			break;
		}
}

bool SettingsManager::ReadSettingsFromRegistry() {
	PLOG_VERBOSE << "SettingsManager::ReadSettingsFromRegistry() called";

	std::wstring difficulty = bulls_trainer_key.GetStringValue(kRegDifficulty);
	std::wstring logging = bulls_trainer_key.GetStringValue(kRegLogging);

	if (difficulty == L"Recruit") {
		SetGameDifficulty(Difficulty::kRecruit);
	} else 	if (difficulty == L"Rookie") {
		SetGameDifficulty(Difficulty::kRookie);
	} else if (difficulty == L"Cadet") {
		SetGameDifficulty(Difficulty::kCadet);
	} else if (difficulty == L"Veteran") {
		SetGameDifficulty(Difficulty::kVeteran);
	} else if (difficulty == L"Ace") {
		SetGameDifficulty(Difficulty::kAce);
	} else {
		return FALSE;
	}

	if (logging == L"verbose") {
		SetLoggingLevel(1);
	} else if (logging == L"info") {
		SetLoggingLevel(2);
	} else if (logging == L"warning") {
		SetLoggingLevel(3);
	} else {
		return FALSE;
	}

	return true;
}

Difficulty& SettingsManager::GetGameDifficulty() {
    PLOG_VERBOSE << "SettingsManager::GetGameDifficulty() called";

    return game_difficulty;
}

void SettingsManager::SetGameDifficulty(const Difficulty& level) {
    PLOG_VERBOSE << "SettingsManager::GetGameDifficulty() called";

    game_difficulty = level;
}


void SettingsManager::SetLoggingLevel(int log_level) {
    PLOG_VERBOSE << "SettingsManager::SetLoggingLevel() called";

    logging_level = log_level;
}

int SettingsManager::GetLoggingLevel() const {
    PLOG_VERBOSE << "SettingsManager::GetLoggingLevel() called";

    return logging_level;
}
