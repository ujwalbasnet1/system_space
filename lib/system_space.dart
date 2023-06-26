import 'dart:async';

import 'package:flutter/services.dart';

class SystemSpace {
  static const MethodChannel _channel = MethodChannel('system_space');

  static Future<int> getAvailableSpace() async {
    final int result = await _channel.invokeMethod('getAvailableSpace');
    return result;
  }
}
