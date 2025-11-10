package main

import (
	"bufio"
	"database/sql"
	"encoding/json"
	"fmt"
	"os"
	"time"
	_ "github.com/mattn/go-sqlite3"
)

type LogEntry struct {
	Time   string      `json:"time"`
	Method string      `json:"method"`
	Path   string      `json:"path"`
	Body   interface{} `json:"body"`
}

func main() {
	fmt.Println("Collector started")
	db, _ := sql.Open("sqlite3", "logs.db")
	defer db.Close()

	db.Exec(`CREATE TABLE IF NOT EXISTS logs (
		time TEXT,
		method TEXT,
		path TEXT,
		body TEXT
	)`)

	lastSize := int64(0)
	for {
		info, err := os.Stat("app.log")
		if err != nil {
			time.Sleep(1 * time.Second)
			fmt.Println("Could not find app.log file")
			continue
		}
		if info.Size() == lastSize {
			fmt.Println("No changes")
			time.Sleep(1 * time.Second)
			continue
		}

		file, _ := os.Open("app.log")
		file.Seek(lastSize, 0)
		scanner := bufio.NewScanner(file)
		for scanner.Scan() {
			line := scanner.Text()
			var entry LogEntry
			if err := json.Unmarshal([]byte(line), &entry); err == nil {
				bodyBytes, _ := json.Marshal(entry.Body)
				db.Exec("INSERT INTO logs (time, method, path, body) VALUES (?, ?, ?, ?)",
					entry.Time, entry.Method, entry.Path, string(bodyBytes))
				fmt.Println("Stored:", entry.Path)
			}
		}
		lastSize = info.Size()
		file.Close()
	}
}

