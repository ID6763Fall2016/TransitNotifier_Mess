#include <Adafruit_DotStar.h>
#include <ESP8266WiFi.h>
#include <vector>
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

const char* ssid = "GTother";
const char* password = "GeorgeP@1927";
const char* host = "gtbuses.herokuapp.com";

const char* techPrediction = "/multiPredictions?stops=tech|techsqua";  // mode1
const char* trolleyPrediction =
    "/multiPredictions?stops=trolley|techsqua";  // mode2
String feed;

// Use WiFiClientS class to create TCP connections
WiFiClientSecure client;
const int port = 443;
XMLDocument doc;
// button State Control
#define buttonPIN 12
int modedd = 2;

// dotStar LEDs
#define NUMPIXELS 51
#define DATAPIN 4
#define CLOCKPIN 5
uint32_t color = 0xFFFF00;
Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DATAPIN, CLOCKPIN);

// For Time
int HOUR = 13;
int MIN = 22;

// for state monitor
int prevTime;
int currentTime;
int buttonState;
int prevState = 0;
bool flag = false;

// extra data structure
class Predictions {
 public:
  String direction;
  String routeTitle;
  String stopTitle;
  vector<int> times;
};
vector<Predictions> predicList;

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

bool getTime() {
  WiFiClient time_client;
  while (!!!time_client.connect("google.com", 80)) {
    Serial.println("connection failed, retrying...");
  }

  time_client.print("HEAD / HTTP/1.1\r\n\r\n");
  String theDate = "";
  if (time_client.available()) {
    if (time_client.read() == '\n') {
      if (time_client.read() == 'D') {
        if (time_client.read() == 'a') {
          if (time_client.read() == 't') {
            if (time_client.read() == 'e') {
              if (time_client.read() == ':') {
                time_client.read();
                theDate = time_client.readStringUntil('\r');
                HOUR = theDate.substring(17, 19).toInt();
                MIN = theDate.substring(20, 22).toInt();
                if (HOUR < 4) {
                  HOUR = HOUR + 20;
                } else {
                  HOUR = HOUR - 4;
                }
                time_client.stop();
              }
            }
          }
        }
      }
    }
  }

  if (theDate != "")
    return true;
  else
    return false;
}

void fetchFeed(int mode) {
  feed = "";  // clear Feed

  Serial.print("connecting to ");
  Serial.println(host);
  // test connection to server
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    return;
  }

  String url = composeRequest(mode);
  Serial.print("Requesting URL: ");
  Serial.println(url);

  // Send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host +
               "\r\n" +
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

  
  feed = "";
  feed = "<body copyright=\"All data copyright Georgia Tech Campus 2016.\"><predictions agencyTitle=\"Georgia Tech Campus\" routeTitle=\"Tech Trolley\" routeTag=\"trolley\" stopTitle=\"Technology Square\" stopTag=\"techsqua\"><direction title=\"Transit Hub\"><prediction epochTime=\"1476745358127\" seconds=\"225\" minutes=\"3\" isDeparture=\"false\" affectedByLayover=\"true\" dirTag=\"hub\" vehicle=\"401\" block=\"0102\"/><prediction epochTime=\"1476746041460\" seconds=\"909\" minutes=\"15\" isDeparture=\"false\" affectedByLayover=\"true\" dirTag=\"hub\" vehicle=\"406\" block=\"0101\"/><prediction epochTime=\"1476746488786\" seconds=\"1356\" minutes=\"22\" isDeparture=\"false\" affectedByLayover=\"true\" dirTag=\"hub\" vehicle=\"403\" block=\"0103\"/><prediction epochTime=\"1476746807478\" seconds=\"1675\" minutes=\"27\" isDeparture=\"false\" affectedByLayover=\"true\" dirTag=\"hub\" vehicle=\"401\" block=\"0102\"/><prediction epochTime=\"1476747918111\" seconds=\"2785\" minutes=\"46\" isDeparture=\"false\" affectedByLayover=\"true\" dirTag=\"hub\" vehicle=\"403\" block=\"0103\"/></direction></predictions><keyForNextTime value=\"1066084336875\"/></body>";
}

