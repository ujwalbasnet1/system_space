//
//  Generated file. Do not edit.
//

// clang-format off

#include "generated_plugin_registrant.h"

#include <system_space/system_space_plugin.h>

void fl_register_plugins(FlPluginRegistry* registry) {
  g_autoptr(FlPluginRegistrar) system_space_registrar =
      fl_plugin_registry_get_registrar_for_plugin(registry, "SystemSpacePlugin");
  system_space_plugin_register_with_registrar(system_space_registrar);
}
