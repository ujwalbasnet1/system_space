#ifndef FLUTTER_PLUGIN_SYSTEM_SPACE_PLUGIN_H_
#define FLUTTER_PLUGIN_SYSTEM_SPACE_PLUGIN_H_

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>

#include <memory>

namespace system_space {

class SystemSpacePlugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

  SystemSpacePlugin();

  virtual ~SystemSpacePlugin();

  // Disallow copy and assign.
  SystemSpacePlugin(const SystemSpacePlugin&) = delete;
  SystemSpacePlugin& operator=(const SystemSpacePlugin&) = delete;

  // Called when a method is called on this plugin's channel from Dart.
  void HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
};

}  // namespace system_space

#endif  // FLUTTER_PLUGIN_SYSTEM_SPACE_PLUGIN_H_
