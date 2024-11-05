// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CyrusFPSGame : ModuleRules
{
	public CyrusFPSGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		//Adding exra dependencies for json integration
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" , "HTTP", "Json", "JsonUtilities" });
	}
}
