#include <iostream>
#include <vector>
#include <memory>

class Command {
 public:
  virtual ~Command() = default;
  virtual void execute() = 0;
  virtual std::string getDescription() const = 0;
};

class UploadFileCommand : public Command {
 public:
  void execute() override {
    std::cout << "Uploading file..." << std::endl;
  }
  std::string getDescription() const override {
    return "Upload an unclassified csv data file";
  }
};

class AlgorithmSettingsCommand : public Command {
 public:
  void execute() override {
    std::cout << "Opening algorithm settings..." << std::endl;
  }
  std::string getDescription() const override {
    return "Algorithm settings";
  }
};

class ClassifyDataCommand : public Command {
 public:
  void execute() override {
    std::cout << "Classifying data..." << std::endl;
  }
  std::string getDescription() const override {
    return "Classify data";
  }
};

class DisplayResultsCommand : public Command {
 public:
  void execute() override {
    std::cout << "Displaying results..." << std::endl;
  }
  std::string getDescription() const override {
    return "Display results";
  }
};

class DownloadResultsCommand : public Command {
 public:
  void execute() override {
    std::cout << "Downloading results..." << std::endl;
  }
  std::string getDescription() const override {
    return "Download results";
  }
};

class ExitCommand : public Command {
 public:
  void execute() override {
    std::cout << "Exiting..." << std::endl;
  }
  std::string getDescription() const override {
    return "Exit";
  }
};