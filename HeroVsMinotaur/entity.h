//Elaine He jhe48
//Shanelle scao15
//Jose Delgado jdelgad9
#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "position.h"
#include "entitycontroller.h"

class EntityController;

// Class representing a game entity (hero, minotaur, inanimate object, etc.)
// This class is *not* intended to have dervied classes.
class Entity {
private:
  // TODO: add fields
  Position m_pos;
  std::string m_glyph;
  std::string m_properties;
  EntityController* m_controller;

  // copy constructor and assignment operator are disallowed
  Entity(const Entity &);
  Entity &operator=(const Entity &);


public:
  Entity();
  ~Entity();

  // Set the glyph that will represent this Entity.
  // Should consist of a single character.
  void setGlyph(const std::string &glyph);

  // Set the properties of this Entity.  Each character in the
  // string represents a single property.
  void setProperties(const std::string &props);

  // Get the glyph representing this Entity.
  std::string getGlyph() const;

  // Get the string containing this Entity's properties.
  std::string getProperties() const;

  // Return true if the Entity's properties contain the specified
  // character, false otherwise.
  bool hasProperty(char prop) const;

  // Set this Entity's EntityController, which will determine how it moves.
  // The Entity assumes responsibility for deleting it.
  void setController(EntityController *controller);

  // Get this Entity's EntityController.
  EntityController *getController();

  // Set this Entity's Position.
  void setPosition(const Position &pos);

  // Return this Entity's Position.
  Position getPosition() const;
};

#endif // ENTITY_H
