#include "include/core/service.h"
#include <stdio.h>
#include <stdlib.h>

// NOTE: 1. Endpoint actions
char *get_new_article_name() {
  return "HTTP/1.1 200 OK\r\n"
         "Content-Type: text/html; charset=UTF-8\r\n"
         "Content-Length: 56\r\n"
         "\r\n"
         "<h1>Top 10 reasons why it sucks to be Front-End dev</h1>";
}

char *get_all_article_names() {
  return "HTTP/1.1 200 OK\r\n"
         "Content-Type: text/html; charset=UTF-8\r\n"
         "Content-Length: 79\r\n"
         "\r\n"
         "<h1>Top 12 reasons why it sucks to be Front-End dev, Why low level is cool</h1>";
}

char *get_default_users() {
  return "HTTP/1.1 200 OK\r\n"
         "Content-Type: text/html; charset=UTF-8\r\n"
         "Content-Length: 23\r\n"
         "\r\n"
         "<h1>User 1, User 2</h1>";
}

char *get_admin_users() {
  return "HTTP/1.1 200 OK\r\n"
         "Content-Type: text/html; charset=UTF-8\r\n"
         "Content-Length: 20\r\n"
         "\r\n"
         "<h1>Sniper king</h1>";
}


char *post_new_user() {
  return "HTTP/1.1 200 OK\r\n"
         "Content-Type: text/html; charset=UTF-8\r\n"
         "Content-Length: 17\r\n"
         "\r\n"
         "<h1>Created!</h1>";
}

int main() {
  Serv *service = init_service();

  // NOTE: 2. Endpoint assignment
  // assignment of a function pointer
  add_endpoint(service->router, GET, "/articles/new", get_new_article_name);
  add_endpoint(service->router, GET, "/articles/all", get_all_article_names);
  add_endpoint(service->router, GET, "/users/default", get_default_users);
  add_endpoint(service->router, GET, "/users/admin", get_admin_users);

  // Create a new user
  add_endpoint(service->router, POST, "/users/create", post_new_user);

  // NOTE: 3. Run the server
  start_service(service);
  return 0;
}
