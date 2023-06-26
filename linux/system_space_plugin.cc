#include "include/system_space/system_space_plugin.h"

#include <flutter_linux/flutter_linux.h>
#include <gtk/gtk.h>
#include <sys/statvfs.h>

#define SYSTEM_SPACE_PLUGIN(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), system_space_plugin_get_type(), \
                              SystemSpacePlugin))

struct _SystemSpacePlugin {
  GObject parent_instance;
};

G_DEFINE_TYPE(SystemSpacePlugin, system_space_plugin, g_object_get_type())

// Called when a method call is received from Flutter.
static void system_space_plugin_handle_method_call(
    SystemSpacePlugin* self,
    FlMethodCall* method_call) {
  g_autoptr(FlMethodResponse) response = NULL;

  const gchar* method = fl_method_call_get_name(method_call);
  if (strcmp(method, "getAvailableSpace") == 0) {
    struct statvfs fs_info;
    if (statvfs("/", &fs_info) != -1) {
      guint64 available_space = fs_info.f_bavail * fs_info.f_frsize;
      response = FL_METHOD_RESPONSE(fl_method_success_response_new(
          fl_value_new_int(available_space)));
    } else {
      response = FL_METHOD_RESPONSE(fl_method_error_response_new(
          "PLATFORM_ERROR", "Failed to retrieve available space.", NULL));
    }
  } else {
    response = FL_METHOD_RESPONSE(fl_method_not_implemented_response_new());
  }

  fl_method_call_respond(method_call, response, NULL);
}

// Called when the plugin is first initialized.
static void system_space_plugin_init(SystemSpacePlugin* self) {}

static void system_space_plugin_class_init(SystemSpacePluginClass* klass) {
  FL_METHOD_CHANNEL_DEFINE(system_space_plugin, "system_space",
                           FL_METHOD_CALL(system_space_plugin_handle_method_call));

  G_OBJECT_CLASS(klass)->dispose = system_space_plugin_dispose;
}

SystemSpacePlugin* system_space_plugin_new() {
  SystemSpacePlugin* plugin = g_object_new(system_space_plugin_get_type(), NULL);
  return plugin;
}

void system_space_plugin_register_with_registrar(FlPluginRegistrar* registrar) {
  SystemSpacePlugin* plugin = system_space_plugin_new();
  system_space_plugin_register_with_registrar(system_space_plugin_get_type(),
                                              plugin, registrar);
}
