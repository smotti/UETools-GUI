#include "Unreal.h"






SDK::UConsole* Unreal::Console::Get()
{
	SDK::UGameViewportClient* GameViewportClient = GameViewportClient::Get();
	if (GameViewportClient == nullptr || GameViewportClient->ViewportConsole == nullptr)
		return nullptr;

	return GameViewportClient->ViewportConsole;
}

bool Unreal::Console::Construct(const bool& ignorePresence)
{
	SDK::UGameViewportClient* GameViewportClient = GameViewportClient::Get();
	if (GameViewportClient == nullptr)
		return false;

	if (ignorePresence == false && GameViewportClient->ViewportConsole) // If presence shouldn't be ignored, we're looking up if Console already exist.
		return false;

	/*
		If Engine is present, the Console Class defined in it will be used.
		Otherwise, the default Console Class will serve as a fallback.

		Before assigning Console to the Game Viewport Client, ensure that SpawnObject() returned a valid pointer.
	*/
	SDK::UEngine* Engine = Engine::Get();
	if (SDK::UObject* objectReference = SDK::UGameplayStatics::SpawnObject(Engine ? Engine->ConsoleClass : SDK::TSubclassOf<SDK::UConsole>(SDK::UConsole::StaticClass()), GameViewportClient))
	{
		GameViewportClient->ViewportConsole = static_cast<SDK::UConsole*>(objectReference); // Clarify that newly spawned Object is of class Console.
		return true;
	}
	else
		return false;
}


bool Unreal::Console::Print(const std::wstring& wideString)
{
	const wchar_t* wCharString = wideString.c_str();
	wprintf(L"%ls\n", wCharString); // Print to std::cout (if present).

	if (SDK::APlayerController* playerController = PlayerController::Get())
	{
		playerController->ClientMessage(SDK::FString(wCharString), SDK::UKismetStringLibrary::Conv_StringToName(L"None"), 0);
		return true;
	}
	else
		return false;
}
bool Unreal::Console::Print(const std::string& string)
{
	return Print(std::wstring(string.begin(), string.end()));
}

bool Unreal::Console::Print(const int32_t& integer)
{
	return Print(std::to_wstring(integer));
}
bool Unreal::Console::Print(const uint32_t& unsignedInteger)
{
	return Print(std::to_wstring(unsignedInteger));
}

bool Unreal::Console::Print(const SDK::FVector& vector)
{
	return Print(SDK::UKismetStringLibrary::Conv_VectorToString(vector).ToWString());
}
bool Unreal::Console::Print(const SDK::FRotator& rotator)
{
	return Print(SDK::UKismetStringLibrary::Conv_RotatorToString(rotator).ToWString());
}

bool Unreal::Console::Print(SDK::UObject* objectReference)
{
	return Print(SDK::UKismetStringLibrary::Conv_ObjectToString(objectReference).ToWString());
}

bool Unreal::Console::Print()
{
	return Print(L" ");
}


bool Unreal::Console::Clear()
{
	static const std::wstring emptyLines = L" \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n ";
	return Print(emptyLines);
}






SDK::UInputSettings* Unreal::InputSettings::Get()
{
	SDK::UInputSettings* InputSettings = SDK::UInputSettings::GetDefaultObj();
	return InputSettings ? InputSettings : nullptr;
}


bool Unreal::InputSettings::AssignConsoleBindings()
{
	SDK::UInputSettings* InputSettings = InputSettings::Get();
	if (InputSettings == nullptr)
		return false;

	int32_t bindingsNum = InputSettings->ConsoleKeys.Num();
	if (bindingsNum > 0)
		InputSettings->ConsoleKeys[0].KeyName = SDK::UKismetStringLibrary::Conv_StringToName(L"Tilde");
	if (bindingsNum > 1)
		InputSettings->ConsoleKeys[1].KeyName = SDK::UKismetStringLibrary::Conv_StringToName(L"F10");
	if (bindingsNum > 2)
		InputSettings->ConsoleKeys[2].KeyName = SDK::UKismetStringLibrary::Conv_StringToName(L"¸");

	return true;
}






SDK::UGameViewportClient* Unreal::GameViewportClient::Get()
{
	SDK::UEngine* Engine = Engine::Get();
	if (Engine == nullptr || Engine->GameViewport == nullptr)
		return nullptr;

	return Engine->GameViewport;
}






SDK::UEngine* Unreal::Engine::Get()
{
	SDK::UEngine* Engine = SDK::UEngine::GetEngine();
	return Engine ? Engine : nullptr;
}






