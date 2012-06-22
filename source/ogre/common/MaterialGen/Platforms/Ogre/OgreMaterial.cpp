#include "OgreMaterial.hpp"

#include <OgreMaterialManager.h>
#include <OgreTechnique.h>

#include "OgrePass.hpp"

namespace sh
{
	static const std::string sDefaultTechniqueName = "SH_DefaultTechnique";

	OgreMaterial::OgreMaterial (const std::string& name, const std::string& resourceGroup)
		: Material()
	{
		assert (Ogre::MaterialManager::getSingleton().getByName(name).isNull() && "Material already exists");
		mMaterial = Ogre::MaterialManager::getSingleton().create (name, resourceGroup);
		mMaterial->removeAllTechniques();
		mMaterial->createTechnique()->setSchemeName (sDefaultTechniqueName);
	}

	boost::shared_ptr<Pass> OgreMaterial::createPass ()
	{
		return boost::shared_ptr<Pass> (new OgrePass (this));
	}

	Ogre::MaterialPtr OgreMaterial::getOgreMaterial ()
	{
		return mMaterial;
	}

	Ogre::Technique* OgreMaterial::getOgreTechniqueForConfiguration (const std::string& configurationName)
	{
		return mMaterial->getTechnique (configurationName); /// \todo don't use strings here?
	}
}