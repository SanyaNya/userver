#pragma once

#include <chrono>

#include <engine/future.hpp>
#include <engine/subprocess/child_process_status.hpp>

namespace engine {
namespace ev {

struct ChildProcessMapValue {
  explicit ChildProcessMapValue(
      Promise<subprocess::ChildProcessStatus> status_promise)
      : start_time(std::chrono::steady_clock::now()),
        status_promise(std::move(status_promise)) {}

  std::chrono::steady_clock::time_point start_time;
  Promise<subprocess::ChildProcessStatus> status_promise;
};

// All ChildProcessMap* methods should be called from ev_default_loop's thread
// only.
ChildProcessMapValue* ChildProcessMapGetOptional(int pid);

void ChildProcessMapErase(int pid);

std::pair<ChildProcessMapValue*, bool> ChildProcessMapSet(
    int pid, ChildProcessMapValue&& value);

}  // namespace ev
}  // namespace engine