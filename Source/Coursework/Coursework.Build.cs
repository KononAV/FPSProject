// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Coursework : ModuleRules
{
	public Coursework(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
            "Core", 
            "CoreUObject", 
            "Engine", 
            "InputCore", 
            "EnhancedInput", 
            "UMG", 
            "AIModule", 
            "Niagara",
        });

		PrivateDependencyModuleNames.AddRange(new string[] {
            "Slate",
            "SlateCore" 
        });

      
    }
}
