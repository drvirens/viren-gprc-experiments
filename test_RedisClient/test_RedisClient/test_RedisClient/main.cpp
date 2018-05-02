//
//  main.cpp
//  test_RedisClient
//
//  Created by Virendra Shakya on 4/30/18.
//  Copyright © 2018 Virendra Shakya. All rights reserved.
//

#include <iostream>
#include <CoreFoundation/CoreFoundation.h>
#include "hiredis.h"
#include "async.h"
#include "macosx.h"

#include "CSVFileLineTokenizer.hpp"
#include "CSVFileReader.hpp"
#include "CSVFileLineTokenizer.hpp"



static void connectCallback(const redisAsyncContext* c, int status) {
  if (status != REDIS_OK) {
    printf("Error: %s\n", c->errstr);
    return;
  }
  printf("Connected with redis fuck yeah\n");
}
static void disconnectCallback(const redisAsyncContext* c, int status) {
  if (status != REDIS_OK) {
    printf("Error: %s\n", c->errstr);
    return;
  }
  CFRunLoopStop(CFRunLoopGetCurrent());
  printf("Dis-fucking-Connected with redis hell yeah\n");
}
#pragma mark --
static void getCommandCallback(redisAsyncContext* c, void* r, void* privdata) {
  redisReply* reply = (redisReply*)r;
  if (!reply) {
    printf("argv[%s]: %s\n", (char*)privdata, reply->str);
    return;
  }
  printf("argv[%s]: %s\n", (char*)privdata, reply->str);
  //redisAsyncDisconnect(c);
}
static void setCommandCallback(redisAsyncContext* c, void* r, void* privdata) {
  redisReply* reply = (redisReply*)r;
  if (!reply) {
    return;
  }
  printf("argv[%s]: %s\n", (char*)privdata, reply->str);
  //redisAsyncDisconnect(c);
}



#pragma mark -- georadius
static void geoRadiusCommandCallback(redisAsyncContext* c, void* r, void* privdata) {
  redisReply* reply = (redisReply*)r;
  if (!reply) {
    return;
  }
  int type = reply->type;
  if (type == REDIS_REPLY_INTEGER) {
    printf("argv[%s]: %lld inserted\n", (char*)privdata, reply->integer);
  } else {
    printf("argv[%s]: %s\n", (char*)privdata, reply->str);
  }
  //redisAsyncDisconnect(c);
}

static void fireGeoRadiusQuery(redisAsyncContext* c,
                                const char* key,
                                const char* longitude,
                                const char* latitude,
                                const char* radius,
                                const char* unit) {
    //redis> GEORADIUS Sicily 15 37 200 km
  static const int kSpaceSize = 1;
  static const char* kGeoRadius = "GEORADIUS";
  
  //
  //GEOADD    Sicily 13.361389 38.115556 "Palermo"
  //GEORADIUS Sicily 15        37        200       km
  //
  size_t len =
              strlen(kGeoRadius)    + kSpaceSize +
              strlen(key)           + kSpaceSize +
              strlen(longitude)     + kSpaceSize +
              strlen(latitude)      + kSpaceSize +
              strlen(radius)        + kSpaceSize +
              strlen(unit)          + kSpaceSize;
  char* cmd = (char*)malloc(len);
  int ret = snprintf(cmd, len, "%s %s %s %s %s %s", kGeoRadius, key, longitude, latitude, radius, unit);
  if (ret == len) { //expected
    printf("stuffed into geoadd");
  }
  
  int err = redisAsyncCommand(c, &geoRadiusCommandCallback, (char*)"privData", cmd);
  if (REDIS_OK == err) {
    printf(" georadius fired successfully\n");
  }

}


#pragma mark -- geoadd

static void geoAddCommandCallback(redisAsyncContext* c, void* r, void* privdata) {
  redisReply* reply = (redisReply*)r;
  if (!reply) {
    return;
  }
  int type = reply->type;
  if (type == REDIS_REPLY_INTEGER) {
    printf("argv[%s]: %lld inserted\n", (char*)privdata, reply->integer);
  } else {
    printf("argv[%s]: %s\n", (char*)privdata, reply->str);
  }
  
  char* strindex = (char*)privdata;
  int index = atoi(strindex);
  if (index >= 2) {
    fireGeoRadiusQuery(c, "Sicily", "15", "37", "200", "km");
  }
}


