using UnrealBuildTool;

public class MyXyzModule : ModuleRules
{
	public MyXyzModule(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicDependencyModuleNames.AddRange(
			new[] { "Core", "CoreUObject" }
		);
	}
}