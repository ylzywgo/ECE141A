//
//  Model.cpp
//  Assignment4
//
//  Created by rick gessner on 2/15/20.
//

#include "Model.hpp"
#include <cstring>
#include <iostream>
#include <iterator>
#include <string>

namespace ECE141 {

    ModelNode::ModelNode(Element type, std::string name){
        this->name = name;
        this->type = type;
    }

    ModelNode& ModelNode::operator=(const ModelNode& node){
        *this = node;
        return *this;
    }

  ModelQuery::ModelQuery(Model &aModel) : model(aModel) {
      cur = model.getRoot();
      nodes = new ModelCollection();
      nodes->addNode(cur);
      order = true;
  }

  ModelQuery& ModelQuery::operator=(ModelQuery &aModel){
      *this = aModel;
      return *this;
  }

  std::vector<ModelNode*> ModelQuery::search(std::string aTarget) {
      std::vector<ModelNode*> res;
      for (ModelNode* node : nodes->getNodes()){
//          std::cout << node->getName() << std::endl;
          if (strcmp(node->getName().c_str(), aTarget.c_str()) == 0){
              res.push_back(node);
          }
          dfs(aTarget, node, res);
      }

    return res;
  }

  void ModelQuery::dfs(std::string aTarget, ModelNode* node, std::vector<ModelNode*> &res){
      if (node->isConstant()) return;
      for (ModelNode* n : node->getNodes()){
          if (strcmp(n->getName().c_str(), aTarget.c_str()) == 0){
              res.push_back(n);
          }
          dfs(aTarget, n, res);
      }
  }

  ModelQuery& ModelQuery::all(const std::string &aTarget) {
      if (strcmp("*", aTarget.c_str()) == 0){
          return *this;
      }

      std::vector<ModelNode*> tmp = search(aTarget);
      if (tmp.size() == 0){
          cur = nullptr;
          nodes->clear();
          return *this;
      }

      cur = tmp[0];

//      for (ModelNode* node : nodes->getNodes()){
//          if (strcmp(node->getName().c_str(), aTarget.c_str()) == 0){
//              cur = node;
//              break;
//          }
//      }

      nodes->clear();
      nodes->addNodes(cur->getNodes());

      return *this;
  }

  ModelQuery& ModelQuery::first(const std::string &aTarget) {
      int index = 0;
      if (strcmp("*", aTarget.c_str()) == 0){
          if (!order) index = nodes->size() - 1;
          if (cur->isArray()){
              cur = cur->getNodes()[index];
          }
          else{
              cur = nodes->getNodes()[index];
          }
      }
      else{
          std::vector<ModelNode*> tmp = search(aTarget);
          if (tmp.size() == 0){
              std::cout << "empty" << std::endl;
              return *this;
          }
          else{
              if (!order) index = tmp.size() - 1;
              cur = tmp[index];
          }
//          for (ModelNode* node : nodes->getNodes()){
//              if (strcmp(node->getName().c_str(), aTarget.c_str()) == 0){
//                  cur = node->getNodes()[0];
//                  break;
//              }
//          }
      }
//      std::cout << cur->getName() << std::endl;
      nodes->clear();
      nodes->addNodes(cur->getNodes());

      return *this;
  }

  ModelQuery& ModelQuery::last(const std::string &aTarget) {
      int index = 0;
      if (strcmp("*", aTarget.c_str()) == 0){
          if (order) index = nodes->size() - 1;

          if (cur->isArray()){
              cur = cur->getNodes()[index];
          }
          else{
              cur = nodes->getNodes()[index];
          }
      }
      else{
          std::vector<ModelNode*> tmp = search(aTarget);
          if (tmp.size() == 0)
              return *this;
          else{
              if (order) index = tmp.size() - 1;
              cur = tmp[index];
          }
//          for (ModelNode* node : nodes->getNodes()){
//              if (strcmp(node->getName().c_str(), aTarget.c_str()) == 0){
//                  cur = node->getNodes()[nodes->size() - 1];
//                  break;
//              }
//          }
      }
//      std::cout << cur->getName() << std::endl;
      nodes->clear();
      nodes->addNodes(cur->getNodes());

      return *this;
  }

