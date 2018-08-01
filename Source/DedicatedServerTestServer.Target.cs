// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
 
using UnrealBuildTool;
using System.Collections.Generic;

 [SupportedPlatforms(UnrealPlatformClass.Server)]
public class DedicatedServerTestServerTarget : TargetRules
{
    public DedicatedServerTestServerTarget(TargetInfo Target)
    {
        Type = TargetType.Server;
        ExtraModuleNames.Add("DedicatedServerTest");
    }
 
    /*public override bool GetSupportedPlatforms(ref List<UnrealTargetPlatform> OutPlatforms)
    {
        // It is valid for only server platforms
        return UnrealBuildTool.UnrealBuildTool.GetAllServerPlatforms(ref OutPlatforms, false);
    }*/

}