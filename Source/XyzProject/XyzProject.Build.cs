// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class XyzProject : ModuleRules
{
	public XyzProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new[]
			{
				"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput",
				"MyXyzModule"
			}
		);
	}
}