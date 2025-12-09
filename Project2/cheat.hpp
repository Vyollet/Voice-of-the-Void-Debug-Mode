using namespace SDK;

typedef struct _TslEntity
{
	int index;
	AActor* ActorObject;
	APawn* PawnActor;
	std::string Name;
	FVector Location;
	FVector Bounds;
}TslEntity;

class cheat_manager {
private:
	UEngine* Engine;
	UWorld* World;
	APlayerController* MyController;
	ULocalPlayer* LocalPlayer;
	UKismetSystemLibrary* KismetSystemLib;
	AGameModeBase* GameMode;
	AMainGamemode_C* MainGameMode;
	ADaynightCycle_C* Time;
	AMainPlayer_C* MyPawnPlayer;
	ULevel* Level;
	APawn* Pawn;
	ACar1_C* Car;
	FVector2D Screen;
	FVector Location;
	FVector bbExtends;
	FVector Location2;
	AActor* ActorObject;
	float sphereRadius = 1.0f;
	bool actorScan = false;
	int ActorsNum;
	int ChooseObject = 0;
	int item_previous = 0;
public:
	FVector PlayerLocation;
	float x;
	float y;
	float z;

	void cheat_thread();
	void exploits();
	void game_time(float day);
	void ESP();
	void actor_scan();
	void removed_items();
	void text_generate(const char* entity, float X, float Y, float Z);
	void teleportList();
	void teleport(TslEntity entity);
	void tips();
};