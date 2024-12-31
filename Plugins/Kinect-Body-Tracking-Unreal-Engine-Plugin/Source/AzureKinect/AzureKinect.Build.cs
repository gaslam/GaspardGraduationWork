// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class AzureKinect : ModuleRules
{
	public AzureKinect(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;


			string sdkPath = System.Environment.GetEnvironmentVariable("AZUREKINECT_SDK");

            System.Console.WriteLine($"{nameof(sdkPath)}: {sdkPath}");
            string bodySdkPath = System.Environment.GetEnvironmentVariable("AZUREKINECT_BODY_SDK");
            System.Console.WriteLine($"{nameof(bodySdkPath)}: {bodySdkPath}");

            string depthEngineDllPath = Path.Combine(sdkPath, "sdk", "windows-desktop", "amd64", "release", "bin", "depthengine_2_0.dll");

            System.Console.WriteLine($"{nameof(depthEngineDllPath)}: {depthEngineDllPath}");
            string k4aDllPath = Path.Combine(sdkPath, "sdk", "windows-desktop", "amd64", "release", "bin", "k4a.dll");
            System.Console.WriteLine($"{nameof(k4aDllPath)}: {k4aDllPath}");
            string k4abtDllPath = Path.Combine(bodySdkPath, "sdk", "windows-desktop", "amd64", "release", "bin", "k4abt.dll");
            System.Console.WriteLine($"{nameof(k4abtDllPath)}: {k4abtDllPath}");

            string bodyTrackingDLL = Path.Combine(bodySdkPath, "sdk", "netstandard2.0", "release", "microsoft.azure.kinect.bodytracking.dll");
            System.Console.WriteLine($"{nameof(bodyTrackingDLL)}: {bodyTrackingDLL}");
            string bodyTrackingPDB = Path.Combine(bodySdkPath, "sdk", "netstandard2.0", "release", "Microsoft.Azure.Kinect.BodyTracking.pbd");
            System.Console.WriteLine($"{nameof(bodyTrackingPDB)}: {bodyTrackingPDB}");

            PublicIncludePaths.AddRange(
				new string[] {
					Path.Combine(sdkPath, "sdk", "include"),
					Path.Combine(bodySdkPath, "sdk", "include")
				});

			PublicAdditionalLibraries.AddRange(
				new string[] {
					Path.Combine(sdkPath, "sdk", "windows-desktop", "amd64", "release", "lib", "k4a.lib"),
					Path.Combine(sdkPath, "sdk", "windows-desktop", "amd64", "release", "lib", "k4arecord.lib"),
					Path.Combine(bodySdkPath, "sdk", "windows-desktop", "amd64", "release", "lib", "k4abt.lib"),
				});

            bEnableExceptions = true;

            System.Console.WriteLine(depthEngineDllPath);
			PublicDelayLoadDLLs.AddRange(
				new string[] {
					depthEngineDllPath,
					bodyTrackingDLL,
					bodyTrackingPDB,
					k4aDllPath,
					k4abtDllPath,
				});

			RuntimeDependencies.Add(depthEngineDllPath);
			RuntimeDependencies.Add(k4aDllPath);
			RuntimeDependencies.Add(k4abtDllPath);
		

		PrivateIncludePaths.AddRange(
			new string[]
			{
				"AzureKinect/Private",
			});

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"RenderCore",
				"RHI",
				"AnimGraphRuntime",
			});
		
	}
}
