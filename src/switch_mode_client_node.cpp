#include "ros/ros.h"
#include "switch_mode_srvs/SwitchMode.h"
#include <cstdlib>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "switch_mode_client_node");

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<switch_mode_srvs::SwitchMode>("switch_path");
  switch_mode_srvs::SwitchMode my_srv;

  while (ros::ok())
  {
    //generate a random integer from 1 to 5, 5 should give error from server
    int r = rand()%5 + 1;
    my_srv.request.mode = r;
    ROS_INFO("Next mode: %d", (int)my_srv.request.mode);
    if (client.call(my_srv))
    {
      if (!my_srv.response.ack)
      {
        ROS_WARN("Service request sent but ACK=false was received.");
      }
      else
      {
        ROS_INFO("Service request sent and positive ACK received. Waiting 3 sec.");
        sleep(3);
      }
    }
    else
    {
      ROS_ERROR("Failed to call service switch_path");
      return 1;
    }
  }
  return 0;
}

