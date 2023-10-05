extends Node


func _ready() -> void:
	$HelloWorld.hello_world("Yolo")
	pass


func _process(delta: float) -> void:
	pass


func _on_hello_world_hello_world_signal(data: String) -> void:
	print("Yolo from GDExtension")
	pass
