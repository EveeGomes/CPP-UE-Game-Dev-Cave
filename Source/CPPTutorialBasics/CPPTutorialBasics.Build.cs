// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CPPTutorialBasics : ModuleRules
{
	public CPPTutorialBasics(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput", "GameplayTasks" });
    }
}
