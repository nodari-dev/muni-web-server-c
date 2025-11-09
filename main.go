package main

import (
	"fmt"
	"log"
	"net/http"
)

func main() {
	http.HandleFunc("/articles/all", func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "text/html; charset=utf-8")
		fmt.Fprintf(w, `<h1>Top 12 reasons why it sucks to be Front-End dev, Why low level is cool</h1>`)
	})

	http.HandleFunc("/articles/new", func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "text/html; charset=utf-8")
		fmt.Fprintf(w, `<h1>Top 10 reasons why it sucks to be Front-End dev</h1>`)
	})

	http.HandleFunc("/users/default", func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "text/html; charset=utf-8")
		fmt.Fprintf(w, `<h1>User 1, User 2</h1>`)
	})

	http.HandleFunc("/users/admin", func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "text/html; charset=utf-8")
		fmt.Fprintf(w, `<h1>Sniper king</h1>`)
	})

	log.Println("Server started on http://localhost:8080")
	log.Fatal(http.ListenAndServe(":8080", nil))
}