SDK::UGameInstance* Unreal::GameInstance::Get()
{
	SDK::UWorld* World = World::Get();
	if (World == nullptr)
		return nullptr;

	SDK::UGameInstance* GameInstance = SDK::UGameplayStatics::GetGameInstance(World);
	if (GameInstance == nullptr)
		return nullptr;

	return GameInstance;
}






SDK::AGameModeBase* Unreal::GameMode::Get()
{
	SDK::UWorld* World = World::Get();
	if (World == nullptr)
		return nullptr;

	SDK::AGameModeBase* GameMode = SDK::UGameplayStatics::GetGameMode(World);
	if (GameMode == nullptr)
		return nullptr;

	return GameMode;
}







SDK::AGameStateBase* Unreal::GameState::Get()
{
	SDK::UWorld* World = World::Get();
	if (World == nullptr)
		return nullptr;

	SDK::AGameStateBase* GameState = SDK::UGameplayStatics::GetGameState(World);
	if (GameState == nullptr)
		return nullptr;

	return GameState;
}






std::vector<Unreal::LevelStreaming::DataStructure> Unreal::LevelStreaming::FilterByLevelPath(const std::vector<LevelStreaming::DataStructure>& levelStreamingsArray, const std::string& filter, const bool& caseSensitive)
{
	std::vector<LevelStreaming::DataStructure> outCollection;
	size_t filterLength = filter.length();

	/* Filter Level Streamings by "Search Filter" */
	for (Unreal::LevelStreaming::DataStructure levelStreaming : levelStreamingsArray)
	{
		/* "Search Filter" is empty - Actor considered a match automatically. */
		bool matchFilters = filterLength == 0;

		if (matchFilters == false)
		{
			if (caseSensitive)
				matchFilters = levelStreaming.levelPath.find(filter) != std::string::npos;
			else
			{
				std::string levelPathLowerCase = levelStreaming.levelPath;
				std::string filterLowerCase = filter;

				std::transform(levelPathLowerCase.begin(), levelPathLowerCase.end(), levelPathLowerCase.begin(),
					[](unsigned char c) { return std::tolower(c); });
				std::transform(filterLowerCase.begin(), filterLowerCase.end(), filterLowerCase.begin(),
					[](unsigned char c) { return std::tolower(c); });

				matchFilters = levelPathLowerCase.find(filterLowerCase) != std::string::npos;
			}
		}

		if (matchFilters)
			outCollection.push_back(levelStreaming); // Actor is good to go, can be considered "filtered".
	}

	return outCollection;
}


bool Unreal::LevelStreaming::LoadLevelInstance(const SDK::FString& levelPath, const SDK::FVector& locationOffset, const SDK::FRotator& rotationOffset)
{
	SDK::UWorld* world = Unreal::World::Get();
	if (world == nullptr)
		return false;

	bool outSuccess;
#ifdef UE5
	static const SDK::FString optionalLevelNameOverride;
	static SDK::TSubclassOf<SDK::ULevelStreamingDynamic> optionalLevelStreamingClass;
	SDK::ULevelStreamingDynamic::LoadLevelInstance(world, levelPath, locationOffset, rotationOffset, &outSuccess, optionalLevelNameOverride, optionalLevelStreamingClass, false);
#else
	static const SDK::FString optionalLevelNameOverride;
	SDK::ULevelStreamingDynamic::LoadLevelInstance(world, levelPath, locationOffset, rotationOffset, &outSuccess, optionalLevelNameOverride);
#endif

	return outSuccess;
}






SDK::UWorld* Unreal::World::Get()
{
	SDK::UWorld* World = SDK::UWorld::GetWorld();
	return World ? World : nullptr;
}






SDK::APawn* Unreal::Pawn::Get(const int32_t& playerIndex)
{
	SDK::UWorld* World = World::Get();
	if (World == nullptr)
		return nullptr;

	SDK::APawn* Pawn = SDK::UGameplayStatics::GetPlayerPawn(World, playerIndex);
	if (Pawn == nullptr)
		return nullptr;

	return Pawn;
}






bool Unreal::CheatManager::Construct(const bool& ignorePresence)
{
	SDK::APlayerController* PlayerController = PlayerController::Get();
	if (PlayerController == nullptr)
		return false;

	if (ignorePresence == false && PlayerController->CheatManager) // If presence shouldn't be ignored, we're looking up if Cheat Manager already exist.
		return false;

	if (PlayerController->CheatClass == nullptr) // If Player Controller has no cheating class specified, fallback to default Cheat Manager class.
		PlayerController->CheatClass = SDK::UCheatManager::StaticClass();

	/* Before assigning Cheat Manager to the Player Controller, ensure that SpawnObject() returned a valid pointer. */
	if (SDK::UObject* objectReference = SDK::UGameplayStatics::SpawnObject(PlayerController->CheatClass, PlayerController))
	{
		PlayerController->CheatManager = static_cast<SDK::UCheatManager*>(objectReference); // Clarify that newly spawned Object is of class Cheat Manager.
		return true;
	}
	else
		return false;
}






