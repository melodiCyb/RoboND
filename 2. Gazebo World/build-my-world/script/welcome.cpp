#include <gazebo/gazebo.hh>

namespace gazebo
{
  class WorldPluginFourWheels : public WorldPlugin
  {
    public: WorldPluginFourWheels() : WorldPlugin()
            {
              printf("Welcome to Melodi's World!\n");
            }

    public: void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf)
            {
            }
  };
  GZ_REGISTER_WORLD_PLUGIN(WorldPluginFourWheels)
}



