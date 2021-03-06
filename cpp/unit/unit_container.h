// Copyright 2014-2014 the openage authors. See copying.md for legal info.

#ifndef OPENAGE_UNIT_UNIT_CONTAINER_H_
#define OPENAGE_UNIT_UNIT_CONTAINER_H_

#include <memory>
#include <unordered_map>

#include "../coord/tile.h"
#include "../handlers.h"

namespace openage {

class Command;
class Terrain;
class Unit;
class UnitProducer;
class UnitContainer;

using id_t = unsigned long int;

class UnitReference {
public:
	UnitReference();
	UnitReference(const UnitContainer *c, id_t id, Unit *);
	bool is_valid() const;
	Unit *get() const;

private:
	const UnitContainer *container;
	id_t unit_id;
	Unit *unit_ptr;
};

/**
 * the list of units that are currently in use
 * will also give a view of the current game state for networking in later milestones
 */
class UnitContainer : public TickHandler {
public:
	UnitContainer();
	~UnitContainer();

	/**
	 * checks the id is valid
	 */
	bool valid_id(id_t id) const;

	/**
	 * returns a reference to a unit
	 */
	UnitReference get_unit(id_t id);

	/**
	 * adds a new unit to the container
	 */
	bool new_unit(UnitProducer &producer, Terrain *terrain, coord::tile tile);

	/**
	 * give a command to a unit -- unit creation and deletion should be done as commands
	 */
	bool dispatch_command(id_t to_id, const Command &cmd);

	/**
	 * update dispatched by the game engine
	 * this will update all game objects
	 */
	bool on_tick();

private:
	uint next_new_id;

	/**
	 * mapping unit ids to unit objects
	 */
	std::unordered_map<id_t, std::unique_ptr<Unit>> live_units;

};

} // namespace openage

#endif
