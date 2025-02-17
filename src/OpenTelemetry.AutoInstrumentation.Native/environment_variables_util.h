/*
 * Copyright The OpenTelemetry Authors
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef OTEL_CLR_PROFILER_ENVIRONMENT_VARIABLES_UTIL_H_
#define OTEL_CLR_PROFILER_ENVIRONMENT_VARIABLES_UTIL_H_

#include "environment_variables.h"
#include "environment_variables_parser.h"
#include "string.h"
#include "util.h"

#define CheckIfTrue(EXPR)                                  \
  static int sValue = -1;                                  \
  if (sValue == -1) {                                      \
    const auto envValue = EXPR;                            \
    sValue              = TrueCondition(envValue) ? 1 : 0; \
  }                                                        \
  return sValue == 1;

#define CheckIfFalse(EXPR)                                  \
  static int sValue = -1;                                   \
  if (sValue == -1) {                                       \
    const auto envValue = EXPR;                             \
    sValue              = FalseCondition(envValue) ? 1 : 0; \
  }                                                         \
  return sValue == 1;

#define ToBooleanWithDefault(EXPR, DEFAULT) \
  static int sValue = -1;                   \
  if (sValue == -1) {                       \
    const auto envValue = EXPR;             \
    if (TrueCondition(envValue)) {          \
      sValue = 1;                           \
    } else if (FalseCondition(envValue)) {  \
      sValue = 0;                           \
    } else {                                \
      sValue = DEFAULT;                     \
    }                                       \
  }                                         \
  return sValue == 1;

namespace trace {

bool DisableOptimizations() {
  CheckIfTrue(GetEnvironmentValue(environment::clr_disable_optimizations));
}

bool EnableInlining() {
  ToBooleanWithDefault(GetEnvironmentValue(environment::clr_enable_inlining), true);
}

bool IsNGENEnabled() {
  ToBooleanWithDefault(GetEnvironmentValue(environment::clr_enable_ngen),
                       false);
}

bool IsDumpILRewriteEnabled() {
  CheckIfTrue(GetEnvironmentValue(environment::dump_il_rewrite_enabled));
}

bool IsAzureAppServices() {
  CheckIfTrue(GetEnvironmentValue(environment::azure_app_services));
}

bool AreTracesEnabled() {
  ToBooleanWithDefault(GetEnvironmentValue(environment::traces_enabled), true);
}

bool AreMetricsEnabled() {
  ToBooleanWithDefault(GetEnvironmentValue(environment::metrics_enabled), true);
}

bool AreLogsEnabled() {
  ToBooleanWithDefault(GetEnvironmentValue(environment::logs_enabled), true);
}

bool IsNetFxAssemblyRedirectionEnabled() {
  ToBooleanWithDefault(GetEnvironmentValue(environment::netfx_assembly_redirection_enabled), true);
}

bool AreInstrumentationsEnabledByDefault() {
  ToBooleanWithDefault(GetEnvironmentValue(environment::instrumentation_enabled), true);
}

bool AreTracesInstrumentationsEnabledByDefault(const bool enabled_if_not_configured) {
  ToBooleanWithDefault(GetEnvironmentValue(environment::traces_instrumentation_enabled), enabled_if_not_configured);
}

bool AreMetricsInstrumentationsEnabledByDefault(const bool enabled_if_not_configured) {
  ToBooleanWithDefault(GetEnvironmentValue(environment::metrics_instrumentation_enabled), enabled_if_not_configured);
}

bool AreLogsInstrumentationsEnabledByDefault(const bool enabled_if_not_configured) {
  ToBooleanWithDefault(GetEnvironmentValue(environment::logs_instrumentation_enabled), enabled_if_not_configured);
}

}  // namespace trace

#endif  // OTEL_CLR_PROFILER_ENVIRONMENT_VARIABLES_UTIL_H_
