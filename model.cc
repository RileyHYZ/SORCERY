#include "model.h"

#include <string>
#include <memory>

using namespace std;

// Adapted from CS 247 Tutorial 9 code

// Constructor

Model::Model() {}

// Protected Helper Methods

void Model::addView(unique_ptr<View> v){
  views.emplace_back(move(v));
}

void Model::addController(unique_ptr<Controller> c){
  controller = move(c);
}

// Public interface methods

void Model::displayMessage(const string& s){
  for(auto& view: views){
    view->displayMessage(s);
  }
}

void Model::displayViews(){
  for(auto& view: views){
    view->displayView();
  }
}

Command Model::getCommand(){
  return controller->getCommand();
}