SDK::APlayerController* Unreal::PlayerController::Get(const int32_t& playerIndex)
{
	SDK::UWorld* World = World::Get();
	if (World == nullptr)
		return nullptr;

	SDK::APlayerController* PlayerController = SDK::UGameplayStatics::GetPlayerController(World, playerIndex);
	if (PlayerController == nullptr)
		return nullptr;

	return PlayerController;
}






SDK::ACharacter* Unreal::Character::Get(const int32_t& playerIndex)
{
	SDK::UWorld* World = World::Get();
	if (World == nullptr)
		return nullptr;

	SDK::ACharacter* Character = SDK::UGameplayStatics::GetPlayerCharacter(World, playerIndex);
	if (Character == nullptr)
		return nullptr;

	return Character;
}


int32_t Unreal::Character::GetJumpMaxCount(SDK::ACharacter* characterReference)
{
	return characterReference ? characterReference->JumpMaxCount : 0;
}
int32_t Unreal::Character::GetJumpMaxCount(const int32_t& playerIndex)
{
	return GetJumpMaxCount(Character::Get(playerIndex));
}


bool Unreal::Character::SetJumpMaxCount(SDK::ACharacter* characterReference, const int32_t& value)
{
	if (characterReference)
	{
		characterReference->JumpMaxCount = value;
		return true;
	}
	else
		return false;
}
bool Unreal::Character::SetJumpMaxCount(const int32_t& playerIndex, const int32_t& value)
{
	return SetJumpMaxCount(Character::Get(playerIndex), value);
}


float Unreal::Character::GetJumpVelocity(SDK::ACharacter* characterReference)
{
	if (characterReference == nullptr || characterReference->CharacterMovement == nullptr)
		return 0.0f;

	return characterReference->CharacterMovement->JumpZVelocity;
}
float Unreal::Character::GetJumpVelocity(const int32_t& playerIndex)
{
	return GetJumpVelocity(Character::Get(playerIndex));
}

bool Unreal::Character::SetJumpVelocity(SDK::ACharacter* characterReference, const float& value)
{
	if (characterReference == nullptr || characterReference->CharacterMovement == nullptr)
		return false;

	characterReference->CharacterMovement->JumpZVelocity = value;
}
bool Unreal::Character::SetJumpVelocity(const int32_t& playerIndex, const float& value)
{
	return SetJumpVelocity(Character::Get(playerIndex), value);
}


bool Unreal::Character::Jump(SDK::ACharacter* characterReference)
{
	if (characterReference == nullptr)
		return false;

	bool canJump = characterReference->CanJump();
	if (canJump)
		characterReference->Jump();

	return canJump;
}
bool Unreal::Character::Jump(const int32_t& playerIndex)
{
	SDK::ACharacter* Character = Character::Get(playerIndex);

	if (Character == nullptr)
		return false;

	bool canJump = Character->CanJump();
	if (canJump)
		Character->Jump();

	return canJump;
}


bool Unreal::Character::Launch(SDK::ACharacter* characterReference, const SDK::FVector& launchVelocity, const bool& overrideHorizontalVelocity, const bool& overrideVerticalVelocity)
{
	if (characterReference == nullptr || characterReference->CharacterMovement == nullptr
									  || characterReference->CharacterMovement->bCheatFlying == true
									  || characterReference->CharacterMovement->MovementMode == SDK::EMovementMode::MOVE_None
									  || characterReference->CharacterMovement->IsActive() == false)
		return false;

	SDK::FVector finalVelocity = launchVelocity;
	const SDK::FVector characterVelocity = characterReference->GetVelocity();

	if (overrideHorizontalVelocity == false)
	{
		finalVelocity.X += characterVelocity.X;
		finalVelocity.Y += characterVelocity.Y;
	}

	if (overrideVerticalVelocity == false)
	{
		finalVelocity.Z += characterVelocity.Z;
	}

	characterReference->CharacterMovement->PendingLaunchVelocity = finalVelocity;
	characterReference->OnLaunched(finalVelocity, overrideHorizontalVelocity, overrideVerticalVelocity);

	if (characterReference->CharacterMovement->bCheatFlying)
	{
		characterReference->SetActorEnableCollision(true);
		characterReference->CharacterMovement->bCheatFlying = false;
		characterReference->CharacterMovement->SetMovementMode(SDK::EMovementMode::MOVE_Walking, 0);
	}

	return true;
}
bool Unreal::Character::Launch(const int32_t& playerIndex, const SDK::FVector& launchVelocity, const bool& overrideHorizontalVelocity, const bool& overrideVerticalVelocity)
{
	return Launch(Character::Get(playerIndex), launchVelocity, overrideHorizontalVelocity, overrideVerticalVelocity);
}


