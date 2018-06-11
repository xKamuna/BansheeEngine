//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsScriptEnginePrerequisites.h"
#include "Script/BsScriptManager.h"

namespace bs
{
	/** @addtogroup SBansheeEngine
	 *  @{
	 */

	/** Handles initialization/shutdown of the script systems and loading/refresh of engine-specific assemblies. */
	class BS_SCR_BE_EXPORT EngineScriptLibrary : public ScriptLibrary
	{
	public:
		EngineScriptLibrary();

		/**	Loads the all assemblies in folder and subfolders. */
		void loadOtherAssemblies(Vector<std::pair<String, Path>>& assemblies);

		/**	Adds the all assemblies in folder and subfolders to assemblies. */
		void addOtherAssemblies(const Path& path, Vector<std::pair<String, Path>>& assemblies);

		/** @copydoc ScriptLibrary::initialize */
		void initialize() override;

		/** @copydoc ScriptLibrary::reload */
		void reload() override;

		/** @copydoc ScriptLibrary::destroy */
		void destroy() override;

	protected:
		/** Unloads all manages assemblies and the mono domain. */
		void unloadAssemblies();

		/** Shuts down all script engine modules. */
		void shutdownModules();

	private:
		bool mScriptAssembliesLoaded;
	};

	/** @} */
}