  ModelQuery& ModelQuery::nth(const std::string &aTarget, size_t anIndex) {
      int index = anIndex - 1;
//      std::cout << "nth" << std::endl;
      try{
          if (strcmp("*", aTarget.c_str()) == 0){
              if (!order) index = nodes->size() - anIndex;

              if (cur->isArray()){
                  cur = cur->getNodes()[index];
              }
              else{
                  cur = nodes->getNodes()[index];
              }
          }
          else{
              std::vector<ModelNode*> tmp = search(aTarget);
              if (tmp.size() == 0)
                  return *this;
              else{
                  if (!order) index = tmp.size() - anIndex;
                  cur = tmp[index];
              }
//          for (ModelNode* node : nodes->getNodes()){
//              if (strcmp(node->getName().c_str(), aTarget.c_str()) == 0){
//                  cur = node->getNodes()[anIndex];
//                  break;
//              }
//          }
          }
//          std::cout << cur->getName() << std::endl;
          nodes->clear();
          nodes->addNodes(cur->getNodes());

          return *this;
      }
      catch (...){
          return *this;
      }
  }

  ModelQuery& ModelQuery::before(const std::string &aTarget) {
      order = false;
      if (strcmp("*", aTarget.c_str()) == 0){
          return *this;
      }
      else{
          std::vector<ModelNode*>::iterator it = nodes->getNodes().end() - 1;
          int i = nodes->size() - 1;
          while (it != nodes->getNodes().begin() - 1){
              ModelNode* n = *it;
//              std::cout << n->getName() << std::endl;
              if (strcmp(n->getName().c_str(), aTarget.c_str()) == 0){
                  break;
              }
              it--;
              i--;
          }
          if (i >= 0){
              nodes->deleteNode(i, nodes->size());
              cur = (*(--it));
//              std::cout << nodes->size() << std::endl;
          }
      }
      return *this;
  }

  ModelQuery& ModelQuery::after(const std::string &aTarget) {
      order = true;
      if (strcmp("*", aTarget.c_str()) == 0){
          return *this;
      }
      else{
          std::vector<ModelNode*>::iterator it = nodes->getNodes().begin();
          int i = 0;
          while (it != nodes->getNodes().end()){
              ModelNode* n = *it;
              if (strcmp(n->getName().c_str(), aTarget.c_str()) == 0){
                  break;
              }
              it++;
              i++;
          }
          if (i <= nodes->size()){
              nodes->deleteNode(0, i + 1);
              cur = (*(++it));
          }
      }
      return *this;
  }

  ModelQuery& ModelQuery::within(const std::string &aTarget){
      std::string aTar = aTarget;
//      std::cout << aTar.substr(0, 4) << std::endl;
      if (strcmp(aTar.substr(0, 4).c_str(), "root") != 0)
          aTar.insert(0, "root.");
      return withinHelper(aTar);
  }

  ModelQuery& ModelQuery::withinHelper(const std::string &aTarget) {
      int index = 0;

      if ((index = aTarget.find(".")) == -1){
//          std::cout << aTarget << std::endl;
          for (ModelNode* node : nodes->getNodes()){
              if (strcmp(node->getName().c_str(), aTarget.c_str()) == 0){
                  cur = node;
                  break;
              }
          }
//          std::cout << cur->getName() << std::endl;
          nodes->clear();
          nodes->addNodes(cur->getNodes());
      }
      else{
          std::string curNode = aTarget.substr(0, index);
          for (ModelNode* node : nodes->getNodes()){
//              std::cout << "curnode:" << node->getName() << std::endl;
              if (strcmp(node->getName().c_str(), curNode.c_str()) == 0){
                  cur = node;
                  break;
              }
          }
          nodes->clear();
          nodes->addNodes(cur->getNodes());
          withinHelper(aTarget.substr(index + 1));
      }
//      std::cout << "out" << std::endl;
      return *this;
  }

