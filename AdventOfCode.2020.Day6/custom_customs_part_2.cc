#include "AdventOfCode.2020.Day6/custom_customs_part_1.h"

#include <fstream>
#include <numeric>
#include <string>
#include <unordered_set>

namespace AdventOfCode2020::Day6::Part2
{
  struct Person {
    std::vector<char> answered_questions = {};
  };

  struct Group {
    std::vector<Person> people = {};

    [[nodiscard]] std::unordered_set<char> QuestionSet() const;
    [[nodiscard]] std::unordered_set<char> AnsweredQuestions() const;
  };

  std::unordered_set<char> Group::QuestionSet() const {
    std::unordered_set<char> question_set = {};
    for (const auto& person : this->people) {
      for (const auto& question : person.answered_questions) {
        question_set.insert(question);
      }
    }
    return question_set;
  }

  std::unordered_set<char> Group::AnsweredQuestions() const {
    std::unordered_set<char> answered_questions = {};
    for (const auto& question : this->QuestionSet()) {
      int question_answers_count = 0;
      for (const auto& person : this->people) {
        const auto question_answer = std::find(person.answered_questions.begin(), person.answered_questions.end(), question);
        if (question_answer != person.answered_questions.end()) {
          question_answers_count++;
        }
      }
      if (question_answers_count == this->people.size()) {
        answered_questions.insert(question);
      }
    }
    return answered_questions;
  }

  std::vector<Group> ParseGroups(const std::string_view file_path) {
    std::vector<Group> groups = {};
    std::string line = {};
    std::ifstream stream(file_path.data());

    if (!stream) {
      return {};
    }

    Group group = {};

    while (std::getline(stream, line)) {
      if (line.empty()) {
        groups.push_back(group);
        group = {};
      } else {
        Person person = {};
        for (const auto& question : line) {
          person.answered_questions.push_back(question);
        }
        group.people.push_back(person);
      }
    }

    groups.push_back(group);

    return groups;
  }

  int AccumulateGroupAnsweredQuestions(const std::vector<Group>& groups) {
    return std::accumulate(groups.begin(), groups.end(), 0, [](const int accumulated, const Group& group) -> int {
      return accumulated + static_cast<int>(group.AnsweredQuestions().size());
    });
  }

  int Solve(const std::string_view file_path) {
    const auto groups = ParseGroups(file_path);

    return AccumulateGroupAnsweredQuestions(groups);
  }
}
