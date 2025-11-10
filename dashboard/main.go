package main

import (
	"database/sql"
	"encoding/json"
	"fmt"
	"net/http"

	_ "github.com/mattn/go-sqlite3"
)

type LogEntry struct {
	Time   string `json:"time"`
	Method string `json:"method"`
	Path   string `json:"path"`
	Body   string `json:"body"`
}

func main() {
	db, _ := sql.Open("sqlite3", "logs.db")
	defer db.Close()

	http.Handle("/", http.FileServer(http.Dir("dashboard/static/")))

	http.HandleFunc("/logs", func(w http.ResponseWriter, r *http.Request) {
		rows, _ := db.Query("SELECT time, method, path, body FROM logs ORDER BY time DESC LIMIT 50")
		defer rows.Close()

		var logs []LogEntry
		for rows.Next() {
			var l LogEntry
			rows.Scan(&l.Time, &l.Method, &l.Path, &l.Body)
			logs = append(logs, l)
		}

		w.Header().Set("Content-Type", "application/json")
		json.NewEncoder(w).Encode(logs)
	})

	fmt.Println("Dashboard running on http://localhost:4000")
	http.ListenAndServe(":4000", nil)
}