bool Unreal::Character::Walk(SDK::ACharacter* characterReference)
{
	if (characterReference == nullptr || characterReference->CharacterMovement == nullptr)
		return false;

	characterReference->SetActorEnableCollision(true);

	characterReference->CharacterMovement->bCheatFlying = false;
	characterReference->CharacterMovement->SetMovementMode(SDK::EMovementMode::MOVE_Walking, 0);

	return true;
}
bool Unreal::Character::Walk(const int32_t& playerIndex)
{
	return Walk(Character::Get(playerIndex));
}

bool Unreal::Character::Fly(SDK::ACharacter* characterReference)
{
	if (characterReference == nullptr || characterReference->CharacterMovement == nullptr)
		return false;

	characterReference->SetActorEnableCollision(true);

	characterReference->CharacterMovement->bCheatFlying = true;
	characterReference->CharacterMovement->SetMovementMode(SDK::EMovementMode::MOVE_Flying, 0);

	return true;
}
bool Unreal::Character::Fly(const int32_t& playerIndex)
{
	return Fly(Character::Get(playerIndex));
}

bool Unreal::Character::Ghost(SDK::ACharacter* characterReference)
{
	if (characterReference == nullptr || characterReference->CharacterMovement == nullptr)
		return false;

	characterReference->SetActorEnableCollision(false);

	characterReference->CharacterMovement->bCheatFlying = true;
	characterReference->CharacterMovement->SetMovementMode(SDK::EMovementMode::MOVE_Flying, 0);

	return true;
}
bool Unreal::Character::Ghost(const int32_t& playerIndex)
{
	return Ghost(Character::Get(playerIndex));
}






std::vector<Unreal::ActorComponent::DataStructure> Unreal::ActorComponent::FilterByObjectName(const std::vector<ActorComponent::DataStructure>& componentsArray, const std::string& filter, const bool& caseSensitive)
{
	std::vector<ActorComponent::DataStructure> outCollection;
	size_t filterLength = filter.length();

	/* Filter Components by "Search Filter" */
	for (ActorComponent::DataStructure component : componentsArray)
	{
		/* "Search Filter" is empty - Component considered a match automatically. */
		bool matchFilters = filterLength == 0;

		if (matchFilters == false)
		{
			if (caseSensitive)
				matchFilters = component.objectName.find(filter) != std::string::npos;
			else
			{
				std::string classNameLowerCase = component.objectName;
				std::string filterLowerCase = filter;

				std::transform(classNameLowerCase.begin(), classNameLowerCase.end(), classNameLowerCase.begin(),
					[](unsigned char c) { return std::tolower(c); });
				std::transform(filterLowerCase.begin(), filterLowerCase.end(), filterLowerCase.begin(),
					[](unsigned char c) { return std::tolower(c); });

				matchFilters = classNameLowerCase.find(filterLowerCase) != std::string::npos;
			}
		}

		if (matchFilters)
			outCollection.push_back(component); // Component is good to go, can be considered "filtered".
	}

	return outCollection;
}






std::vector<SDK::AActor*> Unreal::Actor::GetAllDefaultOfClass(const SDK::TSubclassOf<SDK::AActor>& actorClass)
{
	std::vector<SDK::AActor*> outCollection;

	int32_t objectsNum = SDK::UObject::GObjects->Num();
	for (int i = 0; i < objectsNum; i++)
	{
		SDK::UObject* objectReference = SDK::UObject::GObjects->GetByIndex(i);

		if (objectReference == nullptr || objectReference->IsDefaultObject() == false)
			continue;

		if (objectReference->IsA(actorClass))
			outCollection.push_back(static_cast<SDK::AActor*>(objectReference)); // Clarify that found Object is of class Actor.
	}

	return outCollection;
}
std::vector<SDK::AActor*> Unreal::Actor::GetAllOfClass(const SDK::TSubclassOf<SDK::AActor>& actorClass)
{
	std::vector<SDK::AActor*> outCollection;

	int32_t objectsNum = SDK::UObject::GObjects->Num();
	for (int i = 0; i < objectsNum; i++)
	{
		SDK::UObject* objectReference = SDK::UObject::GObjects->GetByIndex(i);

		if (objectReference == nullptr || objectReference->IsDefaultObject())
			continue;

		if (objectReference->IsA(actorClass))
			outCollection.push_back(static_cast<SDK::AActor*>(objectReference)); // Clarify that found Object is of class Actor.
	}

	return outCollection;
}


