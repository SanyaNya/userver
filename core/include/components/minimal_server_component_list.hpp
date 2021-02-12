#pragma once

/// @file components/minimal_server_component_list.hpp
/// @brief @copybrief components::MinimalServerComponentList()

#include <components/component_list.hpp>

namespace components {

/// Returns list of componenets to start a basic HTTP server. The list could
/// be used in components::Run() and components::RunOnce().
///
/// The list contains:
/// * components::HttpServerSettings<>
/// * components::Server
/// * components::AuthCheckerSettings
/// * components::Logging
/// * components::Tracer
/// * components::ManagerControllerComponent
/// * components::StatisticsStorage
/// * components::TaxiConfig
ComponentList MinimalServerComponentList();

}  // namespace components
