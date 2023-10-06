#include "HelloWorld.hpp"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <hiredis/hiredis.h>

using namespace godot;

void HelloWorld::_bind_methods()
{
    // Expose the below methods to GDScript
    ClassDB::bind_method(D_METHOD("get_speed"), &HelloWorld::get_speed);
    ClassDB::bind_method(D_METHOD("set_speed", "speed"), &HelloWorld::set_speed);
    ClassDB::add_property("HelloWorld", PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");

    ClassDB::bind_method(D_METHOD("hello_world", "words"), &HelloWorld::hello_world);

    ADD_SIGNAL(MethodInfo("hello_world_signal", PropertyInfo(Variant::STRING, "data")));
}

HelloWorld::HelloWorld()
{
    if (Engine::get_singleton()->is_editor_hint())
    {
        set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
    }
    UtilityFunctions::print("Hello World");

    redisContext *context = redisConnect("localhost", 6379);
    if (context == NULL || context->err)
    {
        if (context)
        {
            UtilityFunctions::print("Connection error: %s\n", context->errstr);
            redisFree(context);
        }
        else
        {
            UtilityFunctions::print("Connection error: Can't allocate redis context\n");
        }
        exit(1);
    }

    UtilityFunctions::print("Redis connection successful");

    // SET a key-value pair
    redisReply *reply = (redisReply *)redisCommand(context, "SET mykey myvalue");
    if (reply == NULL)
    {
        UtilityFunctions::print("SET failed\n");
        exit(1);
    }
    freeReplyObject(reply);
    UtilityFunctions::print("Redis SET successful");

    // GET the value of a key
    redisReply *getReply = (redisReply *)redisCommand(context, "GET mykey");
    if (getReply == NULL)
    {
        UtilityFunctions::print("GET failed\n");
        exit(1);
    }
    UtilityFunctions::print("GET mykey: ", getReply->str);
    freeReplyObject(getReply);

    redisFree(context);
}

HelloWorld::~HelloWorld()
{
}

void HelloWorld::hello_world(String words)
{
    UtilityFunctions::print("Call hello world: " + words);
    emit_signal("hello_world_signal", "data!");
}

void HelloWorld::_process(double delta)
{
    // UtilityFunctions::print("Hello from process");
    velocity = Vector2(0.0f, 0.0f);
    Input &inputSingleton = *Input::get_singleton();
    if (inputSingleton.is_action_pressed("d"))
    {
        velocity.x += 1.0f;
    }
    if (inputSingleton.is_action_pressed("a"))
    {
        velocity.x -= 1.0f;
    }
    if (inputSingleton.is_action_pressed("w"))
    {
        velocity.y -= 1.0f;
    }
    if (inputSingleton.is_action_pressed("s"))
    {
        velocity.y += 1.0f;
    }

    set_position(get_position() + (velocity * speed * delta));
}

void HelloWorld::set_speed(const double speed)
{
    this->speed = speed;
}

double HelloWorld::get_speed() const
{
    return speed;
}