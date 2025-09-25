extends Node2D

# In your scene's script
func _ready():
   $GDExampleNode.pulse_finished.connect(_on_pulse_finished)
   $GDExampleNode.sprite_scaled.connect(_on_sprite_scaled)
   
func _on_pulse_finished():
   print("Pulse finished received!")
   
func _on_sprite_scaled():
   print("Sprite scaled received!")
