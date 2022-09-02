#pragma once
#include <string>

using std::string;

namespace settings
{
	const int width = 1920;
	const int height = 1080;
	const int move_of_player = 10;
	const int move_of_bullet = 5;
	const int move_of_enemy = 5;
	const string player_path_to_texture = "textures/player.png";
	const string opponent_path_to_texture = "textures/opponent.png";
	const string bullet_path_to_texture = "textures/bullet.png";
	const string path_to_font = "fonts/Subtle Curves Italic.ttf";
}