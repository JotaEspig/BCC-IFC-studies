package main

import (
	"database/sql"
	"log"
	"net/http"
	"os"

	"github.com/labstack/echo/v4"
	_ "github.com/lib/pq" // PostgreSQL driver
)

// Database connection
func connectDB() (*sql.DB, error) {
	dbURL := os.Getenv("DATABASE_URL")
	return sql.Open("postgres", dbURL)
}

func main() {
	e := echo.New()

	// Database connection
	db, err := connectDB()
	if err != nil {
		log.Fatalf("Could not connect to the database: %v", err)
	}
	defer db.Close()

	// Ping database
	e.GET("/ping", func(c echo.Context) error {
		if err := db.Ping(); err != nil {
			return c.String(http.StatusInternalServerError, err.Error())
		}
		return c.String(http.StatusOK, "Database connected!")
	})

	// Start server
	port := os.Getenv("PORT")
	if port == "" {
		port = "8080"
	}
	e.Logger.Fatal(e.Start(":" + port))
}
