/****************************************************************************
 *  Copyright (C) 2018 RoboMaster.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#ifndef ROBORTS_DECISION_GOAL_FACORY_H
#define ROBORTS_DECISION_GOAL_FACORY_H

#include <Eigen/Core>
#include "io/io.h"
#include <ros/ros.h>
#include <tf/tf.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/PoseStamped.h>
#include "../proto/decision.pb.h"
#include "../blackboard/blackboard.h"


namespace roborts_decision
{

class GoalFactory
{
public:
  typedef std::shared_ptr<GoalFactory> GoalFactoryPtr;

  GoalFactory(const Blackboard::Ptr &blackboard_ptr, const std::string &proto_file_path) : blackboard_ptr_(blackboard_ptr)

  {
    LoadParam(proto_file_path);
  }

  ~GoalFactory() = default;

  geometry_msgs::PoseStamped GetEscapeGoal()
  {
    geometry_msgs::PoseStamped goal = patrol_goals_[patrol_count_];
    patrol_count_ = ++patrol_count_ % point_size_;
    return goal;
  }

  bool IsPatrolGoalsEmpty()
  {
    return patrol_goals_.empty();
  }

  geometry_msgs::PoseStamped GetPatrolGoal()
  {
    geometry_msgs::PoseStamped goal = patrol_goals_[patrol_count_];
    patrol_count_ = ++patrol_count_ % point_size_;
    return goal;
  }

  geometry_msgs::PoseStamped GetChaseGoal()
  {
    geometry_msgs::PoseStamped goal = patrol_goals_[patrol_count_];
    patrol_count_ = ++patrol_count_ % point_size_;
    return goal;
  }

  geometry_msgs::PoseStamped GetSearchGoal()
  {
    geometry_msgs::PoseStamped goal = patrol_goals_[patrol_count_];
    patrol_count_ = ++patrol_count_ % point_size_;
    return goal;
  }

  geometry_msgs::PoseStamped GetBuffGoal()
  {
    geometry_msgs::PoseStamped goal = patrol_goals_[patrol_count_];
    patrol_count_ = ++patrol_count_ % point_size_;
    return goal;
  }

  geometry_msgs::PoseStamped GetSupplyGoal()
  {
    geometry_msgs::PoseStamped goal = patrol_goals_[patrol_count_];
    patrol_count_ = ++patrol_count_ % point_size_;
    return goal;
  }

  geometry_msgs::PoseStamped GetTurnWoundedGoal()
  {
    geometry_msgs::PoseStamped goal = patrol_goals_[patrol_count_];
    patrol_count_ = ++patrol_count_ % point_size_;
    return goal;
  }

  geometry_msgs::PoseStamped GetTurnDetectedGoal()
  {
    geometry_msgs::PoseStamped goal = patrol_goals_[patrol_count_];
    patrol_count_ = ++patrol_count_ % point_size_;
    return goal;
  }

  void UpdateRobotPose()
  {

  }

  void LoadParam(const std::string &proto_file_path)
  {
    roborts_decision::DecisionConfig decision_config;
    if (!roborts_common::ReadProtoFromTextFile(proto_file_path, &decision_config))
    {
      return;
    }

    point_size_ = (unsigned int)(decision_config.point().size());
    patrol_goals_.resize(point_size_);
    for (int i = 0; i != point_size_; i++)
    {
      patrol_goals_[i].header.frame_id = "map";
      patrol_goals_[i].pose.position.x = decision_config.point(i).x();
      patrol_goals_[i].pose.position.y = decision_config.point(i).y();
      patrol_goals_[i].pose.position.z = decision_config.point(i).z();

      tf::Quaternion quaternion = tf::createQuaternionFromRPY(decision_config.point(i).roll(),
                                                              decision_config.point(i).pitch(),
                                                              decision_config.point(i).yaw());
      patrol_goals_[i].pose.orientation.x = quaternion.x();
      patrol_goals_[i].pose.orientation.y = quaternion.y();
      patrol_goals_[i].pose.orientation.z = quaternion.z();
      patrol_goals_[i].pose.orientation.w = quaternion.w();
    }
  }

protected:
  Blackboard::Ptr blackboard_ptr_;

  //! patrol buffer
  std::vector<geometry_msgs::PoseStamped> patrol_goals_;
  unsigned int patrol_count_;
  unsigned int point_size_;
};

} // namespace roborts_decision

#endif //ROBORTS_DECISION_GOAL_FACORY_H
