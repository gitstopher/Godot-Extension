#include <godot_cpp/godot.hpp>
#include "gdexample.h"

using namespace godot;

void initialize_example_module(ModuleInitializationLevel p_level) {
    if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
        ClassDB::register_class<GDExample>();
    }
}

void uninitialize_example_module(ModuleInitializationLevel p_level) {
    // Cleanup here if needed
}

extern "C" GDE_EXPORT GDExtensionBool GDE_EXPORT example_library_init(
    GDExtensionInterfaceGetProcAddress p_interface,
    GDExtensionClassLibraryPtr p_library,
    GDExtensionInitialization* r_initialization
) {
    GDExtensionBinding::InitObject init_obj(p_interface, p_library, r_initialization);

    init_obj.register_initializer(initialize_example_module);
    init_obj.register_terminator(uninitialize_example_module);
    init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

    return init_obj.init();
}

