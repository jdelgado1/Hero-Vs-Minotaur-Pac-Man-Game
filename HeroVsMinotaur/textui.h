//Elaine He jhe48
//Shanelle scao15
//Jose Delgado jdelgad9
#ifndef TEXTUI_H
#define TEXTUI_H

#include "ui.h"

// A TextUI object implements the virtual functions of UI by printing
// to cout and reading from cin.
class TextUI : public UI {
private:
  // TODO: add fields
  // copy constructor and assignment operator disallowed
  TextUI(const TextUI &);
  TextUI &operator=(const TextUI &);

protected:
  std::string m_msg;

public:
  TextUI();
  virtual ~TextUI();

  virtual Direction getMoveDirection();

  virtual void displayMessage(const std::string &msg, bool endgame);

  virtual void render(Game *game);
};

#endif // TEXTUI_H
