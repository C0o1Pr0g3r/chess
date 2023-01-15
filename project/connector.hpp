#ifndef CONNECTOR_H
#define CONNECTOR_H

void ConnectToEngine(char* path);

void SetEngineSkillLevel(std::string level);

std::string getNextMove(std::string position);

void CloseConnection();

#endif CONNECTOR_H