std::vector<Unreal::Actor::DataStructure> Unreal::Actor::FilterByClassName(const std::vector<Actor::DataStructure>& actorsArray, const std::string& filter, const bool& caseSensitive)
{
	std::vector<Actor::DataStructure> outCollection;
	size_t filterLength = filter.length();

	/* Filter Actors by "Search Filter" */
	for (Unreal::Actor::DataStructure actor : actorsArray)
	{
		/* "Search Filter" is empty - Actor considered a match automatically. */
		bool matchFilters = filterLength == 0;

		if (matchFilters == false)
		{
			if (caseSensitive)
				matchFilters = (actor.superClassName.find(filter) != std::string::npos) || (actor.className.find(filter) != std::string::npos);
			else
			{
				std::string superClassNameLowerCase = actor.superClassName;
				std::string classNameLowerCase = actor.className;
				std::string filterLowerCase = filter;

				std::transform(superClassNameLowerCase.begin(), superClassNameLowerCase.end(), superClassNameLowerCase.begin(),
					[](unsigned char c) { return std::tolower(c); });
				std::transform(classNameLowerCase.begin(), classNameLowerCase.end(), classNameLowerCase.begin(),
					[](unsigned char c) { return std::tolower(c); });
				std::transform(filterLowerCase.begin(), filterLowerCase.end(), filterLowerCase.begin(),
					[](unsigned char c) { return std::tolower(c); });

				matchFilters = (superClassNameLowerCase.find(filterLowerCase) != std::string::npos) || (classNameLowerCase.find(filterLowerCase) != std::string::npos);
			}
		}

		if (matchFilters)
			outCollection.push_back(actor); // Actor is good to go, can be considered "filtered".
	}

	return outCollection;
}

std::vector<Unreal::Actor::DataStructure> Unreal::Actor::FilterByObjectName(const std::vector<Actor::DataStructure>& actorsArray, const std::string& filter, const bool& caseSensitive)
{
	std::vector<Actor::DataStructure> outCollection;
	size_t filterLength = filter.length();

	/* Filter Actors by "Search Filter" */
	for (Unreal::Actor::DataStructure actor : actorsArray)
	{
		/* "Search Filter" is empty - Actor considered a match automatically. */
		bool matchFilters = filterLength == 0;

		if (matchFilters == false)
		{
			if (caseSensitive)
				matchFilters = actor.objectName.find(filter) != std::string::npos;
			else
			{
				std::string classNameLowerCase = actor.objectName;
				std::string filterLowerCase = filter;

				std::transform(classNameLowerCase.begin(), classNameLowerCase.end(), classNameLowerCase.begin(),
					[](unsigned char c) { return std::tolower(c); });
				std::transform(filterLowerCase.begin(), filterLowerCase.end(), filterLowerCase.begin(),
					[](unsigned char c) { return std::tolower(c); });

				matchFilters = classNameLowerCase.find(filterLowerCase) != std::string::npos;
			}
		}

		if (matchFilters)
			outCollection.push_back(actor); // Actor is good to go, can be considered "filtered".
	}

	return outCollection;
}

