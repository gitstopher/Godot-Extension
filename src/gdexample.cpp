#include "gdexample.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/button.hpp>

using namespace godot;

void GDExample::_bind_methods() {
    // Export parameters
    ClassDB::bind_method(D_METHOD("set_movement_radius", "radius"), &GDExample::set_movement_radius);
    ClassDB::bind_method(D_METHOD("get_movement_radius"), &GDExample::get_movement_radius);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "movement_radius"), "set_movement_radius", "get_movement_radius");

    ClassDB::bind_method(D_METHOD("set_scale_speed", "speed"), &GDExample::set_scale_speed);
    ClassDB::bind_method(D_METHOD("get_scale_speed"), &GDExample::get_scale_speed);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "scale_speed"), "set_scale_speed", "get_scale_speed");

    // NodePaths
    ClassDB::bind_method(D_METHOD("set_label_path", "path"), &GDExample::set_label_path);
    ClassDB::bind_method(D_METHOD("get_label_path"), &GDExample::get_label_path);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "label_path"), "set_label_path", "get_label_path");

    ClassDB::bind_method(D_METHOD("set_button_path", "path"), &GDExample::set_button_path);
    ClassDB::bind_method(D_METHOD("get_button_path"), &GDExample::get_button_path);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "button_path"), "set_button_path", "get_button_path");

    // Signals
    ADD_SIGNAL(MethodInfo("pulse_finished"));
    ADD_SIGNAL(MethodInfo("sprite_scaled"));

    // Methods
    ClassDB::bind_method(D_METHOD("on_button_pressed"), &GDExample::on_button_pressed);
    ClassDB::bind_method(D_METHOD("update_label_text", "text"), &GDExample::update_label_text);
}

GDExample::GDExample() {
    time_passed = 0.0;
    movement_radius = 50.0;
    scale_speed = 1.0;
}

GDExample::~GDExample() {}

void GDExample::_ready() {
    // Connect button
    if (!button_path.is_empty()) {
        Node *btn_node = get_node_or_null(button_path);
        godot::Button *btn = Object::cast_to<godot::Button>(btn_node);
        if (btn) {
            btn->connect("pressed", Callable(this, "on_button_pressed"));
        }
    }

    // Initialize label
    if (!label_path.is_empty()) {
        Node *lbl_node = get_node_or_null(label_path);
        godot::Label *lbl = Object::cast_to<godot::Label>(lbl_node);
        if (lbl) {
            lbl->set_text("Ready!");
        }
    }
}

void GDExample::_process(double delta) {
    time_passed += delta;

    // Movement
    Vector2 new_position(
        100.0 + movement_radius * Math::sin(time_passed * 2.0),
        100.0 + movement_radius * Math::cos(time_passed * 1.5)
    );
    set_position(new_position);

    // Pulsing
    double scale_amount = 1.0 + 0.25 * Math::sin(time_passed * scale_speed);
    set_scale(Vector2(scale_amount, scale_amount));

    // Signals
    if (static_cast<int>(time_passed) % 5 == 0) {
        emit_signal("pulse_finished");
    }
    if (scale_amount > 1.2) {
        emit_signal("sprite_scaled");
    }
}

// Setters/Getters
void GDExample::set_movement_radius(double p_radius) { movement_radius = p_radius; }
double GDExample::get_movement_radius() const { return movement_radius; }

void GDExample::set_scale_speed(double p_speed) { scale_speed = p_speed; }
double GDExample::get_scale_speed() const { return scale_speed; }

void GDExample::set_label_path(const NodePath &p_path) { label_path = p_path; }
NodePath GDExample::get_label_path() const { return label_path; }

void GDExample::set_button_path(const NodePath &p_path) { button_path = p_path; }
NodePath GDExample::get_button_path() const { return button_path; }

// Custom Methods
void GDExample::on_button_pressed() {
    UtilityFunctions::print("Button pressed! Sprite reacts.");
    set_scale(Vector2(2.0, 2.0));
    update_label_text("Button clicked!");
}

void GDExample::update_label_text(const String &text) {
    if (!label_path.is_empty()) {
        Node *lbl_node = get_node_or_null(label_path);
        godot::Label *lbl = Object::cast_to<godot::Label>(lbl_node);
        if (lbl) {
            lbl->set_text(text);
        }
    }
}