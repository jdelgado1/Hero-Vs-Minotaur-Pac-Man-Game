//Elaine He jhe48
//Shanelle scao15
//Jose Delgado jdelgad9
#include "entity.h"
#include "entitycontroller.h"

Entity::Entity() {
}

Entity::~Entity() {
  delete m_controller;
}

void Entity::setGlyph(const std::string &glyph) {
  m_glyph = glyph;
}

void Entity::setProperties(const std::string &props) {
  m_properties = props;
}

std::string Entity::getGlyph() const {
  return m_glyph;
}

std::string Entity::getProperties() const {
  return m_properties;
}

bool Entity::hasProperty(char prop) const {
  for(std::string::const_iterator it = m_properties.cbegin(); it != m_properties.cend(); ++it) {
    if(*it == prop) {
      return true;
    }
  }
  return false;
}

void Entity::setController(EntityController *controller) {
  m_controller = controller;
}

EntityController *Entity::getController() {
  return m_controller;
}

void Entity::setPosition(const Position &pos) {
  m_pos = pos;
}

Position Entity::getPosition() const {
  return m_pos;
}