std::vector<Unreal::Actor::DataStructure> Unreal::Actor::FilterByClassAndObjectName(const std::vector<Actor::DataStructure>& actorsArray, const std::string& filter, const bool& caseSensitive)
{
	std::vector<Actor::DataStructure> outCollection;
	size_t filterLength = filter.length();

	/* Filter Actors by "Search Filter" */
	for (Unreal::Actor::DataStructure actor : actorsArray)
	{
		/* "Search Filter" is empty - Actor considered a match automatically. */
		bool matchFilters = filterLength == 0;

		if (matchFilters == false)
		{
			if (caseSensitive)
				matchFilters = (actor.superClassName.find(filter) != std::string::npos) || (actor.className.find(filter) != std::string::npos) || (actor.objectName.find(filter) != std::string::npos);
			else
			{
				std::string superClassNameLowerCase = actor.superClassName;
				std::string classNameLowerCase = actor.className;
				std::string objectNameLowerCase = actor.objectName;
				std::string filterLowerCase = filter;

				std::transform(superClassNameLowerCase.begin(), superClassNameLowerCase.end(), superClassNameLowerCase.begin(),
					[](unsigned char c) { return std::tolower(c); });
				std::transform(classNameLowerCase.begin(), classNameLowerCase.end(), classNameLowerCase.begin(),
					[](unsigned char c) { return std::tolower(c); });
				std::transform(objectNameLowerCase.begin(), objectNameLowerCase.end(), objectNameLowerCase.begin(),
					[](unsigned char c) { return std::tolower(c); });
				std::transform(filterLowerCase.begin(), filterLowerCase.end(), filterLowerCase.begin(),
					[](unsigned char c) { return std::tolower(c); });

				matchFilters = (superClassNameLowerCase.find(filterLowerCase) != std::string::npos) || (classNameLowerCase.find(filterLowerCase) != std::string::npos) || (objectNameLowerCase.find(filterLowerCase) != std::string::npos);
			}
		}

		if (matchFilters)
			outCollection.push_back(actor); // Actor is good to go, can be considered "filtered".
	}

	return outCollection;
}


void Unreal::Actor::SetVisibility(SDK::AActor* actorReference, const bool& newVisibility, const bool& propagateToComponents)
{
	if (actorReference == nullptr)
		return;

	actorReference->SetActorHiddenInGame(!newVisibility);
	
	if (propagateToComponents && actorReference->RootComponent)
		actorReference->RootComponent->SetVisibility(newVisibility, true);
}


SDK::AActor* Unreal::Actor::Summon(const SDK::TSubclassOf<SDK::AActor>& actorClass, const Unreal::Transform& transform)
{
	SDK::UWorld* world = Unreal::World::Get();
	if (world == nullptr)
		return nullptr;

	static const SDK::FTransform dummyTransform = SDK::FTransform();
#ifdef UE5
	SDK::AActor* actorReference = SDK::UGameplayStatics::BeginDeferredActorSpawnFromClass(world, actorClass, dummyTransform, SDK::ESpawnActorCollisionHandlingMethod::AlwaysSpawn, nullptr, SDK::ESpawnActorScaleMethod::SelectDefaultAtRuntime);
#else
	SDK::AActor* actorReference = SDK::UGameplayStatics::BeginDeferredActorSpawnFromClass(world, actorClass, dummyTransform, SDK::ESpawnActorCollisionHandlingMethod::AlwaysSpawn, nullptr);
#endif
	if (actorReference == nullptr)
		return nullptr;

#ifdef UE5
	SDK::UGameplayStatics::FinishSpawningActor(actorReference, dummyTransform, SDK::ESpawnActorScaleMethod::SelectDefaultAtRuntime);
#else
	SDK::UGameplayStatics::FinishSpawningActor(actorReference, dummyTransform);
#endif
	actorReference->K2_TeleportTo(transform.location, transform.rotation);
	actorReference->SetActorScale3D(transform.scale);

	return actorReference;
}


SDK::AActor* Unreal::Actor::SoftSummon(const SDK::FString actorPath, const Unreal::Transform& transform)
{
	SDK::UWorld* world = Unreal::World::Get();
	if (world == nullptr)
		return nullptr;

	SDK::FSoftClassPath softClassPath = SDK::UKismetSystemLibrary::MakeSoftClassPath(actorPath);
	SDK::TSoftClassPtr<SDK::UClass> softClassPtr = SDK::UKismetSystemLibrary::Conv_SoftClassPathToSoftClassRef(softClassPath);
	SDK::UClass* actorClass = SDK::UKismetSystemLibrary::Conv_SoftClassReferenceToClass(softClassPtr);

	if (actorClass)
		return Unreal::Actor::Summon(actorClass, transform);
	else
	{
		int32_t initialStreamingLevelsNum = world->StreamingLevels.Num();
		Unreal::LevelStreaming::LoadLevelInstance(actorPath);

		/*
			LoadLevelInstance() take some time to load asset in to a memory;
			Since we can't know when asset will be loaded, we use hardcoded Sleep() assuming it will be enough.
		*/
		int8_t maximumIntervals = 10; // Sleep(10) * 10 = 100ms.
		for (int8_t waitInterval = 0; (actorClass == nullptr && waitInterval < maximumIntervals); ++waitInterval)
		{
			Sleep(10);
			actorClass = SDK::UKismetSystemLibrary::Conv_SoftClassReferenceToClass(softClassPtr);
		}

		int32_t streamingLevelsNum = world->StreamingLevels.Num();
		if (streamingLevelsNum > initialStreamingLevelsNum)
			world->StreamingLevels.Remove(streamingLevelsNum - 1); // Remove remnants of our dirty trick from streaming levels array.

		if (actorClass)
			return Unreal::Actor::Summon(actorClass, transform);
	}
}


