#include "include/system_space/system_space_plugin.h"

#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>
#include <windows.h>

namespace {

class SystemSpacePlugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows* registrar);

  SystemSpacePlugin();

  virtual ~SystemSpacePlugin();

 private:
  // Handles the method call when invoking the 'getAvailableSpace' method.
  void GetAvailableSpace(
      const flutter::MethodCall<flutter::EncodableValue>& method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);

  // Retrieves the available space on the system.
  int64_t GetAvailableSpaceOnSystem();
};

// static
void SystemSpacePlugin::RegisterWithRegistrar(
    flutter::PluginRegistrarWindows* registrar) {
  auto plugin = std::make_unique<SystemSpacePlugin>();

  auto channel =
      std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
          registrar->messenger(), "system_space",
          &flutter::StandardMethodCodec::GetInstance());

  channel->SetMethodCallHandler(
      [plugin_pointer = plugin.get()](const auto& call, auto result) {
        plugin_pointer->HandleMethodCall(call, std::move(result));
      });

  registrar->AddPlugin(std::move(plugin));
}

SystemSpacePlugin::SystemSpacePlugin() {}

SystemSpacePlugin::~SystemSpacePlugin() {}

void SystemSpacePlugin::GetAvailableSpace(
    const flutter::MethodCall<flutter::EncodableValue>& method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  int64_t availableSpace = GetAvailableSpaceOnSystem();
  result->Success(flutter::EncodableValue(availableSpace));
}

int64_t SystemSpacePlugin::GetAvailableSpaceOnSystem() {
  ULARGE_INTEGER availableSpace;
  GetDiskFreeSpaceEx(NULL, &availableSpace, NULL, NULL);
  return static_cast<int64_t>(availableSpace.QuadPart);
}

}  // namespace

void SystemSpacePluginRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  SystemSpacePlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
