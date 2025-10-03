#pragma once
#include "SDK\Engine_classes.hpp"
#include "SDK\UMG_classes.hpp"

#include "definitions.h"
#include "Windows.h"

#include <vector>
#include <algorithm>
#include <cwctype>






namespace Unreal
{
	struct Transform
	{
		SDK::FVector location;
		SDK::FRotator rotation;
		SDK::FVector scale;
	};






	class Console
	{
	public:
		struct DataStructure
		{
			SDK::UConsole* reference;
			std::string className;
			std::string objectName;
		};


		/*
		* @brief Retrieves the current instance of the Console, if one is available.
		* @return A valid pointer to the existing instance;
		*		  otherwise returns 'nullptr' to indicate that no instance is currently accessible.
		*/
		static SDK::UConsole* Get();

		/*
		* @brief Constructs a Console and assigns it to the active Game Viewport Client.
		* @param ignorePresence - If set to 'True', a new Console will always be created, even if one already exist.
		* @return 'True' if the Console was successfully created and assigned; 'False' otherwise.
		*/
		static bool Construct(const bool& ignorePresence = false);


		/*
		* @brief Outputs a message in to the Console. Multiple overloads for convenience, including Unreal Engine data types.
		* @param std::wstring
		* @param std::string
		* @param int32_t
		* @param uint32_t
		* @param FVector
		* @param FRotator
		* @param UObject*
		* @param Empty line
		* @return 'True' if the value was successfully printed; 'False' otherwise.
		*/
		static bool Print(const std::wstring& wideString);
		static bool Print(const std::string& string);

		static bool Print(const int32_t& integer);
		static bool Print(const uint32_t& unsignedInteger);

		static bool Print(const SDK::FVector& vector);
		static bool Print(const SDK::FRotator& rotator);

		static bool Print(SDK::UObject* objectReference);

		static bool Print();


		/*
		* @brief Outputs a set of empty lines in to the Console.
		* @return 'True' if the Console was successfully cleared; 'False' otherwise.
		*/
		static bool Clear();
	};


	class InputSettings
	{
	public:
		struct DataStructure
		{
			SDK::UGameViewportClient* reference;
			std::string className;
			std::string objectName;
		};


		/*
		* @brief Retrieves the current instance of the Input Settings, if one is available.
		* @return A valid pointer to the existing instance;
		*		  otherwise returns 'nullptr' to indicate that no instance is currently accessible.
		*/
		static SDK::UInputSettings* Get();


		/*
		* @brief Assigns a set of pre-determined key bindings for toggling the Console (open, expand, or close).
		* @return 'True' if the keys were successfully assigned; otherwise 'False'.
		*/
		static bool AssignConsoleBindings();
	};


	class GameViewportClient
	{
	public:
		struct DataStructure
		{
			SDK::UGameViewportClient* reference;
			std::string className;
			std::string objectName;

			Console::DataStructure console;
		};


		/*
		* @brief Retrieves the current instance of the Game Viewport Client, if one is available.
		* @return A valid pointer to the existing instance;
		*		  otherwise returns 'nullptr' to indicate that no instance is currently accessible.
		*/
		static SDK::UGameViewportClient* Get();
	};


	class Engine
	{
	public:
		struct DataStructure
		{
			SDK::UEngine* reference;
			std::string className;
			std::string objectName;

			GameViewportClient::DataStructure gameViewportClient;

			bool fixedFrameRateEnabled;
			double fixedFrameRate;

			bool smoothFrameRateEnabled;
			SDK::FFloatRange smoothFrameRateRange;

			bool subtitlesEnabled;
			bool subtitlesForcedOff;

			bool pauseOnLossOfFocus;
		};


		/*
		* @brief Retrieves the current instance of the Unreal Engine, if one is available.
		* @return A valid pointer to the existing instance; 
		*		  otherwise returns 'nullptr' to indicate that no instance is currently accessible.
		*/
		static SDK::UEngine* Get();
	};






	class OnlineSession
	{
	public:
		struct DataStructure
		{
			SDK::UOnlineSession* reference;
			std::string className;
			std::string objectName;
		};
	};


	class GameInstance
	{
	public:
		struct DataStructure
		{
			SDK::UGameInstance* reference;
			std::string className;
			std::string objectName;

			OnlineSession::DataStructure onlineSession;
		};


		/*
		* @brief Retrieves the current instance of the Game Instance, if one is available.
		* @return A valid pointer to the existing instance;
		*		  otherwise returns 'nullptr' to indicate that no instance is currently accessible.
		*/
		static SDK::UGameInstance* Get();
	};






	class GameSession
	{
	public:
		struct DataStructure
		{
			SDK::AGameSession* reference;
			std::string className;
			std::string objectName;

