// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class GraduationWorkEditorTarget : TargetRules
{
	public GraduationWorkEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;

        ExtraModuleNames.AddRange( new string[] { "GraduationWork" } );
	}
}