Unreal::Transform Unreal::Actor::GetTransform(SDK::AActor* actorReference)
{
	if (actorReference == nullptr)
		return Transform();

	Unreal::Transform outTransform;
	outTransform.location = actorReference->K2_GetActorLocation();
	outTransform.rotation = actorReference->K2_GetActorRotation();
	outTransform.scale = actorReference->GetActorScale3D();

	return outTransform;
}


bool Unreal::Actor::IsValid(SDK::AActor* actorReference)
{
	if (actorReference)
	{
		/*
			Most of the Actors can be found within arrays of currently loaded game levels.

			Walking through these small arrays, we can save up on performance and only
			use full scan as our last resort - if neither of methods have found the Actor.
			
		*/
		SDK::UWorld* world = Unreal::World::Get();
		if (world)
		{
			/* Check is Actor is present within current Persistent Level. */
			if (world->PersistentLevel)
			{
				SDK::TArray<SDK::AActor*>& persistentLevelActors = world->PersistentLevel->Actors;
				for (SDK::AActor* actor : persistentLevelActors)
				{
					if (actor == actorReference)
						return SDK::UKismetSystemLibrary::IsValid(actor);
				}
			}
			
			/* Walk through all of the streaming levels. */
			if (world->StreamingLevels.Num() > 0)
			{
				for (SDK::ULevelStreaming* streamingLevel : world->StreamingLevels)
				{
					if (streamingLevel->LoadedLevel)
					{
						SDK::TArray<SDK::AActor*>& streamingLevelActors = streamingLevel->LoadedLevel->Actors;
						for (SDK::AActor* actor : streamingLevelActors)
						{
							if (actor == actorReference)
								return SDK::UKismetSystemLibrary::IsValid(actor);
						}
					}
				}
			}
		}

		/* Full scan. Extremely expensive to perform. */
		int32_t objectsNum = SDK::UObject::GObjects->Num();
		for (int i = 0; i < objectsNum; i++)
		{
			SDK::UObject* objectReference = SDK::UObject::GObjects->GetByIndex(i);

			if (objectReference == actorReference)
				return SDK::UKismetSystemLibrary::IsValid(objectReference);
		}
	}

	return false;
}






std::vector<SDK::UUserWidget*> Unreal::UserWidget::GetAllOfClass(const SDK::TSubclassOf<SDK::UUserWidget>& widgetClass)
{
	std::vector<SDK::UUserWidget*> outCollection;

	int32_t objectsNum = SDK::UObject::GObjects->Num();
	for (int i = 0; i < objectsNum; i++)
	{
		SDK::UObject* objectReference = SDK::UObject::GObjects->GetByIndex(i);

		if (objectReference == nullptr || objectReference->IsDefaultObject())
			continue;

		if (objectReference->IsA(widgetClass))
			outCollection.push_back(static_cast<SDK::UUserWidget*>(objectReference)); // Clarify that found Object is of class User Widget.
	}

	return outCollection;
}


std::vector<Unreal::UserWidget::DataStructure> Unreal::UserWidget::FilterByObjectName(const std::vector<UserWidget::DataStructure>& widgetsArray, const std::string& filter, const bool& caseSensitive, const bool& topLevelOnly)
{
	std::vector<UserWidget::DataStructure> outCollection;
	size_t filterLength = filter.length();

	/* Filter Actors by "Search Filter" */
	for (Unreal::UserWidget::DataStructure widget : widgetsArray)
	{
		if (topLevelOnly && widget.isInViewport == false)
			continue;

		/* "Search Filter" is empty - Widget considered a match automatically. */
		bool matchFilters = filterLength == 0;

		if (matchFilters == false)
		{
			if (caseSensitive)
				matchFilters = widget.objectName.find(filter) != std::string::npos;
			else
			{
				std::string classNameLowerCase = widget.objectName;
				std::string filterLowerCase = filter;

				std::transform(classNameLowerCase.begin(), classNameLowerCase.end(), classNameLowerCase.begin(),
					[](unsigned char c) { return std::tolower(c); });
				std::transform(filterLowerCase.begin(), filterLowerCase.end(), filterLowerCase.begin(),
					[](unsigned char c) { return std::tolower(c); });

				matchFilters = classNameLowerCase.find(filterLowerCase) != std::string::npos;
			}
		}

		if (matchFilters)
			outCollection.push_back(widget); // Widget is good to go, can be considered "filtered".
	}

	return outCollection;
}


