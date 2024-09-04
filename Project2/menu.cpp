#include "includes.hpp"

void DrawSeparator(const USHORT& extend)
{
	ImVec2 pos = ImGui::GetCursorScreenPos();
	ImGui::GetForegroundDrawList()->AddLine(
		pos,																				
		{ pos.x + extend, pos.y },															
		(ImColor)ImGui::GetStyle().Colors[ImGuiCol_Separator],								
		1.f);																				
}

void menu_imgui::cheat_gui()
{
	float powerDistance = 10.0f;
	float power = 2.0f;
	float final_cursor_pos = ImGui::GetCursorPosX();
	float Log_cursor_pos = ImGui::GetCursorPosX();
	auto& io = ImGui::GetIO();

	if (!cfg->init_hooks) {
		static char Login[128] = "Enter the login";
		static char Password[128] = "Enter the password";
		static bool once;

		ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));

		ImVec2 WindowSize(750, 385);

		ImGui::SetNextWindowSize(WindowSize, ImGuiCond_Once);

		ImGui::Begin("Authorisation panel", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollWithMouse);
		ImGui::Columns(2);
		ImGui::SetColumnOffset(1, 375);

		ImGui::TextUnformatted("@@@@@@@@@#+%@@@@@@@@%*+++++++*%@@@@@@@@%+#@@@@@@@@@");
		ImGui::TextUnformatted("@@@@@@#=%@@@@@@%*+++++++++++++++++*@@@@@@@%=%@@@@@@");
		ImGui::TextUnformatted("@@@@*=@@@@@@@*::+++++++++++++++++++::#@@@@@@@=#@@@@");
		ImGui::TextUnformatted("@@%-%@@@@@@%+++++--===++++++++==--=++++@@@@@@@#-%@@");
		ImGui::TextUnformatted("@==@@@@@@@%++++*++++++-:...:-+++++*+++++%@@@@@@@==@");
		ImGui::TextUnformatted("-+@@@@@@@%+++++***+-..........:-+**++++++@@@@@@@@+-");
		ImGui::TextUnformatted("+@@@@@@@@#+++++++--:...........:--=++++++#@@@@@@@@=");
		ImGui::TextUnformatted("@@@@@@@@@*+++++-...................-++++**@@@@@@@@%");
		ImGui::TextUnformatted("@@@@@@@@%#++++=...=++=.......=++=:..-++++#@@@@@@@@@");
		ImGui::TextUnformatted("@---:-:+#*+++#::::::...........::::::*+++##+:--:--@");
		ImGui::TextUnformatted("@@#:::::+*+*@@@@@@@@#:.......:%@@@@@@@@++#+:::::#@@");
		ImGui::TextUnformatted("@@@@=::::++++%#+%@@@%=.......+%@@@%+%%+++*::::=@@@@");
		ImGui::TextUnformatted("@@@@@@#-=++++++#-*++:.........:***-#+++++*:-#@@@@@@");
		ImGui::TextUnformatted("@@@@@@@*-:=++#:.........:::.........:#+++::#@@@@@@@");
		ImGui::TextUnformatted("%@@@@@@****++%+:....................+#++****@@@@@@#");
		ImGui::TextUnformatted("-@@@@@@@@++*++%%:.....::---::.....:#%++#+*@@@@@@@@-");
		ImGui::TextUnformatted("--@@@@@@%+++#+***#+:...........:+****+#+++@@@@@@@--");
		ImGui::TextUnformatted("---%@@@@#+++***+*****#*:...-*#*****++*++++@@@@@%---");
		ImGui::TextUnformatted("----+@@@#+++**#**+**%@@@@@@@@@*******#++++%@@@=---=");
		ImGui::TextUnformatted("#=----+@#+++**#*#****::=@#**-:*******#*+++#@+:---+#");
		ImGui::TextUnformatted("@@#---:-#+++*%#*%#=:::::@%*+-:::=*#**@*+++#*----#%@");

		ImGui::NextColumn();
		ImGui::SetCursorPosX(450);

		ImGui::Text("Please Enter Username & Password");

		ImGui::SetCursorPosY(200);
		ImGui::SetCursorPosX(450);

		ImGui::InputText("  ", Login, IM_ARRAYSIZE(Login));
		ImGui::SetCursorPosX(450);
		ImGui::InputText(" ", Password, IM_ARRAYSIZE(Password));

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::SetCursorPosX(520);
		if (ImGui::Button("Authorisation", ImVec2(100, 30))) {
			cfg->init_hooks = !cfg->init_hooks;
		}

		ImGui::End();
	}

	if (cfg->init_hooks) {
		ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, NULL), ImGuiCond_Once);
		ImGui::Begin("Ariral's debug mode", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollWithMouse);
		ImGui::SetWindowSize({ 400, 350 });		
		ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
		if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
		{
			ImGui::SetCursorPosX(325);
			ImGui::SetCursorPosY(30);
			ImGui::Text("Console F2");

			if (ImGui::BeginTabItem("Buffs")) {
				ImGui::Columns(2);
				ImGui::SetColumnOffset(1, 200);
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Checkbox("Auth", &cfg->init_hooks);
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Checkbox("Pause Game", &cfg->pause);
				ImGui::Checkbox("Game Time", &cfg->game_time);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Additional window");
				ImGui::Spacing();
				ImGui::Spacing();

				ImGui::Checkbox("Fly", &cfg->fly);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Fly with collision");
				if (cfg->fly) {
					ImGui::SetCursorPosX(final_cursor_pos + 15);
					ImGui::Checkbox("Disable Collision", &cfg->noclip);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Don't use in tutorial level, it's crashed your game. \nTry to find another way.");
				}

				ImGui::Spacing();
				ImGui::Spacing();

				ImGui::Checkbox("Chad Dr. Kel", &cfg->hulk);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Big things are now lightweight");
				ImGui::Checkbox("No Damage", &cfg->nodamage);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Don't die! For Arirals...");

				ImGui::Checkbox("No need food", &cfg->food);
				ImGui::Checkbox("No need sleep", &cfg->sleep);
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Checkbox("Time", &cfg->time);
				if (cfg->time)
					ImGui::SliderFloat("Time Scale", &cfg->time_change, 0.05, 100);
				ImGui::Spacing();
				ImGui::Spacing();

				ImGui::SetCursorPosY(550 - 30);
				ImGui::Checkbox("Tips", &cfg->tips);

				ImGui::NextColumn();

				ImGui::Spacing();
				ImGui::Spacing();

				if (ImGui::Button("Add 50000 points")) {
					cfg->money = true;
				}

				ImGui::Text("Current Location:");
				ImGui::Text("X:%f\nY:%f\nZ:%f", sdk->PlayerLocation.X, sdk->PlayerLocation.Y, sdk->PlayerLocation.Z);

				static float vec4fX[1] = { 0 };
				static float vec4fY[1] = { 0 };
				static float vec4fZ[1] = { 0 };

				ImGui::InputFloat("X: ", vec4fX);
				ImGui::InputFloat("Y: ", vec4fY);
				ImGui::InputFloat("Z: ", vec4fZ);

				if (ImGui::Button("Teleport")) {
					sdk->x = vec4fX[0];
					sdk->y = vec4fY[0];
					sdk->z = vec4fZ[0];
					cfg->teleport = true;
				}
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Don't forget to turn off collision in fly so you don't get in backrooms");

				ImGui::Spacing();
				ImGui::Spacing();

				ImGui::Text("Car modding");
				ImGui::Checkbox("Fuel", &cfg->fuel);
				ImGui::Checkbox("Health", &cfg->health_car);

				ImGui::Columns(1);

				ImGui::EndTabItem();

			}

			if(ImGui::BeginTabItem("Objects")){
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Checkbox("Misc", &cfg->esp);
				if (cfg->esp) {
					final_cursor_pos = ImGui::GetCursorPosX();
					ImGui::SetCursorPosX(final_cursor_pos + 15);
					ImGui::Checkbox("Draw Distance", &cfg->draw_distance);
					if (cfg->draw_distance) {
						ImGui::SliderFloat("Distance Value", &cfg->distance, 0.1, 50000.0f, "%.3lf", ImGuiSliderFlags_Logarithmic);
					}
					ImGui::SetCursorPosX(final_cursor_pos + 15);
					ImGui::Checkbox("Names", &cfg->names);
					ImGui::SetCursorPosX(final_cursor_pos + 15);
					ImGui::Checkbox("Box", &cfg->box);
					ImGui::SetCursorPosX(final_cursor_pos + 15);
					ImGui::Checkbox("Lines", &cfg->lines);
					ImGui::Checkbox("List Objects", &cfg->list_objects);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Shows visible objects (if Names are enabled), and deleted objects");
					ImGui::Checkbox("Prop Positions", &cfg->prop);
				}
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
		ImGui::End();
	}
}

