#include "PropertyBase.hpp"

#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

namespace sh
{

	IntValue::IntValue(int in)
		: mValue(in)
	{
	}

	IntValue::IntValue(const std::string& in)
	{
		mValue = boost::lexical_cast<int>(in);
	}

	std::string IntValue::serialize()
	{
		return boost::lexical_cast<std::string>(mValue);
	}

	// ------------------------------------------------------------------------------

	BooleanValue::BooleanValue (bool in)
		: mValue(in)
	{
	}

	BooleanValue::BooleanValue (const std::string& in)
	{
		if (in == "true")
			mValue = true;
		else if (in == "false")
			mValue = false;
		else
		{
			std::cerr << "sh::BooleanValue: Warning: Unrecognized value \"" << in << "\" for property value of type BooleanValue" << std::endl;
			mValue = false;
		}
	}

	std::string BooleanValue::serialize ()
	{
		if (mValue)
			return "true";
		else
			return "false";
	}

	// ------------------------------------------------------------------------------

	StringValue::StringValue (const std::string& in)
	{
		mStringValue = in;
	}

	std::string StringValue::serialize()
	{
		return mStringValue;
	}

	// ------------------------------------------------------------------------------

	FloatValue::FloatValue (float in)
	{
		mValue = in;
	}

	FloatValue::FloatValue (const std::string& in)
	{
		mValue = boost::lexical_cast<float>(in);
	}

	std::string FloatValue::serialize ()
	{
		return boost::lexical_cast<std::string>(mValue);
	}

	// ------------------------------------------------------------------------------

	Vector2::Vector2 (float x, float y)
		: mX(x)
		, mY(y)
	{
	}

	Vector2::Vector2 (const std::string& in)
	{
		std::vector<std::string> tokens;
		boost::split(tokens, in, boost::is_any_of(" "));
		assert ((tokens.size() == 2) && "Invalid Vector2 conversion");
		mX = boost::lexical_cast<float> (tokens[0]);
		mY = boost::lexical_cast<float> (tokens[1]);
	}

	std::string Vector2::serialize ()
	{
		return boost::lexical_cast<std::string>(mX) + " "
			+ boost::lexical_cast<std::string>(mY);
	}

	// ------------------------------------------------------------------------------

	Vector3::Vector3 (float x, float y, float z)
		: mX(x)
		, mY(y)
		, mZ(z)
	{
	}

	Vector3::Vector3 (const std::string& in)
	{
		std::vector<std::string> tokens;
		boost::split(tokens, in, boost::is_any_of(" "));
		assert ((tokens.size() == 3) && "Invalid Vector3 conversion");
		mX = boost::lexical_cast<float> (tokens[0]);
		mY = boost::lexical_cast<float> (tokens[1]);
		mZ = boost::lexical_cast<float> (tokens[2]);
	}

	std::string Vector3::serialize ()
	{
		return boost::lexical_cast<std::string>(mX) + " "
			+ boost::lexical_cast<std::string>(mY) + " "
			+ boost::lexical_cast<std::string>(mZ);
	}

	// ------------------------------------------------------------------------------

	Vector4::Vector4 (float x, float y, float z, float w)
		: mX(x)
		, mY(y)
		, mZ(z)
		, mW(w)
	{
	}

	Vector4::Vector4 (const std::string& in)
	{
		std::vector<std::string> tokens;
		boost::split(tokens, in, boost::is_any_of(" "));
		assert ((tokens.size() == 4) && "Invalid Vector4 conversion");
		mX = boost::lexical_cast<float> (tokens[0]);
		mY = boost::lexical_cast<float> (tokens[1]);
		mZ = boost::lexical_cast<float> (tokens[2]);
		mW = boost::lexical_cast<float> (tokens[3]);
	}

	std::string Vector4::serialize ()
	{
		return boost::lexical_cast<std::string>(mX) + " "
			+ boost::lexical_cast<std::string>(mY) + " "
			+ boost::lexical_cast<std::string>(mZ) + " "
			+ boost::lexical_cast<std::string>(mW);
	}

	// ------------------------------------------------------------------------------

	void PropertySet::setProperty (const std::string& name, PropertyValuePtr &value)
	{
		setPropertyOverride (name, value);
	}

	bool PropertySet::setPropertyOverride (const std::string& name, PropertyValuePtr &value)
	{
		// if we got here, none of the sub-classes was able to make use of the property
		std::cerr << "sh::PropertySet: Warning: No match for property with name '" << name << "'" << std::endl;
		return false;
	}

	// ------------------------------------------------------------------------------

	PropertySetGet::PropertySetGet (PropertySetGet* parent)
		: mParent(parent)
	{
	}

	PropertySetGet::PropertySetGet ()
		: mParent(NULL)
	{
	}

	void PropertySetGet::setParent (PropertySetGet* parent)
	{
		if (mParent)
			throw std::runtime_error ("PropertySetGet already has a parent");
		mParent = parent;
	}

	void PropertySetGet::setProperty (const std::string& name, PropertyValuePtr value)
	{
		mProperties [name] = value;
	}

	PropertyValuePtr& PropertySetGet::getProperty (const std::string& name)
	{
		bool found = mProperties.find(name) != mProperties.end();

		if (!found)
		{
			if (!mParent)
				throw std::runtime_error ("Trying to retrieve property that does not exist");
			else
				return mParent->getProperty (name);
		}
		else
			return mProperties[name];
	}
}