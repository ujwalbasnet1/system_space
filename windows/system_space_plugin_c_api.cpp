#include "include/system_space/system_space_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "system_space_plugin.h"

void SystemSpacePluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  system_space::SystemSpacePlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