SDK::UUserWidget* Unreal::UserWidget::Construct(const SDK::TSubclassOf<SDK::UUserWidget>& widgetClass)
{
	SDK::UWorld* world = Unreal::World::Get();
	if (world == nullptr)
		return nullptr;

	return SDK::UWidgetBlueprintLibrary::Create(world, widgetClass, nullptr);
}


SDK::UUserWidget* Unreal::UserWidget::SoftConstruct(const SDK::FString widgetPath)
{
	SDK::UWorld* world = Unreal::World::Get();
	if (world == nullptr)
		return nullptr;

	SDK::FSoftClassPath softClassPath = SDK::UKismetSystemLibrary::MakeSoftClassPath(widgetPath);
	SDK::TSoftClassPtr<SDK::UClass> softClassPtr = SDK::UKismetSystemLibrary::Conv_SoftClassPathToSoftClassRef(softClassPath);
	SDK::UClass* widgetClass = SDK::UKismetSystemLibrary::Conv_SoftClassReferenceToClass(softClassPtr);

	if (widgetClass)
		return Unreal::UserWidget::Construct(widgetClass);
	else
	{
		int32_t initialStreamingLevelsNum = world->StreamingLevels.Num();
		Unreal::LevelStreaming::LoadLevelInstance(widgetPath);

		/*
			LoadLevelInstance() take some time to load asset in to a memory;
			Since we can't know when asset will be loaded, we use hardcoded Sleep() assuming it will be enough.
		*/
		int8_t maximumIntervals = 10; // Sleep(10) * 10 = 100ms.
		for (int8_t waitInterval = 0; (widgetClass == nullptr && waitInterval < maximumIntervals); ++waitInterval)
		{
			Sleep(10);
			widgetClass = SDK::UKismetSystemLibrary::Conv_SoftClassReferenceToClass(softClassPtr);
		}

		int32_t streamingLevelsNum = world->StreamingLevels.Num();
		if (streamingLevelsNum > initialStreamingLevelsNum)
			world->StreamingLevels.Remove(streamingLevelsNum - 1); // Remove remnants of our dirty trick from streaming levels array.

		if (widgetClass)
			return Unreal::UserWidget::Construct(widgetClass);
	}
}






std::vector<SDK::UObject*> Unreal::Object::GetAllDefaultOfClass(const SDK::TSubclassOf<SDK::UObject>& objectClass)
{
	std::vector<SDK::UObject*> outCollection;

	int32_t objectsNum = SDK::UObject::GObjects->Num();
	for (int i = 0; i < objectsNum; i++)
	{
		SDK::UObject* objectReference = SDK::UObject::GObjects->GetByIndex(i);

		if (objectReference == nullptr || objectReference->IsDefaultObject() == false)
			continue;

		if (objectReference->IsA(objectClass))
			outCollection.push_back(objectReference);
	}

	return outCollection;
}
std::vector<SDK::UObject*> Unreal::Object::GetAllOfClass(const SDK::TSubclassOf<SDK::UObject>& objectClass)
{
	std::vector<SDK::UObject*> outCollection;

	int32_t objectsNum = SDK::UObject::GObjects->Num();
	for (int i = 0; i < objectsNum; i++)
	{
		SDK::UObject* objectReference = SDK::UObject::GObjects->GetByIndex(i);

		if (objectReference == nullptr || objectReference->IsDefaultObject())
			continue;

		if (objectReference->IsA(objectClass))
			outCollection.push_back(objectReference);
	}

	return outCollection;
}






std::vector<SDK::FString> Unreal::String::Split(const std::wstring& wideString, const wchar_t& separator, const bool& removeSeparatorSpaces)
{
	std::vector<SDK::FString> outCollection;

	if (wideString.empty())
		return outCollection;

	size_t position = 0;
	while (true)
	{
		const size_t separatorPosition = wideString.find(separator, position);

		std::wstring token = (separatorPosition == std::wstring::npos)
							 ? wideString.substr(position)
							 : wideString.substr(position, separatorPosition - position);

		if (removeSeparatorSpaces)
		{
			size_t first = 0;
			while (first < token.size() && std::iswspace(token[first]))
				++first;

			size_t last = token.size();
			while (last > first && std::iswspace(token[last - 1]))
				--last;

			token = token.substr(first, last - first);
		}

		if (token.empty() == false)
			outCollection.push_back(SDK::FString(token.c_str()));

		if (separatorPosition == std::wstring::npos)
			break;

		position = separatorPosition + 1;
	}

	return outCollection;
}