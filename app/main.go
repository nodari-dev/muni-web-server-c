package main

import (
	"encoding/json"
	"fmt"
	"net/http"
	"os"
	"time"
)

type LogEntry struct {
	Time   string      `json:"time"`
	Method string      `json:"method"`
	Path   string      `json:"path"`
	Body   interface{} `json:"body"`
}

func main() {
	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		logEntry := LogEntry{
			Time:   time.Now().Format(time.RFC3339),
			Method: r.Method,
			Path:   r.URL.Path,
			Body:   nil,
		}

		data, _ := json.Marshal(logEntry)
		f, _ := os.OpenFile("app.log", os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
		defer f.Close()
		f.WriteString(string(data) + "\n")

		fmt.Println("Logged:", logEntry.Method, logEntry.Path)
		w.Write([]byte("Logged!\n"))
	})

	fmt.Println("App running on port 3000...")
	http.ListenAndServe(":3000", nil)
}