			int32_t maxPlayers;
			int32_t maxSpectators;
			int32_t maxPartySize;
			int8_t maxSplitScreensPerConnection;

			std::string sessionName;
		};
	};


	class GameMode
	{
	public:
		struct DataStructure
		{
			SDK::AGameModeBase* reference;
			std::string className;
			std::string objectName;

			GameSession::DataStructure gameSession;

			int32_t playersCount;
			int32_t spectatorsCount;

			bool startPlayersAsSpectators;
			std::string defaultPlayerName;

			bool useSeamlessTravel;

			std::string options;
			bool isPausable;
		};


		/*
		* @brief Retrieves the current instance of the Game Mode, if one is available.
		* @return A valid pointer to the existing instance;
		*		  otherwise returns 'nullptr' to indicate that no instance is currently accessible.
		*/
		static SDK::AGameModeBase* Get();
	};






	class GameState
	{
	public:
		struct DataStructure
		{
			SDK::AGameStateBase* reference;
			std::string className;
			std::string objectName;
		};


		/*
		* @brief Retrieves the current instance of the Game State, if one is available.
		* @return A valid pointer to the existing instance;
		*		  otherwise returns 'nullptr' to indicate that no instance is currently accessible.
		*/
		static SDK::AGameStateBase* Get();
	};


	class NetDriver
	{
	public:
		struct DataStructure
		{
			SDK::UNetDriver* reference;
			std::string className;
			std::string objectName;
		};
	};


	class DemoNetDriver
	{
	public:
		struct DataStructure
		{
			SDK::UNetDriver* reference;
			std::string className;
			std::string objectName;
		};
	};






	class WorldSettings
	{
	public:
		struct DataStructure
		{
			SDK::AWorldSettings* reference;
			std::string className;
			std::string objectName;

			bool highPriorityLoading;
			bool localHighPriorityLoading;

			double unitsToMeters;
		};
	};


	class Level
	{
	public:
		struct DataStructure
		{
			SDK::ULevel* reference;
			std::string className;
			std::string objectName;

			bool isVisible;

			WorldSettings::DataStructure worldSettings;
		};
	};


	class LevelStreaming
	{
	public:
		struct DataStructure
		{
			SDK::ULevelStreaming* reference;
			std::string className;
			std::string objectName;

			std::string levelPath;
			SDK::FLinearColor levelColor;

			Level::DataStructure level;
		};


		static std::vector<LevelStreaming::DataStructure> FilterByLevelPath(const std::vector<LevelStreaming::DataStructure>& levelStreamingsArray, const std::string& filter, const bool& caseSensitive);


		static bool LoadLevelInstance(const SDK::FString& levelPath, const SDK::FVector& locationOffset = { 0.0f, 0.0f, 0.0f }, const SDK::FRotator& rotationOffset = { 0.0f, 0.0f, 0.0f });
	};


	class World
	{
	public:
		struct DataStructure
		{
			SDK::UWorld* reference;
			std::string className;
			std::string objectName;

			GameState::DataStructure gameState;

			NetDriver::DataStructure netDriver;
			DemoNetDriver::DataStructure demoNetDriver;

			Level::DataStructure persistentLevel;

			std::vector<LevelStreaming::DataStructure> streamingLevels;

			double gameTimeInSeconds;

			bool isServer;
			bool isDedicatedServer;
			bool isSplitScreen;
			bool isStandalone;
		};


		/*
		* @brief Retrieves the current instance of the World, if one is available.
		* @return A valid pointer to the existing instance;
		*		  otherwise returns 'nullptr' to indicate that no instance is currently accessible.
		*/
		static SDK::UWorld* Get();
	};






	class Player
	{
	public:
		struct DataStructure
		{
			SDK::UPlayer* reference;
			std::string className;
			std::string objectName;
		};
	};


	class Pawn
	{
	public:
		struct DataStructure
		{
			SDK::APawn* reference;
			std::string className;
			std::string objectName;

			SDK::FVector location;
			SDK::FRotator rotation;
			SDK::FVector scale;

			bool isControlled;
			bool isPawnControlled;
			bool isPlayerControlled;
			bool isLocallyControlled;
			bool isBotControlled;
		};


	public:
		/*
		* @brief Retrieves the current instance of the Pawn, if one is available.
		* @param playerIndex - index of the local player to query.
		* @return A valid pointer to the existing instance;
		*		  otherwise returns 'nullptr' to indicate that no instance is currently accessible.
		*/
		static SDK::APawn* Get(const int32_t& playerIndex = 0);
	};


	class CameraManager
	{
	public:
		struct DataStructure
		{
			SDK::APlayerCameraManager* reference;
			std::string className;
			std::string objectName;

