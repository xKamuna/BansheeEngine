//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "BsEditorScriptLibrary.h"
#include "BsEditorScriptManager.h"
#include "BsEditorApplication.h"
#include "BsScriptObjectManager.h"
#include "FileSystem/BsFileSystem.h"
#include "BsMonoManager.h"
#include "Serialization/BsScriptAssemblyManager.h"
#include "BsMonoAssembly.h"
#include "Scene/BsGameObjectManager.h"

namespace bs
{
	EditorScriptLibrary::EditorScriptLibrary()
		:mScriptAssembliesLoaded(false)
	{ }

	void EditorScriptLibrary::initialize()
	{
		EngineScriptLibrary::initialize();

		EditorScriptManager::startUp();
	}

	void EditorScriptLibrary::reload()
	{
		Path engineAssemblyPath = gApplication().getEngineAssemblyPath();
		Path gameAssemblyPath = gApplication().getGameAssemblyPath();
		const Path gameResourcesPath = Paths::getGameResourcesPath().getAbsolute(gEditorApplication().getProjectPath());

		Path editorAssemblyPath = gEditorApplication().getEditorAssemblyPath();
		Path editorScriptAssemblyPath = gEditorApplication().getEditorScriptAssemblyPath();

#if BS_DEBUG_MODE
		mScriptAssembliesLoaded = true; // Force assembly refresh as an ad hoc unit test in debug mode
#endif

		// Do a full refresh if we have already loaded script assemblies
		if (mScriptAssembliesLoaded)
		{
			Vector<std::pair<String, Path>> assemblies;

			assemblies.push_back({ ENGINE_ASSEMBLY, engineAssemblyPath });
			if (gEditorApplication().isProjectLoaded())
			{
				if (FileSystem::exists(gameAssemblyPath))
					assemblies.push_back({ SCRIPT_GAME_ASSEMBLY, gameAssemblyPath });
			}

			assemblies.push_back({ EDITOR_ASSEMBLY, editorAssemblyPath });
			if (gEditorApplication().isProjectLoaded())
			{
				if (FileSystem::exists(editorScriptAssemblyPath))
					assemblies.push_back({ SCRIPT_EDITOR_ASSEMBLY, editorScriptAssemblyPath });
			}

			if (FileSystem::exists(gameResourcesPath))
			{
				addOtherAssemblies(gameResourcesPath, assemblies);
				MonoManager::instance().buildAssembliesPath(assemblies);
			}

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

			MonoManager::instance().loadAssembly(editorAssemblyPath.toString(), EDITOR_ASSEMBLY);
			ScriptAssemblyManager::instance().loadAssemblyInfo(EDITOR_ASSEMBLY);

			if (FileSystem::exists(editorScriptAssemblyPath))
			{
				MonoManager::instance().loadAssembly(editorScriptAssemblyPath.toString(), SCRIPT_EDITOR_ASSEMBLY);
				ScriptAssemblyManager::instance().loadAssemblyInfo(SCRIPT_EDITOR_ASSEMBLY);
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

	void EditorScriptLibrary::destroy()
	{
		GameObjectManager::instance().destroyQueuedObjects();

		unloadAssemblies();
		EditorScriptManager::shutDown();
		shutdownModules();
	}
}
