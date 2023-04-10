#ifndef HUMAN_H_
#define HUMAN_H_

#include "IEntity.h"
#include "IStrategy.h"

class Human : public IEntity {
 public:
  /**
   * @brief Drones are created with a name
   * @param obj JSON object containing the drone's information
   */
  Human(JsonObject& obj);

  /**
   * @brief Destroy the Human object
   */
  ~Human();
  /**
   * @brief Gets the speed of the drone
   * @return The speed of the drone
   */
  float GetSpeed() const { return speed; }

  /**
   * @brief Gets the position of the drone
   * @return The position of the drone
   */
  Vector3 GetPosition() const { return position; }

  /**
   * @brief Gets the direction of the drone
   * @return The direction of the drone
   */
  Vector3 GetDirection() const { return direction; }

  /**
   * @brief Gets the destination of the drone
   * @return The destination of the drone
   */
  Vector3 GetDestination() const { return destination; }

  /**
   * @brief Gets the details information of the drone
   * @return The details information of the drone
   */
  JsonObject GetDetails() const { return details; }

  /**
   * @brief Updates the drone's position
   * @param dt Delta time
   * @param scheduler Vector containing all the entities in the system
   */
  void Update(double dt, std::vector<IEntity*> scheduler);

  /**
   * @brief Sets the position of the drone
   * @param pos_ The new position of the drone
   */
  void SetPosition(Vector3 pos_) { position = pos_; }

  /**
   * @brief Sets the direction of the drone
   * @param dir_ The new direction of the drone
   */
  void SetDirection(Vector3 dir_) { direction = dir_; }

  /**
   * @brief Sets the destination of the drone
   * @param des_ The new destination of the drone
   */
  void SetDestination(Vector3 des_) { destination = des_; }

  void CreateNewDestination();

  private:
  JsonObject details;
  Vector3 position;
  Vector3 direction;
  Vector3 destination;
  float speed;
  IStrategy* toDestination = nullptr;
};

#endif