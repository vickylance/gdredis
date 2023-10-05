#ifndef HELLO_WORLD_HPP
#define HELLO_WORLD_HPP

#include <godot_cpp/classes/node2d.hpp>

namespace godot
{
    class HelloWorld : public Node2D
    {
        GDCLASS(HelloWorld, Node2D)

    private:
        double speed;
        Vector2 velocity;

    protected:
        static void _bind_methods();

    public:
        HelloWorld();  // constructor
        ~HelloWorld(); // destructor
        void hello_world(String words);
        void set_speed(const double speed);
        double get_speed() const;
        void _process(double delta) override;
    };
}

#endif