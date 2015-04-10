#ifndef SPATIAL_WORLD_MODEL_TRACKER_H_
#define SPATIAL_WORLD_MODEL_TRACKER_H_

#include <mysql/mysql.h>
#include <ros/ros.h>
#include <interactive_world_msgs/StoreObservation.h>
#include <interactive_world_msgs/FindObservations.h>

#define SWM_DEFAULT_SERVER "localhost"

#define SWM_DEFAULT_PORT 3306

#define SWM_DEFAULT_USER "ros"

#define SWM_DEFAULT_PASSWORD ""

#define SWM_DEFAULT_DATABASE "rms"

#define SWM_TABLE "swms"

#define SWM_CREATE_TABLE "CREATE TABLE IF NOT EXISTS `swms` \
                         (`id` int(10) unsigned NOT NULL AUTO_INCREMENT, \
                          `surface` varchar(255) NOT NULL, \
                          `placement_surface_frame_id` varchar(255) NOT NULL, \
                          `item` varchar(255) NOT NULL, \
                          `item_conf` double NOT NULL, \
                          `x` double NOT NULL, \
                          `y` double NOT NULL, \
                          `z` double NOT NULL, \
                          `theta` float NOT NULL, \
                          `time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP, \
                          PRIMARY KEY (`id`) \
                         ) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1;"

class spatial_world_model_server
{
public:
  spatial_world_model_server();

  ~spatial_world_model_server();

  bool connected();

private:
  bool store_observation_cb(interactive_world_msgs::StoreObservation::Request &req, interactive_world_msgs::StoreObservation::Response &resp);
  bool find_observations_cb(interactive_world_msgs::FindObservations::Request &req,
      interactive_world_msgs::FindObservations::Response &resp);

  time_t extract_time(const std::string &str) const;

  MYSQL_RES *query(std::string query);

  /** Main MySQL connection */
  MYSQL *conn_;

  ros::NodeHandle private_;
  std::string host_, user_, password_, database_;
  int port_;
  bool connected_;

  ros::ServiceServer store_observation_, find_observations_;
};

int main(int argc, char **argv);

#endif
