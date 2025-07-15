#ifndef REGISTRY_H
#define REGISTRY_H

#include <unordered_map>
#include <string>
#include <functional>

#define DECLARE_REGISTRY(BASE, ARGTYPES)                                        \
public:                                                                         \
    using fp = std::function<BASE* ARGTYPES>;                                   \
    static std::unordered_map<std::string, fp>& BASE##_registry(){              \
        static std::unordered_map<std::string, fp> BASE##_registry_table;       \
        return BASE##_registry_table;                                           \
    }

#define REGISTER_DERIVED(BASE, DERIVED, ARGNAMES, VARNAMES)                     \
    namespace {                                                                 \
        struct DERIVED##Registrar{                                              \
            DERIVED##Registrar(){                                               \
                BASE::BASE##_registry()[#DERIVED] =                             \
                []ARGNAMES -> BASE* {return new DERIVED VARNAMES;};            \
            }                                                                   \
        };                                                                      \
        static DERIVED##Registrar global_##DERIVED##_registrar;                 \
    }


#endif
