#include "includes.hpp"

std::vector<TslEntity> entityList;

std::list <std::string> menu = {};

void cheat_manager::cheat_thread()
{
	if (cfg->tips && cfg->menu_open) {
		tips();
	}

	static bool once;
    Engine = SDK::UEngine::GetEngine();
	World = SDK::UWorld::GetWorld();
	MyController = World->OwningGameInstance->LocalPlayers[0]->PlayerController;
	GameMode = World->AuthorityGameMode;
	MainGameMode = static_cast<SDK::AMainGamemode_C*>(GameMode);
	Time = static_cast<SDK::ADaynightCycle_C*>(MainGameMode->DaynightCycle);
	
	if (cfg->debug_console && !once) {
		SDK::UInputSettings::GetDefaultObj()->ConsoleKeys[0].KeyName = SDK::UKismetStringLibrary::Conv_StringToName(L"F2");
		SDK::UObject* NewObject = SDK::UGameplayStatics::SpawnObject(Engine->ConsoleClass, Engine->GameViewport);
		Engine->GameViewport->ViewportConsole = static_cast<SDK::UConsole*>(NewObject);
		once = true;
	}

	if (MyController->Pawn->IsA(SDK::AMainPlayer_C::StaticClass()) || MyController->Pawn->IsA(SDK::ACar1_C::StaticClass()))
	{
		
		if (MyController->Pawn->IsA(SDK::AMainPlayer_C::StaticClass())) {
			MyPawnPlayer = static_cast<SDK::AMainPlayer_C*>(MyController->Pawn);
			PlayerLocation = MyPawnPlayer->K2_GetActorLocation();
			Level = World->PersistentLevel;
		}

		else if (MyController->Pawn->IsA(SDK::ACar1_C::StaticClass())) {
			bool once = false;
			Car = static_cast<SDK::ACar1_C*>(MyController->Pawn);

			PlayerLocation = Car->K2_GetActorLocation();
			if (cfg->fuel) {
				Car->Diff_fuel = 0.0f;
			}
			else if (!cfg->fuel) {
				Car->Diff_fuel = 1.0f;
			}

			if (cfg->health_car) {
				Car->Health = 100.0f;
			}
		}

		exploits();

		if (cfg->esp) {
			//if (cfg->prop) {
			//	teleport();
			//}

			SDK::TArray<SDK::AActor*>& volatile Actors_list = Level->Actors;
			if (cfg->logs) {
				removed_items();
			}
			if ((actorScan && entityList.empty()) || Actors_list.Num() != ActorsNum) {
				actorScan = false;
			}
			if (!actorScan) {
				entityList.clear();
				actor_scan();
				actorScan = true;
			}
			if (!entityList.empty()) {
				ESP();
			}
		}
	}
	if (!MyController->Pawn->IsA(SDK::AMainPlayer_C::StaticClass()) && !MyController->Pawn->IsA(SDK::ACar1_C::StaticClass()))
	{
		cfg->time = cfg->noclip = cfg->esp = cfg->game_time = cfg->logs = false;
		menu.clear();
		entityList.clear();
		actorScan = false;
	}
}

void cheat_manager::actor_scan() {
	int i = -1;
	SDK::TArray<SDK::AActor*>& volatile Actors_list = Level->Actors;
	ActorsNum = Actors_list.Num();
	std::vector<TslEntity> tmpList;

	for (SDK::AActor* Actor : Actors_list)
	{
		if (!Actor)
			continue;
		if (Actor->GetName() == MyPawnPlayer->GetName())
			continue;
		
		i++;

		Pawn = static_cast<SDK::APawn*>(Actor);

		TslEntity tslEntity{ };

		tslEntity.index += i;
		tslEntity.ActorObject = Actor;
		tslEntity.PawnActor = Pawn;
		tslEntity.Name = Pawn->GetName();
	
		tmpList.push_back(tslEntity);
	}
	entityList = tmpList;
}

