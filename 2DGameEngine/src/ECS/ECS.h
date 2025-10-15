#pragma once

#include <bitset>
#include <vector>

const unsigned int MAX_COMPONENTS = 32;

/////////////////////////////////////////////////////////////////////////
/// Signature
/////////////////////////////////////////////////////////////////////////
/// We use a bitset (1s and 0s) to keep track of which componments an entity has,
/// and also helps keep track of which entities a system is interested in.
/////////////////////////////////////////////////////////////////////////
typedef std::bitset<MAX_COMPONENTS> Signature;

struct IComponent
{
protected:
	static int next_id;
};

class Entity
{
private:
	int id;

public:
	Entity(int id) : id(id) {};
	Entity(const Entity& entity) = default;
	int get_id() const;

	Entity& operator = (const Entity& other) = default;
	bool operator == (const Entity& other) const { return id == other.id; }
	bool operator != (const Entity& other) const { return id != other.id; }
	bool operator > (const Entity& other) const { return id > other.id; }
	bool operator < (const Entity& other) const { return id < other.id; }
};

/////////////////////////////////////////////////////////////////////////
/// Component
/////////////////////////////////////////////////////////////////////////
/// Used to assign a unique id to a component type
/////////////////////////////////////////////////////////////////////////
template <typename T>
class Component: public IComponent
{
public:
	// Returns the unique id of Component<T>
	static int get_id()
	{
		static auto id = next_id++;
		return id;
	}
};


/////////////////////////////////////////////////////////////////////////
/// System
/////////////////////////////////////////////////////////////////////////
/// The system processes entities that contain a specific signature
/////////////////////////////////////////////////////////////////////////
class System
{
private:
	Signature component_signature;
	std::vector<Entity> entities;

public:
	System() = default;
	~System() = default;

	void add_entity_to_system(Entity entity);
	void remove_entity_from_system(Entity entity);
	std::vector<Entity> get_system_entities() const;
	const Signature& get_component_signature() const;

	// Defines the component type that entities must have to be considered
	// by the system.
	template<typename T> void require_component();
};

class Registry
{

};


template<typename T>
void System::require_component()
{
	const auto component_id = Component<T>::get_id();
	component_signature.set(component_id);
}
