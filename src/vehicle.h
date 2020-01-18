#ifndef VEHICLE_H
#define VEHICLE_H

#include <map>
#include <string>
#include <vector>
#include "spline.h"
#include "helpers.h"

using std::map;
using std::string;
using std::vector;

class Vehicle {
 public:
  // Constructors
  Vehicle();
  Vehicle(int lane, float s, float d, float v, float a, float x, float y, float yaw, string state="CS");

  // Destructor
  virtual ~Vehicle();

  // Vehicle functions
  // -----------------
  // Generate a trajectory
  void generateXYTrajectory(vector<double> &next_vals_x, vector<double> &next_vals_y, vector<double> &previous_x_path, vector<double> &previous_y_path,
                              const vector<double> &map_s_waypoints, const vector<double> &map_x_waypoints, const vector<double> &map_y_waypoints,
                              double r_vel, int target_lane);

  // Implement a trajectory
  void implementNextTrajectory(map<int, Vehicle> &vehicles, map<int ,vector<Vehicle> > &predictions, vector<double> &next_vals_x, vector<double> &next_vals_y,
                               vector<double> &previous_x_path,
                               vector<double> &previous_y_path, const vector<double> &map_s_waypoints,
                               const vector<double> &map_x_waypoints,
                               const vector<double> &map_y_waypoints, double &r_vel, int current_lane,
                               bool &init_acc_over);

  // Regulate velocity
  void regulateVelocity(map<int, Vehicle> &vehicles, double &ref_vel, vector<double> &previous_path_x, bool &init_acc_over);

  // Define successor states according to FSM
  vector<string> successorStates();

  // Generate trajectory predictions for non-Ego
  vector<Vehicle> generatePredictions(const vector<double> &map_s_waypoints, const vector<double> &map_x_waypoints,
                          const vector<double> &map_y_waypoints,int length);

  // Vehicle attributes
  // ------------------
  int lane, goal_lane, lanes_available;

  float v, a;

  float s, d, x, y, yaw;

  string state;
};

#endif  // VEHICLE_H
