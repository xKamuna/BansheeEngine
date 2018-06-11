//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "BsEngineScriptLibrary.h"
#include "BsMonoManager.h"
#include "BsMonoAssembly.h"
#include "Serialization/BsScriptAssemblyManager.h"
#include "BsScriptResourceManager.h"
#include "BsScriptGameObjectManager.h"
#include "BsManagedResourceManager.h"
#include "Script/BsScriptManager.h"
#include "Wrappers/BsScriptInput.h"
#include "Wrappers/BsScriptVirtualInput.h"
#include "BsScriptObjectManager.h"
#include "Resources/BsGameResourceManager.h"
#include "BsApplication.h"
#include "FileSystem/BsFileSystem.h"
#include "Wrappers/BsScriptDebug.h"
#include "Wrappers/GUI/BsScriptGUI.h"
#include "BsPlayInEditorManager.h"
#include "Wrappers/BsScriptScene.h"
#include "GUI/BsGUIManager.h"

namespace bs
{
	EngineScriptLibrary::EngineScriptLibrary()
		:mScriptAssembliesLoaded(false)
	{ }

	void EngineScriptLibrary::loadOtherAssemblies(Vector<std::pair<String, Path>>& assemblies)
	{
		for (auto assembly : assemblies)
		{
			MonoManager::instance().loadAssembly(assembly.second.toString(), assembly.first);
			ScriptAssemblyManager::instance().loadAssemblyInfo(assembly.first);
		}
	}

	void EngineScriptLibrary::addOtherAssemblies(const Path& path, Vector<std::pair<String, Path>>& assemblies)
	{
		Vector<Path> files;
		Vector<Path> directories;
		String name;
		FileSystem::getChildren(path, files, directories);
		for (auto& file : files)
		{
			//If dll, load assembly.  TODO: Linux/Mac/etc. formats.  Make platform-agnostic.
			if (file.getExtension() == ".dll")
			{
				name = file.getFilename(false);
				assemblies.push_back({ name, file });
			}
		}
		for (auto& directory : directories)
		{
			addOtherAssemblies(directory, assemblies); //Search in subdirectories.
		}
	}

	void EngineScriptLibrary::initialize()
	{
		Path engineAssemblyPath = gApplication().getEngineAssemblyPath();
		const String ASSEMBLY_ENTRY_POINT = "Program::Start";

		MonoManager::startUp();
		MonoAssembly& bansheeEngineAssembly = MonoManager::instance().loadAssembly(engineAssemblyPath.toString(), ENGINE_ASSEMBLY);

		PlayInEditorManager::startUp();
		ScriptDebug::startUp();
		GameResourceManager::startUp();
		ScriptObjectManager::startUp();
		ManagedResourceManager::startUp();
		ScriptAssemblyManager::startUp();
		ScriptResourceManager::startUp();
		ScriptGameObjectManager::startUp();
		ScriptScene::startUp();
		ScriptInput::startUp();
		ScriptVirtualInput::startUp();
		ScriptGUI::startUp();

		ScriptAssemblyManager::instance().loadAssemblyInfo(ENGINE_ASSEMBLY);

		Path gameAssemblyPath = gApplication().getGameAssemblyPath();
		if (FileSystem::exists(gameAssemblyPath))
		{
			MonoManager::instance().loadAssembly(gameAssemblyPath.toString(), SCRIPT_GAME_ASSEMBLY);
			ScriptAssemblyManager::instance().loadAssemblyInfo(SCRIPT_GAME_ASSEMBLY);
		}

		

		bansheeEngineAssembly.invoke(ASSEMBLY_ENTRY_POINT);
	}

	void EngineScriptLibrary::reload()
	{
		Path engineAssemblyPath = gApplication().getEngineAssemblyPath();
		Path gameAssemblyPath = gApplication().getGameAssemblyPath();
		Path gameResourcesPath = Paths::getGameResourcesPath();

		// Do a full refresh if we have already loaded script assemblies
		if (mScriptAssembliesLoaded)
		{
			Vector<std::pair<String, Path>> assemblies;
			assemblies.push_back({ ENGINE_ASSEMBLY, engineAssemblyPath });

			if (FileSystem::exists(gameAssemblyPath))
				assemblies.push_back({ SCRIPT_GAME_ASSEMBLY, gameAssemblyPath });

			if (FileSystem::exists(gameResourcesPath))
			{
				addOtherAssemblies(gameResourcesPath, assemblies);
				MonoManager::instance().buildAssembliesPath(assemblies);
			}

			MonoManager::instance().buildAssembliesPath(assemblies);
			ScriptObjectManager::instance().refreshAssemblies(assemblies);
		}
		else // Otherwise just additively load them
		{
			MonoManager::instance().loadAssembly(engineAssemblyPath.toString(), ENGINE_ASSEMBLY);
			ScriptAssemblyManager::instance().loadAssemblyInfo(ENGINE_ASSEMBLY);

			if (FileSystem::exists(gameAssemblyPath))
			{
				MonoManager::instance().loadAssembly(gameAssemblyPath.toString(), SCRIPT_GAME_ASSEMBLY);
				ScriptAssemblyManager::instance().loadAssemblyInfo(SCRIPT_GAME_ASSEMBLY);
			}
			
			if (FileSystem::exists(gameResourcesPath))
			{
				Vector<std::pair<String, Path>> assemblies;
				addOtherAssemblies(gameResourcesPath, assemblies);
				MonoManager::instance().buildAssembliesPath(assemblies);
				loadOtherAssemblies(assemblies);
			}

			mScriptAssembliesLoaded = true;
		}
	}

	void EngineScriptLibrary::destroy()
	{
		unloadAssemblies();
		shutdownModules();
	}

	void EngineScriptLibrary::unloadAssemblies()
	{
		ManagedResourceManager::instance().clear();
		MonoManager::instance().unloadScriptDomain();
		ScriptObjectManager::instance().processFinalizedObjects();
	}

	void EngineScriptLibrary::shutdownModules()
	{
		ScriptGUI::shutDown();
		ScriptVirtualInput::shutDown();
		ScriptInput::shutDown();
		ScriptScene::shutDown();
		ManagedResourceManager::shutDown();
		MonoManager::shutDown();
		ScriptGameObjectManager::shutDown();
		ScriptResourceManager::shutDown();
		ScriptAssemblyManager::shutDown();
		ScriptObjectManager::shutDown();
		GameResourceManager::shutDown();
		ScriptDebug::shutDown();
		PlayInEditorManager::shutDown();

		// Make sure all GUI elements are actually destroyed
		GUIManager::instance().processDestroyQueue();
	}
}