  std::string ModelQuery::valueOf() {
    return std::string("hi");
  }

  ModelCollection* ModelQuery::get() {
    return nodes;
  }

  std::string ModelQuery::get(const std::string &aKey) {
      std::string res = "";
      try{
          for (ModelNode* node : nodes->getNodes()){
              if (strcmp(node->getName().c_str(), aKey.c_str()) == 0){
                  if (!node->isConstant()) return res;
                  ConstantNode* cur = static_cast<ConstantNode*>(node);
                  return cur->getValue();
              }
          }

          return res;
      }
      catch (...) {
          return res;
      }
  }

  size_t ModelQuery::count() {
      try {
          return nodes->size();
      }
      catch (...){
          return 0;
      }
  }

  double ModelQuery::avg(const std::string &aField) {
      double s = sum(aField);
      if (s == 0.0) return 0.0;
      int count = 0;
      if (aField == ""){
          return s / nodes->size();
      }
      for (ModelNode* node : nodes->getNodes()){
          if (strcmp(node->getName().c_str(), aField.c_str()) == 0) {
              if (node->isConstant()) {
                  return s;
              } else {
                  for (ModelNode *n : node->getNodes()) {
                      if (n->isConstant()) {
                          ConstantNode *cur = static_cast<ConstantNode *>(n);
                          if (cur->isNumber())
                              count++;
                      }
                  }
              }
          }
      }
      return s / count;
  }

  double ModelQuery::sum(const std::string &aField) {
      double res = 0.0;
      if (aField == ""){
          if (!cur->isArray()){
              return res;
          }
          for (ModelNode* node : nodes->getNodes()){
              if (node->isConstant()) {
                  ConstantNode *cur = static_cast<ConstantNode *>(node);
                  if (cur->isNumber())
                      res += std::stod(cur->getValue());
              }
          }
      }
      else{
          for (ModelNode* node : nodes->getNodes()){
              if (strcmp(node->getName().c_str(), aField.c_str()) == 0){
                  if (node->isConstant()) {
                      std::cout << "sum = " << std::endl;
                      ConstantNode *cur = static_cast<ConstantNode *>(node);
                      if (cur->isNumber())
                          return std::stod(cur->getValue());
                      else
                          return res;
                  }
                  else if (node->isArray()){
                      for (ModelNode* n : node->getNodes()){
                          if (n->isConstant()) {
                              ConstantNode *cur = static_cast<ConstantNode *>(n);
                              if (cur->isNumber())
                                  res += std::stod(cur->getValue());
                          }
                      }
                  }
                  else{
                      return res;
                  }
              }
          }
      }
      return res;
  }

  //---------------------- implement the model class... --------------------

  Model::Model() {
  }

  Model::Model(ModelNode* node) {
      root = node;
  }

  Model::Model(const Model &aCommand) {
      *this= aCommand;
  }
  
  Model& Model::operator=(const Model &aCommand) {
//      std::cout << "Model = " << std::endl;
      *this = aCommand;
      return *this;
  }
    
  ModelQuery Model::query() {
    ModelQuery theQuery(*this);
    return theQuery;
  }


  bool Model::addKeyValuePair(const std::string &aKey, const std::string &aValue) {
    std::cout <<  "\t|" << aKey <<":" << aValue << "| \n";
    ModelNode* child = new ConstantNode(aValue, aKey);

    if (stack.size() == 0) {
//        std::cout << "1111" << std::endl;
        return false;
    }

    ModelNode* node = stack.top();
    if (!node->isObject()) {
//        std::cout << "2222" << std::endl;
        return false;
    }

    node->addNode(child);

    return true;
  }
    
