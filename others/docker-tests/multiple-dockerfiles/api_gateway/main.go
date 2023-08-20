package main

import (
	"fmt"
	"io"
	"net/http"
	"os"

	"github.com/labstack/echo/v4"
	"github.com/labstack/echo/v4/middleware"
)

var apiTypes map[string]int = map[string]int{
	"bye": 8082,
}

func getGateway(c echo.Context) error {
	apiPath := c.Param("api")
	port, ok := apiTypes[apiPath]
	if !ok {
		return c.NoContent(404)
	}

	url := fmt.Sprintf("http://localhost:%d/%s", port, apiPath)
	req, err := http.Get(url)
	if err != nil {
		c.Error(err)
	}
	content, _ := io.ReadAll(req.Body)
	return c.String(200, string(content))
}

func main() {
	e := echo.New()
	e.Use(middleware.Logger())
	e.Use(middleware.Recover())
	e.Use(middleware.CORS())

	e.GET("/api/:api", getGateway)
	e.Start(":" + os.Getenv("PORT"))
}
