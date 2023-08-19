package main

import (
	"fmt"
	"io"
	"log"
	"net/http"
	"os"
	"time"
)

var byeTempl string = `
    <h1 style="font-family:Times New Roman">%s</h1>
`

func bye(w http.ResponseWriter, _ *http.Request) {
	before := time.Now()

	req, err := http.Get("http://localhost:8081/bye")
	if err != nil {
		fmt.Fprintf(w, "%s", err)
		return
	}

	content, _ := io.ReadAll(req.Body)
	fmt.Fprintf(w, byeTempl, content)

	dt := time.Now().Sub(before)
	log.Printf("%d us\n", dt.Microseconds())
}

func main() {
	http.HandleFunc("/bye", bye)
	http.ListenAndServe(":"+os.Getenv("PORT"), nil)
}