void cheat_manager::ESP() {
	auto entityListCopy = entityList;
	drawings Draw;
	auto& io = ImGui::GetIO();

	for (unsigned long i = 0; i < entityListCopy.size(); ++i) {
		TslEntity entity = entityListCopy[i];
		
		if (!KismetSystemLib->IsValid(entity.PawnActor)) {
			menu.push_back(entity.Name);
			actorScan = false;
			continue;
		}		
		
		// test props spawn/usage //
		
		//if (entity.ActorObject-> IsA(SDK::AProp_batts_C::StaticClass())) {
		//	AProp_C* Prop = static_cast<AProp_C*>(entity.ActorObject);
		//	AProp_batts_C* battery = static_cast<AProp_batts_C*>(Prop);
		//	battery->Energy = -1.0f;
		//}

		entity.ActorObject->GetActorBounds(true, &entity.Location, &entity.Bounds, false);
		
		if (MyController->ProjectWorldLocationToScreen(entity.Location, &Screen, false) && MyPawnPlayer->GetDistanceTo(entity.ActorObject) < (cfg->distance * 100.0f))
		{
			ImVec2 Pos(Screen.X, Screen.Y);
			if (Draw.IsOnScreen(Pos)) {
				if (cfg->box) Draw.Box3D(MyController, entity.Location, entity.Bounds);
				if (cfg->names) {
					ImGui::GetBackgroundDrawList()->AddText(Pos, ImColor(255, 255, 255), entity.Name.c_str());
					if (cfg->list_objects && !cfg->all_objects) {
						text_generate(entity.Name.c_str(), entity.Location.X, entity.Location.Y, entity.Location.Z);
					}
				}
			}
			if (cfg->lines) {
				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(static_cast<float>(io.DisplaySize.x / 2), static_cast<float>(io.DisplaySize.y)), Pos, ImColor(255, 0, 0), 0.7);
			}
		}

		if (cfg->all_objects && cfg->list_objects && cfg->names) {
			text_generate(entity.Name.c_str(), entity.Location.X, entity.Location.Y, entity.Location.Z);
		}		
		
		if (cfg->prop && cfg->esp && cfg->menu_open){
			teleportList();
			teleport(entityListCopy[i]);
		}
	}
}

void cheat_manager::exploits() {
	static bool once2, once3, once4, once5, once6, once7, thrOnce1, thrOnce2, thrOnce3 = false;

	if (cfg->menu_open && !once5) {
		cfg->pause = once5 = cfg->menu_open;
	}
	else if (!cfg->menu_open && once5)
	{
		cfg->pause = once5 = cfg->menu_open;
	}
	if (!UGameplayStatics::IsGamePaused(World) && cfg->pause) {
		UGameplayStatics::SetGamePaused(World, true);
	}
	else if (UGameplayStatics::IsGamePaused(World) && !cfg->pause) {
		UGameplayStatics::SetGamePaused(World, false);
	}

	MyPawnPlayer->HulkMode = cfg->hulk;
	if (cfg->sleep) {
		MyPawnPlayer->SleepDraining = 0.0f;
	}
	if (cfg->food) {
		MyPawnPlayer->FoodDraining = 0.0f;
	}
	MainGameMode->Immortal = cfg->nodamage;
	if (cfg->time) {
		Time->SettingMultiplayer = cfg->time_change * 10.0f;
		once4 = true;
	}
	else if (!cfg->time && once4) {
		Time->SettingMultiplayer = 1.0f;
		once4 = false;
	}
	if (cfg->money && !once6) {
		MainGameMode->AddPoints(50000);
		once6 = true;
	}
	else if (once6) {
		cfg->money = false;
		once6 = false;
	}
	if (cfg->teleport && !once7) {
		MyPawnPlayer->K2_SetActorLocation(FVector(x, y, z), 0, 0, 0);
		once7 = true;
	}
	else if (once7) {
		cfg->teleport = false;
		once7 = false;
	}
	if (cfg->game_time) {
		game_time(Time->Day);
	}
	if (cfg->fly) {
		MyPawnPlayer->Noclip = cfg->fly;
		MyPawnPlayer->CharacterMovement->MovementMode = SDK::EMovementMode::MOVE_None;
		once2 = true;
	}
	if (cfg->noclip && cfg->fly) {
		MyPawnPlayer->bActorEnableCollision = 0;
		once3 = true;
	}
	else if (!cfg->fly && once2) {
		MyPawnPlayer->Noclip = cfg->fly;
		MyPawnPlayer->CharacterMovement->MovementMode = SDK::EMovementMode::MOVE_Falling;
		cfg->noclip = once2 = false;
	}
	if (!cfg->noclip && once3) {
		MyPawnPlayer->bActorEnableCollision = 1;
		once3 = false;
	}
}

void cheat_manager::game_time(float day) {
	auto& screen = ImGui::GetIO();
	ImGui::StyleColorsDark();
	ImGui::SetNextWindowPos(ImVec2(screen.DisplaySize.x - (screen.DisplaySize.x), NULL), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(60, 40));
	ImGui::Begin("Time", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);
	ImGui::SetWindowFontScale(1.5f);
	ImGui::Text("%02d:%02d", (int)fmod(day / 187.5, 24), (int)fmod(day / 3.125, 60));
	ImGui::SetWindowFontScale(1.0f);
	ImGui::End();
}

void cheat_manager::text_generate(const char* entity, float X, float Y , float Z) {
	auto& screen = ImGui::GetIO();
	ImGui::SetNextWindowPos(ImVec2(screen.DisplaySize.x - (screen.DisplaySize.x / 5), NULL), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(screen.DisplaySize.x / 5, screen.DisplaySize.y), ImGuiCond_Once);
	ImGui::StyleColorsDark();
	ImGui::Begin("List Cookies", nullptr, ImGuiWindowFlags_NoScrollbar);
	ImGui::BeginChild("Scrolling");
	ImGui::Text("%s | X:%f Y:%f Z:%f", entity, X,Y,Z);
	ImGui::EndChild();
	ImGui::End();
}

