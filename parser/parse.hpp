#pragma once

#include <string>
#include <tuple>
#include <vector>
#include <map>

class EnvVal {
public:
  EnvVal();
  EnvVal(std::string value,
         std::map<std::string, EnvVal> *env);

  std::string resolveValue();

private:
  std::string value;
  std::map<std::string, EnvVal> *env;
};

class Step {
public:
  Step();
  Step(std::string process,
       std::string type,
       std::vector<std::string> flags,
       std::vector<std::string> regexes,
       std::map<std::string, EnvVal> *env);

  int run(std::vector<std::string> filenames);
  std::vector<std::string> changedFiles(std::vector<std::string> filenames);
  std::vector<std::string> getRegexes();
  std::string getObject(std::string filename);
private:
  std::map<std::string, EnvVal> *env;
  std::vector<std::string> regexes;
  std::string type;
  std::vector<std::string> flags;
  std::vector<EnvVal> commands;
  bool hasflag(std::string sflag);
  int runObject(bool all, std::vector<std::string> filenames);
  int runCommands();
};

class Target {
public:
  Target();
  Target(std::string process,
         std::vector<std::string> inherits,
         std::map<std::string, Target> *targets,
         std::map<std::string, EnvVal> *env);
  
  std::map<std::string, std::vector<Step>> getSteps();

  int runStep(std::string type,
                      std::vector<std::string> filenames);
  std::vector<std::string> changedFiles(std::vector<std::string> filenames);
  int processFiles(std::vector<std::string> filenames);
private:
  std::map<std::string, std::vector<Step>> steps;
  std::map<std::string, EnvVal> *env;
  std::map<std::string, EnvVal> delayed_env;
  std::map<std::string, Target> *targets;
  std::vector<std::string> inherits;
};

class Config {
public:
  Config();
  Config(std::string filename);
  
  int processTarget(std::string target);
private:
  std::string file;
  std::map<std::string, Target> targets;
  std::map<std::string, EnvVal> env;

  std::vector<std::string> changedFiles(std::string target);
};
