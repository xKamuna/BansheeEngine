#pragma once

#include "BsScriptEnginePrerequisites.h"
#include "Wrappers/BsScriptResource.h"

namespace bs
{
	class AnimationClip;
	struct __AnimationEventInterop;

	class BS_SCR_BE_EXPORT ScriptAnimationClip : public TScriptResource<ScriptAnimationClip, AnimationClip>
	{
	public:
		SCRIPT_OBJ(ENGINE_ASSEMBLY, "BansheeEngine", "AnimationClip")

		ScriptAnimationClip(MonoObject* managedInstance, const ResourceHandle<AnimationClip>& value);

		static MonoObject* createInstance();

	private:
		static MonoObject* Internal_getCurves(ScriptAnimationClip* thisPtr);
		static void Internal_setCurves(ScriptAnimationClip* thisPtr, MonoObject* curves);
		static MonoArray* Internal_getEvents(ScriptAnimationClip* thisPtr);
		static void Internal_setEvents(ScriptAnimationClip* thisPtr, MonoArray* events);
		static MonoObject* Internal_getRootMotion(ScriptAnimationClip* thisPtr);
		static bool Internal_hasRootMotion(ScriptAnimationClip* thisPtr);
		static bool Internal_isAdditive(ScriptAnimationClip* thisPtr);
		static float Internal_getLength(ScriptAnimationClip* thisPtr);
		static uint32_t Internal_getSampleRate(ScriptAnimationClip* thisPtr);
		static void Internal_setSampleRate(ScriptAnimationClip* thisPtr, uint32_t sampleRate);
		static void Internal_create(MonoObject* managedInstance, bool isAdditive);
		static void Internal_create0(MonoObject* managedInstance, MonoObject* curves, bool isAdditive, uint32_t sampleRate, MonoObject* rootMotion);
	};
}