bool waypoint_getter(void* data, int index, const char** output)
{
	TslEntity* tslEntityObjects = (TslEntity*)data; //bruh
	TslEntity& current_waypoint = tslEntityObjects[index];
	*output = current_waypoint.Name.c_str(); //change

	return true;
}

void cheat_manager::teleportList() {
	ImGui::SetNextWindowSize({ 400, 700 });
	ImGui::SetNextWindowPos({ 500, 200 }, ImGuiCond_Once);
	ImGui::StyleColorsDark();
	ImGui::Begin("Teleport objects", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollWithMouse);
	ImGui::PushItemWidth(-1);
	ImGui::ListBox("##List box", &ChooseObject, waypoint_getter, entityList.data(), entityList.size(), 35);
	ImGui::End();
}

void cheat_manager::teleport(TslEntity entity) {
	bool once = false;

	if (!once && ChooseObject != item_previous) {
		if (entity.index == ChooseObject) {
			item_previous = ChooseObject;
			once = true;
			ActorObject = static_cast<AActor*>(entity.ActorObject); //rechange offset 0x08? props or 0x19B 
			PawnActor = static_cast<APawn*>(entity.PawnActor);  //rechange offset 0x08? props or 0x19B 
		}
	}

	else if (once && ChooseObject == item_previous) once = false;

	ImGui::Begin("Teleport objects", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollWithMouse);
	ImGui::SetCursorPosY(640);
	if (ImGui::Button("Teleport to me", ImVec2(400, 30)) && !once) {
		PawnActor->K2_SetActorLocation(PlayerLocation, NULL, NULL, NULL);
	}
	ImGui::SetCursorPosY(670);
	if (ImGui::Button("Spawn to me", ImVec2(400, 30)) && !once) {
			//AProp_C* test = static_cast<AProp_C*>(ActorObject);// 0x018 child objects //todo
			//	if (test->GetName().c_str() == ActorObject->GetName().c_str()) {
			//}
			//MainGameMode->SpawnPropThroughGamemode(ActorObject->Name, ActorObject->GetTransform(), 1, &ActorObject);

			UVictoryBPFunctionLibrary::SpawnActorIntoLevel(World, PawnActor->Class, World->Name, PlayerLocation, FRotator(0), 0);
		}
	ImGui::End();
}

void cheat_manager::removed_items() {
	auto& screen = ImGui::GetIO();
	ImGui::SetNextWindowPos(ImVec2(screen.DisplaySize.x - ((screen.DisplaySize.x / 5)*2), NULL), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(screen.DisplaySize.x / 5, screen.DisplaySize.y / 3), ImGuiCond_Once);
	ImGui::StyleColorsDark();
	ImGui::Begin("Missing Cookies(", nullptr, ImGuiWindowFlags_NoScrollbar);
	ImGui::BeginChild("Scrolling removes Items");
	for (std::string men : menu) {
		ImGui::Text(men.c_str());
	}
	if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
		ImGui::SetScrollHereY(1.0f);
	}
	ImGui::EndChild();
	ImGui::End();
}

void cheat_manager::tips() {
	auto& screen = ImGui::GetIO();
	ImGui::SetNextWindowSize(ImVec2(930, 400), ImGuiCond_Once);
	ImGui::SetNextWindowPos(ImVec2(screen.DisplaySize.x * 0.5f, screen.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	ImGui::StyleColorsDark();
	ImGui::Begin("Credit: github.com/Vyollet", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);
	ImGui::Text("0. Don't use this unless you want to ruin your experience with the game.\
		\nI'm serious. Not all people, but for most people it will ruin the experience.\
		\n\n1. Don't use this program to ruin other people's experiences, please.\
		\nOnly use it for your own research.\
		\n\n2. Don't use clock in tutorial levels. \
		\n2.1 On the pre-alpha 0.8 (pa08_0011) pre-test, there is no map border crossing in the first tutorial level, you can disable collision. \
		\nDon't forget to return collision it when switching to tutorial3_1.\
        \n2.2 No boundary traversal in classic levels when collision is destroyed. \
		\n\n3. Sound is buggy when accelerating time, be careful. \
        \nThere is also a chance to screw up the save if you rewind a few days forward, which will ruin the ability to save the game.\
		\n\n4. If your computer is weak enough, don't use high distance, box and line rendering.\
        \n\n5. When teleporting, use the collision disable to avoid getting into backrooms. \
        \n\n6. Teleportation has been limited to props (partially) so as not to cause random crashes when moving certain objects.\
		\n\nHave fun! \
		");
	ImGui::SetCursorPos(ImVec2(780, 330));
	ImGui::Text("Yours faithfully, Ray");
	ImGui::SetCursorPos(ImVec2(0, 360));
	if (ImGui::Button("I Understand!", ImVec2(930, 40)))
		cfg->tips = false;
	ImGui::End();
}