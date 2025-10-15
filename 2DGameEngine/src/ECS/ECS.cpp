#include "ECS.h"


int Entity::get_id() const
{
	return id;
}

void System::add_entity_to_system(Entity entity)
{
	entities.push_back(entity);
}

void System::remove_entity_from_system(Entity entity)
{
	std::erase(entities, entity);
}

std::vector<Entity> System::get_system_entities() const
{
	return entities;
}

const Signature& System::get_component_signature() const
{
	return component_signature;
}
