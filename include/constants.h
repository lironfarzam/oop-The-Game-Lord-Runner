
#pragma once

// number of lives for player
const static int NUM_LIVES = 3;

const static char PLAYER = '@';
const static char ENEMY = '%';
const static char POLE = '-';
const static char LADDER = 'H';
const static char WALL = '#';
const static char COIN = '*';
const static char EMPTY = ' ';
const static char GIFT = '+';
const static char GIFT4 = '!';

const static int WALL_IMG = 0;
const static int PLAYER_IMG = 1;
const static int ENEMY_IMG = 2;
const static int LADDER_IMG = 3;
const static int POLE_IMG = 4;
const static int COIN_IMG = 5;
const static int GIFT_IMG = 6;
const static int RUNNER_IMG = 7;
const static int GUARD_IMG = 8;
const static int COVER_IMG = 9;
const static int COVER_HELP_IMG = 10;



const int BEEP_SOUND = 0;
const int BORN_SOUND = 1;
const int DEAD_SOUND = 2;
const int DIG_SOUND = 3;
const int DOWN_SOUND = 4;
const int ENDING_SOUND = 5;
const int FALL_SOUND = 6;
const int GET_GOLD_SOUND = 7;
const int GOLD_FINISG_SOUND = 8;
const int PASS_SOUND = 9;
const int SCORE_BELL_SOUND = 10;
const int SCORE_COUNT_SOUND = 11;
const int SCORE_ENDING_SOUND = 12;
const int TRAP_SOUND = 13;

const int MENU_WIDTH = 1120;
const int MENU_HEIGHT = 768;

const int BUTTON_WIDTH = 220;
const int BUTTON_HEIGHT = 160;

const int BONUS_TO_LIVES = 1;
const int BONUS_TO_SCORE = 100;


const int MAX_HEALTH = 3;
const int BONUS_LEVEL = 50;
const int COIN_FACTOR = 2;


constexpr auto ShapeHeight = 44.f;
constexpr auto ShapeWidth = 40.f;

constexpr auto ShapeSpeed = ShapeWidth * 3;

constexpr auto ANIMATION_SPEED = 0.1f;

const static int STATUS_HEIGHT = 80;

constexpr auto GAME_OVER_MESSAGE = "Game Over !";
constexpr auto WELCOME_MESSAGE = "Welcome";



