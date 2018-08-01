// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class DedicatedServerTest : ModuleRules
{
    public DedicatedServerTest(ReadOnlyTargetRules Target)
        : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PublicDependencyModuleNames.AddRange(new string[] {  });


        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "UMG", "Paper2D" }); //2D

        PublicDependencyModuleNames.AddRange(new string[] { "Voice", "OnlineSubsystem", "OnlineSubsystemUtils" });


        PrivateDependencyModuleNames.AddRange(new string[] { "EngineSettings" });
        //DynamicallyLoadedModuleNames.Add("OnlineSubsystemNull");
        DynamicallyLoadedModuleNames.Add("OnlineSubsystemHorizon");
        DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
        //DynamicallyLoadedModuleNames.Add("OnlineSubsystemGooglePlay");
       // DynamicallyLoadedModuleNames.Add("OnlineSubsystemIOS");
        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
