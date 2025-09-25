#ifndef GDEXAMPLE_H
#define GDEXAMPLE_H

#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/node_path.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/node.hpp>

using namespace godot;

class GDExample : public Sprite2D {
    GDCLASS(GDExample, Sprite2D);

private:
    double time_passed;
    double movement_radius;
    double scale_speed;
    double last_pulse_time;  // Track when we last emitted pulse_finished
    NodePath label_path;
    NodePath button_path;

protected:
    static void _bind_methods();

public:
    GDExample();
    ~GDExample();
    
    void _ready();                 // lifecycle method
    void _process(double delta);   // update loop
    
    // Exposed parameters
    void set_movement_radius(double p_radius);
    double get_movement_radius() const;
    
    void set_scale_speed(double p_speed);
    double get_scale_speed() const;
    
    // Label + Button paths
    void set_label_path(const NodePath &p_path);
    NodePath get_label_path() const;
    
    void set_button_path(const NodePath &p_path);
    NodePath get_button_path() const;
    
    // Custom behaviors
    void on_button_pressed();      // triggered externally
    void update_label_text(const String &text); // helper to change label
};

#endif // GDEXAMPLE_H