			SDK::FVector location;
			SDK::FRotator rotation;
			SDK::FVector scale;
		};
	};


	class CheatManager
	{
	public:
		struct DataStructure
		{
			SDK::UCheatManager* reference;
			std::string className;
			std::string objectName;
		};


		/*
		* @brief Constructs a Cheat Manager and assigns it to the active Player Controller.
		* @param ignorePresence - If set to 'True', a new Cheat Manager will always be created, even if one already exist.
		* @return 'True' if the Cheat Manager was successfully created and assigned; 'False' otherwise.
		*/
		static bool Construct(const bool& ignorePresence = false);
	};


	class PlayerController
	{
	public:
		struct DataStructure
		{
			SDK::APlayerController* reference;
			std::string className;
			std::string objectName;

			Player::DataStructure player;

			Pawn::DataStructure pawn;

			CameraManager::DataStructure cameraManager;

			CheatManager::DataStructure cheatManager;
		};


	public:
		/*
		* @brief Retrieves the current instance of the Player Controller, if one is available.
		* @param playerIndex - index of the local player to query.
		* @return A valid pointer to the existing instance;
		*		  otherwise returns 'nullptr' to indicate that no instance is currently accessible.
		*/
		static SDK::APlayerController* Get(const int32_t& playerIndex = 0);
	};


	class Character
	{
	public:
		/*
		* @brief Retrieves the current instance of the Character, if one is available.
		* @param playerIndex - index of the local player to query.
		* @return A valid pointer to the existing instance;
		*		  otherwise returns 'nullptr' to indicate that no instance is currently accessible.
		*/
		static SDK::ACharacter* Get(const int32_t& playerIndex = 0);


		static int32_t GetJumpMaxCount(SDK::ACharacter* characterReference);
		static int32_t GetJumpMaxCount(const int32_t& playerIndex);

		static bool SetJumpMaxCount(SDK::ACharacter* characterReference, const int32_t& value);
		static bool SetJumpMaxCount(const int32_t& playerIndex, const int32_t& value);


		static float GetJumpVelocity(SDK::ACharacter* characterReference);
		static float GetJumpVelocity(const int32_t& playerIndex);

		static bool SetJumpVelocity(SDK::ACharacter* characterReference, const float& value);
		static bool SetJumpVelocity(const int32_t& playerIndex, const float& value);


		static bool Jump(SDK::ACharacter* characterReference);
		static bool Jump(const int32_t& playerIndex);


		static bool Launch(SDK::ACharacter* characterReference, const SDK::FVector& launchVelocity, const bool& overrideHorizontalVelocity = false, const bool& overrideVerticalVelocity = false);
		static bool Launch(const int32_t& playerIndex, const SDK::FVector& launchVelocity, const bool& overrideHorizontalVelocity = false, const bool& overrideVerticalVelocity = false);


		static bool Walk(SDK::ACharacter* characterReference);
		static bool Walk(const int32_t& playerIndex);

		static bool Fly(SDK::ACharacter* characterReference);
		static bool Fly(const int32_t& playerIndex);

		static bool Ghost(SDK::ACharacter* characterReference);
		static bool Ghost(const int32_t& playerIndex);
	};






	class ActorComponent
	{
	public:
		struct DataStructure
		{
			SDK::UActorComponent* reference;
			std::string className;
			std::string objectName;

			bool isActive;
			bool autoActivate;
			bool editorOnly;

			bool netAddressible;
			bool replicates;

			SDK::EComponentCreationMethod creationMethod;
		};


		static std::vector<ActorComponent::DataStructure> FilterByObjectName(const std::vector<ActorComponent::DataStructure>& componentsArray, const std::string& filter, const bool& caseSensitive);
	};


	class Actor
	{
	public:
		struct DataStructure
		{
			SDK::AActor* reference;
			std::string superClassName;
			std::string className;
			std::string objectName;

			SDK::FVector location;
			SDK::FRotator rotation;
			SDK::FVector scale;

			std::vector<ActorComponent::DataStructure> components;
		};


		/*
		* @brief Retrieves all existing Actors that are default instances of the specified class.
		* @param objectClass - Class used as a filter when searching for Actors.
		* @return A collection of pointers to all matching Actors;
		*		  otherwise returns an empty vector if no Actors are found.
		*/
		static std::vector<SDK::AActor*> GetAllDefaultOfClass(const SDK::TSubclassOf<SDK::AActor>& actorClass);
		/*
		* @brief Retrieves all existing Actors that are instances of the specified class.
		* @param objectClass - Class used as a filter when searching for Actors.
		* @return A collection of pointers to all matching Actors;
		*		  otherwise returns an empty vector if no Actors are found.
		*/
		static std::vector<SDK::AActor*> GetAllOfClass(const SDK::TSubclassOf<SDK::AActor>& actorClass);