/*
GEOADD key longitude latitude member [longitude latitude member ...]
Time complexity: O(log(N)) for each item added, where N is the number of elements in the sorted set.

GEOADD Sicily 13.361389 38.115556 "Palermo" 15.087269 37.502669 "Catania"
(integer) 2
redis> GEODIST Sicily Palermo Catania
"166274.1516"
redis> GEORADIUS Sicily 15 37 100 km
1) "Catania"
redis> GEORADIUS Sicily 15 37 200 km
1) "Palermo"
2) "Catania"
*/

static void addGeoLocations(redisAsyncContext* c,
        const char* key,
        const char* longitude,
        const char* latitude,
        const char* member,
        const int index) {
  static const int kSpaceSize = 1;
  static const char* kGeoAdd = "GEOADD";
  
  //
  //GEOADD Sicily 13.361389 38.115556 "Palermo"
  //
  size_t len =
              strlen(kGeoAdd) + kSpaceSize +
              strlen(key) + kSpaceSize +
              strlen(longitude) + kSpaceSize +
              strlen(latitude) + kSpaceSize +
              strlen(member) + 2*kSpaceSize;
  char* cmd = (char*)malloc(len);
  int ret = snprintf(cmd, len, "%s %s %s %s %s", kGeoAdd, key, longitude, latitude, member);
  if (ret == len) { //expected
    printf("stuffed into geoadd");
  }
  
  size_t ll = sizeof("") + sizeof (index);
  char* privData = (char*)malloc( ll + 1 + 1);
  snprintf(privData, ll, "%s%d", "", index);
  
  int err = redisAsyncCommand(c, &geoAddCommandCallback, privData, cmd);
  if (REDIS_OK == err) {
    printf("will insert geoadd shortly\n");
  }
}

static void addManyGeoLocations(redisAsyncContext* c) {
    int index = 0;
    addGeoLocations(c, "Sicily", "13.361389", "38.115556", "Palermo", ++index);
    addGeoLocations(c, "Sicily", "15.087269", "37.502669", "Catania", ++index);
}



class RedisGeoAdder : public CSVFileLineTokenizer {
 public:
    RedisGeoAdder(redisAsyncContext* c) : context_(c), index_(0), rediskey_("starbucks") {}
    virtual void didReadOneEntry(std::string& longitude, std::string& latitude, std::string& member) const;
 private:
    redisAsyncContext* context_;
    int index_;
    const std::string rediskey_;
};
void RedisGeoAdder::didReadOneEntry(std::string& longitude, std::string& latitude, std::string& member) const {
    addGeoLocations(context_, rediskey_.c_str(), longitude.c_str(), latitude.c_str(), member.c_str(), index_);
}

static void addStarbucks(redisAsyncContext* c) {
    const RedisGeoAdder tokenizer(c);
    //const std::string csvfile = "starbucks_us_locations_original.csv";
    const std::string csvfile = "starbucks_us_locations_test.csv";
    CSVFileReader csv(tokenizer, csvfile);
    csv.read();
}


int main(int argc, const char * argv[]) {
  std::cout << "Hello, World!\n";
  
  signal(SIGPIPE, SIG_IGN);
  CFRunLoopRef loop = CFRunLoopGetCurrent();
  if( !loop ) {
      printf("Error: Cannot get current run loop\n");
      return 1;
  }
  
  {
    redisAsyncContext* c = redisAsyncConnect("127.0.0.1", 6379);
    if (c->err) {
      redisAsyncFree(c);
      return 1;
    }
    redisMacOSAttach(c, loop);
    redisAsyncSetConnectCallback(c, &connectCallback);
    redisAsyncSetDisconnectCallback(c, &disconnectCallback);
  
//    redisAsyncCommand(c, &setCommandCallback, (char*)"start-1", "SET key viren");
//    redisAsyncCommand(c, &getCommandCallback, (char*)"end-1", "GET key");
//    redisAsyncCommand(c, &geoAddCommandCallback, (char*)"geoadd", "GEOADD Pune -122.431297 37.773972 \"VirenS\"");
//    addManyGeoLocations(c);
    
    addStarbucks(c);
  }
  CFRunLoopRun();
  return 0;
}
