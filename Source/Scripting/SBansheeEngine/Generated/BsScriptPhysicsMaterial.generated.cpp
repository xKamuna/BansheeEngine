#include "BsScriptPhysicsMaterial.generated.h"
#include "BsMonoMethod.h"
#include "BsMonoClass.h"
#include "BsMonoUtil.h"
#include "../../../bsf/Source/Foundation/bsfCore/Physics/BsPhysicsMaterial.h"
#include "BsScriptResourceManager.h"
#include "BsScriptPhysicsMaterial.generated.h"

namespace bs
{
	ScriptPhysicsMaterial::ScriptPhysicsMaterial(MonoObject* managedInstance, const ResourceHandle<PhysicsMaterial>& value)
		:TScriptResource(managedInstance, value)
	{
	}

	void ScriptPhysicsMaterial::initRuntimeData()
	{
		metaData.scriptClass->addInternalCall("Internal_setStaticFriction", (void*)&ScriptPhysicsMaterial::Internal_setStaticFriction);
		metaData.scriptClass->addInternalCall("Internal_getStaticFriction", (void*)&ScriptPhysicsMaterial::Internal_getStaticFriction);
		metaData.scriptClass->addInternalCall("Internal_setDynamicFriction", (void*)&ScriptPhysicsMaterial::Internal_setDynamicFriction);
		metaData.scriptClass->addInternalCall("Internal_getDynamicFriction", (void*)&ScriptPhysicsMaterial::Internal_getDynamicFriction);
		metaData.scriptClass->addInternalCall("Internal_setRestitutionCoefficient", (void*)&ScriptPhysicsMaterial::Internal_setRestitutionCoefficient);
		metaData.scriptClass->addInternalCall("Internal_getRestitutionCoefficient", (void*)&ScriptPhysicsMaterial::Internal_getRestitutionCoefficient);
		metaData.scriptClass->addInternalCall("Internal_create", (void*)&ScriptPhysicsMaterial::Internal_create);

	}

	 MonoObject*ScriptPhysicsMaterial::createInstance()
	{
		bool dummy = false;
		void* ctorParams[1] = { &dummy };

		return metaData.scriptClass->createInstance("bool", ctorParams);
	}
	void ScriptPhysicsMaterial::Internal_setStaticFriction(ScriptPhysicsMaterial* thisPtr, float value)
	{
		thisPtr->getHandle()->setStaticFriction(value);
	}

	float ScriptPhysicsMaterial::Internal_getStaticFriction(ScriptPhysicsMaterial* thisPtr)
	{
		float tmp__output;
		tmp__output = thisPtr->getHandle()->getStaticFriction();

		float __output;
		__output = tmp__output;

		return __output;
	}

	void ScriptPhysicsMaterial::Internal_setDynamicFriction(ScriptPhysicsMaterial* thisPtr, float value)
	{
		thisPtr->getHandle()->setDynamicFriction(value);
	}

	float ScriptPhysicsMaterial::Internal_getDynamicFriction(ScriptPhysicsMaterial* thisPtr)
	{
		float tmp__output;
		tmp__output = thisPtr->getHandle()->getDynamicFriction();

		float __output;
		__output = tmp__output;

		return __output;
	}

	void ScriptPhysicsMaterial::Internal_setRestitutionCoefficient(ScriptPhysicsMaterial* thisPtr, float value)
	{
		thisPtr->getHandle()->setRestitutionCoefficient(value);
	}

	float ScriptPhysicsMaterial::Internal_getRestitutionCoefficient(ScriptPhysicsMaterial* thisPtr)
	{
		float tmp__output;
		tmp__output = thisPtr->getHandle()->getRestitutionCoefficient();

		float __output;
		__output = tmp__output;

		return __output;
	}

	void ScriptPhysicsMaterial::Internal_create(MonoObject* managedInstance, float staticFriction, float dynamicFriction, float restitution)
	{
		ResourceHandle<PhysicsMaterial> instance = PhysicsMaterial::create(staticFriction, dynamicFriction, restitution);
		ScriptResourceManager::instance().createBuiltinScriptResource(instance, managedInstance);
	}
}
