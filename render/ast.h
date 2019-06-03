#ifndef AST_H
#define AST_H

#include <ostream>
#include <list>
#include <variant>

#include "location.hh"

class FQN {
    public:
        FQN();
        FQN(const std::string &identifier, yy::location &loc);
        FQN(const FQN &parent, const std::string &identifier, yy::location &loc);

        friend std::ostream& operator<<(std::ostream& stream, const FQN& fqn);

    private:
        std::list<std::string> parts_;
        yy::location loc_;
};

std::ostream& operator<<(std::ostream& stream, const FQN& fqn);

class Value {
    public:
        Value();
        Value(int intval, yy::location &loc);
        Value(const std::string &value, yy::location &loc);
        Value(const FQN &fqn, yy::location &loc);

        friend std::ostream& operator<<(std::ostream& stream, const Value& value);

    private:
        std::variant<int, std::string, FQN> contents_; 
        yy::location loc_;
};

std::ostream& operator<<(std::ostream& stream, const Value& value);

class Property {
    public:
        Property();
        Property(const std::string &key, const Value &value, yy::location &loc);

        friend std::ostream& operator<<(std::ostream& stream, const Property& property);

    private:
        std::string key_;
        Value value_;
        yy::location loc_;
};

std::ostream& operator<<(std::ostream& stream, const Property& property);

class Entity {
    public:
        Entity();
        Entity(const std::string &type, const std::string &name, const std::list<Property> &properties,
            const std::list<Entity> &entities, yy::location &loc);

        friend std::ostream& operator<<(std::ostream& stream, const Entity& entity);

    private:
        std::string type_;
        std::string name_;
        std::list<Property> properties_;
        std::list<Entity> entities_;
        yy::location loc_;
};

std::ostream& operator<<(std::ostream& stream, const Entity& entity);

std::ostream& operator<<(std::ostream& stream, const std::list<Entity>& entities);

std::ostream& operator<<(std::ostream &stream, const std::pair<std::list<Property>,std::list<Entity>> &body);

std::ostream& operator<<(std::ostream &stream, const std::list<Property> &properties);

#endif /* AST_H */
