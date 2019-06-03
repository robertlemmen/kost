#include "ast.h"

using namespace std;

FQN::FQN() {
}

FQN::FQN(const string &identifier, yy::location &loc):
        loc_(loc) {
    parts_.push_back(identifier);
}

FQN::FQN(const FQN &parent, const string &identifier, yy::location &loc):
        parts_(parent.parts_),
        loc_(loc) {
    parts_.push_back(identifier);
}

ostream& operator<<(ostream &stream, const FQN &fqn) {
    bool first = true;
    for (auto it: fqn.parts_) {
        if (first) {
            first = false;
        }
        else {
            stream << "::";
        }
        stream << it;
    }
    return stream;
}

Value::Value() {
}

Value::Value(int intval, yy::location &loc):
        contents_(intval),
        loc_(loc) {
}

Value::Value(const string &value, yy::location &loc):
        contents_(value),
        loc_(loc) {
}

Value::Value(const FQN &fqn, yy::location &loc):
        contents_(fqn),
        loc_(loc) {
}

ostream& operator<<(ostream &stream, const Value &value) {
    visit([&stream](auto const& e){ stream << e; }, value.contents_);
    return stream;
}

Property::Property() {
}

Property::Property(const string &key, const Value &value, yy::location &loc):
        key_(key),
        value_(value),
        loc_(loc) {
}

ostream& operator<<(ostream &stream, const Property &prop) {
    stream << prop.key_ << ": " << prop.value_ << "      [" << prop.loc_ << "]" << endl;
    return stream;
}

Entity::Entity() {
}

Entity::Entity(const string &type, const string &name, const list<Property> &properties,
            const list<Entity> &entities, yy::location &loc):
        type_(type),
        name_(name),
        properties_(properties),
        entities_(entities),
        loc_(loc) {
}

ostream& operator<<(ostream &stream, const Entity &entity) {
    stream << entity.type_ << " " << entity.name_ << " {      [" << entity.loc_ << "] " << endl;
    for (auto it : entity.properties_) {
        stream << it;
    }
    for (auto it : entity.entities_) {
        stream << it;
    }
    stream << "}" << endl;
    return stream;
}

ostream& operator<<(ostream& stream, const list<Entity>& entities) {
    for (auto it : entities) {
        stream << it;
    }
    return stream;
}

ostream& operator<<(ostream &stream, const pair<list<Property>,list<Entity>> &body) {
    // XXX
    return stream;
}

ostream& operator<<(ostream &stream, const list<Property> &properties) {
    for (auto it : properties) {
        stream << it;
    }
    return stream;
}