  bool Model::addItem(const std::string &aValue) {
    std::cout <<  "\t" << aValue << " \n";
    ModelNode* child = new ConstantNode(aValue);

    if (stack.size() == 0) {
//        std::cout << "3333" << std::endl;
        return false;
    }

    ModelNode* node = stack.top();
    if (!node->isArray()) {
//        std::cout << "4444" << std::endl;
        return false;
    }

    node->addNode(child);
    return true;
  }

  bool Model::openContainer(const std::string &aContainerName, ECE141::Element aType){
    //open a new unnamed container in our model...
    std::cout << aContainerName << " { \n";

    ModelNode* node;
    switch (aType){
        case Element::object:
            node = new ObjectNode(aContainerName);
            break;
        case Element::array:
            node = new ArrayNode(aContainerName);
            break;
        default:
//            std::cout << "5555" << std::endl;
            return false;
    }

    if (stack.size() == 0) {
        stack.push(node);
        return true;
    }

    ModelNode* prev = stack.top();
//    std::cout << "0000" << std::endl;
    if (!prev->isObject() && !prev->isArray()) {
//        std::cout << "6666" << std::endl;
        return false;
    }

    prev->addNode(node);

    stack.push(node);
//    std::cout << "push" << std::endl;
    return true;
  }

  bool Model::closeContainer(const std::string &aContainerName, ECE141::Element aType){
    std::cout  << " } \n";
    ModelNode* node = stack.top();
    if (node->getType() != aType) {
//        std::cout << "7777" << std::endl;
        return false;
    }
    stack.pop();
    if (stack.size() == 0){
        root = node;
        root->setName("root");
    }
//    std::cout << "pop" << std::endl;

    return true;
  }

  std::ostream& operator<<(std::ostream& anOutput, const Model& aModel){
        aModel.root->print(anOutput);
        return anOutput;
    }

//  void Model::print(){
//      printHelper(root);
//  }

//  void Model::printHelper(ModelNode* cur){
//      Element type = cur->getType();
//      switch (type){
//          case Element::constant: {
//              ConstantNode *curNode = static_cast<ConstantNode *>(cur);
//              curNode->print();
//              break;
//          }
//          case Element::object:{
//              std::cout << cur->getName() << "{" << std::endl;
//              ObjectNode *curNode = static_cast<ObjectNode *>(cur);
//              for (auto n : curNode->getNodes()){
//                  printHelper(n);
//              }
//              std::cout << "}" << std::endl;
//              break;
//          }
//          case Element::array:{
//              std::cout << cur->getName() << "[" << std::endl;
//              ArrayNode *curNode = static_cast<ArrayNode *>(cur);
//              for (auto n : curNode->getNodes()){
//                  printHelper(n);
//              }
//              std::cout << "]" << std::endl;
//              break;
//          }
//          default:
//              break;
//      }
//  }

  std::vector<ModelNode*> ModelCollection::getNodes(){
      return nodes;
  }

  void ModelCollection::addNode(ModelNode* aNode){
      nodes.push_back(aNode);
  }

  void ModelCollection::addNodes(std::vector<ModelNode*> aNodes){
      nodes.insert(nodes.end(), aNodes.begin(), aNodes.end());
  }

  void ModelCollection::deleteNode(int s, int e){
      nodes.erase(nodes.begin() + s, nodes.begin() + e);
  }

  int ModelCollection::size(){
      return nodes.size();
  }

  void ModelCollection::clear(){
      nodes.clear();
  }

  std::ostream& operator <<(std::ostream& anOutput, const ModelCollection& aModelCollect){

      for (ModelNode* n : aModelCollect.nodes){
          n->print(anOutput);
//          if (n->isConstant() && n->getName() == ""){
//              ConstantNode *curNode = static_cast<ConstantNode *>(n);
//              anOutput << curNode->getValue() << " ";
//          }else{
//              anOutput << n->getName() << " ";
//          }
      }
      return anOutput;
  }
}
