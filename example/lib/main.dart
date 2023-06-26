import 'package:flutter/material.dart';
import 'package:system_space/system_space.dart';

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('System Space Example'),
        ),
        body: Center(
          child: FutureBuilder<int>(
            future: SystemSpace.getAvailableSpace(),
            builder: (BuildContext context, AsyncSnapshot<int> snapshot) {
              if (snapshot.hasData) {
                if (snapshot.data != null) {
                  return Text(
                    'Available Space: ${snapshot.data! / (1024 * 1024 * 1024)} GB',
                  );
                }
                return const Text('Available Space: NULL');
              } else if (snapshot.hasError) {
                return Text('Error: ${snapshot.error}');
              }
              return CircularProgressIndicator();
            },
          ),
        ),
      ),
    );
  }
}
