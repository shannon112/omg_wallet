#include <assert.h>

String getStringBetweenKeys(const String& body, const String& leftKey, const String& rightKey, const int fromIdx = 0) {
  const String leftStr = '"' + leftKey + '"';
  const String rightStr = '"' + rightKey + '"';
  const int idFrom = body.indexOf(leftStr, fromIdx);
  const int idTo = body.indexOf(rightStr, fromIdx) -1; // minus one for a comma
  assert(idFrom != -1 && idTo != -1);
  return body.substring(idFrom, idTo);
}

String getValWithKeys(const String& body, const String& key, const String& endKey, const int fromIdx = 0) {
  const String keyValPairStr = getStringBetweenKeys(body, key, endKey, fromIdx);
  const int splitIdx = keyValPairStr.indexOf(':');
  assert(splitIdx != -1);
  return keyValPairStr.substring(splitIdx + 1);
}

void setup() {
  Serial.begin(115200);
  // assumption
  const String responseAboutAlbumImages = "\"album_images\":{\"count\":2,\"images\":[{\"hash\":\"VlVMfth\",\"title\":\"\",\"description\":null,\"has_sound\":false,\"width\":907,\"height\":523,\"size\":263680,\"ext\":\".png\",\"animated\":false,\"prefer_video\":false,\"looping\":false,\"datetime\":\"2023-05-14 03:34:25\",\"edited\":\"0\"},{\"hash\":\"zWhyREP\",\"title\":\"\",\"description\":null,\"has_sound\":false,\"width\":836,\"height\":1169,\"size\":361123,\"ext\":\".png\",\"animated\":false,\"prefer_video\":false,\"looping\":false,\"datetime\":\"2023-05-14 03:39:48\",\"edited\":\"0\"}]},";
  Serial.println(responseAboutAlbumImages);

  // parsing
  const int imagesCount = getValWithKeys(responseAboutAlbumImages, "count", "images").toInt();
  for (int iter = 0, lastIdx = 0; iter < imagesCount; iter++) {
    // get image info
    const String responseAboutImage = getStringBetweenKeys(responseAboutAlbumImages, "hash", "edited", lastIdx);
    Serial.println(responseAboutImage);

    // save image info
    const int width = getValWithKeys(responseAboutImage, "width", "height").toInt();
    Serial.println(width);
    const int height = getValWithKeys(responseAboutImage, "height", "size").toInt();
    Serial.println(height);
    const String hash = getValWithKeys(responseAboutImage, "hash", "title");
    Serial.println(hash);

    lastIdx = responseAboutAlbumImages.indexOf("edited") + 1;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}