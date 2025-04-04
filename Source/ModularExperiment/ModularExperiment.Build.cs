// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ModularExperiment : ModuleRules
{
	public ModularExperiment(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
