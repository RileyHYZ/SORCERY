#include "model.h"

using namespace std;

// Adapted from CS 247 Tutorial 9 code

Model::Model() {}

// View-Related Methods

void Model::addView(unique_ptr<View> v){
  views.emplace_back(move(v));
}

// void Model::updateViews(int row, int col, State s){
//   for( auto& view: views ){
//     view->update(row, col, s);
//   }
// }

// void Model::updateViews(const string& s){
//   for( auto& view: views ){
//     view->update(s);
//   }
// }

void Model::displayViews(){
  for(auto& view: views){
    view->updateView();
  }
}

// Controller-Related Methods

void Model::addController(unique_ptr<Controller> c){
  controller = move(c);
}
bool Model::hasController(){
  return controller != nullptr;
}

Command Model::getCommand(){
  return controller->getCommand();
}
