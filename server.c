#include "include/core/service.h"
#include <stdio.h>
#include <stdlib.h>

// NOTE: 1. Endpoint actions
char *get_article_name() {
  return "HTTP/1.1 200 OK\r\n"
         "Content-Type: text/html; charset=UTF-8\r\n"
         "Content-Length: 57\r\n"
         "\r\n"
         "<h1>Top 10 reasons why it sucks to be Front-End dev</h1>";
}

char *get_article_name_id() {
  return "HTTP/1.1 200 OK\r\n"
         "Content-Type: text/html; charset=UTF-8\r\n"
         "Content-Length: 57\r\n"
         "\r\n"
         "<h1>Top 12 reasons why it sucks to be Front-End dev</h1>";
}

char *post_new_article() {
  return "HTTP/1.1 200 OK\r\n"
         "Content-Type: text/html; charset=UTF-8\r\n"
         "Content-Length: 19\r\n"
         "\r\n"
         "<h1>Created!</h1>";
}

int main() {
  Serv *service = init_service();

  // NOTE: 2. Endpoint assignment
  // assignment of a function pointer
  add_endpoint(service->router, GET, "/latest", get_article_name);
  add_endpoint(service->router, GET, "/latest/id", get_article_name_id);
  add_endpoint(service->router, POST, "/new", post_new_article);

  // NOTE: 3. Run the server
  start_service(service);
  return 0;
}
