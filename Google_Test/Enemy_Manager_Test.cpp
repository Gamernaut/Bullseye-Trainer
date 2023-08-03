#include "pch.h"

// Include relevant headers from Bulls trainer 2023
#include "../src/enemy_manager.h"
#include "../src/round_manager.h"
#include "../src/settings_manager.h"

using namespace cpv;

//TEST(EnemyManagerTest, case_1) {
//
//		RoundManager rm;
//		GameState state = GameState::kNewRound;
//		std::unique_ptr<SettingsManager> settings_manager = std::make_unique<SettingsManager>();
//		settings_manager->SetGameDifficulty(Difficulty::kRecruit);
//		rm.SetupRound(settings_manager);
//		rm.CheckGuessAgainstWinCondition(state, Coordinate(100, 100), settings_manager, Coordinate(100, 100), 180, Coordinate(100, 100), 35, 100);
//		auto res = state == GameState::kRoundPlaying;
//		EXPECT_TRUE(res);
//
//		int guesses = rm.GetRemainingGuesses();
//		EXPECT_EQ(guesses, 2);
//
//}

TEST(EnemyManagerTest, case_1) {
    
    EnemyManager    em;

    em.CreateBogey(1);
    EXPECT_EQ(em.GetBogieCount(), 1);

}

TEST(EnemyManagerTest, case_2) {

    EnemyManager    em;

    em.CreateBogey(2);
    EXPECT_EQ(em.GetBogieCount(), 2);

}

TEST(EnemyManagerTest, case_3) {

    EnemyManager    em;

    em.CreateBogey(3);
    EXPECT_EQ(em.GetBogieCount(), 3);

}
TEST(EnemyManagerTest, case_4) {

    EnemyManager    em;

    em.CreateBogey(4);
    EXPECT_EQ(em.GetBogieCount(), 3);

}

TEST(EnemyManagerTest, case_5) {

    EnemyManager    em;

    em.CreateBogey(0);
    EXPECT_EQ(em.GetBogieCount(), 0);

}

TEST(EnemyManagerTest, case_6) {

    EnemyManager    em;

    em.CreateBogey(3);
    EXPECT_EQ(em.GetBogieCount(), 3);

    em.DeleteBogies();
    EXPECT_EQ(em.GetBogieCount(), 0);
}