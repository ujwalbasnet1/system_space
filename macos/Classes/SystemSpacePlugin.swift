import FlutterMacOS

public class SystemSpacePlugin: NSObject, FlutterPlugin {
  public static func register(with registrar: FlutterPluginRegistrar) {
    let channel = FlutterMethodChannel(name: "system_space", binaryMessenger: registrar.messenger)
    let instance = SystemSpacePlugin()
    registrar.addMethodCallDelegate(instance, channel: channel)
  }

  public func handle(_ call: FlutterMethodCall, result: @escaping FlutterResult) {
    if call.method == "getAvailableSpace" {
      result(getAvailableSpace())
    } else {
      result(FlutterMethodNotImplemented)
    }
  }

  private func getAvailableSpace() -> Int64 {
      let fileManager = FileManager.default
      do {
          let systemAttributes = try fileManager.attributesOfFileSystem(forPath: "/")
          if let freeSize = systemAttributes[.systemFreeSize] as? NSNumber {
              return freeSize.int64Value
          }
      } catch {

      }

      return nil
  }
}
