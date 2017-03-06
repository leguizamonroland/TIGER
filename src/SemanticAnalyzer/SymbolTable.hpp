
#pragma once

#include <unordered_map>

#include "Level.hpp"
#include "Record.hpp"
#include "SymbolTablePair.hpp"

/// Implement the scoping and symbol table details in this file
class SymbolTable;

using SymbolTablePtr = std::shared_ptr<SymbolTable>;

class SymbolTable {
 private:
  Level topLevel;
  Level currLevel;

  int scopeLevel;
  std::map<SymbolTablePair, RecordPtr> table_;

 public:
  SymbolTable(int level) {
    scopeLevel = level;
    insertConstants();
  }

  void insertTypes(SymbolTablePair& idx,     // NOLINT
                   std::string arg1,         // NOLINT
                   std::string arg2 = "",    // NOLINT
                   std::string arg3 = "") {  // NOLINT
    RecordPtr record = std::make_shared<Record>(scopeLevel);
    if (arg1 == "array") {
      /*************************************
      * type id = array [num] of type_id
      *            |      |        |
      *           arg1   arg2     arg3
      *************************************/
      record->dimension = std::stoi(arg2);
      record->type = arg3;
    } else {
      /*************************************
      * type id = <id> | int | float
      *************************************/
      record->dimension = lookup(Entry::Types, arg1)->getDimension();
      record->type = lookup(Entry::Types, arg1)->getType();
    }
    // insert into table
    table_[idx] = record;
  }

  void insertFunctions(SymbolTablePair& idx,                  // NOLINT
                       std::string retType,                   // NOLINT
                       std::vector<std::string>& paramTypes,  // NOLINT
                       std::vector<std::string>& params) {    // NOLINT
    RecordPtr record = std::make_shared<Record>(scopeLevel);
    record->parameterTypes.reserve(paramTypes.size());
    record->parameterDimensions.reserve(paramTypes.size());
    for (auto& paramType : paramTypes) {
      // assign parameters type
      record->parameterTypes.push_back(
          lookup(Entry::Types, paramType)->getType());
      // assign parameters dim
      record->parameterDimensions.push_back(
          lookup(Entry::Types, paramType)->getDimension());
    }
    // assign parameters
    record->parameters = std::move(params);

    // assign return type
    record->returnType = retType;
    // insert into table
    table_[idx] = record;
  }

  void insertVariables(SymbolTablePair& idx,     // NOLINT
                       std::string arg1,         // NOLINT
                       std::string arg2 = "",    // NOLINT
                       std::string arg3 = "") {  // NOLINT
    RecordPtr record = std::make_shared<Record>(scopeLevel);

    if (arg1 == "array") {
      record->dimension = std::stoi(arg2);
      record->type = arg3;
    } else {
      record->dimension = lookup(Entry::Types, arg1)->getDimension();
      record->type = lookup(Entry::Types, arg1)->getType();
    }
    table_[idx] = record;
  }

  void insertConstants() {
    RecordPtr record1 = std::make_shared<Record>(scopeLevel);
    record1->dimension = 1;
    record1->type = "int";
    SymbolTablePair idx1(Entry::Types, "int");
    table_[idx1] = record1;

    RecordPtr record2 = std::make_shared<Record>(scopeLevel);
    record2->dimension = 1;
    record2->type = "float";
    SymbolTablePair idx2(Entry::Types, "float");
    table_[idx2] = record2;
  }

  void insertTemporaries() {
    std::cerr << "Not Implemented! \n";
    std::exit(EXIT_FAILURE);
  }

  const RecordPtr lookup(Entry entry, std::string name) {
    SymbolTablePair idx(entry, name);
    if (table_.find(idx) == table_.end()) {
      std::cerr << name << " is not defined before! \n";
      std::exit(EXIT_FAILURE);
    }
    return table_[idx];
  }

  void dump() {
    for (auto& item : table_) {
      std::cout << "\n\n----------------------------------------" << std::endl;
      std::cout << "Table: ";
      if (item.first.getEntry() == Entry::Types) {
        std::cout << "Types" << std::endl;
        std::cout << "Name: " << item.first.getName() << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "Scope: " << scopeLevel << std::endl;
        std::cout << "Type: " << item.second->getType() << std::endl;
        std::cout << "Dimension: " << item.second->getDimension() << std::endl;
        std::cout << "Parameters: -" << std::endl;
        std::cout << "Parameter types: -" << std::endl;
        std::cout << "Parameter dimensions: -" << std::endl;
        std::cout << "Return type: -" << std::endl;
      } else if (item.first.getEntry() == Entry::Variables) {
        std::cout << "Variables:" << std::endl;
        std::cout << "Name: " << item.first.getName() << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "Scope: " << scopeLevel << std::endl;
        std::cout << "Type: " << item.second->getType() << std::endl;
        std::cout << "Dimension: " << item.second->getDimension() << std::endl;
        std::cout << "Parameters: -" << std::endl;
        std::cout << "Parameter types: -" << std::endl;
        std::cout << "Parameter dimensions: -" << std::endl;
        std::cout << "Return type: -" << std::endl;
      } else if (item.first.getEntry() == Entry::Functions) {
        std::cout << "Functions:" << std::endl;
        std::cout << "Name: " << item.first.getName() << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "Scope: " << scopeLevel << std::endl;
        std::cout << "Type: -" << std::endl;
        std::cout << "Dimension: -" << std::endl;
        auto& paramType = item.second->getParameterTypes();
        auto& paramDims = item.second->getParameterDimensions();
        auto& params = item.second->getParameters();
        size_t size = params.size();
        std::cout << "Parameters: [";
        for (int i = 0; i < size; ++i) {
          std::cout << params[i];
          if (i != size - 1) {
            std::cout << ",";
          }
        }
        std::cout << "]" << std::endl;

        std::cout << "Parameter types: [";
        for (int i = 0; i < size; ++i) {
          std::cout << paramType[i];
          if (i != size - 1) {
            std::cout << ",";
          }
        }
        std::cout << "]" << std::endl;

        std::cout << "Parameter dimensions: [";
        for (int i = 0; i < size; ++i) {
          std::cout << paramDims[i];
          if (i != size - 1) {
            std::cout << ",";
          }
        }
        std::cout << "]" << std::endl;
        std::cout << "Return type: " << item.second->getReturnType()
                  << std::endl;
      }
    }
    std::cout << "----------------------------------------\n" << std::endl;
  }
};
