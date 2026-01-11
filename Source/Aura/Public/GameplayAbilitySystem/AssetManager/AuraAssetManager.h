// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "AuraAssetManager.generated.h"

/**
 * It's another singleton class and it has to do with loading primary assets, and it's
 * where we can initialize our GameplayTags Singleton.
 * Asset Manager:
 * Unique, global object that exists in the editor and packaged games. It can be overridden
 * and customized for any project and provides a framework for managing Assets that can divide
 * content into chunks.
 *
 * To set our Asset Manager to use for our project; go to the Config(folder)->DefaultEngine.ini
 * In the [/Script/Engine.Engine] section Add the following part.
 * AssetManagerClassName=/Script/<ProjectName>.<ClassName>
 * AssetManagerClassName=/Script/Aura.AuraAssetManager
 */
UCLASS()
class AURA_API UAuraAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static const UAuraAssetManager& Get() { return *(Cast<UAuraAssetManager>(GEngine->AssetManager)); }

protected:
	/* Function that we are going to initialize the gameplay tags. */
	virtual void StartInitialLoading() override;
};