String composeRequest(int mode) {
  String request;
  if (mode == 1) {
    request = String(techPrediction);
  } else if (mode == 2) {
    request = String(trolleyPrediction);
  } else {
    // do nothing
  }
  return request;
}

int parseRouteAtStopFeed() {
  if (MIN = -1) getTime();

  doc.Parse(feed.c_str());
  XMLNode* body = doc.FirstChild();  //<body>
  // each predictions is a route at a stop with multiple prediction
  XMLElement* XMLpredictions = body->FirstChildElement("predictions");

  while (XMLpredictions != NULL) {
    Predictions current_predictions;
    current_predictions.routeTitle = XMLpredictions->Attribute("routeTitle");
    current_predictions.stopTitle = XMLpredictions->Attribute("stopTitle");

    XMLElement* XMLdirention = XMLpredictions->FirstChildElement("direction");
    current_predictions.direction = XMLdirention->Attribute("title");

    XMLElement* predictTime = XMLpredictions->FirstChildElement("direction")
                                  ->FirstChildElement("prediction");
    while (predictTime != NULL) {
      const char* aTime = predictTime->Attribute("minutes");
      current_predictions.times.push_back(atoi(aTime));
      predictTime = predictTime->NextSiblingElement("prediction");
    }
    predicList.push_back(current_predictions);
    XMLpredictions = XMLpredictions->NextSiblingElement("predictions");
  }

  return doc.ErrorID();
}

void mapParsedFeed() {
  Serial.println("\nParsing results:\n");
  int listLen = predicList.size();
  int index = 0;
  while (index < listLen) {
    Predictions ps = predicList[index];
    Serial.println("You are at " + ps.stopTitle);
    Serial.println("Route " + ps.routeTitle + " going towards " + ps.direction);
    int len = ps.times.size();
    int LEDs[len];
    int i = 0;
    while (i < len) {
      LEDs[i] = MIN + ps.times[i];
      Serial.print("Bus " + String(i + 1) + " will come in ");
      Serial.print(ps.times[i]);
      Serial.println(" mins");
      i++;
    }
    i = 0;
    // set LEDs
    clearLEDsetting();
    while (i < len) {
      if (LEDs[i] <= NUMPIXELS) {
        strip.setPixelColor(LEDs[i], color);
      }
      i++;
    }
    strip.show();  // Turn on LEDs

    Serial.println();
    index++;
  }
  predicList.erase(predicList.begin(), predicList.end());
}

void clearLEDsetting() {
  int i = 0;
  while (i < NUMPIXELS) {
    strip.setPixelColor(i, 0x0000);
    i++;
  }
}

void heyGetIt() {
    fetchFeed(modedd);
    parseRouteAtStopFeed();
    mapParsedFeed();
    prevTime = currentTime;
}

void stateCheck() {
  buttonState = digitalRead(buttonPIN);
  int difference = currentTime - prevTime;
  if (difference > 30000) getTime();

  if (buttonState == 1 and prevState == 0) {
    Serial.println(String("Hour: ")+HOUR+" MIN:"+ MIN);
    if (flag == false) {
      Serial.println("Change to Tech");
      modedd = 1;          // tech
      color = 0x008000;  // for Tech, orange
      flag = true;
      heyGetIt();
    } else {
      Serial.println("Change to Trolley");
      modedd = 2;          // trolley
      color = 0xFFFF00;  // for Trolley, yellow
      flag = false;
      heyGetIt();
    }

  } else {
    // do nothing
  }
}

void setup() {
  Serial.begin(115200);
  delay(10);
  connectWIFI();
  getTime();
  strip.begin();  // Initialize pins for output
  strip.show();   // Turn all LEDs off ASAP
  prevTime = millis();
  currentTime = millis();
  heyGetIt();
}

void loop() {
  stateCheck();
  currentTime = millis();
  int difference = currentTime - prevTime;
  if (difference > 60000) {
    MIN += 1;
    heyGetIt();
  }
}

