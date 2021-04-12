// Copyright 2019 DeepMind Technologies Ltd. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "open_spiel/utils/run_python.h"

#include "open_spiel/abseil-cpp/absl/flags/flag.h"
#include "open_spiel/abseil-cpp/absl/flags/parse.h"
#include "open_spiel/spiel_utils.h"

ABSL_FLAG(std::string, python_command, open_spiel::kDefaultPythonCommand,
          "The Python command to use.");

namespace open_spiel {
namespace {

const char test_module[] = "open_spiel.utils.run_python_test_file";

void TestRunPython() {
  std::string python_command = absl::GetFlag(FLAGS_python_command);
  SPIEL_CHECK_TRUE(RunPython(test_module, {"--return_value", "0"},
                             python_command));
  SPIEL_CHECK_FALSE(RunPython(test_module, {"--return_value", "1"},
                             python_command));

  SPIEL_CHECK_TRUE(RunPython(test_module, {"--print_value", "asdf"},
                             python_command));
  SPIEL_CHECK_FALSE(RunPython(test_module, {"--bogus_flag"},
                              python_command));
}

}  // namespace
}  // namespace open_spiel

int main(int argc, char** argv) { 
  absl::ParseCommandLine(argc, argv);
  open_spiel::TestRunPython();
}
