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
  
    redisAsyncCommand(c, &setCommandCallback, (char*)"SET key viren", "SET key viren");
    redisAsyncCommand(c, &getCommandCallback, (char*)"end-1", "GET key");
    
  }
  CFRunLoopRun();
  return 0;
}
