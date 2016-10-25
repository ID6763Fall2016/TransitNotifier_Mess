#include <ESP8266WiFi.h>
#include <vector>
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

//const char* ssid = "9402-2G";
//const char* password = "rjwzhdws9402";
const char* ssid = "GTother";
const char* password = "GeorgeP@1927";
const char* host = "gtbuses.herokuapp.com";

const char* routeConfig = "/routeConfig";
const char* busLocation = "/locations";
const char* busPrediction = "/predictions/blue";
const char* stopPrediction = "/multiPredictions?stops=blue|cherfers";
const char* busSchedule = "/schedule";
String feed;

// Use WiFiClientS class to create TCP connections
WiFiClientSecure client;
const int port = 443;
XMLDocument doc;

void connectWIFI() {
  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void fetchFeed(int mode) {
  Serial.print("connecting to ");
  Serial.println(host);
  //test connection to server
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    return;
  }

  String url = composeRequest(mode);
  Serial.print("Requesting URL: ");
  Serial.println(url);

  // Send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Accept: application/xhtml+xml,application/xml\r\n"
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");

  delay(5000);

  bool isXML = false;
  // Read all the lines of the reply from server and print them to Serial
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line.startsWith("<body")) isXML = true;
    if (isXML) feed += line + "\n";
    if (line.startsWith("</body>")) break;
  }
  Serial.println("\r\nXML body received");
}

String composeRequest(int mode) {
  String request;
  if (mode == 1) {
    request = String(stopPrediction);
  } else if (mode == 2) {
    request = String(busPrediction);
  } else {
    // do nothing
  }
  return request;
}

class Location {
  public:
    String vehicleID, routeTag, dirTag, lat, lon;
};
class Prediction {
  public:
    String seconds, dir, vehicleID;
};
class Predictions {
  public:
    String routeTitle, routeTag, stopTitle, stopTag;
    vector<Prediction> predictions;
};


int parseLocationsFeed() {
  doc.Parse(feed.c_str());
  XMLNode * pRoot = doc.FirstChild();//<body>
  XMLElement * pElement = pRoot->FirstChildElement("predictions");
  const char* attribute1 = pElement->Attribute("routeTitle");
  const char* attribute2 = pElement->Attribute("routeTag");
  const char* attribute3 = pElement->Attribute("stopTitle");
  const char* attribute4 = pElement->Attribute("stopTag");
  Serial.println();
  Serial.print("routeTitle: " + String(attribute1)
               + "\nrouteTag: " + String(attribute2)
               + "\nstopTitle: " + String(attribute3)
               + "\nstopTag: " + String(attribute4));
  XMLElement * pListElement = pElement->FirstChildElement("message");
  const char* msgTitle = pListElement->Attribute("text");
  pListElement = pListElement->NextSiblingElement("message");
  const char* msgContent = pListElement->Attribute("text");
  Serial.println("\nmessage:\n"+String(msgTitle)+"\n"+String(msgContent));
  return doc.ErrorID();
}

int parseRouteAtStopFeed() {
  doc.Parse(feed.c_str());
  XMLNode * pRoot = doc.FirstChild();//<body>
  XMLElement * pElement = pRoot->FirstChildElement("predictions");
  const char* attribute1 = pElement->Attribute("routeTitle");
  const char* attribute2 = pElement->Attribute("routeTag");
  const char* attribute3 = pElement->Attribute("stopTitle");
  const char* attribute4 = pElement->Attribute("stopTag");
  Serial.println();
  Serial.print("routeTitle: " + String(attribute1)
               + "\nrouteTag: " + String(attribute2)
               + "\nstopTitle: " + String(attribute3)
               + "\nstopTag: " + String(attribute4));
  XMLElement * pListElement = pElement->FirstChildElement("message");
  const char* msgTitle = pListElement->Attribute("text");
  pListElement = pListElement->NextSiblingElement("message");
  const char* msgContent = pListElement->Attribute("text");
  Serial.println("\nmessage:\n"+String(msgTitle)+"\n"+String(msgContent));
  return doc.ErrorID();
}


void setup() {
  Serial.begin(115200);
  delay(10);
  connectWIFI();
  fetchFeed(1);
  Serial.println("feed string is:\n");
  Serial.print(feed);
}

void loop() {
}

