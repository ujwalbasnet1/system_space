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
    let fileURL = URL(fileURLWithPath: "/")
    do {
      let resourceValues = try fileURL.resourceValues(forKeys: [.volumeAvailableCapacityForImportantUsageKey])
      if let availableSpace = resourceValues.volumeAvailableCapacityForImportantUsage {
        return Int64(availableSpace)
      } else {
        return -1
      }
    } catch {
      return -1
    }
  }
}
