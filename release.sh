#!/bin/sh

set -x
set -e

AndroidVersion="3.0.9"
iOSVersion="3.0.9"

cd "$(dirname $0)"

rm -rf TapForTap*

cd ..

cd android-v3
./release.sh
cd ..
cd Android
cp -r ../android-v3/release/* .
cp -r ../android-v3/release/TapForTap.jar example-app/libs/TapForTap.jar
cp -r ../android-v3/release/TapForTapAdMob.jar example-app/libs/TapForTapAdMob.jar
cd ..
cd SDK
mkdir TapForTap-Android-"$AndroidVersion"
cd TapForTap-Android-"$AndroidVersion"
cp -r ../../Android/Readme.md .
cp -r ../../android-v3/release/* .
mkdir example-app
cp -r ../../Android/example-app/libs example-app/
cp -r ../../Android/example-app/src example-app/
cp -r ../../Android/example-app/AndroidManifest.xml example-app/
cp -r ../../Android/example-app/res example-app/
cd ..
cd ..

cd ios-v3
./release.sh
cd ..
cd iOS
cp -r ../ios-v3/release/* .
cp -r ../ios-v3/release/TapForTap example-app/example-app/
cp -r ../ios-v3/release/TapForTapAdMob example-app/example-app/
cd ..
cd SDK
mkdir TapForTap-iOS-"$iOSVersion"
cd TapForTap-iOS-"$iOSVersion"
cp -r ../../iOS/Readme.md .
cp -r ../../ios-v3/release/* .
mkdir example-app
cp -r ../../iOS/example-app/example-app example-app/
cp -r ../../iOS/example-app/example-app.xcodeproj/project.pbxproj example-app/
cd ..
cd ..
