#ifndef MODEL_H
#define MODEL_H

#include <string>

class ModelEntity {
};

class ModelFactory {
    public:
        static ModelFactory& getInstance() {
            static ModelFactory instance;
            return instance;
        }

        template <class T>
        void addNamedType(const std::string &name) {
        };

    private:
        ModelFactory() { };
        
    // this is a singleton and cannot be copied
    public:
        ModelFactory(ModelFactory const&)   = delete;
        void operator=(ModelFactory const&) = delete;
};

#endif /* MODEL_H */