		static std::vector<Actor::DataStructure> FilterByClassName(const std::vector<Actor::DataStructure>& actorsArray, const std::string& filter, const bool& caseSensitive);
		static std::vector<Actor::DataStructure> FilterByObjectName(const std::vector<Actor::DataStructure>& actorsArray, const std::string& filter, const bool& caseSensitive);
		static std::vector<Actor::DataStructure> FilterByClassAndObjectName(const std::vector<Actor::DataStructure>& actorsArray, const std::string& filter, const bool& caseSensitive);


		static void SetVisibility(SDK::AActor* actorReference, const bool& newVisibility, const bool& propagateToComponents = false);


		static SDK::AActor* Summon(const SDK::TSubclassOf<SDK::AActor>& actorClass, const Unreal::Transform& transform);


		static SDK::AActor* SoftSummon(const SDK::FString actorPath, const Unreal::Transform& transform);


		static Unreal::Transform GetTransform(SDK::AActor* actorReference);


		static bool IsValid(SDK::AActor* actorReference);
	};






	class UserWidget
	{
	public:
		struct DataStructure
		{
			SDK::UUserWidget* reference;
			std::string className;
			std::string objectName;

			SDK::UPanelWidget* parent;

			bool isInViewport;
			SDK::ESlateVisibility visibility;
		};


		static std::vector<SDK::UUserWidget*> GetAllOfClass(const SDK::TSubclassOf<SDK::UUserWidget>& widgetClass);


		static std::vector<UserWidget::DataStructure> FilterByObjectName(const std::vector<UserWidget::DataStructure>& widgetsArray, const std::string& filter, const bool& caseSensitive, const bool& topLevelOnly);


		static SDK::UUserWidget* Construct(const SDK::TSubclassOf<SDK::UUserWidget>& widgetClass);


		static SDK::UUserWidget* SoftConstruct(const SDK::FString widgetPath);
	};
	





	class Object
	{
	public:
		struct DataStructure
		{
			SDK::UObject* reference;
			std::string className;
			std::string objectName;
		};


		/*
		* @brief Retrieves all existing Objects that are default instances of the specified class.
		* @param objectClass - Class used as a filter when searching for Objects.
		* @return A collection of pointers to all matching Objects;
		*		  otherwise returns an empty vector if no Objects are found.
		*/
		static std::vector<SDK::UObject*> GetAllDefaultOfClass(const SDK::TSubclassOf<SDK::UObject>& objectClass);
		/*
		* @brief Retrieves all existing Objects that are instances of the specified class.
		* @param objectClass - Class used as a filter when searching for Objects.
		* @return A collection of pointers to all matching Objects;
		*		  otherwise returns an empty vector if no Objects are found.
		*/
		static std::vector<SDK::UObject*> GetAllOfClass(const SDK::TSubclassOf<SDK::UObject>& objectClass);
	};






	class String
	{
	public:
		static SDK::FString WString_ToFString(const std::wstring& wideString)
		{
			return SDK::FString(wideString.c_str());
		}
		static SDK::FString String_ToFString(const std::string& string)
		{
			return WString_ToFString(std::wstring(string.begin(), string.end()));
		}
		static SDK::FString CString_ToFString(const char* charString)
		{
			return String_ToFString(std::string(charString));
		}


		static std::vector<SDK::FString> Split(const std::wstring& wideString, const wchar_t& separator, const bool& removeSeparatorSpaces = true);
		static std::vector<SDK::FString> Split(const std::wstring& wideString, const char& separator, const bool& removeSeparatorSpaces = true)
		{
			return Split(wideString, (wchar_t)separator, removeSeparatorSpaces);
		}

		static std::vector<SDK::FString> Split(const std::string& string, const wchar_t& separator, const bool& removeSeparatorSpaces = true)
		{
			return Split(std::wstring(string.begin(), string.end()), separator, removeSeparatorSpaces);
		}
		static std::vector<SDK::FString> Split(const std::string& string, const char& separator, const bool& removeSeparatorSpaces = true)
		{
			return Split(std::wstring(string.begin(), string.end()), separator, removeSeparatorSpaces);
		}

		static std::vector<SDK::FString> Split(const char* charString, const wchar_t& separator, const bool& removeSeparatorSpaces = true)
		{
			return Split(std::string(charString), separator, removeSeparatorSpaces);
		}
		static std::vector<SDK::FString> Split(const char* charString, const char& separator, const bool& removeSeparatorSpaces = true)
		{
			return Split(std::string(charString), separator, removeSeparatorSpaces);
		}
	};
};

