package main

import (
	"fmt"
	"net/http"
	"os"
	"time"

	"github.com/labstack/echo/v4"
	"github.com/labstack/echo/v4/middleware"
)

func bye(c echo.Context) error {
	return c.String(http.StatusOK, fmt.Sprintf("Bye: %s", time.Now().Local()))
}

func main() {
	e := echo.New()
	e.Use(middleware.Logger())
	e.Use(middleware.Recover())
	e.Use(middleware.CORS())

	e.GET("/bye", bye)
	e.Start(":" + os.Getenv("PORT"))
}
