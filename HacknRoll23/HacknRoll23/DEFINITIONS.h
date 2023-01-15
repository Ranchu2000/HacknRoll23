#ifndef header_H
#define header_H

//MAP
#define GRIDSIZE 50
#define MAPSIZE 56
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define TITLE "Jobpocalypse"
#define FRAME_LIMIT 120
#define VERTICAL_SYNC false
#define SPLASH_TIME 1.5f

#define PIXEL_FONT_FILEPATH "Resources/Font/Pixel.ttf"
#define LOGO_FILEPATH "Resources/Res/Logo.png"
#define TITLE_FILEPATH "Resources/Res/Title.png"
#define RETRY_ICON_FILEPATH "Resources/Res/Retry.png"
#define HOME_ICON_FILEPATH "Resources/Res/Home.png"
#define RESUME_ICON_FILEPATH "Resources/Res/ResumeIcon.png"
#define LOSS_ICON_FILEPATH "Resources/Res/Loss.png"
#define WON_ICON_FILEPATH "Resources/Res/Won.png"
#define PRIZE_ICON_FILEPATH "Resources/Res/Prize.png"

#define MELEE_ENEMY_FILEPATH "Resources/Res/MeleeEnemy.png"
#define MELEE_ENEMY_FILEPATH "Resources/Res/MeleeEnemy.png"
#define RANGED_ENEMY_FILEPATH "Resources/Res/RangedEnemy.png"
#define ENEMY_PROJ_FILEPATH "Resources/Res/ThumbsDown.png"
#define PLAYER_PROJ_FILEPATH "Resources/Res/Resume.png"
#define PLAYER_FILEPATH "Resources/Res/Player.png"

//intermission State
#define ATTACK_FILEPATH "Resources/Res/Angular.png"
#define HEALTH_FILEPATH "Resources/Res/Postgresql.png"
#define SPEED_FILEPATH "Resources/Res/Swift.png"
#define FIRING_FILEPATH "Resources/Res/Redux.png"
#define BURN_FILEPATH "Resources/Res/Firebase.png"
#define PIERCE_FILEPATH "Resources/Res/Vue.png"
#define GAME_BACKGROUND_FILEPATH "Resources/Res/Game Background.png"
#define PAUSE_ICON_FILEPATH "Resources/Res/Pause.png"

#define NAVY_COLOR 21,0,80
#define BROWN_COLOR 51,43,40,255
#define RED_COLOR 119,47,50,255
#define DARK_RED_COLOR 92,15,19,255
#define GOLD_COLOR 236,179,101,255
#define DARK_BLUE_COLOR 17,29,50,255
#define DARK_NAVY_COLOR 4,41,58,255
#define GREY_COLOR 116,143,152,255
#define PURPLE_COLOR 63,0,113
#define PINK_COLOR 251,37.f,118,255
#define DARK_GREY_COLOR 73,113,116,255
#define GREEN_COLOR 97,135,110,255

//PLAYER
#define PLAYER_TEXTURE_SHEET "Resources/Textures/PlayerSheet.png"
#define BURN_PROJECTILE ""
#define PLAYER_PROJECTILE "Resources/Textures/Resume.png"

#define PLAYER_INITIAL_SPEED 570.f
#define PLAYER_UPGRADE_SPEED 180.f
#define PLAYER_INITIAL_DAMAGE 2

#define PLAYER_UPGRADE_DAMAGE 1
#define PLAYER_INITIAL_HEALTH 20
#define PLAYER_UPGRADE_HEALTH 5
#define MAX_UPGRADE_QTY 3

//ENEMY
#define MELEE_ENEMY_TEXTURE_SHEET "Resources/Textures/MeleeEnemy.png"
#define RANGED_ENEMY_TEXTURE_SHEET "Resources/Textures/RangedEnemyComplete.png"
#define ENEMY_PROJECTILE "Resources/Textures/ThumbsDown.png"

//MUSIC
#define MAIN_MENU_MUSIC "Resources/assets/MainMenuMusic.ogg"
#define GAME_OVER_MUSIC "Resources/assets/GameOverMusic.ogg"
#define GAME_STATE_MUSIC "Resources/assets/GameStateMusic.ogg"
#define VICTORY_MUSIC "Resources/assets/VictoryMusic.ogg"

#define ENEMY_TAKE_DMG_SOUND "Resources/assets/EnemyHitSound.wav"
#define PLAYER_TAKE_DMG_SOUND "Resources/assets/TakeDamageSound.ogg"
#define SHOOT_SOUND "Resources/assets/ShootSound.ogg"


#endif