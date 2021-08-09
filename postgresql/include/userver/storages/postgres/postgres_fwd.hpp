#pragma once

#include <chrono>
#include <functional>
#include <memory>

namespace storages::postgres {

class Transaction;
class ResultSet;
class Row;

class Cluster;
using ClusterPtr = std::shared_ptr<Cluster>;

namespace detail {
class Connection;
class ConnectionImpl;
class ConnectionPtr;
using ConnectionCallback = std::function<void(Connection*)>;

class ResultWrapper;
using ResultWrapperPtr = std::shared_ptr<const ResultWrapper>;
}  // namespace detail

using TimeoutDuration = std::chrono::milliseconds;

class DefaultCommandControls;

}  // namespace storages::postgres