//
//  Model.hpp
//  Assignment4
//
//  Created by rick gessner on 2/15/20.
//

#ifndef Model_hpp
#define Model_hpp

#include <stdio.h>
#include <string>
#include "JSONParser.hpp"
#include <vector>
#include <map>
#include <cstring>

namespace ECE141 {
    
  class ModelQuery; //forward declare

  //STUDENT: Your Model is built from a bunch of these...
  class ModelNode {
  public:

      //sometimes a node holds a simple value.
      //sometimes a node is named
      //sometimes a node holds a collection of elements (or even other nodes)
      //would subclasses help or hurt here?
      ModelNode(Element type, std::string name="");
      ModelNode& operator=(const ModelNode& node);

      virtual void print(std::ostream& anOutput) = 0;
      virtual void addNode(ModelNode* aNode = nullptr) = 0;
      virtual std::vector<ModelNode*> getNodes() = 0;

      bool isObject(){ return type == Element::object;}
      bool isArray(){ return type == Element::array;}
      bool isConstant(){ return type == Element::constant;}

      Element getType() const { return type;}
      std::string getName(){ return name;}
      void setName(std::string n){ name = n;}

  protected:
      Element type;
      std::string name;
  };

  class ArrayNode : public ModelNode{
  public:
      ArrayNode(std::string name):ModelNode(Element::array, name){};

      void addNode(ModelNode* aNode){ nodes.push_back(aNode);}
      std::vector<ModelNode*> getNodes(){ return nodes;}
      void print(std::ostream& anOutput){
          anOutput << getName() << ":[" << std::endl;
          for (auto n : getNodes()){
              n->print(anOutput);
          }
          std::cout << "]" << std::endl;
      }
  protected:
        std::vector<ModelNode*> nodes;;
  };

  class ObjectNode : public ModelNode{
  public:
      ObjectNode(std::string name):ModelNode(Element::object, name){};

      void addNode(ModelNode* aNode){ nodes.push_back(aNode);}
      std::vector<ModelNode*> getNodes(){ return nodes;}
      void print(std::ostream& anOutput){
          anOutput << getName() << ":{" << std::endl;
          for (auto n : getNodes()){
              n->print(anOutput);
          }
          std::cout << "}" << std::endl;
      }
  protected:
      std::vector<ModelNode*> nodes;
  };

  enum ConstantType{number, boolean, quoted};
  class ConstantNode : public ModelNode{
  public:
      ConstantNode(std::string v, std::string name = ""):ModelNode(Element::constant, name), value(v){
          char c = v.c_str()[0];
          if (strcmp(v.c_str(), "true") == 0 || strcmp(v.c_str(), "false") == 0)
              cType = ConstantType::boolean;
          else if (c >= '0' && c <= '9')
              cType = ConstantType::number;
          else
              cType = ConstantType::quoted;
      };
      void addNode(ModelNode* aNode){}
      std::vector<ModelNode*> getNodes(){
          std::vector<ModelNode*> curNodes;
          curNodes.push_back(this);
          return curNodes;
      }
      void print(std::ostream& anOutput){
          if (getName() != "") anOutput << getName() << ":" << value << std::endl;
          else anOutput << value << std::endl;
      }
      std::string getValue(){
          return value;
      }
      bool isNumber(){
          return cType == ConstantType::number;
      }

  protected:
      std::string value;
      ConstantType cType;
  };


  class Model : public JSONListener {
   public:

     Model();
     Model(ModelNode* aNode);
     Model(const Model &aCommand);
     Model& operator=(const Model &aCommand);
     friend std::ostream& operator << (std::ostream& anOutput, const Model& aModel);

     ModelQuery query();
     ModelNode* getRoot() {return root;}

   protected:

      virtual bool addKeyValuePair(const std::string &aKey, const std::string &aValue);
      virtual bool addItem(const std::string &aValue);
      virtual bool openContainer(const std::string &aKey, Element aType);
      virtual bool closeContainer(const std::string &aKey, Element aType);

      void printHelper(ModelNode* cur);


//      bool addNodeToModel(ModelNode* node);
      
      // STUDENT: Your model will contain a collection of ModelNode*'s
      //          Choose your container(s) wisely
      ModelNode* root;
      std::stack<ModelNode*> stack;
   };

    //this is what gets returned when you query a model for a list of elements
  class ModelCollection {
  public:
      ModelCollection(){}
      ~ModelCollection(){}
      std::vector<ModelNode*> getNodes();
      void addNode(ModelNode* aNode);
      void addNodes(std::vector<ModelNode*> aNodes);
      void deleteNode(int s, int e);
      int size();
      void clear();

      friend std::ostream& operator << (std::ostream& anOutput, const ModelCollection& aModelCollect);

  protected:
      std::vector<ModelNode*> nodes;
     //STUDENT: choose an STL container to hold ModelNode* elements from your Model after a query...
  };

  class ModelQuery {
  public:
    
    ModelQuery& all(const std::string &aTarget);
    ModelQuery& first(const std::string &aTarget);
    ModelQuery& last(const std::string &aTarget);
    ModelQuery& nth(const std::string &aTarget, size_t anIndex);

    ModelQuery& before(const std::string &aTarget);
    ModelQuery& after(const std::string &aTarget);
    ModelQuery& within(const std::string &aTarget);
    ModelQuery& withinHelper(const std::string &aTarget);
    std::string valueOf();
    
    size_t            count();
    double            sum(const std::string &aField);
    double            avg(const std::string &aField);
    ModelCollection*  get();
    std::string       get(const std::string &aKey); //return value or empty string

    ModelQuery(Model &aModel);

    ModelQuery& operator=(ModelQuery &aModel);
          
    friend class Model;
    
    Model &model;

  protected:
      ModelNode* cur;
      ModelCollection* nodes;
      bool order;

      std::vector<ModelNode*> search(std::string aTarget);
      void dfs(std::string aTarget, ModelNode* node, std::vector<ModelNode*> &res);
//      ModelCollection nodes;
  };
  
 

}

#endif /* Model_hpp */
